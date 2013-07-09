#include "include/core/math_primitives.h"
#include "include/Grammar/parse.h"
#include <time.h>

namespace panopticon
{

FunctionClosure construct_math_primitive(int op,std::string name)
{
    std::vector<std::string> args;
    args.push_back("x");
    args.push_back("y");
    std::vector<llvm::Type*> doubles;
    doubles.push_back(llvm::Type::getDoubleTy(llvm::getGlobalContext()));
    doubles.push_back(llvm::Type::getDoubleTy(llvm::getGlobalContext()));
    PrototypeAST* proto = new PrototypeAST(name,args,doubles,llvm::Type::getDoubleTy(llvm::getGlobalContext()));

    VariableExprAST* var_x = new VariableExprAST("x");
    VariableExprAST* var_y = new VariableExprAST("y");
    BinaryExprAST* body = new BinaryExprAST(op,var_x,var_y);

    double (*primitive)(double,double) = (double (*)(double,double))(intptr_t)jit_compile(new FunctionAST(proto,body));
    FunctionClosure closure = {
        (void*)primitive,
        get_string_hash(name),
        2
    };

    return closure;
}

//Construct Boolean Math Primitive
FunctionClosure construct_boolean_math_primitive(int op,std::string name)
{
    std::vector<std::string> args;
    args.push_back("x");
    args.push_back("y");
    std::vector<llvm::Type*> doubles;
    doubles.push_back(llvm::Type::getDoubleTy(llvm::getGlobalContext()));
    doubles.push_back(llvm::Type::getDoubleTy(llvm::getGlobalContext()));
    PrototypeAST* proto = new PrototypeAST(name,args,doubles,llvm::Type::getInt1Ty(llvm::getGlobalContext()));

    VariableExprAST* var_x = new VariableExprAST("x");
    VariableExprAST* var_y = new VariableExprAST("y");
    BinaryExprAST* body = new BinaryExprAST(op,var_x,var_y);

    bool (*primitive)(double,double) = (bool (*)(double,double))(intptr_t)jit_compile(new FunctionAST(proto,body));

    FunctionClosure closure = {
        (void*)primitive,
        get_string_hash(name),
        2
    };
    return closure;
}

FunctionClosure construct_boolean_compare_primitive(int op,std::string name)
{
    std::vector<std::string> args;
    args.push_back("x");
    args.push_back("y");
    std::vector<llvm::Type*> doubles;
    doubles.push_back(llvm::Type::getInt1Ty(llvm::getGlobalContext()));
    doubles.push_back(llvm::Type::getInt1Ty(llvm::getGlobalContext()));
    PrototypeAST* proto = new PrototypeAST(name,args,doubles,llvm::Type::getInt1Ty(llvm::getGlobalContext()));

    VariableExprAST* var_x = new VariableExprAST("x");
    VariableExprAST* var_y = new VariableExprAST("y");
    BinaryExprAST* body = new BinaryExprAST(op,var_x,var_y);

    bool (*primitive)(bool,bool) = (bool (*)(bool,bool))(intptr_t)jit_compile(new FunctionAST(proto,body));

    FunctionClosure closure = {
        (void*)primitive,
        get_string_hash(name),
        2
    };
    return closure;
}

void test_call_math_primitive(std::string name, double x, double y)
{
    std::vector<ExprAST*> args;

    NumberExprAST* x_ast = new NumberExprAST(x);
    NumberExprAST* y_ast = new NumberExprAST(y);

    args.push_back(x_ast);
    args.push_back(y_ast);

    CallExprAST* call_expr = new CallExprAST(name,args);

    FunctionAST* top_level = convert_to_top_level_function(call_expr,llvm::Type::getDoubleTy(llvm::getGlobalContext()));
    double (*compiled_function)() = (double (*)())(intptr_t)jit_compile(top_level);
    std::cout << "Calling function: " << name << ", with arguments x: " << x << " , and y: " << y << std::endl;
    std::cout << "result: " << compiled_function() << std::endl;
}

void test_call_bool_primitive(std::string name, double x, double y)
{
    std::vector<ExprAST*> args;

    NumberExprAST* x_ast = new NumberExprAST(x);
    NumberExprAST* y_ast = new NumberExprAST(y);

    args.push_back(x_ast);
    args.push_back(y_ast);

    CallExprAST* call_expr = new CallExprAST(name,args);

    FunctionAST* top_level = convert_to_top_level_function(call_expr,llvm::Type::getInt1Ty(llvm::getGlobalContext()));
    bool (*compiled_function)() = (bool (*)())(intptr_t)jit_compile(top_level);
    std::cout << "Calling function: " << name << ", with arguments x: " << x << " , and y: " << y << std::endl;
    std::cout << "result: " << compiled_function() << std::endl;
}

void test_call_bool_compare_primitive(std::string name, bool x, bool y)
{
    std::vector<ExprAST*> args;

    BooleanExprAST* x_ast = new BooleanExprAST(x);
    BooleanExprAST* y_ast = new BooleanExprAST(y);

    args.push_back(x_ast);
    args.push_back(y_ast);

    CallExprAST* call_expr = new CallExprAST(name,args);

    FunctionAST* top_level = convert_to_top_level_function(call_expr,llvm::Type::getInt1Ty(llvm::getGlobalContext()));
    bool (*compiled_function)() = (bool (*)())(intptr_t)jit_compile(top_level);
    std::cout << "Calling function: " << name << ", with arguments x: " << x << " , and y: " << y << std::endl;
    std::cout << "result: " << compiled_function() << std::endl;
}

void parse_math_primitives()
{
    clock_t init, final;
//    init=clock();
    FunctionClosure add = construct_math_primitive(BinaryExprAST::Add,"add");
    FunctionClosure subtract = construct_math_primitive(BinaryExprAST::Subtract,"subtract");
    FunctionClosure divide = construct_math_primitive(BinaryExprAST::Divide,"divide");
    FunctionClosure multiply = construct_math_primitive(BinaryExprAST::Multiply,"multiply");
    FunctionClosure modulus = construct_math_primitive(BinaryExprAST::Modulus,"modulus");
    FunctionClosure shift_left = construct_math_primitive(BinaryExprAST::ShiftLeft,"shift_left");
    FunctionClosure shift_right = construct_math_primitive(BinaryExprAST::ShiftRight,"shift_right");
    FunctionClosure bit_and = construct_math_primitive(BinaryExprAST::BitAnd,"bit_and");
    FunctionClosure bit_or = construct_math_primitive(BinaryExprAST::BitOr,"bit_or");
    FunctionClosure bit_xor = construct_math_primitive(BinaryExprAST::BitXOr,"bit_xor");

    FunctionClosure lessThan = construct_boolean_math_primitive(BinaryExprAST::LessThan,"lessThan");
    FunctionClosure greaterThan = construct_boolean_math_primitive(BinaryExprAST::GreaterThan,"greaterThan");
    FunctionClosure lessThanOrEq = construct_boolean_math_primitive(BinaryExprAST::LessThanEq,"LessThanOrEq");
    FunctionClosure greaterThsnOrEq = construct_boolean_math_primitive(BinaryExprAST::GreatherThanEq,"GreaterThanOrEq");
    FunctionClosure equalTo = construct_boolean_math_primitive(BinaryExprAST::EqualTo,"equalTo");
    FunctionClosure notEqualTo = construct_boolean_math_primitive(BinaryExprAST::NotEqualTo,"NotEqualTo");

    FunctionClosure and_func = construct_boolean_compare_primitive(BinaryExprAST::And,"and");
    FunctionClosure or_func = construct_boolean_compare_primitive(BinaryExprAST::Or,"or");

//    final=clock()-init;
//    std::cout << "TIME TO COMPILE FUNCTIONS: " << (double)final / ((double)CLOCKS_PER_SEC) << std::endl;

    test_call_math_primitive("add", 2, 3);
    test_call_math_primitive("subtract", 2, 3);
    test_call_math_primitive("divide", 2, 3);
    test_call_math_primitive("multiply", 2, 3);
    test_call_math_primitive("modulus", 20, 3);

    test_call_bool_primitive("lessThan", 2, 3);
    test_call_bool_primitive("greaterThan", 2, 3);
    test_call_bool_primitive("LessThanOrEq", 2, 3);
    test_call_bool_primitive("GreaterThanOrEq", 2, 3);
    test_call_bool_primitive("equalTo", 2, 3);
    test_call_bool_primitive("NotEqualTo", 2, 3);

    test_call_math_primitive("shift_left", 2, 3);
    test_call_math_primitive("shift_right", 2, 3);
    test_call_math_primitive("bit_and", 2, 3);
    test_call_math_primitive("bit_or", 2, 3);
    test_call_math_primitive("bit_xor", 2, 3);

    test_call_bool_compare_primitive("and", true, false);
    test_call_bool_compare_primitive("or", true, false);
}

}
