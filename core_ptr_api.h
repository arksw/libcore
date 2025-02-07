#ifndef SW_CORE_PTR_API_H_
#define SW_CORE_PTR_API_H_

#include "core_preface.h"

typedef SwU64       SwPtrUInt;
typedef const void* SwPtrAddr;

SW_PUBL_API_IMPL inline SwBool swPtrEqual(SwPtrAddr ptr1, SwPtrAddr ptr2) { return (SwPtrUInt)ptr1 == (SwPtrUInt)ptr2; }
SW_PUBL_API_IMPL inline SwBool swPtrInAddrRange  (SwPtrAddr ptr, SwPtrAddr addrLoIncl, SwPtrAddr addrHiIncl) { SW_DASSERT(addrLoIncl <= addrHiIncl); return ((SwPtrUInt)ptr - (SwPtrUInt)addrLoIncl) <= ((SwPtrUInt)addrHiIncl - (SwPtrUInt)addrLoIncl); }
SW_PUBL_API_IMPL inline SwBool swPtrInAddrRangeEx(SwPtrAddr ptr, SwPtrAddr addrLoIncl, SwPtrAddr addrHiExcl) { SW_DASSERT(addrLoIncl <= addrHiExcl); return ((SwPtrUInt)ptr - (SwPtrUInt)addrLoIncl) <  ((SwPtrUInt)addrHiExcl - (SwPtrUInt)addrLoIncl); }
SW_PUBL_API_IMPL inline SwBool swPtrInSizedMem(SwPtrAddr ptr, SwUsz byteSize, SwPtrAddr memBegin) { return swPtrInAddrRangeEx(ptr, memBegin, (const SwU8*)memBegin + byteSize); }

#endif  // SW_CORE_PTR_API_H_