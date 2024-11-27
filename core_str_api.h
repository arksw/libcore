#ifndef SW_CORE_STR_API_H_
#define SW_CORE_STR_API_H_

#include "core_preface.h"
#include "core_mem_api.h"
#include "core_char_api.h"
#include "core_utf8_api.h"

typedef SwOrZero(SwUsz) SwMatchLenOrZero;

SW_PUBL_API_IMPL inline SwUsz swStrByteLen8z(SwStrUtf8z str) { return __builtin_strlen((const char*)str); }
SW_PUBL_API_IMPL inline SwUsz swStrCodeptLen8z(SwStrUtf8z str) { SwUsz len = 0; while (*str != 0) { SW_DASSERT(swByteIsCodeptUtf8(*str) & !swByteIsContinUtf8(*str)); ++len; str += swByteGetCodeptByteLenUtf8(*str); } return len; }

SW_PUBL_API_IMPL inline SwIsz swStrCompare8z(SwStrUtf8z str1, SwStrUtf8z str2) { return __builtin_strcmp((const char*)str1, (const char*)str2); }
SW_PUBL_API_IMPL inline SwBool  swStrEqual8z(SwStrUtf8z str1, SwStrUtf8z str2) { return swStrCompare8z(str1, str2) == 0; }
#define swStrIsAny8z(str,...) SW_TOK_CAT2(swStrIsAny8z_VA,SW_VA_COUNT(__VA_ARGS__))
SW_PUBL_API_IMPL inline SwBool swStrIsAny8z_VA1(SwStrUtf8z str, SwStrUtf8z a1) { return swStrEqual8z(str,a1); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8z_VA2(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8z_VA3(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2)|swStrEqual8z(str,a3); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8z_VA4(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2)|swStrEqual8z(str,a3)|swStrEqual8z(str,a4); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8z_VA5(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2)|swStrEqual8z(str,a3)|swStrEqual8z(str,a4)|swStrEqual8z(str,a5); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8z_VA6(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5, SwStrUtf8z a6) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2)|swStrEqual8z(str,a3)|swStrEqual8z(str,a4)|swStrEqual8z(str,a5)|swStrEqual8z(str,a6); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8z_VA7(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5, SwStrUtf8z a6, SwStrUtf8z a7) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2)|swStrEqual8z(str,a3)|swStrEqual8z(str,a4)|swStrEqual8z(str,a5)|swStrEqual8z(str,a6)|swStrEqual8z(str,a7); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8z_VA8(SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5, SwStrUtf8z a6, SwStrUtf8z a7, SwStrUtf8z a8) { return swStrEqual8z(str,a1)|swStrEqual8z(str,a2)|swStrEqual8z(str,a3)|swStrEqual8z(str,a4)|swStrEqual8z(str,a5)|swStrEqual8z(str,a6)|swStrEqual8z(str,a7)|swStrEqual8z(str,a8); }

