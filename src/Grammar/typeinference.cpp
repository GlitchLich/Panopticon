#include "include/Grammar/typeinference.h"
#include <iostream>
#include "include/Grammar/parse.h"
#include <stdio.h>

namespace panopticon
{

namespace typing
{

//Globals
int id_counter = 0;
char current_char = 'a';
EnvMap global_scope;
EnvMap::iterator dynamic_scope_pointer;
Environment initial_scope;
Environment::iterator scope_pointer;
Environment* current_scope;

//====================================================
//Environment and scoping
//====================================================

void init_inference_env()
{
    global_scope.push_back(&initial_scope);
    current_scope = &initial_scope;
    scope_pointer = current_scope->end();
    dynamic_scope_pointer = global_scope.begin();

    TypeOperator* num_op = new TypeOperator;
    TypeDefinition num_def;
    num_def.type = TYPE_OPERATOR;
    num_def.data.type_op = num_op;
    num_def.name = get_string_hash("Num");

    TypeOperator* char_op = new TypeOperator;
    TypeDefinition char_def;
    char_def.type = TYPE_OPERATOR;
    char_def.data.type_op = char_op;
    char_def.name = get_string_hash("Char");

    set_variable(num_def.name,num_def);
    set_variable(char_def.name,char_def);
}

void clear_heap()
{
    while(global_scope.size())
    {
        global_scope.pop_back();
    }
}

void push_scope(Environment *scope)
{
    global_scope.push_back(scope);
    current_scope = scope;
    scope_pointer = current_scope->begin();
}

void pop_scope()
{
    global_scope.pop_back();
    current_scope = global_scope.back();
    scope_pointer = current_scope->begin();
}

TypeDefinition get_variable(Variable id)
{
    dynamic_scope_pointer = global_scope.end();

    // Iterate backwards through each scope
    while(--dynamic_scope_pointer >= global_scope.begin())
    {
        // Check to see if that scope contains the variable we want
        scope_pointer = (*dynamic_scope_pointer)->find(id);

        // If it does assign the results and return OK
        if(scope_pointer != (*dynamic_scope_pointer)->end())
        {
            // *result = mem_copy(scope_pointer->second);
            return scope_pointer->second;
        }
    }

    // If we get to the end we never found it. Return = NULL, return VARIABLE_NOT_FOUND
    TypeDefinition type;
    type.type = NONE;
    return type;
}

RESULT set_variable(Variable id, TypeDefinition& type)
{
    scope_pointer = current_scope->find(id);
    //    if(scope_pointer == current_scope->end())
    //    {
    // current_scope->insert(std::make_pair(String(*variable_name), mem_copy(value)));
    current_scope->insert(std::make_pair(id, type));
    return OK;
    //    }

    //    else
    //    {
    //        return VARIABLE_ALREADY_BOUND;
    //    }
}

//====================================================
//TypeVariable
//====================================================
int next_id()
{
    return id_counter++;
}

Variable next_variable_name()
{
    current_char = current_char+1;
    if(current_char>122)
    {
        current_char = 97;
    }
    std::string name;
    name += current_char;
    return get_string_hash(name);
}

TypeDefinition create_type_variable()
{
    TypeDefinition n;
    n.type = NONE;
    TypeVariable* type_var = new TypeVariable;
    //    type_var->id = next_id();
    //    type_var->name = next_variable_name();
    type_var->instance = n;
    TypeDefinition t_op;
    t_op.type = TYPE_VARIABLE;
    t_op.name = next_variable_name();
    t_op.data.type_var = type_var;
    return t_op;
}

void print_type(Variable type_def_name, int level)
{
    TypeDefinition type_def = get_variable(type_def_name);

    switch(type_def.type)
    {
    case TYPE_OPERATOR:
        out() << reverse_variable_name_lookup[type_def_name];
        if(type_def.data.type_op->is_sum)
        {
            out() << " ";
            for(int i=0;i<type_def.data.type_op->sum_types.size();++i)
            {
                print_type(type_def.data.type_op->sum_types.at(i).name,1);

                if(i<type_def.data.type_op->sum_types.size()-1)
                {
                    out() << " | ";
                }
            }
        }
        else
        {
            if(type_def.data.type_op->product_types.size() > 0)
            {
                out() << "[ ";
                for(int i=0;i<type_def.data.type_op->product_types.size();++i)
                {
                    print_type(type_def.data.type_op->product_types.at(i).name,1);
                    out() << " ";
                }
                out() << "]";
            }
        }
        break;
    case TYPE_VARIABLE:
        out() << "var: ";
        out() << reverse_variable_name_lookup[type_def_name];
        if(type_def.data.type_var->product_types.size() > 0)
        {
            out() << "[ ";
            for(int i=0;i<type_def.data.type_var->product_types.size();++i)
            {
                print_type(type_def.data.type_var->product_types.at(i).name,1);
                out() << " ";
            }
            out() << "]";
        }
        break;
    case NONE:
    default:
        out() << reverse_variable_name_lookup[type_def_name] << "?";
        break;
    }

    if(level==0)
    {
        out() << std::endl;
    }
}

void parse_error()
{
    out() << "Parse Error." << std::endl;
}

void type_error()
{
    out() << "Type Error." << std::endl;
}

//====================================================
//TypeOperator
//====================================================

TypeDefinition create_poly_operator(Variable name, std::deque<TypeDefinition> types)
{
    TypeDefinition t_op;
    t_op.type = TYPE_OPERATOR;
    t_op.name = name;
    t_op.data.type_op = new TypeOperator;
    t_op.data.type_op->product_types = types;
    return t_op;
}

TypeDefinition Boolean_type_op = create_poly_operator(get_string_hash("bool"),std::deque<TypeDefinition>());
TypeDefinition Number_type_op = create_poly_operator(get_string_hash("num"),std::deque<TypeDefinition>());
TypeDefinition String_type_op = create_poly_operator(get_string_hash("string"),std::deque<TypeDefinition>());

//====================================================
//Analysis
//====================================================

TypeDefinition prune(TypeDefinition t)
{
    if(t.type == TYPE_VARIABLE)
    {
        if(t.data.type_var->instance.type != NONE)
        {
            return prune(t.data.type_var->instance);
        }
        return t.data.type_var->instance;
    }
    else
    {
        return t;
    }
}

//bool occurs_in(TypeOperator& v, Environment& env, std::deque<TypeOperator>& non_generics)
//{

//}

//Takes TypeVariable
bool occurs_in(TypeDefinition& v, Environment& env, std::deque<TypeDefinition>& non_generics)
{
    //    return any(occursInType(t, t2) for t2 in types);

    for(int i=0;i<v.data.type_var->product_types.size();++i)
    {

    }
}

//Takes TypeVariable
bool is_generic(TypeDefinition& v, Environment& env, std::deque<TypeDefinition>& non_generics)
{
    return !occurs_in(v,env,non_generics);
}

TypeDefinition freshrec(const TypeDefinition& t, Environment& env, std::deque<TypeDefinition>& non_generics)
{
    TypeDefinition p = prune(t);
    if(p.type == TYPE_VARIABLE)
    {
        if(is_generic(p,env,non_generics))
        {
            if(env.find(p.name) != env.end())
            {
                env[t.name] = create_type_variable();
            }
            return env[t.name];
        }
        else
        {
            return p;
        }
    }
    else if(p.type == TYPE_OPERATOR)
    {
        TypeDefinition t_op;
        t_op.type = TYPE_OPERATOR;
        t_op.data.type_op = new TypeOperator;
        t_op.name = p.name;

        for(int i=0;i<p.data.type_op->product_types.size();++i)
        {
            TypeDefinition x = freshrec(p.data.type_op->product_types.at(i),env,non_generics);
            if(x.type!=NONE)
            {
                t_op.data.type_op->product_types.push_back(x);
            }
        }

        return t_op;
    }
}

inline TypeDefinition fresh(TypeDefinition& t, std::deque<TypeDefinition>& non_generics)
{
    Environment env;
    return freshrec(t,env,non_generics);
}


inline TypeDefinition get_type(unsigned long long name, Environment& env, std::deque<TypeDefinition>& non_generics)
{
    if(env.find(name) != env.end())
    {
        return fresh(env[name], non_generics);
    }
    else
    {
        ParseError parseError = {name};
        TypeDefinition perr;
        perr.type = PARSE_ERROR;
        perr.data.parse_error = parseError;
        return perr;
    }
}

TypeDefinition analyze(object node, Environment* env, std::deque<TypeDefinition> non_generics)
{
    switch(node.type)
    {
    case BOOL:
        return Boolean_type_op;
    case NUMBER:
        return Number_type_op;
    case VARIABLE:
        break;
    case FUNCTION_CALL:
        break;
    case FUNCTION_DECLARATION:
        break;
    case PRIMITIVE:
        break;
    case LAMBDA:
        break;
    case RECURSIVE_CALL:
        break;
    case CASE:
        break;
    case STRING:
        return String_type_op;
    }
}

void is_type_def_generic(optic::typing::TypeDefinition& type_def)
{
    if(isupper(reverse_variable_name_lookup[type_def.name].at(0)))
    {
        type_def.type = optic::typing::TYPE_OPERATOR;
        type_def.data.type_op = new optic::typing::TypeOperator;
    }
    else
    {
        type_def.type = optic::typing::TYPE_VARIABLE;
        type_def.data.type_var = new optic::typing::TypeVariable;

        if(get_variable(type_def.name).type == NONE)
        {
            set_variable(type_def.name,type_def);
        }
    }
}

bool create_type_def_product(object &A, object &B, object &C)
{
    std::deque<optic::typing::TypeDefinition> product_types;

    if(C.type == optic::ARRAY)
    {
        for(int i=0;i<C.data.array->size();++i)
        {
            optic::typing::TypeDefinition product_def;
            product_def.name = C.data.array->at(i).data.variable;
            is_type_def_generic(product_def);
            product_types.push_back(product_def);
        }
    }
    else
    {
        optic::typing::TypeDefinition product_def;
        product_def.name = C.data.variable;
        is_type_def_generic(product_def);
        product_types.push_back(product_def);
    }

    optic::typing::TypeOperator* type_op = new optic::typing::TypeOperator;
    type_op->product_types = product_types;

    optic::typing::TypeDefinition type_def;
    type_def.type = optic::typing::TYPE_OPERATOR;
    type_def.data.type_op = type_op;
    type_def.name = B.data.variable;

    optic::typing::set_variable(type_def.name,type_def);
    optic::typing::print_type(type_def.name);
}


//TODO: implement type parameters
bool create_type_def_sum(object &A, object &B, object &C)
{
    optic::typing::TypeOperator* sum = new optic::typing::TypeOperator;
    sum->is_sum = true;

    for(int i=0;i<C.data.array->size();++i)
    {
        const object& type_def_obj = C.data.array->at(i);
        std::deque<optic::typing::TypeDefinition> product_types;

        optic::typing::TypeDefinition sub_type_def;

        if(type_def_obj.type == optic::ARRAY)
        {
            //Possiblly Old or New types

            sub_type_def.name = type_def_obj.data.array->at(0).data.variable;
            sub_type_def.type = optic::typing::TYPE_OPERATOR;

            for(int i=1;i<type_def_obj.data.array->size();++i)
            {
                optic::typing::TypeDefinition product_def;
                product_def.name = type_def_obj.data.array->at(i).data.variable;
                is_type_def_generic(product_def);
                product_types.push_back(product_def);
            }
        }
        else
        {
            //Assume these have been or will be initialized before later
            sub_type_def.name = C.data.array->at(i).data.variable;
        }

        is_type_def_generic(sub_type_def);

        if(sub_type_def.type == TYPE_OPERATOR)
        {
            sub_type_def.data.type_op->product_types = product_types;
            if(type_def_obj.type == ARRAY)
            {
                if(get_variable(sub_type_def.name).type == NONE)
                {
                    set_variable(sub_type_def.name,sub_type_def);
                }
            }
        }

        sum->sum_types.push_back(sub_type_def);
    }

    optic::typing::TypeDefinition type_def;
    type_def.type = optic::typing::TYPE_OPERATOR;
    type_def.data.type_op = sum;
    type_def.name = B.data.variable;

    optic::typing::set_variable(type_def.name,type_def);
    optic::typing::print_type(type_def.name);
}

}

}
