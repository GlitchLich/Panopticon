#include "../../include/Grammar/minus.h"
#include "../../include/core/operators.h"
namespace panopticon
{

//================================
//Switches
//================================

void number_divide(object&A,object& B, object& C)
{
    switch(C.type)
    {
    case NUMBER:
        A.type = NUMBER;
        A.data.number = B.data.number / C.data.number;
        break;
    case STRING:
        out() << print_error(DivideStringError) << std::endl;
        correct_parsing = false;
        break;
    case BOOL:
        out() << print_error(DivideBooolError) << std::endl;
        correct_parsing = false;
        break;
    }
}

void bool_divide(object&A, object& B, object& C)
{
    out() << print_error(DivideBooolError) << std::endl;
    correct_parsing = false;
}


void string_divide(object&A, object& B, object& C)
{
    out() << print_error(DivideStringError) << std::endl;
    correct_parsing = false;
}


}
