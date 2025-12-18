#ifndef SW_CORE_INT_API_H_
#define SW_CORE_INT_API_H_

#include "core_preface.h"


SW_PUBL_API_IMPL inline SwBool32 swIntInRangeU32(SwU32 val, SwU32 minIncl, SwU32 maxIncl) { SW_DASSERT(minIncl <= maxIncl); return (SwU32)(val - minIncl) <= (SwU32)(maxIncl - minIncl); }
SW_PUBL_API_IMPL inline SwBool64 swIntInRangeU64(SwU64 val, SwU64 minIncl, SwU64 maxIncl) { SW_DASSERT(minIncl <= maxIncl); return (SwU64)(val - minIncl) <= (SwU64)(maxIncl - minIncl); }
SW_PUBL_API_IMPL inline SwBool32 swIntInRangeI32(SwI32 val, SwI32 minIncl, SwI32 maxIncl) { SW_DASSERT(minIncl <= maxIncl); return (val >= minIncl) & (val <= maxIncl); }
SW_PUBL_API_IMPL inline SwBool64 swIntInRangeI64(SwI64 val, SwI64 minIncl, SwI64 maxIncl) { SW_DASSERT(minIncl <= maxIncl); return (val >= minIncl) & (val <= maxIncl); }

SW_PUBL_API_IMPL inline SwU32 swIntToDigitCountU32(SwU32 n) { return ((n < 10u) ? 1 : (n < 100u) ? 2 : (n < 1000u) ? 3 : (n < 10000u) ? 4 : (n < 100000u) ? 5 : (n < 1000000u) ? 6 : (n < 10000000u) ? 7 : (n < 100000000u) ? 8 : (n < 1000000000u) ? 9 : 10); }
SW_PUBL_API_IMPL inline SwU32 swIntToDigitCountU64(SwU64 n) { return ((n < 10llu) ? 1 : (n < 100llu) ? 2 : (n < 1000llu) ? 3 : (n < 10000llu) ? 4 : (n < 100000llu) ? 5 : (n < 1000000llu) ? 6 : (n < 10000000llu) ? 7 : (n < 100000000llu) ? 8 : (n < 1000000000llu) ? 9 : (n < 10000000000llu) ? 10 : (n < 100000000000llu) ? 11 : (n < 1000000000000llu) ? 12 : (n < 10000000000000llu) ? 13 : (n < 100000000000000llu) ? 14 : (n < 1000000000000000llu) ? 15 : (n < 10000000000000000llu) ? 16 : (n < 100000000000000000llu) ? 17 : (n < 1000000000000000000llu) ? 18 : (n < 10000000000000000000llu) ? 19 : 20); }


#endif // SW_CORE_INT_API_H_
