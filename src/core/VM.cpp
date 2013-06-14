#include "llvm/Analysis/Passes.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/DataLayout.h"
#include "llvm/DerivedTypes.h"
#include "llvm/IRBuilder.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"

#include <cstdio>

#include "include/core/VM.h"
#include "include/core/types.h"

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
    llvm::Module* module = new llvm::Module("panopticon JIT", context);

    // Create the JIT. This takes ownership of the module
    executionEngine = llvm::EngineBuilder(module).setErrorStr(&error_string).create();

    if(!executionEngine)
    {
        fprintf(stderr, "Could not create ExecutionEngine: %s\n", error_string.c_str());
        exit(1);
    }

    passManager = new llvm::FunctionPassManager(module);

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
}

void vm_shutdown()
{
    delete executionEngine;
    delete passManager;
}

jit_function jit_compile(const FunctionAST& func)
{
    llvm::Function* llvmFunc = func.codeGen();

    // JIT compile the function, return a function pointer
    void* funcPtr = executionEngine->getPointerToFunction(llvmFunc);

    // Cast it to the right type
    jit_function cFunc = (jit_function) (intptr_t) funcPtr;

    // Finally, call it
    return (jit_function) cFunc();
}

}
