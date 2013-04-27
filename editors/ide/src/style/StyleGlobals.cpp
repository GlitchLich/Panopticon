#include "ide/include/style/StyleGlobals.h"

namespace panopticon
{

namespace ide
{

#ifdef __LINUX__
QFont mainFont("Ubuntu", 13);
QFont monoFont("Ubuntu Mono", 15);
#else
QFont mainFont("Myriad", 11);
QFont monoFont("Menlo", 11);
#endif

} // ide namespace

} // panopticon namespace
