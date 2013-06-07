#include "include/core/function.h"
#include "../../include/core/containers.h"
#include "../../include/Grammar/parse.h"
#include "core/Memory.h"
#include "../../include/core/stack.h"
#include "../../include/Grammar/parsingutilities.h"
#include "../../include/core/operators.h"
#include "../../include/core/heap.h"
#include "include/core/Memory.h"
#include "include/core/container_primitives.h"

namespace panopticon
{

inline bool call_primitive_function(object &A, const object &B, const object &C)
{
    B.data.primitive->p_func(A,*C.data.array);
}

/**
 * @brief create_function
 * @param A
 * @param B Arguments for the Function. First argument is the function name (unless anonymous)
 * @param C Body of the function, stored as an operation_tree.
 * @return
 */
bool create_function(object &A, const object &B, const object &C)
{
    //    print_object(C);
    //    if(B.data.array->size()>1)
    //    {
    A = mem_alloc(FUNCTION);
    Function* function = A.data.function;
    if(B.type == FUNCTION_ARG_NAMES)
    {
        function->num_arguments = B.data.array->size();
        function->arguments = *B.data.array;
        function->name = B.data.array->at(0).data.variable_number;
    }

    else if(B.type == UNDECLARED_VARIABLE || B.type == VARIABLE)
    {
        function->num_arguments = 0;
        function->arguments.push_back(B);
        function->name = B.data.variable_number;
    }

    function->body = C;
    function->body.type = OPERATION_TREE;
    //    }
    //    else
    //    {
    //        //Force evaluation on functions with 0 arguments, as they are essentially constants.
    //        A = mem_alloc(OPERATION_TREE);
    //        A.data.array = C.data.array;
    //        optic_stack.push_back(A);
    //        evaluate_top();
    //        A = optic_stack.back();
    //        optic_stack.pop_back();
    //        out() << type_string(A.type) << std::endl;
    //    }
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
    A = optic_stack.back();
    optic_stack.pop_back();
}

bool pop_scope(object &A, object &B)
{
    A = B;
}

//Not Lazy enough! Make this more lazy!
//Keep track of tail call stuff during initial operation_tree/thunk creation!

bool strict = true;

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

    switch(B.type)
    {
    case VARIABLE:
    case UNDECLARED_VARIABLE:


        if(get_variable(B.data.variable_number, &function) != OK)
        {
            out() << "Unable to find function: " << reverse_variable_name_lookup[B.data.variable_number] << " in current scope" << std::endl;
            correct_parsing = false;
            return false;
        }

        if(function.type == ARRAY)
        {
            return call_function_array(A, function, C);
        }

        else if(function.type == PRIMITIVE)
        {
            return call_primitive_function(A,function,C);
        }

        else if(function.type != FUNCTION)
        {
            out() << "Error: Attempted to call a non-function of type: " << type_string(function.type) << std::endl;
            correct_parsing = false;
            return false;
        }

        break;
    case PRIMITIVE:
        return call_primitive_function(A,B,C);
    case STRING:
        out() << "Error: Malformed Function call." << std::endl;
        correct_parsing = false;
        return false;
        break;
    case FUNCTION:
        function = B; // Will this cause a mem_free crash later? Not sure, something to test for.
        break;

    default:
        out() << "Object is not a function and is not callable: ";
        out() << "OBJECT TYPE: " << type_string(B.type) << " ";
        print_object(B);
        correct_parsing = false;
        return false;
        break;
    }

    // Conflicts with partial application currently....solve this!
    //    if(C.data.array->size()<function.data.function->arguments.size()-1)
    //    {
    //        partial_application(A,function,C);
    //        return true;
    //    }

    Dictionary context;
    context.insert(std::make_pair(function.data.function->name, function));

    if(function.data.function->arguments.size() > 1) // if it has any arguments
    {
        //=============================
        // Strict Argument Evaluation:
        //=============================
        if(strict)
        {
            // iterate backwards through the argument list to put them on the stack, this way the resolve in the correct order when we collect them for mapping
            // we use arguments.size() - 2 because we don't want to count the function name which is included in the arguments array
            for(int i = function.data.function->arguments.size() - 2; i >= 0; --i)
            {
                // optic_stack.push_back(mem_copy(C.data.array->at(i)));
                optic_stack.push_back(C.data.array->at(i));
            }

            // Collect the the results and map them to the local scope
            for(int i = 1; i < function.data.function->num_arguments && optic_stack.size() > 0; ++i)
            {
                evaluate_top();
                Variable arg_name = function.data.function->arguments.at(i).data.variable_number;
                context.insert(std::make_pair(arg_name, optic_stack.back())); // optimization: insert into map without copy because nothing else is pointing to it
                optic_stack.pop_back();
            }
        }

        //=============================
        // Lazy Argument Evaluation:
        //=============================
        else
        {
            for(int i = function.data.function->arguments.size() - 2; i >= 0; --i)
            {
                Variable arg_name = function.data.function->arguments.at(i).data.variable_number;
                context.insert(std::make_pair(arg_name, C.data.array->at(i)));
            }
        }
    }

