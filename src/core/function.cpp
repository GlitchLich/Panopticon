#include "include/core/function.h"
#include "../../include/core/containers.h"
#include "../../include/Grammar/parse.h"
#include "core/Memory.h"
#include "../../include/core/stack.h"
#include "../../include/Grammar/parsingutilities.h"
#include "../../include/core/operators.h"
#include "../../include/core/heap.h"

namespace panopticon
{

/**
 * @brief create_function
 * @param A
 * @param B Arguments for the Function. First argument is the function name (unless anonymous)
 * @param C Body of the function, stored as an operation_tree.
 * @return
 */
bool create_function(object &A, const object &B, const object &C)
{
    A = mem_alloc(FUNCTION);
    Function* function = A.data.function;

    if(B.type == FUNCTION_ARG_NAMES)
    {
        function->num_arguments = B.data.array->size();
        for(int i = 0; i < function->num_arguments; ++i)
        {
//            function->arguments.push_back(mem_copy(B.data.array->at(i)));
            function->arguments.push_back(B.data.array->at(i));
        }

        function->name = std::string(*B.data.array->at(0).data.string);
    }

    else if(B.type == STRING)
    {
        function->num_arguments = 0;
//        function->arguments.push_back(mem_copy(B));
        function->arguments.push_back(B);
        function->name = std::string(*B.data.string);
    }

//    function->body = mem_copy(C);
    function->body = C;
    function->body.type = OPERATION_TREE;
}

bool call_function_array(object& A, const object& B, const object& C)
{
//    optic_stack.push_back(mem_copy(C));
//    optic_stack.push_back(mem_copy(B));
    optic_stack.push_back(C);
    optic_stack.push_back(B);
//    object call;
//    call.type = OPERATION;
//    call.data.operator_func = call_function;
    optic_stack.push_back(C);
    evaluate_top();
    A = optic_stack.back(); // optimization: skip copy/free because nothing else will reference it
    optic_stack.pop_back();
}

/**
* @brief call_function
* @param A = Result
* @param B = Function name (STRING)
* @param C = Function Arguments (ARRAY, zero indexed!)
* @return
*/
bool call_function(object& A, const object& B, const object& C)
{
    object function;
    bool free_function = true;

    switch(B.type)
    {
    case VARIABLE:
    case UNDECLARED_VARIABLE:
    case STRING:

        if(get_variable(B.data.string, &function) != OK)
        {
            out() << "Unable to find function: " << B.data.string->c_str() << " in current scope" << std::endl;
            correct_parsing = false;
            return false;
        }

        if(function.type == ARRAY)
        {
            return call_function_array(A, function, C);
        }

        else if(function.type != FUNCTION)
        {
            return false;
        }

        break;

    case FUNCTION:
        // function = mem_copy(B);
        function = B; // Will this cause a mem_free crash later? Not sure, something to test for.
        free_function = false;
        break;

    default:
        out() << "Object is not a function and is not callable: ";
        out() << "OBJECT TYPE: " << B.type << " ";
        print_object(B);
        return false;
        break;
    }
    std::string function_name = function.data.function->name;
    Dictionary context;
    context.insert(std::make_pair(function_name, function));

    if(function.data.function->arguments.size() > 1) // if it has any arguments
    {
        // iterate backwards through the argument list to put them on the stack, this way the resolve in the correct order when we collect them for mapping
        // we use arguments.size() - 2 because we don't want to count the function name which is included in the arguments array
        for(int i = function.data.function->arguments.size() - 2; i >= 0; --i)
        {
//            optic_stack.push_back(mem_copy(C.data.array->at(i)));
            optic_stack.push_back(C.data.array->at(i));
        }

        // Collect the the results and map them to the local scope
        for(int i = 1; i < function.data.function->num_arguments && optic_stack.size() > 0; ++i)
        {
            evaluate_top();
            String arg_name = function.data.function->arguments.at(i).data.string->c_str();
            context.insert(std::make_pair(arg_name, optic_stack.back())); // optimization: insert into map without copy because nothing else is pointing to it
            optic_stack.pop_back();
        }
    }

    push_scope(&context);
    resolve_stack_from_parser(function.data.function->body, false);

    if(optic_stack.back().type == ARRAY)
    {
        object parse_array = mem_alloc(UNARY_OPERATION);
        parse_array.data.unary_operator_func = resolve_function_array;
        optic_stack.push_back(parse_array); // optimization: No need for mem_copy, UNARY_OPERATION doesn't allocate memory
        evaluate_top();
    }

    A = optic_stack.back(); // Move, no need to copy/free
    optic_stack.pop_back();

    pop_scope(); // frees dictionary memory as well
//    context.erase(function_name);
    mem_free_dictionary(context);
    if(free_function)
        mem_free(function);
    return true;
}

bool resolve_function_array(object& A, const object& B)
{
    if(B.type != FUNCTION)
    {
//        optic_stack.push_back(mem_copy(B));
        optic_stack.push_back(B);
        evaluate_top();
        A = optic_stack.back();
        optic_stack.pop_back();
    }

    else
    {
//        A = mem_copy(B);
        A = B;
    }
}

} // panopticon namespace
