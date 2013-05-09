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
bool prepend(object& result_A, const object& B, const object& container_C);

/**
 * @brief prepend
 * @param A Result
 * @param B Containter being appended.
 * @param C Object to append
 * @return
 */
bool append(object& result_A, const object& container_B, const object& object_C);

/**
 * @brief concatenation
 * @param A Result
 * @param B Object 1
 * @param C Object 2
 * @return
 */
bool concat(object& A, const object& B, const object& C);


}

#endif // CONTAINERS_H
