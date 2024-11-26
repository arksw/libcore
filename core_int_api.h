#ifndef SW_CORE_INT_API_H_
#define SW_CORE_INT_API_H_

#include "core_preface.h"


SW_PUBL_API_IMPL inline SwBool32 swIntInRangeU32(SwU32 val, SwU32 minIncl, SwU32 maxIncl) { SW_DASSERT(minIncl <= maxIncl); return (SwU32)(val - minIncl) <= (SwU32)(maxIncl - minIncl); }
SW_PUBL_API_IMPL inline SwBool64 swIntInRangeU64(SwU64 val, SwU64 minIncl, SwU64 maxIncl) { SW_DASSERT(minIncl <= maxIncl); return (SwU64)(val - minIncl) <= (SwU64)(maxIncl - minIncl); }
SW_PUBL_API_IMPL inline SwBool32 swIntInRangeI32(SwI32 val, SwI32 minIncl, SwI32 maxIncl) { SW_DASSERT(minIncl <= maxIncl); return (val >= minIncl) & (val <= maxIncl); }
SW_PUBL_API_IMPL inline SwBool64 swIntInRangeI64(SwI64 val, SwI64 minIncl, SwI64 maxIncl) { SW_DASSERT(minIncl <= maxIncl); return (val >= minIncl) & (val <= maxIncl); }


#endif  // SW_INT_API_H_
