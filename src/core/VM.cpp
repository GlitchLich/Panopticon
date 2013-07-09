#include "llvm/Analysis/Passes.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/DataLayout.h"
#include "llvm/DerivedTypes.h"
#include "llvm/IRBuilder.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "include/Grammar/parse.h"

#include <cstdio>

#include "include/core/VM.h"
#include "include/core/types.h"
#include "include/core/math_primitives.h"

namespace panopticon
{

llvm::FunctionPassManager* passManager = NULL;
llvm::ExecutionEngine* executionEngine = NULL;
llvm::Module* module = NULL;
std::string error_string;

void vm_init()
{
    llvm::InitializeNativeTarget();
    llvm::LLVMContext& context = llvm::getGlobalContext();

    // Make the module, which holds all the code
    module = new llvm::Module("Panopticon JIT", context);

    // Create the JIT. This takes ownership of the module
    executionEngine = llvm::EngineBuilder(module).setErrorStr(&error_string).create();

    if(!executionEngine)
    {
        fprintf(stderr, "Could not create ExecutionEngine: %s\n", error_string.c_str());
        exit(1);
    }

    passManager = new llvm::FunctionPassManager(module);

//    passManager->add(llvm::createPrintModulePass(&llvm::outs()));
    // Setup the optimizer pipeline. Start with registering info about how
    // the target lays out data structures
    passManager->add(new llvm::DataLayout(*executionEngine->getDataLayout()));
    // provide basic AliasAnalysis support for GVN.
    passManager->add(llvm::createBasicAliasAnalysisPass());
    // Do simple "peephole"optimiztion and bit-twiddling optzns.
    passManager->add(llvm::createInstructionCombiningPass());
    // Reassociate expressions.
    passManager->add(llvm::createReassociatePass());
    // Eliminate common sub expressions
    passManager->add(llvm::createGVNPass());
    // Simplify the control flow graph (deleting unrechable blocks)
    passManager->add(llvm::createCFGSimplificationPass());

    passManager->doInitialization();

    //Parse the Math primitive functions
    parse_math_primitives();
}

void vm_shutdown()
{
    delete executionEngine;
    delete passManager;
}

void* jit_compile(const FunctionAST* func, bool call_func, bool print)
{
    llvm::Function* llvmFunc = func->codeGen();
    llvmFunc->getReturnType();

    if(print)
        llvmFunc->print(llvm::outs());

    // JIT compile the function, return a function pointer
    void* funcPtr = executionEngine->getPointerToFunction(llvmFunc);

    if(call_func)
    {
        std::vector<llvm::GenericValue> arg_values;
        llvm::GenericValue generic_value = executionEngine->runFunction(llvmFunc,arg_values);

        llvm::Type* return_type = llvmFunc->getReturnType();

        if (return_type->isDoubleTy())
        {
            panopticon::out() << generic_value.DoubleVal << std::endl;
        }
        else if (return_type->isIntegerTy(1))
        {
            if( generic_value.IntVal.getSExtValue() == -1)
            {
                panopticon::out() << "true" << std::endl;
            }
            else
            {
                panopticon::out() << "false" << std::endl;
            }
        }
        else if (return_type->isIntegerTy(32))
        {
            panopticon::out() << generic_value.IntVal.getSExtValue() << std::endl;
        }

    }

    return funcPtr;
}

}
