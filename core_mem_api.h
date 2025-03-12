#ifndef SW_CORE_MEM_API_H_
#define SW_CORE_MEM_API_H_

#include "core_preface.h"

SW_PUBL_API_IMPL inline SwUsz swMemCopyMem(SwUsz nBytesToCopy, mutable SwU8* memInto, const SwU8* memFrom) { SW_DASSERT(memInto && memFrom && nBytesToCopy > 0); __builtin_memcpy(memInto, memFrom, nBytesToCopy); return nBytesToCopy; }
SW_PUBL_API_IMPL inline SwUsz swMemMoveMem(SwUsz nBytesToMove, mutable SwU8* memInto, const SwU8* memFrom) { SW_DASSERT(memInto && memFrom && nBytesToMove > 0); __builtin_memmove(memInto, memFrom, nBytesToMove); return nBytesToMove; }
SW_PUBL_API_IMPL inline SwUsz swMemFillSeq(SwUsz nBytesToFill, mutable SwU8* memInto, SwUsz nBytesInFillSeq, const SwU8* memFillSeq) { SW_DASSERT(memInto && memFillSeq && nBytesToFill > 0 && nBytesInFillSeq > 0); for (SwUsz i = 0; i < nBytesToFill; ++i) { memInto[i] = memFillSeq[i % nBytesInFillSeq]; } return nBytesToFill; }
SW_PUBL_API_IMPL inline SwUsz swMemFillByte(SwUsz nBytesToFill, mutable SwU8* memInto, SwU8 byteFill) { SW_DASSERT(memInto && nBytesToFill > 0); __builtin_memset(memInto, byteFill, nBytesToFill); return nBytesToFill; }
SW_PUBL_API_IMPL inline SwUsz swMemFillZero(SwUsz nBytesToFill, mutable SwU8* memInto) { return swMemFillByte(nBytesToFill, memInto, 0); }

SW_PUBL_API_IMPL inline SwIsz swMemCompareMem(SwUsz nBytesToComp, const SwU8* mem1, const SwU8* mem2) { SW_DASSERT(mem1 && mem2 && nBytesToComp > 0); return (SwIsz)__builtin_memcmp(mem1, mem2, nBytesToComp); }
SW_PUBL_API_IMPL inline SwIsz swMemCompareSeq(SwUsz nBytesToComp, const SwU8* mem, SwUsz nBytesInCompSeq, const SwU8* memCompSeq) { SW_DASSERT(mem && memCompSeq && nBytesToComp > 0 && nBytesInCompSeq > 0); for (SwUsz i = 0; i < nBytesToComp; ++i) { if (mem[i] != memCompSeq[i % nBytesInCompSeq]) { return mem[i] - memCompSeq[i % nBytesInCompSeq]; } } return 0; }
SW_PUBL_API_IMPL inline SwBool swMemEqualMem(SwUsz nBytesToComp, const SwU8* mem1, const SwU8* mem2) { return (swMemCompareMem(nBytesToComp, mem1, mem2) == 0); }
SW_PUBL_API_IMPL inline SwBool swMemEqualSeq(SwUsz nBytesToComp, const SwU8* mem, SwUsz nBytesInCompSeq, const SwU8* memCompSeq) { return (swMemCompareSeq(nBytesToComp, mem, nBytesInCompSeq, memCompSeq) == 0); }
SW_PUBL_API_IMPL inline SwBool swMemEqualByte(SwUsz nBytesToComp, const SwU8* mem, SwU8 byteComp) { SW_DASSERT(mem && nBytesToComp > 0); for (SwUsz i = 0; i < nBytesToComp; ++i) { if (mem[i] ^ byteComp) { return swFALSE; } } return swTRUE; }
SW_PUBL_API_IMPL inline SwBool swMemEqualZero(SwUsz nBytesToComp, const SwU8* mem) { return swMemEqualByte(nBytesToComp, mem, 0); }

SW_PUBL_API_IMPL inline SwOrZero(const SwU8*) swMemFindMem(SwUsz nBytesToScan, const SwU8* memScan, SwUsz nBytesInMemFind, const SwU8* memFind) { SW_DASSERT(memScan && memFind && nBytesInMemFind > 0); for (SwUsz i = 0; (i + nBytesInMemFind) <= nBytesToScan; ++i) { if (swMemEqualMem(nBytesInMemFind, &memScan[i], memFind)) { return (const SwU8*)&memScan[i]; } } return (const SwU8*)swNULL; }
SW_PUBL_API_IMPL inline SwOrZero(const SwU8*) swMemFindByte(SwUsz nBytesToScan, const SwU8* memScan, SwU8 byteFind) { SW_DASSERT(memScan); return (const SwU8*)__builtin_memchr(memScan, byteFind, nBytesToScan); }
SW_PUBL_API_IMPL inline SwOrZero(const SwU8*) swMemFindZero(SwUsz nBytesToScan, const SwU8* memScan) { return (const SwU8*)swMemFindByte(nBytesToScan, memScan, 0); }

#endif // SW_CORE_MEM_API_H_