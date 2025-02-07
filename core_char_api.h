#ifndef SW_CORE_CHAR_API_H_
#define SW_CORE_CHAR_API_H_

#include "core_preface.h"

SW_ENSURE(' ' == 0x20 && '!' == 0x21 && '~' == 0x7E, "ensure char literals are ASCII");  // @FIXME: we can make this exhaustive

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
SW_PUBL_API_IMPL inline SwBool swCharIsNonPrintA(SwU8 chr) { return (chr <= ' ') | (chr == 0x7F); }  // low ASCII (such as control characters) and DEL are non printable
SW_PUBL_API_IMPL inline SwBool swCharIsPrintA(SwU8 chr) { return swCharInRangeA(chr, '!','~'); }     // printable ASCII range (note how this is exactly the complementary set of the above if and only if the input is guaranteed to be in the ASCII U7 range)
SW_PUBL_API_IMPL inline SwBool swByteIsApproxPrint(SwU8 b) { return !swCharIsNonPrintA(b); }         // technically some bytes could even be invalid UTF8 (or non printable UTF8) but, here, anything not NonPrintA is considered "approximately printable"
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
SW_PUBL_API_IMPL inline SwU8 swToCharDigitA(SwBound(SwU8,<10) d) { SW_DASSERT(d < 10); return ('0' + d); }
SW_PUBL_API_IMPL inline SwU8 swToCharDigitHexUpperA(SwBound(SwU8,<=0xF) x) { SW_DASSERT(x <= 0xF); return (x < 10) ? ('0' + x) : ('A' + (x-10)); }
SW_PUBL_API_IMPL inline SwU8 swToCharDigitHexLowerA(SwBound(SwU8,<=0xF) x) { SW_DASSERT(x <= 0xF); return (x < 10) ? ('0' + x) : ('a' + (x-10)); }
SW_PUBL_API_IMPL inline SwStr4bA swByteToEscapedCharStr4bAz(SwU8 b) {
    SwStr4bA escChar = {0};
    if (swCharIsPrintA(b)) {
        escChar.str[0] = b;
    } else {
        // non printable chars are escaped (printed as hex with leading slash)
        escChar.str[0] = '\\';
        // few exception for octals and common control characters
        switch (b) {
        case 0x00: { escChar.str[1] = '0'; } break;  // (zero/nul byte)
        case 0x01: { escChar.str[1] = '1'; } break;
        case 0x02: { escChar.str[1] = '2'; } break;
        case 0x03: { escChar.str[1] = '3'; } break;
        case 0x04: { escChar.str[1] = '4'; } break;
        case 0x05: { escChar.str[1] = '5'; } break;
        case 0x06: { escChar.str[1] = '6'; } break;
        case 0x07: { escChar.str[1] = 'a'; } break; // (alert/audible bell)
        case 0x08: { escChar.str[1] = 'b'; } break; // (backspace)
        case 0x09: { escChar.str[1] = 't'; } break; // (horizontal tab)
        case 0x0A: { escChar.str[1] = 'n'; } break; // (new line / line feed)
        case 0x0B: { escChar.str[1] = 'v'; } break; // (vertical tab)
        case 0x0C: { escChar.str[1] = 'f'; } break; // (form feed)
        case 0x0D: { escChar.str[1] = 'r'; } break; // (carriage return)
        case 0x1B: { escChar.str[1] = 'e'; } break; // (escape)
        default: {
            escChar.str[1] = 'x';
            escChar.str[2] = swToCharDigitHexUpperA(b >> 4);
            escChar.str[3] = swToCharDigitHexUpperA(b & 0xF);
        } break;
        }
    }
    return escChar;
}

#endif  // SW_CORE_CHAR_API_H_
