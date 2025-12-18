#ifndef SW_CORE_STR_API_H_
#define SW_CORE_STR_API_H_

#include "core_preface.h"
#include "core_mem_api.h"
#include "core_char_api.h"
#include "core_utf8_api.h"


//
// CodeptLen
// (does not check utf8-validity)

SW_PUBL_API_IMPL inline SwUsz swStrCodeptLen8z(SwStrUtf8z str) {
    SW_DASSERT(str);
    SwUsz n_codepts = 0;
    while (*str != 0) { SW_DASSERT(swByteIsBoCodeptUtf8(*str));
        ++n_codepts;
        str += swByteGetCodeptByteLenUtf8(*str);
    }
    return n_codepts;
}

SW_PUBL_API_IMPL inline SwUsz swStrCodeptLen8(SwIsz n_bytes_to_scan_max, SwStrUtf8 str) {
    SW_DASSERT(n_bytes_to_scan_max >= 0 && str);
    SwUsz n_codepts = 0;
    for (SwUsz i = 0; i < n_bytes_to_scan_max && (str[i] != 0);) { SW_DASSERT(swByteIsBoCodeptUtf8(str[i]));
        ++n_codepts;
        i += swByteGetCodeptByteLenUtf8(str[i]);
    }
    return n_codepts;
}

//
// ByteLen
//

SW_PUBL_API_IMPL inline SwUsz swStrByteLen8z(SwStrUtf8z str) {
    SW_DASSERT(str);
#if SWCC_CORE_STR_API_TO_USE_LIBC_BUILTINS
    return __builtin_strlen((const char*)str);
#else
    SwUsz n = 0;
    while (str[n] != 0) { ++n; }
    return n;
#endif
}

SW_PUBL_API_IMPL inline SwUsz swStrByteLen8(SwIsz n_bytes_to_scan_max, SwStrUtf8 str) {
    SW_DASSERT(n_bytes_to_scan_max >= 0 && str);
    SwUsz n = 0;
    while (n < n_bytes_to_scan_max && (str[n] != 0)) { ++n; }
    return n;
}

//
// Compare
// (operates on raw bytes, no unicode sanitization)

SW_PUBL_API_IMPL inline SwI32  swStrCompare8z(SwStrUtf8z str1, SwStrUtf8z str2) {
    SW_DASSERT(str1 && str2);
#if SWCC_CORE_STR_API_TO_USE_LIBC_BUILTINS
    return __builtin_strcmp((const char*)str1, (const char*)str2);
#else
    SwI32 diff = 0;
    SwUsz i = 0;
    do {
        diff = (SwI32)str1[i] - (SwI32)str2[i];
        if (diff | !str1[i] | !str2[i]) { break; }
        ++i;
    } while (1);
    return diff;
#endif
}

SW_PUBL_API_IMPL inline SwI32 swStrCompare8(SwIsz n_bytes_to_comp_max, SwStrUtf8 str1, SwStrUtf8 str2) {
    SW_DASSERT(n_bytes_to_comp_max >= 0 && str1 && str2);
#if SWCC_CORE_STR_API_TO_USE_LIBC_BUILTINS
    return __builtin_strncmp((const char*)str1, (const char*)str2, n_bytes_to_comp_max);
#else
    for (SwUsz i = 0; i < n_bytes_to_comp_max; ++i) {
        SwI32 diff = (SwI32)str1[i] - (SwI32)str2[i];
        if (diff | !str1[i] | !str2[i]) {
            return diff;
        }
    }
    return 0;
#endif
}

//
// Equal
// (operates on raw bytes, no unicode sanitization)

