#include "../../include/Grammar/conditionals.h"
#include "../../include/Grammar/parse.h"
#include "../../include/core/stack.h"
#include "../../include/core/operators.h"
#include "../../include/Grammar/parsingutilities.h"

namespace panopticon
{

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
    const Array* conditions = condition_tree.data.array->at(0).data.array;
    const Array* operations = condition_tree.data.array->at(1).data.array;

    if(conditions->size()!=operations->size())
    {
        out() << "Error: Mismtached condition and expression sizes in guard." << std::endl;
        correct_parsing = false;
        A.type = VOID;
        return false;
    }

    for(int i=0;i<conditions->size();++i)
    {
        optic_stack.push_back(conditions->at(i));
        evaluate_top();
        const object& condition = optic_stack.back();
        optic_stack.pop_back();
        out() << "Condition: ";
        print_object(condition);
        if(condition.type==BOOL)
        {
            if(condition.data.boolean)
            {
                optic_stack.push_back(operations->at(i));
                evaluate_top();
                A = optic_stack.back();
                optic_stack.pop_back();
                return true;
            }
        }
        else
        {
            out() << "Error: Non-boolean found in Guard condition statement." << std::endl;
            correct_parsing = false;
            A.type = VOID;
            return false;
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
 * @param condition_tree The CONDITION_TREE to execute in the guard, An Array containing to Arrays
 * @return
 */
object create_guard(object &function_call_name_and_args, object &condition_tree)
{
    object guard;
    guard.type = GUARD;
    guard.data.array = new Array();
    //2 branches, 1 for the function name/args, one for the condition_tree
    guard.data.array->reserve(2);
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
    object tree;
    tree.type = CONDITION_TREE;
    tree.data.array = new Array();
    //two dimensional array with two branches, one side for conditions, one side for operations
    tree.data.array->reserve(2);

    object condition_branch;
    condition_branch.type = CONDITION_BRANCH;
    condition_branch.data.array = new Array();
    condition_branch.data.array->push_back(condition);
    tree.data.array->push_back(condition_branch);

    object operation_branch;
    operation_branch.type = CONDITION_BRANCH;
    operation_branch.data.array = new Array();
    operation_branch.data.array->push_back(operation);
    tree.data.array->push_back(operation_branch);

    out() << "Condition: ";
    print_object(condition);
    out() << "Operation: ";
    print_object(operation);

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
    tree.data.array->at(1).data.array->at(0).data.array->push_back(condition);
    tree.data.array->at(1).data.array->at(1).data.array->push_back(operation);

    out() << "Condition: ";
    print_object(condition);
    out() << "Operation: ";
    print_object(operation);
}

void add_wildcard_to_tree(object &tree, const object &operation)
{

    object wild_card;
    wild_card.type = BOOL;
    wild_card.data.boolean = true;

    tree.data.array->at(1).data.array->at(0).data.array->push_back(wild_card);
    tree.data.array->at(1).data.array->at(1).data.array->push_back(operation);

//    out() << "Condition: ";
//    print_object(wild_card);
//    out() << "Operation: ";
//    print_object(operation);
}

}
