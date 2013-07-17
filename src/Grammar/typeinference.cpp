#include "include/Grammar/typeinference.h"
#include <iostream>
#include "include/Grammar/parse.h"
#include <stdio.h>
#include "include/core/VM.h"

namespace panopticon
{

namespace typing
{

int next_variable_id = 0;
char next_variable_name = 'a';

char get_next_variable_name()
{
    next_variable_name = next_variable_name+1;
    if(next_variable_name>122)
    {
        next_variable_name = 97;
    }

    return next_variable_name;
}

PrimitiveOperator* number = new PrimitiveOperator("Num",optic::NUMBER);
PrimitiveOperator* boolean = new PrimitiveOperator("Bool",optic::BOOL);
PrimitiveOperator* character = new PrimitiveOperator("Char",optic::CHAR);
PrimitiveOperator* wildCard = new PrimitiveOperator("_",optic::VOID);

typedef std::unordered_map<std::string,TypeDef*> Environment;
Environment* env = new Environment;
TypeVec* non_generics = new TypeVec;

FunctionOperator* basic_math_primitive;
FunctionOperator* boolean_math_primitive;
FunctionOperator* boolean_boolean_primitive;

void init()
{
    (*env)["true"] = boolean;
    (*env)["false"] = boolean;
    (*env)["_"] = wildCard;


    TypeVec two_nums;
    two_nums.push_back(number);
    two_nums.push_back(number);

    TypeVec math_types;
    math_types.push_back(number);
    math_types.push_back(new FunctionOperator("",two_nums));

    TypeVec num_bool;
    num_bool.push_back(number);
    num_bool.push_back(boolean);

    TypeVec boolean_math_types;
    boolean_math_types.push_back(number);
    boolean_math_types.push_back(new FunctionOperator("",num_bool));


    TypeVec two_booleans;
    two_booleans.push_back(boolean);
    two_booleans.push_back(boolean);

    TypeVec boolean_boolean_types;
    boolean_boolean_types.push_back(boolean);
    boolean_boolean_types.push_back(new FunctionOperator("",two_booleans));


    //Math Primitive Types
    basic_math_primitive = new FunctionOperator("",math_types);
    boolean_math_primitive = new FunctionOperator("",boolean_math_types);
    boolean_boolean_primitive = new FunctionOperator("",boolean_boolean_types);

    //Basic Math Primitives
    (*env)["add"] = basic_math_primitive;
    (*env)["subtract"] = basic_math_primitive;
    (*env)["divide"] = basic_math_primitive;
    (*env)["multiply"] = basic_math_primitive;
    (*env)["modulus"] = basic_math_primitive;
    (*env)["power"] = basic_math_primitive;
    (*env)["shift_left"] = basic_math_primitive;
    (*env)["shift_right"] = basic_math_primitive;
    (*env)["bit_and"] = basic_math_primitive;
    (*env)["bit_or"] = basic_math_primitive;
    (*env)["bit_xor"] = basic_math_primitive;

    //Boolean Math Primitves
    (*env)["lessThan"] = boolean_math_primitive;
    (*env)["greaterThan"] = boolean_math_primitive;
    (*env)["equalTo"] = boolean_math_primitive;
    (*env)["lessThanOrEq"] = boolean_math_primitive;
    (*env)["greaterThanOrEq"] = boolean_math_primitive;
    (*env)["notEqualTo"] = boolean_math_primitive;

    //Boolean Boolean Primitives
    (*env)["and"] = boolean_boolean_primitive;
    (*env)["or"] = boolean_boolean_primitive;

    //    std::cout << "add :: " << (*env)["add"]->print_string() << std::endl;
    //    std::cout << "lessThan :: " << (*env)["lessThan"]->print_string() << std::endl;
    //    std::cout << "and :: " << (*env)["and"]->print_string() << std::endl;
}

TypeDef* prune(TypeDef* t)
{
    if(t->type() == TypeDef::TYPE_VAR)
    {
        //        if(((TypeVariable*)t)->instantiated)
        //        {
        //            TypeDef* new_t = prune(t);
        //            return t;
        //        }
        //        else
        //        {
        //            return t;
        //        }
        return t;
    }
    else
    {
        return t;
    }
}

bool occurs_in(TypeDef* t, TypeVec &types);

bool occurs_in_type(TypeDef* t, TypeDef* t2)
{
    TypeDef* pruned_t2 = prune(t2);
    if(pruned_t2->get_name() == t->get_name())
    {
        return true;
    }
    else if(pruned_t2->type() == TypeDef::TYPE_OP)
    {
        return occurs_in(t,((TypeOperator*)pruned_t2)->types);
    }

    return false;
}

bool occurs_in(TypeDef* t, TypeVec& types)
{
    for(int i=0;i<types.size();++i)
    {
        if(occurs_in_type(t,types.at(i)))
        {
            return true;
        }
    }
    return false;
}

bool is_generic(TypeDef* t, TypeVec& non_generics)
{
    return !occurs_in(t,non_generics);
}

TypeDef* unify(TypeDef* t, Environment& env, TypeDef* t2)
{
    TypeDef* a = prune(t);
    TypeDef* b = prune(t2);
    //    std::cout << "unify:: t " << t->print_string() << " and t2 " << t2->print_string() << std::endl;

    if(a->type() == TypeDef::TYPE_VAR)
    {
        //        if(a->get_name() != b->get_name())
        //        {
        if(occurs_in_type(a,b))
        {
            std::cout << "TypeError: Recursive unification with types " << a->get_name() << " and " << b->get_name() << std::endl;
            correct_parsing = false;
        }
        //            std::cout << "a = b" << std::endl;
        //            a = b;
        //            std::cout << "unified test: " << a->print_string() << std::endl;
        //        }
        env[a->get_name()] = b;

        return b;
    }
    else if(a->type() == TypeDef::TYPE_OP && b->type() == TypeDef::TYPE_VAR)
    {
        return unify(b,env,a);
    }
    else if(a->type() == TypeDef::TYPE_OP && b->type() == TypeDef::TYPE_OP)
    {
        if(a->get_name() != b->get_name() || ((TypeOperator*)a)->types.size() != ((TypeOperator*)b)->types.size())
        {
            std::cout << "TypeError: Type mismatch with types " << a->get_name() << " and " << b->get_name() << std::endl;
            correct_parsing = false;
        }
        else
        {
            //            std::cout << "a->types.size() " << ((TypeOperator*)a)->types.size() << std::endl;
            for(int i=0;i<((TypeOperator*)a)->types.size();++i)
            {
                ((TypeOperator*)a)->types.at(i) = unify(((TypeOperator*)a)->types.at(i),env,((TypeOperator*)b)->types.at(i));
                //                std::cout << "unified test2: " << ((TypeOperator*)a)->types.at(i)->print_string() << std::endl;
            }
            return a;
        }
    }
    return a;
}

TypeDef* fresh_rec(TypeDef* t, Environment& mappings, TypeVec& non_generics)
{
    TypeDef* p = prune(t);
    if(p->type() == TypeDef::TYPE_VAR)
    {
        if(is_generic(p,non_generics))
        {
            if(mappings.find(p->get_name()) == mappings.end())
            {
                mappings[p->get_name()] = new TypeVariable();
            }
            return mappings[p->get_name()];
        }
        else
        {
            return p;
        }
    }
    else if(p->type() == TypeDef::TYPE_OP)
    {
        TypeVec fresh_types;
        for(int i=0;i<((TypeOperator*)p)->types.size();++i)
        {
            fresh_types.push_back(fresh_rec(((TypeOperator*)p)->types.at(i),mappings,non_generics));
        }
        switch(((TypeOperator*)p)->sub_type)
        {
        case TypeOperator::Product:
            return new ProductOperator(p->get_name(),fresh_types);
        case TypeOperator::Sum:
            return new SumOperator(p->get_name(),fresh_types);
        case TypeOperator::Primitive:
            return new PrimitiveOperator(p->get_name(),((PrimitiveOperator*)p)->optic_type);
        case TypeOperator::Function:
            return new FunctionOperator(p->get_name(),fresh_types);
        }
    }
}

TypeDef* fresh(TypeDef* t, TypeVec& non_generics)
{
    Environment mappings;
    return fresh_rec(t,mappings,non_generics);
}

TypeDef* get_type(std::string name, Environment& env, TypeVec& non_generics)
{
    if(env.find(name) != env.end())
    {
        //        return fresh(env[name],non_generics);
        return env[name];
    }
    else
    {
        out() << "ParseError, Undefined Symbol: " << name << std::endl;
        correct_parsing = false;
    }
}

llvm::Type* convert_to_llvm(TypeDef* type,bool function_pointer = true)
{
//    std::cout << "llvm::Type* convert_to_llvm(TypeDef* type)" << std::endl;
    std::cout << "converting type: " << type->print_string() << std::endl;
    switch(type->type())
    {
    case TypeDef::TYPE_OP:
        switch(((TypeOperator*)type)->sub_type)
        {
        case TypeOperator::Product:
        {
//            std::cout << "Product" << std::endl;
            ProductOperator* product = (ProductOperator*)type;
            std::vector<llvm::Type*> types;
            for(int i=0; i<product->types.size();++i)
            {
                types.push_back(convert_to_llvm(product->types.at(i)));
            }
            return llvm::StructType::get(llvm::getGlobalContext(),types,false);
        }
        case TypeOperator::Sum:
//            std::cout << "Sum" << std::endl;
            break;
        case TypeOperator::Primitive:
        {
//            std::cout << "Primitive" << std::endl;
            PrimitiveOperator* p = (PrimitiveOperator*)type;
            switch(p->optic_type)
            {
            case optic::NUMBER:
                return llvm::Type::getDoubleTy(llvm::getGlobalContext());
            case optic::CHAR:
                return llvm::Type::getInt8Ty(llvm::getGlobalContext());
            case optic::BOOL:
                return llvm::Type::getInt1Ty(llvm::getGlobalContext());
            case optic::VOID:
                return llvm::Type::getVoidTy(llvm::getGlobalContext());
            }
        }
        case TypeOperator::Function:
        {
//            std::cout << "Function" << std::endl;
            FunctionOperator* func = (FunctionOperator*)type;
//            std::cout << "func->types.size: " << func->types.size() << std::endl;
            llvm::Type* return_type = convert_to_llvm(func->types.at(1));
            std::vector<llvm::Type*> arg_types;
            arg_types.push_back(convert_to_llvm(func->types.at(0)));
            if(function_pointer)
            {
                return llvm::PointerType::getUnqual(llvm::FunctionType::get(return_type,arg_types,false));
            }
            else
            {
                return llvm::FunctionType::get(return_type,arg_types,false);
            }
        }
        }
        break;
    case TypeDef::TYPE_VAR:
        return llvm::Type::getVoidTy(llvm::getGlobalContext());
    }
}

TypeDef* analyze(ExprAST* expr,Environment& env,TypeVec& non_generics)
{
    assert(expr != 0);

    switch(expr->getAST_Type())
    {

    case ExprAST::Variable:
        std::cout << "analyze::Variable: "<< ((VariableExprAST*)expr)->Name << std::endl;
        return get_type(((VariableExprAST*)expr)->Name,env,non_generics);
    case ExprAST::BinaryOp:
    {
        std::cout << "analyze::BinaryOp" << std::endl;
        TypeDef* bin_type;
        BinaryExprAST* bin_op = (BinaryExprAST*)expr;
        switch (bin_op->op) {
        case BinaryExprAST::Add:
        case BinaryExprAST::Subtract:
        case BinaryExprAST::Multiply:
        case BinaryExprAST::Divide:
        case BinaryExprAST::Modulus:
        case BinaryExprAST::ShiftLeft:
        case BinaryExprAST::ShiftRight:
        case BinaryExprAST::BitAnd:
        case BinaryExprAST::BitOr:
        case BinaryExprAST::BitXOr:
        case BinaryExprAST::Power:
            bin_type = basic_math_primitive;
            break;
        case BinaryExprAST::LessThan:
        case BinaryExprAST::GreaterThan:
        case BinaryExprAST::EqualTo:
        case BinaryExprAST::NotEqualTo:
        case BinaryExprAST::GreaterThanEq:
        case BinaryExprAST::LessThanEq:
            bin_type = boolean_math_primitive;
            break;
        case BinaryExprAST::And:
        case BinaryExprAST::Or:
            bin_type = boolean_boolean_primitive;
            break;
        }

        TypeDef* lht = analyze(bin_op->lhs,env,non_generics);
        TypeDef* rht = analyze(bin_op->rhs,env,non_generics);

        TypeVec rhl_args;
        rhl_args.push_back(rht);
        rhl_args.push_back(number);

        TypeVec rhl;
        rhl.push_back(lht);
        rhl.push_back(new FunctionOperator("",rhl_args));

        FunctionOperator* unified = (FunctionOperator*)unify(new FunctionOperator("",rhl),env,bin_type);
        //        std::cout << "env2 test: " << lht->get_name() << " " << env[lht->get_name()]->print_string() << std::endl;
        return ((FunctionOperator*)unified->types.at(1))->types.at(1);
    }

        //Primitives
    case ExprAST::Number:
        std::cout << "analyze::Number" << std::endl;
        return number;
    case ExprAST::Char:
        std::cout << "analyze::Char" << std::endl;
        return character;
    case ExprAST::True:
        std::cout << "analyze::True" << std::endl;
        return boolean;
    case ExprAST::False:
        std::cout << "analyze::False" << std::endl;
        return boolean;

        //Lambda
    case ExprAST::Lambda:
    {
        std::cout << "analyze::lambda" << std::endl;
        LambdaAST* lambda = (LambdaAST*)expr;
        TypeVariable* arg_type = new TypeVariable;
        Environment env2(env);
        TypeVec non_generics2(non_generics);
        if(lambda->proto->args.size()>0)
        {
            env2[lambda->proto->args.at(0)] = arg_type;
            non_generics2.push_back(arg_type);
        }

        TypeDef* result_type = analyze(lambda->body,env2,non_generics2);

        //        std::cout << "env var: " << arg_type->get_name() << " " << env2[arg_type->get_name()]->print_string() << std::endl;

        TypeVec func_types;
        if(lambda->proto->args.size()>0)
        {
            func_types.push_back(env2[arg_type->get_name()]);
        }
        else
        {
            func_types.push_back(wildCard);
        }
        func_types.push_back(result_type);
        TypeDef* lambda_type = new FunctionOperator("",func_types);
//        std::cout << "func_types.size " << func_types.size() << std::endl;
//        std::cout << "lambda argument type: " << func_types.at(0)->print_string() << std::endl;
        llvm::FunctionType* lambda_llvm_type = (llvm::FunctionType*)convert_to_llvm(lambda_type,false);
        llvm::Type* lambda_pointer_type = llvm::PointerType::getUnqual(lambda_llvm_type);
        lambda->arity = lambda_pointer_type;
        lambda->proto->arity = lambda_llvm_type;
        env.swap(env2);
        return lambda_type;
    }
    case ExprAST::Let:
    {
        std::cout << "analyze::let" << std::endl;
        LetAST* let = (LetAST*)expr;
        TypeDef* let_type = analyze(let->body,env,non_generics);
        let->arity = convert_to_llvm(let_type);
        return let_type;
    }
    case ExprAST::LetRec:
        break;
    case ExprAST::Apply:
    {
        std::cout << "analyze::apply" << std::endl;
        ApplyAST* apply = (ApplyAST*)expr;
        TypeDef* func_type = analyze(apply->lambda,env,non_generics);
        //        std::cout << "func_type: " << func_type->print_string() << std::endl;
        TypeDef* arg_type = analyze(apply->arg,env,non_generics);
        //        std::cout << "arg_type: " << arg_type->print_string() << std::endl;
        TypeDef* result_type = new TypeVariable();
        //        std::cout << "result_type: " << result_type->print_string() << std::endl;
        TypeVec type_vec;
        type_vec.push_back(arg_type);
        type_vec.push_back(result_type);
        TypeDef* unified = unify(new FunctionOperator("",type_vec),env,func_type);
        apply->arity = convert_to_llvm(((FunctionOperator*)unified)->types.at(1));
        return ((FunctionOperator*)unified)->types.at(1);
    }

    case ExprAST::Prototype:
        out() << "Parsing Error: received ProtypeAST during TypeInference." << std::endl;
        correct_parsing = false;
        return new TypeVariable;
    case ExprAST::Function:
        out() << "Parsing Error: received FunctionAST during TypeInference." << std::endl;
        correct_parsing = false;
        return new TypeVariable;
    case ExprAST::FunctionCall:
        out() << "Parsing Error: received FunctionCallAST during TypeInference." << std::endl;
        correct_parsing = false;
        return new TypeVariable;
    }
}

TypeDef* analyze(ExprAST* expr)
{
    return analyze(expr,*env,*non_generics);
}

}

}