SW_PUBL_API_IMPL inline SwBool swStrEqual8z(SwStrUtf8z str1, SwStrUtf8z str2) { return swStrCompare8z(str1, str2) == 0; }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8z_VA1(SwStrUtf8z str, SwStrUtf8z a1) { return swStrEqual8z(str,a1); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8z_VA2(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8z_VA3(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2)|swStrEqual8z(str,a3); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8z_VA4(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2)|swStrEqual8z(str,a3)|swStrEqual8z(str,a4); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8z_VA5(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2)|swStrEqual8z(str,a3)|swStrEqual8z(str,a4)|swStrEqual8z(str,a5); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8z_VA6(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5, SwStrUtf8z a6) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2)|swStrEqual8z(str,a3)|swStrEqual8z(str,a4)|swStrEqual8z(str,a5)|swStrEqual8z(str,a6); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8z_VA7(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5, SwStrUtf8z a6, SwStrUtf8z a7) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2)|swStrEqual8z(str,a3)|swStrEqual8z(str,a4)|swStrEqual8z(str,a5)|swStrEqual8z(str,a6)|swStrEqual8z(str,a7); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8z_VA8(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5, SwStrUtf8z a6, SwStrUtf8z a7, SwStrUtf8z a8) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2)|swStrEqual8z(str,a3)|swStrEqual8z(str,a4)|swStrEqual8z(str,a5)|swStrEqual8z(str,a6)|swStrEqual8z(str,a7)|swStrEqual8z(str,a8); }
#define swStrEqualAny8z(str,...) SW_TOK_CAT2(swStrEqualAny8z_VA,SW_VA_COUNT(__VA_ARGS__))

