#ifndef TYPEINFERENCE_H
#define TYPEINFERENCE_H

#include <string>
#include <deque>
#include <unordered_map>

namespace panopticon
{

namespace typing
{

//Forward Declarations
struct TypeVariable;
struct PolymorphicOperator;

struct ParseError
{
    unsigned long long name;
};

struct TypeError
{
    unsigned long long name;
};

enum OperatorTypes{TYPE_VARIABLE,Null,MONO,POLY,FUNC,PARSE_ERROR,TYPE_ERROR,NONE,TYPE_OPERATOR};

union OpType
{
    PolymorphicOperator* type_op;
    TypeVariable* type_var;
    ParseError parse_error;
    TypeError type_error;
};

struct TypeOperator
{
    int type;
    OpType data;
};

struct TypeVariable
{
    unsigned long long name;
    std::deque<TypeOperator> types;
    TypeOperator instance;
};

struct PolymorphicOperator
{
    unsigned long long name;
    std::deque<TypeOperator> types;
};

typedef std::unordered_map<unsigned long long,TypeOperator> Environment;
typedef std::deque<Environment*> EnvMap;
typedef EnvMap::iterator scope_iter_t;
typedef Environment::iterator dict_iter_t;
extern EnvMap global_scope;
extern void init_heap();
extern void clear_heap(); // ONLY CALL THIS ON CLOSE OR FATAL ERROR
extern void push_scope(Environment *scope);
extern void pop_scope();

extern int id_counter;
extern char current_char;

int next_id();
unsigned long long next_variable_name();

TypeOperator create_type_operator(int type);
TypeVariable copy_type(TypeVariable type);
void print_type();

}

}

#endif // TYPEINFERENCE_H