SW_PUBL_API_IMPL inline SwIsz swStrCompare8(SwUsz nBytesToCompMax, SwStrUtf8 str1, SwStrUtf8 str2) {
    for (SwUsz i = 0; i < nBytesToCompMax; ++i) {
        SwIsz diff = str1[i]-str2[i];
        if (diff | !str1[i] | !str2[i]) {
            return diff;
        }
    }
    return 0;
}
SW_PUBL_API_IMPL inline SwBool  swStrEqual8(SwUsz nBytesToCompMax, SwStrUtf8 str1, SwStrUtf8 str2) { return swStrCompare8(nBytesToCompMax, str1, str2) == 0; }
#define swStrIsAny8(nBytesToCompMax,str,...) SW_TOK_CAT2(swStrIsAny8_VA,SW_VA_COUNT(__VA_ARGS__))
SW_PUBL_API_IMPL inline SwBool swStrIsAny8_VA1(SwUsz nBytesToCompMax, SwStrUtf8z str, SwStrUtf8z a1) { return swStrEqual8(nBytesToCompMax,str,a1); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8_VA2(SwUsz nBytesToCompMax, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2) { return swStrEqual8(nBytesToCompMax,str,a1)|swStrEqual8(nBytesToCompMax,str,a2); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8_VA3(SwUsz nBytesToCompMax, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3) { return swStrEqual8(nBytesToCompMax,str,a1)|swStrEqual8(nBytesToCompMax,str,a2)|swStrEqual8(nBytesToCompMax,str,a3); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8_VA4(SwUsz nBytesToCompMax, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4) { return swStrEqual8(nBytesToCompMax,str,a1)|swStrEqual8(nBytesToCompMax,str,a2)|swStrEqual8(nBytesToCompMax,str,a3)|swStrEqual8(nBytesToCompMax,str,a4); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8_VA5(SwUsz nBytesToCompMax, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5) { return swStrEqual8(nBytesToCompMax,str,a1)|swStrEqual8(nBytesToCompMax,str,a2)|swStrEqual8(nBytesToCompMax,str,a3)|swStrEqual8(nBytesToCompMax,str,a4)|swStrEqual8(nBytesToCompMax,str,a5); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8_VA6(SwUsz nBytesToCompMax, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5, SwStrUtf8z a6) { return swStrEqual8(nBytesToCompMax,str,a1)|swStrEqual8(nBytesToCompMax,str,a2)|swStrEqual8(nBytesToCompMax,str,a3)|swStrEqual8(nBytesToCompMax,str,a4)|swStrEqual8(nBytesToCompMax,str,a5)|swStrEqual8(nBytesToCompMax,str,a6); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8_VA7(SwUsz nBytesToCompMax, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5, SwStrUtf8z a6, SwStrUtf8z a7) { return swStrEqual8(nBytesToCompMax,str,a1)|swStrEqual8(nBytesToCompMax,str,a2)|swStrEqual8(nBytesToCompMax,str,a3)|swStrEqual8(nBytesToCompMax,str,a4)|swStrEqual8(nBytesToCompMax,str,a5)|swStrEqual8(nBytesToCompMax,str,a6)|swStrEqual8(nBytesToCompMax,str,a7); }
SW_PUBL_API_IMPL inline SwBool swStrIsAny8_VA8(SwUsz nBytesToCompMax, SwStrUtf8z str, SwStrUtf8z a1, SwStrUtf8z a2, SwStrUtf8z a3, SwStrUtf8z a4, SwStrUtf8z a5, SwStrUtf8z a6, SwStrUtf8z a7, SwStrUtf8z a8) { return swStrEqual8(nBytesToCompMax,str,a1)|swStrEqual8(nBytesToCompMax,str,a2)|swStrEqual8(nBytesToCompMax,str,a3)|swStrEqual8(nBytesToCompMax,str,a4)|swStrEqual8(nBytesToCompMax,str,a5)|swStrEqual8(nBytesToCompMax,str,a6)|swStrEqual8(nBytesToCompMax,str,a7)|swStrEqual8(nBytesToCompMax,str,a8); }

SW_PUBL_API_IMPL inline SwBool swStrIsPrintA(SwUsz n, SwStrA str) { SW_DASSERT(n != 0); while (n != 0) { if (!swCharIsPrintA(str[--n])) { return swFALSE; } } return swTRUE; }
SW_PUBL_API_IMPL inline SwBool swStrIsPrintAz(SwStrAz str) { return swStrIsPrintA(swStrByteLen8z(str), str); }

SW_PUBL_API_IMPL inline SwUsz swStrCountByte8(SwUsz nBytesToScanMax, SwStrUtf8 str, SwU8 byteFind) { SW_DASSERT(byteFind != 0); SwUsz count = 0; for (SwUsz i = 0; i < nBytesToScanMax; ++i) { count += (str[i] == byteFind); if (str[i] == 0) break; } return count; }
SW_PUBL_API_IMPL inline SwUsz swStrCountByte8z(SwStrUtf8z str, SwU8 byteFind) { SW_DASSERT(byteFind != 0); SwUsz count = 0; do { count += (*str == byteFind); } while (*str++); return count; }

SW_PUBL_API_IMPL inline SwOrZero(const SwByteUtf8*) swStrFindByte8z(SwStrUtf8z str, SwU8 byteFind) { do { if (*str == byteFind) { return str; } } while (*str++); return (const SwU8*)swNULL; }
SW_PUBL_API_IMPL inline SwOrZero(const SwByteUtf8*) swStrFindByte8 (SwUsz nBytesToScanMax, SwStrUtf8 str, SwU8 byteFind) { for (SwUsz i = 0; i < nBytesToScanMax; ++i) { if (str[i] == byteFind) { return &str[i]; } if (str[i] == 0) { return (const SwU8*)swNULL; } } return (const SwU8*)swNULL; }
SW_PUBL_API_IMPL inline SwOrZero(const SwByteUtf8*) swStrFindStr8z (SwStrUtf8z str, SwStrUtf8z strFind) { return (const SwU8*)__builtin_strstr((const char*)str, (const char*)strFind); }
SW_PUBL_API_IMPL inline SwOrZero(const SwByteUtf8*) swStrFindStr8  (SwUsz nBytesToScanMax, SwStrUtf8 str, SwUsz nBytesInStrFind, SwStrUtf8 strFind) {
    const SwByteUtf8* earlyZeroTerm = swStrFindByte8(nBytesInStrFind, strFind, 0);
    nBytesInStrFind = earlyZeroTerm ? (earlyZeroTerm - strFind) : nBytesInStrFind;

    if((nBytesInStrFind == 0) | (nBytesToScanMax < nBytesInStrFind)) { return (SwU8*)swNULL; }
    if (nBytesInStrFind == 1) { return swStrFindByte8(nBytesToScanMax, str, *strFind); }

    SwIsz j = 0;
    for (SwIsz i = 0; (i + nBytesInStrFind) <= nBytesToScanMax; ++i) {
        for (j = 0; j < nBytesInStrFind; ++j) {
            if (str[i+j] == 0) return (const SwU8*)swNULL;
            if (str[i+j] != strFind[j]) break;
        }
        if (j == nBytesInStrFind) return &str[i];
    }
    return (const SwU8*)swNULL;
}

SW_PUBL_API_IMPL inline SwMatchLenOrZero swStrMatchTilNonPrintA(SwStrAz str1, SwStrAz str2) {
    SW_DASSERT(str1 && str2 && swCharIsPrintA(*str1) && swCharIsPrintA(*str2));

    SwUsz i = 0;
    SwBool isPri1;
    SwBool isPri2;

    do {
        SW_DASSERT(str1 && str2 && swCharIsPrintA(*str1) && swCharIsPrintA(*str2));
        if (str1[i] ^ str2[i]) { return 0; }  // return false on mismatch
        ++i;
        isPri1 = swCharIsPrintA(str1[i]);
        isPri2 = swCharIsPrintA(str2[i]);
    } while (isPri1 & isPri2);  // breaks as soon as even one is a non printable (which includes e.g. spaces and '\0')

    // either:
    // - we have a mismatch <= str1[i-1] or str2[i-1] is outside the printable ascii range since we broke out of the loop
    // - we have a match <= both str1[i-1] and str2[i-1] must be outside the printable ascii range (i.e. they "terminate" at the same char), and til `i` i.e. chars [0..i) we had a match)
    return (!isPri1 & !isPri2) * i;
}
SW_PUBL_API_IMPL inline SwBool swStrIsMatchTilNonPrintA(SwStrAz str1, SwStrAz str2) {
    return swStrMatchTilNonPrintA(str1, str2) > 0;
}


#endif  // SW_CORE_STR_API_H_
