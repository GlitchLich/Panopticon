#ifndef VM_H
#define VM_H

#include "llvm/PassManager.h"
#include "include/core/types.h"

namespace panopticon
{

extern llvm::FunctionPassManager* passManager;
extern llvm::Module* module;
extern llvm::DataLayout* dataLayout;

void vm_init();
void vm_shutdown();

// JIT compile a function, returning the result as yet another function
void* jit_compile(const FunctionAST *func, bool call_func = false, bool print = false);
void* jit_compile_expr(const ExprAST *expr, bool print = false);


} // panopticon namespace

#endif // VM_H
