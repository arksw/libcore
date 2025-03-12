#ifndef SW_CORE_BIT_API_H_
#define SW_CORE_BIT_API_H_

#include "core_preface.h"

typedef SwU8  SwBitset8;
typedef SwU16 SwBitset16;
typedef SwU32 SwBitset32;
typedef SwU64 SwBitset64;

#define swBitSizeOf(x) (sizeof(x)<<3)
#define swBitsetContains(s1,s2) (((s1)&(s2))==(s2))

SW_PUBL_API_IMPL inline SwU32 swBitLo32(SwU32 N) { return (~((SwU32)0)) >> (32 - N); }
SW_PUBL_API_IMPL inline SwU32 swBitHi32(SwU32 N) { return (~((SwU32)0)) << (32 - N); }
SW_PUBL_API_IMPL inline SwU32 swBitSum32(SwU32 u) { return __builtin_popcount(u); }
SW_PUBL_API_IMPL inline SwU32 swBitClz32(SwU32 u) { SW_DASSERT(u != 0); return __builtin_clz(u); }
SW_PUBL_API_IMPL inline SwU32 swBitCtz32(SwU32 u) { SW_DASSERT(u != 0); return __builtin_ctz(u); }
SW_PUBL_API_IMPL inline SwU32 swBitPackBE32(SwU8 b24,SwU8 b16,SwU8 b08,SwU8 b00) { return ((SwU32)b24<<24)|((SwU32)b16<<16)|((SwU32)b08<<8)|(SwU32)b00; }
SW_PUBL_API_IMPL inline SwU32 swBitPackLE32(SwU8 b00,SwU8 b08,SwU8 b16,SwU8 b24) { return ((SwU32)b24<<24)|((SwU32)b16<<16)|((SwU32)b08<<8)|(SwU32)b00; }
SW_PUBL_API_IMPL inline SwU32 swBitReadBE32(const SwU8* bp) { return swBitPackBE32(bp[0],bp[1],bp[2],bp[3]); }
SW_PUBL_API_IMPL inline SwU32 swBitReadLE32(const SwU8* bp) { return swBitPackLE32(bp[0],bp[1],bp[2],bp[3]); }
SW_PUBL_API_IMPL inline void swBitWriteBE32(mutable SwU8* bp, SwU32 u) { bp[0]=(u>>24); bp[1]=(u>>16)&0xFF; bp[2]=(u>>8)&0xFF; bp[3]=u&0xFF; }
SW_PUBL_API_IMPL inline void swBitWriteLE32(mutable SwU8* bp, SwU32 u) { bp[3]=(u>>24); bp[2]=(u>>16)&0xFF; bp[1]=(u>>8)&0xFF; bp[0]=u&0xFF; }

