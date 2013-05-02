#ifndef CONDITIONALS_H
#define CONDITIONALS_H

#include "../core/types.h"

namespace panopticon
{

/**
 * @brief guard A conditional like a case statemnt with several boolean conditions and expressions associated
 * @param resulting_tree The operation tree to be called, void if none of the conditions are met.
 * @param boolean_array The list of conditions
 * @param operation_tree_array The list of possible conditions to run
 * @return
 */
extern bool guard(object& resulting_tree, object& condition_array, object& operation_tree_array);

extern bool guard(object& A, object& B, object& C);
}
#endif // CONDITIONALS_H
