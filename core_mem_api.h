#ifndef SW_CORE_MEM_API_H_
#define SW_CORE_MEM_API_H_

#include "core_preface.h"

//
// Copy
//
SW_PUBL_API_IMPL inline SwUsz swMemCopyNonOverlapping(SwIsz n_bytes_to_copy, mutable SwU8* mem_into, const SwU8* mem_from) {
    SW_DASSERT(mem_into && mem_from && n_bytes_to_copy > 0);
#if SWCC_CORE_MEM_API_TO_USE_LIBC_BUILTINS
    __builtin_memcpy(mem_into, mem_from, n_bytes_to_copy);
#else
    for (SwIsz i = 0; i < n_bytes_to_copy; ++i) { mem_into[i] = mem_from[i]; }
#endif
    return n_bytes_to_copy;
}

SW_PUBL_API_IMPL inline SwUsz swMemMove(SwIsz n_bytes_to_move, mutable SwU8* mem_into, const SwU8* mem_from) {
    SW_DASSERT(mem_into && mem_from && n_bytes_to_move > 0);
#if SWCC_CORE_MEM_API_TO_USE_LIBC_BUILTINS
    __builtin_memmove(mem_into, mem_from, n_bytes_to_move);
#else
    for (SwIsz i = 0; i < n_bytes_to_move; ++i) { mem_into[i] = mem_from[i]; }
#endif
    return n_bytes_to_move;
}

//
// Fill
//

SW_PUBL_API_IMPL inline SwUsz swMemFillRepeatedSeq(SwIsz n_bytes_to_fill, mutable SwU8* mem_into, SwIsz n_bytes_in_fill_seq, const SwU8* fill_seq) {
    SW_DASSERT(n_bytes_to_fill >= 0 && mem_into && n_bytes_in_fill_seq > 0 && fill_seq);
    for (SwIsz i = 0; i < n_bytes_to_fill; ++i) {
        mem_into[i] = fill_seq[i % n_bytes_in_fill_seq];
    }
    return n_bytes_to_fill;
}

SW_PUBL_API_IMPL inline SwUsz swMemFillByte(SwIsz n_bytes_to_fill, mutable SwU8* mem_into, SwU8 byte_fill) {
    SW_DASSERT(n_bytes_to_fill >= 0 && mem_into);
#if SWCC_CORE_MEM_API_TO_USE_LIBC_BUILTINS
    __builtin_memset(mem_into, byte_fill, n_bytes_to_fill);
#else
    for (SwIsz i = 0; i < n_bytes_to_fill; ++i) {
        mem_into[i] = byte_fill;
    }
#endif
    return n_bytes_to_fill;
}

SW_PUBL_API_IMPL inline SwUsz swMemFillZero(SwIsz n_bytes_to_fill, mutable SwU8* mem_into) {
    return swMemFillByte(n_bytes_to_fill, mem_into, 0);
}

//
// Compare
//

SW_PUBL_API_IMPL inline SwIsz swMemCompare(SwIsz n_bytes_to_comp_max, const SwU8* mem1, const SwU8* mem2) {
    SW_DASSERT(n_bytes_to_comp_max >= 0 && mem1 && mem2);
#if SWCC_CORE_MEM_API_TO_USE_LIBC_BUILTINS
    return (SwIsz)__builtin_memcmp(mem1, mem2, n_bytes_to_comp_max);
#else
    SwIsz diff = 0;
    for (SwIsz i = 0; i < n_bytes_to_comp_max; ++i) {
        diff = (SwIsz)mem1[i] - (SwIsz)mem2[i];
        if (diff) {
            break;
        }
    }
    return diff;
#endif
}


SW_PUBL_API_IMPL inline SwIsz swMemCompareRepeatedSeq(SwIsz n_bytes_to_comp_max, const SwU8* mem, SwIsz n_bytes_in_comp_seq, const SwU8* comp_seq) {
    SW_DASSERT(n_bytes_to_comp_max >= 0 && mem && comp_seq && n_bytes_in_comp_seq > 0);
    SwIsz diff = 0;
    for (SwIsz i = 0; i < n_bytes_to_comp_max; ++i) {
        diff = (SwIsz)mem[i] - (SwIsz)comp_seq[i % n_bytes_in_comp_seq];
        if (diff) {
            break;
        }
    }
    return diff;
}