SW_PUBL_API_IMPL inline SwU64 swBitLo64(SwU64 N) { return (~((SwU64)0)) >> (64 - N); }
SW_PUBL_API_IMPL inline SwU64 swBitHi64(SwU64 N) { return (~((SwU64)0)) << (64 - N); }
SW_PUBL_API_IMPL inline SwUsz swBitSum64(SwU64 u) { return __builtin_popcountll(u); }
SW_PUBL_API_IMPL inline SwUsz swBitClz64(SwU64 u) { SW_DASSERT(u != 0); return __builtin_clzll(u); }
SW_PUBL_API_IMPL inline SwUsz swBitCtz64(SwU64 u) { SW_DASSERT(u != 0); return __builtin_ctzll(u); }
SW_PUBL_API_IMPL inline SwU64 swBitPackBE64(SwU8 b56,SwU8 b48,SwU8 b40,SwU8 b32,SwU8 b24,SwU8 b16,SwU8 b08,SwU8 b00) { return ((SwU64)b56<<56)|((SwU64)b48<<48)|((SwU64)b40<<40)|((SwU64)b32<<32)|((SwU64)b24<<24)|((SwU64)b16<<16)|((SwU64)b08<<8)|(SwU64)b00; }
SW_PUBL_API_IMPL inline SwU64 swBitPackLE64(SwU8 b00,SwU8 b08,SwU8 b16,SwU8 b24,SwU8 b32,SwU8 b40,SwU8 b48,SwU8 b56) { return ((SwU64)b56<<56)|((SwU64)b48<<48)|((SwU64)b40<<40)|((SwU64)b32<<32)|((SwU64)b24<<24)|((SwU64)b16<<16)|((SwU64)b08<<8)|(SwU64)b00; }
SW_PUBL_API_IMPL inline SwU64 swBitReadBE64(const SwU8* bp) { return swBitPackBE64(bp[0],bp[1],bp[2],bp[3],bp[4],bp[5],bp[6],bp[7]); }
SW_PUBL_API_IMPL inline SwU64 swBitReadLE64(const SwU8* bp) { return swBitPackLE64(bp[0],bp[1],bp[2],bp[3],bp[4],bp[5],bp[6],bp[7]); }
SW_PUBL_API_IMPL inline void swBitWriteBE64(mutable SwU8* bp, SwU64 u) { bp[0]=(u>>56); bp[1]=(u>>48)&0xFF; bp[2]=(u>>40)&0xFF; bp[3]=(u>>32)&0xFF; bp[4]=(u>>24)&0xFF; bp[5]=(u>>16)&0xFF; bp[6]=(u>>8)&0xFF; bp[7]=u&0xFF; }
SW_PUBL_API_IMPL inline void swBitWriteLE64(mutable SwU8* bp, SwU64 u) { bp[7]=(u>>56); bp[6]=(u>>48)&0xFF; bp[5]=(u>>40)&0xFF; bp[4]=(u>>32)&0xFF; bp[3]=(u>>24)&0xFF; bp[2]=(u>>16)&0xFF; bp[1]=(u>>8)&0xFF; bp[0]=u&0xFF; }


// Reference for future implementation https://fgiesen.wordpress.com/2018/02/19/reading-bits-in-far-too-many-ways-part-1/
// The `Fw64LSb0` bit layout is forward indexing in the `U64[]` and starts numbering bit from the `LSb-0` bit in each. Schematically, it looks like:
// [    [0],     [1], ...,   [N-1]]
// [    U64,     U64, ...,     U64]
// [63 .. 0, 63 .. 0, ..., 63 .. 0]
// [63 .. 0, 127..64, ..., N*64..(N-1)*64]
// For example, bit index 64 would refer to the lowest bit (LSb-0) in the U64 at index 1.
SW_PUBL_API_IMPL inline SwBool64 swBitGetFw64LSb0(SwU64 bitSize, const SwU64* bitArr64s, SwU64 bitIndex) { SW_DASSERT(bitArr64s && bitIndex < bitSize); return (bitArr64s[bitIndex >> 6] >> (bitIndex & 63)); }
SW_PUBL_API_IMPL inline void     swBitFlipFw64LSb0(SwU64 bitSize, mutable SwU64* bitArr64s, SwU64 bitIndex) { SW_DASSERT(bitArr64s && bitIndex < bitSize); bitArr64s[bitIndex >> 6] ^= ((SwU64)1 << (bitIndex & 63)); }
SW_PUBL_API_IMPL inline void     swBitSet1Fw64LSb0(SwU64 bitSize, mutable SwU64* bitArr64s, SwU64 bitIndex) { SW_DASSERT(bitArr64s && bitIndex < bitSize); bitArr64s[bitIndex >> 6] |= ((SwU64)1 << (bitIndex & 63)); }
SW_PUBL_API_IMPL inline void     swBitSet0Fw64LSb0(SwU64 bitSize, mutable SwU64* bitArr64s, SwU64 bitIndex) { SW_DASSERT(bitArr64s && bitIndex < bitSize); bitArr64s[bitIndex >> 6] &= ~((SwU64)1 << (bitIndex & 63)); }
SW_PUBL_API_IMPL inline void     swBitSetFw64LSb0(SwU64 bitSize, mutable SwU64* bitArr64s, SwU64 bitIndex, SwU64 bitValue) {
    SW_DASSERT(bitArr64s && bitIndex < bitSize);
    SwU64 slotIndex = bitIndex >> 6;
    SwU64 bitOffset = bitIndex & 63;
    SwU64 clearMask = ((SwU64)1 << bitOffset);
    bitArr64s[slotIndex] = (bitArr64s[slotIndex] & ~clearMask) | (bitValue << bitOffset); 
}

#endif // SW_BIT_API_H_