    push_scope(&context);
    resolve_stack_from_parser(function.data.function->body, false);

//TO DO: Fix Array Functors
//    if(optic_stack.back().type == ARRAY)
//    {
//        object parse_array = mem_alloc(UNARY_OPERATION);
//        parse_array.data.unary_operator_func = resolve_function_array;
//        optic_stack.push_back(parse_array); // optimization: No need for mem_copy, UNARY_OPERATION doesn't allocate memory
//        evaluate_top();
//    }

    A = optic_stack.back(); // Move, no need to copy/free
    optic_stack.pop_back();
    pop_scope(); // frees dictionary memory as well
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

//================================================
//Partial Application, Operation Sectioning:
//================================================

bool partial_application(object& result_A, const object &func_B, const object &arguments_C)
{

    //Function name/arg
    object name_array = mem_alloc(ARRAY);
    object name = mem_alloc(UNDECLARED_VARIABLE);
    name.data.variable_number = 0;
    name_array.data.array->push_front(name);

    //Function body
    object body;
    object vars = mem_alloc(FUNCTION_ARG_VALUES);
    vars.data.array = arguments_C.data.array;
    int var_num = 1;
    //Create variables
    for(int i=vars.data.array->size();i<func_B.data.function->arguments.size()-1;++i)
    {
        object arg = mem_alloc(UNDECLARED_VARIABLE);
        arg.data.variable_number = var_num;
        name_array.data.array->push_back(arg);

        object var = mem_alloc(UNDECLARED_VARIABLE);
        var.data.variable_number = var_num;
        vars.data.array->push_back(var);
        var_num++;
    }

    //Store Function call
    store_operations(body,func_B,vars,call_function);
    insure_ready_for_assignment(name_array,body);
    store_operations(result_A,name_array,body,create_function);

    //Resolve on stack
    optic_stack.push_back(result_A);
    evaluate_top();
    result_A = optic_stack.back();
    optic_stack.pop_back();

    return true;
}

bool create_operator_function(object& A, operator_function func, bool expand)
{
    //Function name/arg
    optic::object name_array = mem_alloc(optic::ARRAY);
    object name = mem_alloc(UNDECLARED_VARIABLE);
    name.data.variable_number = 0;
    object arg = mem_alloc(UNDECLARED_VARIABLE);
    arg.data.variable_number = 1;
    object arg2 = mem_alloc(UNDECLARED_VARIABLE);
    arg2.data.variable_number = 2;
    name_array.data.array->push_front(name);
    name_array.data.array->push_back(arg);
    name_array.data.array->push_back(arg2);

    //Function body
    object body;
    store_operations(body,arg,arg2,func,expand);

    insure_ready_for_assignment(name_array,body);
    store_operations(A,name_array,body,optic::create_function);
}

bool left_section(object& A, object &B, operator_function func, bool expand)
{
    //Function name/arg
    optic::object name_array = mem_alloc(optic::ARRAY);
    object name = mem_alloc(UNDECLARED_VARIABLE);
    name.data.variable_number = 0;
    object arg = mem_alloc(UNDECLARED_VARIABLE);
    arg.data.variable_number = 1;
    name_array.data.array->push_front(name);
    name_array.data.array->push_back(arg);

    //Function body
    object var = mem_alloc(UNDECLARED_VARIABLE);
    var.data.variable_number = 1;
    object body;
    store_operations(body,B,var,func,expand);

    insure_ready_for_assignment(name_array,body);
    store_operations(A,name_array,body,optic::create_function,expand);
}

bool right_section(object& A, object &B, operator_function func, bool expand)
{
    //Function name/arg
    optic::object name_array = mem_alloc(optic::ARRAY);
    object name = mem_alloc(UNDECLARED_VARIABLE);
    name.data.variable_number = 0;
    object arg = mem_alloc(UNDECLARED_VARIABLE);
    arg.data.variable_number = 1;
    name_array.data.array->push_front(name);
    name_array.data.array->push_back(arg);

    //Function body
    object var = mem_alloc(UNDECLARED_VARIABLE);
    var.data.variable_number = 1;
    object body;
    store_operations(body,var,B,func,expand);

    insure_ready_for_assignment(name_array,body);
    store_operations(A,name_array,body,optic::create_function,expand);
}

void register_primitive_functions()
{
    register_container_primitives();
}

} // panopticon namespace
