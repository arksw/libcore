#ifndef SW_CORE_CHAR_API_H_
#define SW_CORE_CHAR_API_H_

#include "core_preface.h"

#define swCharIsAnyA(chr,...) SW_TOK_CAT2(swCharIsAnyA_VA,SW_VA_COUNT(__VA_ARGS__))(__VA_ARGS__)
SW_PUBL_API_IMPL inline SwBool swCharIsAnyA_VA1(SwU8 chr, SwU8 a1) { return (chr==a1); }
SW_PUBL_API_IMPL inline SwBool swCharIsAnyA_VA2(SwU8 chr, SwU8 a1, SwU8 a2) { return (chr==a1)|(chr==a2); }
SW_PUBL_API_IMPL inline SwBool swCharIsAnyA_VA3(SwU8 chr, SwU8 a1, SwU8 a2, SwU8 a3) { return (chr==a1)|(chr==a2)|(chr==a3); }
SW_PUBL_API_IMPL inline SwBool swCharIsAnyA_VA4(SwU8 chr, SwU8 a1, SwU8 a2, SwU8 a3, SwU8 a4) { return (chr==a1)|(chr==a2)|(chr==a3)|(chr==a4); }
SW_PUBL_API_IMPL inline SwBool swCharIsAnyA_VA5(SwU8 chr, SwU8 a1, SwU8 a2, SwU8 a3, SwU8 a4, SwU8 a5) { return (chr==a1)|(chr==a2)|(chr==a3)|(chr==a4)|(chr==a5); }
SW_PUBL_API_IMPL inline SwBool swCharIsAnyA_VA6(SwU8 chr, SwU8 a1, SwU8 a2, SwU8 a3, SwU8 a4, SwU8 a5, SwU8 a6) { return (chr==a1)|(chr==a2)|(chr==a3)|(chr==a4)|(chr==a5)|(chr==a6); }
SW_PUBL_API_IMPL inline SwBool swCharIsAnyA_VA7(SwU8 chr, SwU8 a1, SwU8 a2, SwU8 a3, SwU8 a4, SwU8 a5, SwU8 a6, SwU8 a7) { return (chr==a1)|(chr==a2)|(chr==a3)|(chr==a4)|(chr==a5)|(chr==a6)|(chr==a7); }
SW_PUBL_API_IMPL inline SwBool swCharIsAnyA_VA8(SwU8 chr, SwU8 a1, SwU8 a2, SwU8 a3, SwU8 a4, SwU8 a5, SwU8 a6, SwU8 a7, SwU8 a8) { return (chr==a1)|(chr==a2)|(chr==a3)|(chr==a4)|(chr==a5)|(chr==a6)|(chr==a7)|(chr==a8); }
SW_PUBL_API_IMPL inline SwBool swCharInRangeA(SwU8 chr, SwU8 minIncl, SwU8 maxIncl) { SW_DASSERT(minIncl <= maxIncl); return (SwU8)(chr - minIncl) <= (SwU8)(maxIncl - minIncl); }
SW_PUBL_API_IMPL inline SwBool swCharIsSpaceA(SwU8 chr) { return (chr == ' ') | swCharInRangeA(chr, '\t','\r'); }  // equivalent to swCharIsAnyA(chr, ' ','\n','\t','\r','\f','\v')
SW_PUBL_API_IMPL inline SwBool swCharIsPrintA(SwU8 chr) { return swCharInRangeA(chr, '!','~'); }
SW_PUBL_API_IMPL inline SwBool swCharIsDigitA(SwU8 chr) { return swCharInRangeA(chr, '0','9'); }
SW_PUBL_API_IMPL inline SwBool swCharIsDigitHexA(SwU8 chr) { return swCharInRangeA(chr, '0','9') | swCharInRangeA(chr, 'A','F') | swCharInRangeA(chr, 'a','f'); }
SW_PUBL_API_IMPL inline SwBool swCharIsDigitOctA(SwU8 chr) { return swCharInRangeA(chr, '0','7'); }
SW_PUBL_API_IMPL inline SwBool swCharIsDigitBinA(SwU8 chr) { return swCharInRangeA(chr, '0','1'); }
SW_PUBL_API_IMPL inline SwBool swCharIsLowerA(SwU8 chr) { return swCharInRangeA(chr, 'a','z'); }
SW_PUBL_API_IMPL inline SwBool swCharIsUpperA(SwU8 chr) { return swCharInRangeA(chr, 'A','Z'); }
SW_PUBL_API_IMPL inline SwBool swCharIsAlphaA(SwU8 chr) { return swCharIsLowerA(chr) | swCharIsUpperA(chr); }
SW_PUBL_API_IMPL inline SwBool swCharIsAlnumA(SwU8 chr) { return swCharIsAlphaA(chr) | swCharIsDigitA(chr); }
SW_PUBL_API_IMPL inline SwU8 swCharToLowerA(SwU8 chr) { return chr | (0x20 * swCharIsUpperA(chr)); }
SW_PUBL_API_IMPL inline SwU8 swCharToUpperA(SwU8 chr) { return chr ^ (0x20 * swCharIsLowerA(chr)); }
SW_PUBL_API_IMPL inline SwU8 swCharToSwapCaseA(SwU8 chr) { return chr ^ (0x20 * swCharIsAlphaA(chr)); }

#endif  // SW_CORE_CHAR_API_H_
