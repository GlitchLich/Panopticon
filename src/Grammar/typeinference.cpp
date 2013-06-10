#include "include/Grammar/typeinference.h"
#include <iostream>
#include "include/Grammar/parse.h"

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

void init_heap()
{
    global_scope.push_back(&initial_scope);
    current_scope = &initial_scope;
    scope_pointer = current_scope->end();
    dynamic_scope_pointer = global_scope.begin();
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

TypeOperator get_variable(unsigned long long id)
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
    TypeOperator type;
    type.type = NONE;
    return type;
}

RESULT set_variable(unsigned long long id, TypeOperator& type)
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

unsigned long long next_variable_name()
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

TypeOperator create_type_variable()
{
    TypeOperator n;
    n.type = NONE;
    TypeVariable* type_var = new TypeVariable;
//    type_var->id = next_id();
    type_var->name = next_variable_name();
    type_var->instance = n;
    TypeOperator t_op;
    t_op.type = TYPE_VARIABLE;
    t_op.data.type_var = type_var;
    return t_op;
}

void print_type(TypeVariable type)
{
//    out() << "TypeVariable(id = " <<  type.id << ", name = " << type.name << ")" << std::endl;
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

TypeOperator create_poly_operator(unsigned long long name, std::deque<TypeOperator> types)
{
    TypeOperator t_op;
    t_op.type = TYPE_OPERATOR;
    t_op.data.type_op = new PolymorphicOperator{name,types};
    return t_op;
}

TypeOperator Boolean_type_op = create_poly_operator(get_string_hash("bool"),std::deque<TypeOperator>());
TypeOperator Number_type_op = create_poly_operator(get_string_hash("num"),std::deque<TypeOperator>());
TypeOperator String_type_op = create_poly_operator(get_string_hash("string"),std::deque<TypeOperator>());

//====================================================
//Analysis
//====================================================

TypeOperator prune(TypeOperator t)
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
bool occurs_in(TypeOperator& v, Environment& env, std::deque<TypeOperator>& non_generics)
{
//    return any(occursInType(t, t2) for t2 in types);

    for(int i=0;i<v.data.type_var->types.size();++i)
    {

    }
}

//Takes TypeVariable
bool is_generic(TypeOperator& v, Environment& env, std::deque<TypeOperator>& non_generics)
{
    return !occurs_in(v,env,non_generics);
}

TypeOperator freshrec(const TypeOperator& t, Environment& env, std::deque<TypeOperator>& non_generics)
{
    TypeOperator p = prune(t);
    if(p.type == TYPE_VARIABLE)
    {
        if(is_generic(p,env,non_generics))
        {
            if(env.find(p.data.type_var->name) != env.end())
            {
                env[t.data.type_var->name] = create_type_variable();
            }
            return env[t.data.type_var->name];
        }
        else
        {
            return p;
        }
    }
    else if(p.type == TYPE_OPERATOR)
    {
        TypeOperator t_op;
        t_op.type = TYPE_OPERATOR;
        t_op.data.type_op = new PolymorphicOperator;
        t_op.data.type_op->name = p.data.type_op->name;

        for(int i=0;i<p.data.type_op->types.size();++i)
        {
            TypeOperator x = freshrec(p.data.type_op->types.at(i),env,non_generics);
            if(x.type!=NONE)
            {
                t_op.data.type_op->types.push_back(x);
            }
        }

        return t_op;
    }
}

inline TypeOperator fresh(TypeOperator& t, std::deque<TypeOperator>& non_generics)
{
    Environment env;
    return freshrec(t,env,non_generics);
}


inline TypeOperator get_type(unsigned long long name, Environment& env, std::deque<TypeOperator>& non_generics)
{
    if(env.find(name) != env.end())
    {
        return fresh(env[name], non_generics);
    }
    else
    {
        ParseError parseError = {name};
        TypeOperator perr;
        perr.type = PARSE_ERROR;
        perr.data.parse_error = parseError;
        return perr;
    }
}

TypeOperator analyze(object node, Environment* env, std::deque<TypeOperator> non_generics)
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

}

}
