#ifndef SW_CORE_ARR_API_H_
#define SW_CORE_ARR_API_H_

#include "core_preface.h"


#define swArrCopyElemsIntoTilCap(nElemsToCopy,arrInto,arrFrom) do {\
    SwUsz n = nElemsToCopy;\
    for (SwUsz i = 0; i < SW_MIN(n, SW_ARR_COUNT(arrInto)); ++i) { arrInto[i] = arrFrom[i]; }\
} while (0)


#endif // SW_CORE_ARR_API_H_