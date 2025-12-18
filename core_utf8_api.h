#ifndef SW_CORE_UTF8_API_H_
#define SW_CORE_UTF8_API_H_

#include "core_preface.h"
#include "core_bit_api.h"
#include "core_int_api.h"

SW_PUBL_API_IMPL inline SwBool8 swByteMatchHi2(SwU8 b, SwU8 pat2) { SW_DASSERT(pat2 <= 0b11); return (b >> 6) == pat2; }
SW_PUBL_API_IMPL inline SwBool8 swByteIsContinUtf8(SwU8 b) { return swByteMatchHi2(b, 0b10); }  // 0b10xx_xxxx => continuation byte (past a codept leading byte)
SW_PUBL_API_IMPL inline SwBool8 swByteIsBoCodeptUtf8(SwU8 b) { return !swByteIsContinUtf8(b); } // 0b11xx_xxxx => begin byte (of a multi-byte utf8) UNION regular ascii (< 128)
SW_PUBL_API_IMPL inline SwU32   swByteGetCodeptByteLenUtf8(SwU8 b) { return (b < 0xC0) ? 1 : swBitClz8(~b | 1); /* i.e. count leading ones capped to 7 (to prevent propagating zero) */ } // Continuation Byte & Regular Ascii are considered as having ByteLen = 1, Invalid BoCodept bytes will have > 4 len

SW_PUBL_API_IMPL inline SwU32    swCodeptGetByteLenUtf8(SwU32 c) { return (c <= 0x7F) ? 1 : (c <= 0x7FF) ? 2 : (c <= 0xFFFF) ? 3 : 4; } // invalid codepts still return hypothetical (minimum) n bytes needed to encode them
SW_PUBL_API_IMPL inline SwBool32 swCodeptIsValidUtf32(SwU32 codept) { return (codept <= 0xD7FF) | swIntInRangeU32(codept, 0xE000, 0x10FFFF); } // within range & non surrogate pair
SW_PUBL_API_IMPL inline SwBool32 swCodeptIsValidUtf8(SwU32 codept, SwU32 n_utf8_bytes_used_to_encode_codept, SwU32 min_n_utf8_bytes_req_to_encode_codept) { SW_DASSERT(min_n_utf8_bytes_req_to_encode_codept == swCodeptGetByteLenUtf8(codept)); return swCodeptIsValidUtf32(codept) & (n_utf8_bytes_used_to_encode_codept == min_n_utf8_bytes_req_to_encode_codept); } // reject surrogates and out of range (> 0x10FFFF), and non-minimal (using the minimum n of bytes needed to encode the `codept` value in utf8)


#endif // SW_CORE_UTF8_API_H_
