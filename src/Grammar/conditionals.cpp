#include "../../include/Grammar/conditionals.h"
#include "../../include/Grammar/parse.h"
#include "../../include/core/stack.h"
#include "../../include/core/operators.h"
#include "../../include/Grammar/parsingutilities.h"
#include "core/Memory.h"

namespace panopticon
{

bool evaluate_guard(object& A, const object& boolean, const object& true_func)
{

}

/**
 * @brief resolve_guard
 * @param A The result. Either an operation tree if one condition is true, or void.
 * @param condition_tree Consists of two branches, one for conditions, and one for operations.
 * @return
 */
bool resolve_guard(object& A, const object &condition_tree)
{
    if(condition_tree.type!=CONDITION_TREE)
    {
        out() << "Error: Malformed guard statement. Object of type: ";
        out() << condition_tree.type << std::endl;
        correct_parsing = false;
        A.type = VOID;
        return false;
    }

    for(int i=0;i<condition_tree.data.array->size();++i)
    {
        optic_stack.push_back(mem_copy(condition_tree.data.array->at(i)));
        evaluate_top();
        const object& result = optic_stack.back();
        optic_stack.pop_back();

        if(result.type==ERROR)
        {
            correct_parsing = false;
            A.type = VOID;
            return false;
        }
        else if(result.type!=FAILED_CONDITION)
        {
            A = result; // no need to copy, no references to it
//            optic_stack.push_back(A);
            return true;
        }
    }

    out() << "Error: No suitable guard conditions found" << std::endl;
    correct_parsing = false;
    A.type = VOID;
    return false;
}

/**
 * @brief create_guard
 * @param function_call_name_and_args The name of the function that the guard resides in.
 * @param condition_tree The CONDITION_TREE to execute in the guard, An Array containing two Arrays
 * @return
 */
object create_guard(object &function_call_name_and_args, object &condition_tree)
{
    object guard = mem_alloc(GUARD);
    //2 branches, 1 for the function name/args, one for the condition_tree
    //    guard.data.array->reserve(2);
//    guard.data.array->push_back(mem_copy(function_call_name_and_args));
//    guard.data.array->push_back(mem_copy(condition_tree));
    guard.data.array->push_back(function_call_name_and_args);
    guard.data.array->push_back(condition_tree);

    return guard;
}

/**
 * @brief create_condition_tree An 2D Array with 2 branches: 1 for conditions, 1 for operation_trees
 * @param condition A condition to init the tree with.
 * @param operation An operation_tree to init the tree with.
 * @return
 */
object create_condition_tree(const object &condition, const object &operation)
{
    object conditional_function;
    store_operations(conditional_function, condition, operation, &conditional_function_call, false); // store operations copies, no need for mem_copy here
    object tree = mem_alloc(CONDITION_TREE);
    tree.data.array->push_back(conditional_function);
    return tree;
}

/**
 * @brief add_branch_to_tree Adds a matching condition and opertion_tree to a condition_tree
 * @param tree The tree to add to.
 * @param condition The condition to add.
 * @param operation The operation_tree to add.
 */
void add_branch_to_tree(object &tree, const object &condition, const object &operation)
{
    object conditional_function;
    store_operations(conditional_function, condition, operation, &conditional_function_call, false); // store operations copies, no need for mem_copy here
    tree.data.array->at(1).data.array->push_back(conditional_function);
}

void add_wildcard_to_tree(object &tree, const object &operation)
{

    object wild_card;
    wild_card.type = BOOL;
    wild_card.data.boolean = true;

    object conditional_function;
    store_operations(conditional_function, wild_card, operation, &conditional_function_call, false); // store operations copies, no need for mem_copy here
    tree.data.array->at(1).data.array->push_back(conditional_function);
}

bool conditional_function_call(object& result_A,const object& conditional_B,const object& operation_tree_C)
{
//    optic_stack.push_back(mem_copy(conditional_B));
    optic_stack.push_back(conditional_B);
    evaluate_top();

    const object& result_B = optic_stack.back();
    optic_stack.pop_back();
    if(result_B.type == BOOL)
    {
        //resolve here
        if(result_B.data.boolean)
        {
//            optic_stack.push_back(mem_copy(operation_tree_C));
            optic_stack.push_back(operation_tree_C);
            evaluate_top();
            result_A = mem_copy(optic_stack.back());
            optic_stack.pop_back();
            return true;
        }
        else
        {
            result_A.type = FAILED_CONDITION;
            return true;
        }
    }
    else if(result_B.type == ARRAY)
    {
        out() << "Error: Non-boolean found in Guard condition statement." << std::endl;
        out() << "Object is of type ARRAY, consider using map function. See Help for details." << std::endl;
        correct_parsing = false;
        result_A.type = ERROR;
        return false;
    }
    else
    {
        out() << "Error: Non-boolean found in Guard condition statement." << std::endl;
        correct_parsing = false;
        result_A.type = ERROR;
        return false;
    }
}

}
