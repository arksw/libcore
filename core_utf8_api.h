#ifndef SW_CORE_UTF8_API_H_
#define SW_CORE_UTF8_API_H_

#include "core_preface.h"
#include "core_bit_api.h"
#include "core_int_api.h"

SW_PUBL_API_IMPL inline SwBool8 swByteMatchHi2(SwU8 b, SwU8 pat2) { SW_DASSERT(pat2 <= 0b11); return (b >> 6) == pat2; }
SW_PUBL_API_IMPL inline SwBool8 swByteIsContinUtf8(SwU8 b) { return swByteMatchHi2(b, 0b10); } // 0b10xx_xxxx => Continuation Byte (past a Codept Begin Byte)
SW_PUBL_API_IMPL inline SwBool8 swByteIsBoCodeptUtf8(SwU8 b) { return !swByteIsContinUtf8(b); }  // Regular Ascii (< 128) | Codept Begin Byte (0b11xx_xxxx)
SW_PUBL_API_IMPL inline SwU32   swByteGetCodeptByteLenUtf8(SwU8 b) { return (b < 0xC0) ? 1 : swBitClz32((unsigned)(~b) << 24); /* i.e. count leading ones */ } // Continuation Byte & Regular Ascii are considered as having ByteLen = 1

SW_PUBL_API_IMPL inline SwBool32 swCodeptIsValid(SwCodeptUtf32 codept) { return (codept <= 0xD7FF) | swIntInRangeU32(codept, 0xE000, 0x10FFFF); }  // Within range & non surrogate pair
SW_PUBL_API_IMPL inline SwU32    swCodeptGetByteLenUtf8(SwU32 c) { return (c <= 0x7F) ? 1 : (c <= 0x7FF) ? 2 : (c <= 0xFFFF) ? 3 : 4; } // Invalid codepts still return hypothetical n bytes


#endif // SW_CORE_UTF8_API_H_