SW_PUBL_API_IMPL inline SwBool swStrEqual8(SwIsz n_bytes_to_comp_max, SwStrUtf8 str1, SwStrUtf8 str2) { return swStrCompare8(n_bytes_to_comp_max, str1, str2) == 0; }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8_VA1(SwIsz n_bytes_to_comp_max, SwStrUtf8z str, SwStrUtf8z a1) { return swStrEqual8(n_bytes_to_comp_max,str,a1); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8_VA2(SwIsz n_bytes_to_comp_max, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2) { return swStrEqual8(n_bytes_to_comp_max,str,a1)|swStrEqual8(n_bytes_to_comp_max,str,a2); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8_VA3(SwIsz n_bytes_to_comp_max, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3) { return swStrEqual8(n_bytes_to_comp_max,str,a1)|swStrEqual8(n_bytes_to_comp_max,str,a2)|swStrEqual8(n_bytes_to_comp_max,str,a3); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8_VA4(SwIsz n_bytes_to_comp_max, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4) { return swStrEqual8(n_bytes_to_comp_max,str,a1)|swStrEqual8(n_bytes_to_comp_max,str,a2)|swStrEqual8(n_bytes_to_comp_max,str,a3)|swStrEqual8(n_bytes_to_comp_max,str,a4); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8_VA5(SwIsz n_bytes_to_comp_max, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5) { return swStrEqual8(n_bytes_to_comp_max,str,a1)|swStrEqual8(n_bytes_to_comp_max,str,a2)|swStrEqual8(n_bytes_to_comp_max,str,a3)|swStrEqual8(n_bytes_to_comp_max,str,a4)|swStrEqual8(n_bytes_to_comp_max,str,a5); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8_VA6(SwIsz n_bytes_to_comp_max, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5, SwStrUtf8z a6) { return swStrEqual8(n_bytes_to_comp_max,str,a1)|swStrEqual8(n_bytes_to_comp_max,str,a2)|swStrEqual8(n_bytes_to_comp_max,str,a3)|swStrEqual8(n_bytes_to_comp_max,str,a4)|swStrEqual8(n_bytes_to_comp_max,str,a5)|swStrEqual8(n_bytes_to_comp_max,str,a6); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8_VA7(SwIsz n_bytes_to_comp_max, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5, SwStrUtf8z a6, SwStrUtf8z a7) { return swStrEqual8(n_bytes_to_comp_max,str,a1)|swStrEqual8(n_bytes_to_comp_max,str,a2)|swStrEqual8(n_bytes_to_comp_max,str,a3)|swStrEqual8(n_bytes_to_comp_max,str,a4)|swStrEqual8(n_bytes_to_comp_max,str,a5)|swStrEqual8(n_bytes_to_comp_max,str,a6)|swStrEqual8(n_bytes_to_comp_max,str,a7); }
SW_PUBL_API_IMPL inline SwBool swStrEqualAny8_VA8(SwIsz n_bytes_to_comp_max, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5, SwStrUtf8z a6, SwStrUtf8z a7, SwStrUtf8z a8) { return swStrEqual8(n_bytes_to_comp_max,str,a1)|swStrEqual8(n_bytes_to_comp_max,str,a2)|swStrEqual8(n_bytes_to_comp_max,str,a3)|swStrEqual8(n_bytes_to_comp_max,str,a4)|swStrEqual8(n_bytes_to_comp_max,str,a5)|swStrEqual8(n_bytes_to_comp_max,str,a6)|swStrEqual8(n_bytes_to_comp_max,str,a7)|swStrEqual8(n_bytes_to_comp_max,str,a8); }
#define swStrEqualAny8(n_bytes_to_comp_max,str,...) SW_TOK_CAT2(swStrEqualAny8_VA,SW_VA_COUNT(__VA_ARGS__))

//
// Copy
// (operates on raw bytes, no utf8 multi-byte boundary checks)

SW_PUBL_API_IMPL inline SwUsz swStrCopyStr8z(mutable SwByteUtf8* dst, SwStrUtf8z src) {
    SW_DASSERT(dst && src && dst != src);
    SwUsz i = 0;
    do {
        dst[i] = src[i];
    } while (src[i++]); --i;
    // `dst` is always nul terminated
    SW_DASSERT(dst[i] == '\0');
    // return `i`, the number of bytes copied (without counting nul)
    // equivalent to `swStrByteLen8z(src)`
    return i;
}

SW_PUBL_API_IMPL inline SwUsz swStrCopyStr8(SwIsz n_bytes_to_copy_max, mutable SwByteUtf8* dst, SwStrUtf8 src) {
    SW_DASSERT(n_bytes_to_copy_max >= 0 && dst && src && dst != src);
    SwUsz i = 0;
    for (; i < n_bytes_to_copy_max; ++i) {
        dst[i] = src[i];
        if (!src[i]) { break; }
    }
    // `src` has nul before `n_bytes_to_copy_max` => `src`'s nul is the last byte to be copied into `dst`
    // `src` has nul at or after `n_bytes_to_copy_max` || `n_bytes_to_copy_max == 0` => `src`'s nul is not copied into `dst`
    // (this matches `strncpy`'s behavior, which however does not return the number of bytes copied)
    SW_DASSERT(SW_IMPLY(i < n_bytes_to_copy_max, dst[i] == '\0'));
    // return `i`, the number of bytes copied (without counting nul, if any copied)
    // equivalent to `swStrByteLen8(n_max, src)`
    return i;
}

SW_PUBL_API_IMPL inline SwUsz swStrCopyBytes8z(SwIsz n_bytes_to_copy_exact_before_appending_nul, mutable SwU8* dst, const SwU8* src) {
    SW_DASSERT(n_bytes_to_copy_exact_before_appending_nul >= 0 && dst && src && dst != src);

#if SWCC_CORE_STR_API_ALLOW_OVERLAPPING_DST_SRC
    swMemMove(n_bytes_to_copy_exact_before_appending_nul, dst, src);
#else
    swMemCopyNonOverlapping(n_bytes_to_copy_exact_before_appending_nul, dst, src);
#endif
    dst[n_bytes_to_copy_exact_before_appending_nul] = '\0';

    return n_bytes_to_copy_exact_before_appending_nul;
}

//
// Metrics
//

SW_PUBL_API_IMPL inline SwBool swStrIsPrintA(SwUsz n, SwStrA str) { SW_DASSERT(n != 0 && str); while (n != 0) { if (!swCharIsPrintA(str[--n])) { return swFALSE; } } return swTRUE; }
SW_PUBL_API_IMPL inline SwBool swStrIsPrintAz(SwStrAz str) { return swStrIsPrintA(swStrByteLen8z(str), str); }

SW_PUBL_API_IMPL inline SwUsz swStrCountByte8z(SwStrUtf8z str, SwU8 byte_to_find) {
    SW_DASSERT(str && byte_to_find != 0);
    SwUsz count = 0;
    do {
        count += (*str == byte_to_find);
    } while (*str++);
    return count;
}
SW_PUBL_API_IMPL inline SwUsz swStrCountByte8(SwIsz n_bytes_to_scan_max, SwStrUtf8 str, SwU8 byte_to_find) {
    SW_DASSERT(n_bytes_to_scan_max >= 0 && str && byte_to_find != 0);
    SwUsz count = 0;
    for (SwUsz i = 0; i < n_bytes_to_scan_max && (str[i] != 0); ++i) {
        count += (str[i] == byte_to_find);
    }
    return count;
}

//
// Find
//

SW_PUBL_API_IMPL inline SwOrZero(const SwByteUtf8*) swStrFindByte8z(SwStrUtf8z str, SwU8 byte_to_find) {
    SW_DASSERT(str); // byte_to_find == 0 allowed
#if SWCC_CORE_STR_API_TO_USE_LIBC_BUILTINS
    return __builtin_strchr((const char*)str, byte_to_find);
#else
    do {
        if (*str == byte_to_find) {
            return str;
        }
        // nul-termination must be checked after comparison (since byte_to_find = '\0` is valid)
    } while (*str++);
    
    return (const SwU8*)swNULL;
#endif
}

SW_PUBL_API_IMPL inline SwOrZero(const SwByteUtf8*) swStrFindByte8(SwIsz n_bytes_to_scan_max, SwStrUtf8 str, SwU8 byte_to_find) {
    SW_DASSERT(n_bytes_to_scan_max >= 0 && str); // byte_to_find == 0 allowed
    for (SwUsz i = 0; i < n_bytes_to_scan_max; ++i) {
        if (str[i] == byte_to_find) { return &str[i]; }
        // nul-termination must be checked after comparison (since byte_to_find = '\0` is valid)
        if (!str[i]) { break; }
    }
    return (const SwU8*)swNULL;
}

SW_PUBL_API_IMPL inline SwOrZero(const SwByteUtf8*) swStrFindBytes8z(SwStrUtf8z str_to_scan, SwUsz bytes_len, const SwU8* bytes_to_find) {
    SW_DASSERT(str_to_scan && bytes_len > 0 && bytes_to_find);
    SwUsz str_to_scan_len = swStrByteLen8z(str_to_scan); // nul is not considered part of `str_to_scan`
    return swMemFwFind(str_to_scan_len, str_to_scan, bytes_len, bytes_to_find);
}

SW_PUBL_API_IMPL inline SwOrZero(const SwByteUtf8*) swStrFindStr8z(SwStrUtf8z str_to_scan, SwStrUtf8z str_to_find) {
    SW_DASSERT(str_to_scan && str_to_find && *str_to_find != '\0');
#if SWCC_CORE_STR_API_TO_USE_LIBC_BUILTINS
    return __builtin_strstr((const char*)str_to_scan, (const char*)str_to_find);
#else
    return swStrFindBytes8z(str_to_scan, swStrByteLen8z(str_to_find), str_to_find);
#endif
}

SW_PUBL_API_IMPL inline SwOrZero(const SwByteUtf8*) swStrFindStr8(SwIsz n_bytes_to_scan_max, SwStrUtf8 str_to_scan, SwUsz str_to_find_len_max, SwStrUtf8 str_to_find) {
    SW_DASSERT(n_bytes_to_scan_max >= 0 && str_to_scan && str_to_find_len_max > 0 && *str_to_find != '\0');
    SwUsz str_to_scan_len = swStrByteLen8(n_bytes_to_scan_max, str_to_scan);
    SwUsz str_to_find_len = swStrByteLen8(str_to_find_len_max, str_to_find);
    return swMemFwFind(str_to_scan_len, str_to_scan, str_to_find_len, str_to_find);
}

//
// Match
//

typedef SwOrZero(SwUsz) SwStrMatchLenOrZero;

SW_PUBL_API_IMPL inline SwStrMatchLenOrZero swStrMatchTilNonPrintA(SwStrA str1, SwStrA str2) {
    SW_DASSERT(str1 && str2);

    SwUsz i = 0;
    SwBool is_pri1;
    SwBool is_pri2;

    do {
        if (str1[i] ^ str2[i]) { return 0; } // return false on mismatch
        ++i;
        is_pri1 = swCharIsApproxPrint(str1[i]);
        is_pri2 = swCharIsApproxPrint(str2[i]);
    } while (is_pri1 & is_pri2); // breaks as soon as even one is a non printable (which includes e.g. spaces and '\0')

    // either:
    // - we have a mismatch <== str1[i-1] or str2[i-1] is outside the printable ascii range since we broke out of the loop
    // - we have a match <== both str1[i-1] and str2[i-1] must be outside the printable ascii range (i.e. they "terminate" at the same char), and til `i` i.e. chars [0..i) we had a match)
    return (!is_pri1 & !is_pri2) * i;
}
SW_PUBL_API_IMPL inline SwBool swStrIsMatchTilNonPrintA(SwStrA str1, SwStrA str2) {
    return swStrMatchTilNonPrintA(str1, str2) > 0;
}

//
// Binary Formatting
//

#define swStrBinSepPatternGetBitW_U8   8
#define swStrBinSepPattern_U8   (0)
#define swStrBinSepPatternGetBitW_U4x2 8
#define swStrBinSepPattern_U4x2 (1<<4)

#define swStrBinSepPatternGetBitW_U8x2 16
#define swStrBinSepPattern_U8x2 (1<<8)
#define swStrBinSepPatternGetBitW_U4x4 16
#define swStrBinSepPattern_U4x4 ((1<<4)|(1<<8)|(1<<12))

#define swStrBinSepPatternGetBitW_U8x4 32
#define swStrBinSepPattern_U8x4 ((1<<8)|(1<<16)|(1<<24))
#define swStrBinSepPatternGetBitW_U4x8 32
#define swStrBinSepPattern_U4x8 ((1<<4)|(1<<8)|(1<<12)|(1<<16)|(1<<20)|(1<<24)|(1<<28))

#define swStrBinSepPatternGetBitW_U8x8 64
#define swStrBinSepPattern_U8x8 ((1<<8)|(1<<16)|(1<<24)|(1<<32)|(1<<40)|(1<<48)|(1<<56))
#define swStrBinSepPatternGetBitW_U4x16 64
#define swStrBinSepPattern_U4x16 ((1<<4)|(1<<8)|(1<<12)|(1<<16)|(1<<20)|(1<<24)|(1<<28)|(1<<32)|(1<<36)|(1<<40)|(1<<44)|(1<<48)|(1<<52)|(1<<56)|(1<<60))
#define swStrBinSepPatternGetBitW_U4_U6x10 64
#define swStrBinSepPattern_U4_U6x10 0x0820820820820820llu

#define swStrBin_FmtLit "%s"
#define swStrBin_FmtArgs(bits, PAT) swStrFmtBinaryW_WithSepCharA(bits, SW_TOK_CAT2(swStrBinSepPatternGetBitW_,PAT), '_', SW_TOK_CAT2(swStrBinSepPattern_,PAT)).str

SW_PRIV_API_IMPL inline SwStr128bAz swStrFmtBinaryW_WithSepCharA(SwU64 bits, SwU8 bit_w, SwCharA sep_char, SwBitset64 sep_pattern) {
    SW_DASSERT(bit_w > 0 && bit_w <= 64); // will print low `bit_w` bits only
    SW_DASSERT(sep_pattern != swU64_Max); // would overflow 128b cap (64 bin digits + 64 separators + nul = 129b)

    SwStr128bAz out;
    SwU32 r = bit_w-1; // bit index (read)
    SwU32 w = 0; // char index (write)

    do {
        out.as_bytes_mut[w] = sep_char;
        w += (sep_pattern >> r) & 1;
        out.as_bytes_mut[w++] = '0' + ((bits >> r) & 1);
        --r;
    } while (r < bit_w);

    SW_DASSERT(w < 128);
    out.as_bytes_mut[w] = '\0';
    
    return out;
}


#endif // SW_CORE_STR_API_H_
