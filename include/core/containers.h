#ifndef CONTAINERS_H
#define CONTAINERS_H

#include "../core/types.h"

namespace panopticon
{

/**
 * @brief prepend
 * @param A Result
 * @param B Object to prepend
 * @param C Containter being prepeneded.
 * @return
 */
extern bool prepend(object& result_A, const object& B, const object& container_C);


}

#endif // CONTAINERS_H
