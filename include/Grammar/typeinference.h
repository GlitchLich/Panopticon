#ifndef TYPEINFERENCE_H
#define TYPEINFERENCE_H

#include <string>
#include <deque>
#include <unordered_map>
#include "include/core/types.h"

namespace panopticon
{

namespace typing
{

struct TypeVariable
{
    std::deque<TypeDefinition> product_types;
    TypeDefinition instance;
};

struct TypeOperator
{
    std::deque<TypeDefinition> product_types;
    std::deque<TypeDefinition> sum_types;
    bool is_sum = false;
};

void init_inference_env();
RESULT set_variable(Variable id, TypeDefinition& type);

typedef std::unordered_map<Variable,TypeDefinition> Environment;
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
Variable next_variable_name();

TypeDefinition create_type_operator(int type);
TypeVariable copy_type(TypeVariable type);

void print_type(Variable type_def_name, int level = 0);

bool create_type_def_product(object& A, object&B, object& C);
bool create_type_def_sum(object& A, object&B, object& C);


}

}

#endif // TYPEINFERENCE_H
