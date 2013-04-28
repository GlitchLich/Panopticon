#include "../../include/core/errors.h"

namespace panopticon
{
bool correct_parsing = true;
std::string print_error(Error error_code)
{
    switch(error_code)
    {
    case UnknownError:
        return "Syntax Error p0000: Unknown Error";
    case OpenQuoteError://p0001
        return "Syntax Error p0001: Dangling Open Quote.";
    case MulStringError://p0002
        return "Syntax Error p0002: Cannot multiply a String.";
    case DivideStringError: //p0003
        return "Syntax Error p0003: Cannot divide a String or divide with a String";
    case IncorrectBooleanComparisonGreater: //p0004
        return "Syntax Error p0004: A Boolean cannot be greater than than something.";
    case IncorrectBooleanComparisonLesser: //p0005
        return "Syntax Error p0005: A Boolean cannot be less than than something.";
    case IndexOutOfBounds://p0006
        return "Syntax Error p0006: Index out of bounds.";
    case SubtractStringFromNum://p0007
        return "Syntax Error p0007: Cannot subtract a String from a Number.";
    case SubtractBoolFromNum://p0008
        return "Syntax Error p0008: Cannot use subtraction with a Boolean.";
    case DivideBooolError://p0009
        return "Syntax Error p0009: Cannot use division with a Boolean.";
    case MultiplyBoolError://p0010
        return "Syntax Error p0010: Cannot Multiply a Boolean.";
    case MultiplyStringError://p0011
        return "Syntax Error p0011: Cannot Multiply a String.";
    case SubtractNumFromString://p0012
        return "Syntax Error p0012: Cannot subtract a Number from a String.";
    case SubtractBoolFromString://p0013
        return "Syntax Error p0013: Cannot subtract a Boolean from a String.";
    case ModBoolError://p0014
        return "Syntax Error p0014: Cannot Modulo a Boolean.";
    case ModStringError://p0015
        return "Syntax Error p0015: Cannot Modulo a String.";
    }
}

}