//
// Equal
//

SW_PUBL_API_IMPL inline SwBool swMemEqual(SwIsz n_bytes_to_comp_max, const SwU8* mem1, const SwU8* mem2) { return (swMemCompare(n_bytes_to_comp_max, mem1, mem2) == 0); }
SW_PUBL_API_IMPL inline SwBool swMemEqualRepeatedSeq(SwIsz n_bytes_to_comp_max, const SwU8* mem, SwIsz n_bytes_in_comp_seq, const SwU8* comp_seq) { return (swMemCompareRepeatedSeq(n_bytes_to_comp_max, mem, n_bytes_in_comp_seq, comp_seq) == 0); }
SW_PUBL_API_IMPL inline SwBool swMemEqualByte(SwIsz n_bytes_to_comp_max, const SwU8* mem, SwU8 byte_comp) { SW_DASSERT(n_bytes_to_comp_max >= 0 && mem); for (SwIsz i = 0; i < n_bytes_to_comp_max; ++i) { if (mem[i] != byte_comp) { return swFALSE; } } return swTRUE; }
SW_PUBL_API_IMPL inline SwBool swMemEqualZero(SwIsz n_bytes_to_comp_max, const SwU8* mem) { return swMemEqualByte(n_bytes_to_comp_max, mem, 0); }

//
// Find
//

SW_PUBL_API_IMPL inline SwOrZero(const SwU8*) swMemFindByte(SwIsz n_bytes_to_scan_max, const SwU8* mem_to_scan, SwU8 byte_to_find) {
    SW_DASSERT(n_bytes_to_scan_max >= 0 && mem_to_scan);
    #if SWCC_CORE_MEM_API_TO_USE_LIBC_BUILTINS
    return (const SwU8*)__builtin_memchr(mem_to_scan, byte_to_find, n_bytes_to_scan_max);
    #else
    for (SwIsz i = 0; i < n_bytes_to_scan_max; ++i) {
        if (mem_to_scan[i] == byte_to_find) {
            return &mem_to_scan[i];
        }
    }
    return (const SwU8*)swNULL;
    #endif
}

SW_PUBL_API_IMPL inline SwOrZero(const SwU8*) swMemFindZero(SwIsz n_bytes_to_scan_max, const SwU8* mem_to_scan) {
    return swMemFindByte(n_bytes_to_scan_max, mem_to_scan, 0);
}

SW_PUBL_API_IMPL inline SwOrZero(const SwU8*) swMemFwFind(SwIsz n_bytes_to_scan_max, const SwU8* mem_to_scan, SwIsz blob_bsize, const SwU8* blob) {
    SW_DASSERT(n_bytes_to_scan_max >= 0 && mem_to_scan && blob_bsize > 0 && blob);
    for (SwIsz i = 0; i <= (n_bytes_to_scan_max - blob_bsize); ++i) {
        if (swMemEqual(blob_bsize, &mem_to_scan[i], blob)) {
            return &mem_to_scan[i];
        }
    }
    return (const SwU8*)swNULL;
}

SW_PUBL_API_IMPL inline SwOrZero(const SwU8*) swMemBwFind(SwIsz n_bytes_to_scan_max, const SwU8* mem_to_scan, SwIsz blob_bsize, const SwU8* blob) {
    SW_DASSERT(n_bytes_to_scan_max >= 0 && mem_to_scan && blob_bsize > 0 && blob);
    for (SwIsz i = n_bytes_to_scan_max - blob_bsize; i >= 0; --i) {
        if (swMemEqual(blob_bsize, &mem_to_scan[i], blob)) {
            return &mem_to_scan[i];
        }
    }
    return (const SwU8*)swNULL;
}


#endif // SW_CORE_MEM_API_H_
