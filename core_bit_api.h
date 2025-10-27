#ifndef SW_CORE_BIT_API_H_
#define SW_CORE_BIT_API_H_

#include "core_preface.h"

typedef SwU8  SwBitset8;
typedef SwU16 SwBitset16;
typedef SwU32 SwBitset32;
typedef SwU64 SwBitset64;

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

#define swBitOffsetOf(x) __builtin_ctzll(x)
#define swBitSizeOf(x) (sizeof(x)<<3)
#define swBitsetContains(s1,s2) (((s1)&(s2))==(s2))

#define SW_BITSET_VA1(ONE,OFF,i0) ((ONE<<((i0)-(OFF))))
#define SW_BITSET_VA2(ONE,OFF,i0,i1) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF))))
#define SW_BITSET_VA3(ONE,OFF,i0,i1,i2) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF))))
#define SW_BITSET_VA4(ONE,OFF,i0,i1,i2,i3) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF))))
#define SW_BITSET_VA5(ONE,OFF,i0,i1,i2,i3,i4) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF)))|(ONE<<((i4)-(OFF))))
#define SW_BITSET_VA6(ONE,OFF,i0,i1,i2,i3,i4,i5) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF)))|(ONE<<((i4)-(OFF)))|(ONE<<((i5)-(OFF))))
#define SW_BITSET_VA7(ONE,OFF,i0,i1,i2,i3,i4,i5,i6) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF)))|(ONE<<((i4)-(OFF)))|(ONE<<((i5)-(OFF)))|(ONE<<((i6)-(OFF))))
#define SW_BITSET_VA8(ONE,OFF,i0,i1,i2,i3,i4,i5,i6,i7) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF)))|(ONE<<((i4)-(OFF)))|(ONE<<((i5)-(OFF)))|(ONE<<((i6)-(OFF)))|(ONE<<((i7)-(OFF))))
#define SW_BITSET_VA9(ONE,OFF,i0,i1,i2,i3,i4,i5,i6,i7,i8) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF)))|(ONE<<((i4)-(OFF)))|(ONE<<((i5)-(OFF)))|(ONE<<((i6)-(OFF)))|(ONE<<((i7)-(OFF)))|(ONE<<((i8)-(OFF))))
#define SW_BITSET_VA10(ONE,OFF,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF)))|(ONE<<((i4)-(OFF)))|(ONE<<((i5)-(OFF)))|(ONE<<((i6)-(OFF)))|(ONE<<((i7)-(OFF)))|(ONE<<((i8)-(OFF)))|(ONE<<((i9)-(OFF))))
#define SW_BITSET_VA11(ONE,OFF,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF)))|(ONE<<((i4)-(OFF)))|(ONE<<((i5)-(OFF)))|(ONE<<((i6)-(OFF)))|(ONE<<((i7)-(OFF)))|(ONE<<((i8)-(OFF)))|(ONE<<((i9)-(OFF)))|(ONE<<((i10)-(OFF))))
#define SW_BITSET_VA12(ONE,OFF,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF)))|(ONE<<((i4)-(OFF)))|(ONE<<((i5)-(OFF)))|(ONE<<((i6)-(OFF)))|(ONE<<((i7)-(OFF)))|(ONE<<((i8)-(OFF)))|(ONE<<((i9)-(OFF)))|(ONE<<((i10)-(OFF)))|(ONE<<((i11)-(OFF))))
#define SW_BITSET_VA13(ONE,OFF,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF)))|(ONE<<((i4)-(OFF)))|(ONE<<((i5)-(OFF)))|(ONE<<((i6)-(OFF)))|(ONE<<((i7)-(OFF)))|(ONE<<((i8)-(OFF)))|(ONE<<((i9)-(OFF)))|(ONE<<((i10)-(OFF)))|(ONE<<((i11)-(OFF)))|(ONE<<((i12)-(OFF))))
#define SW_BITSET_VA14(ONE,OFF,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF)))|(ONE<<((i4)-(OFF)))|(ONE<<((i5)-(OFF)))|(ONE<<((i6)-(OFF)))|(ONE<<((i7)-(OFF)))|(ONE<<((i8)-(OFF)))|(ONE<<((i9)-(OFF)))|(ONE<<((i10)-(OFF)))|(ONE<<((i11)-(OFF)))|(ONE<<((i12)-(OFF)))|(ONE<<((i13)-(OFF))))
#define SW_BITSET_VA15(ONE,OFF,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF)))|(ONE<<((i4)-(OFF)))|(ONE<<((i5)-(OFF)))|(ONE<<((i6)-(OFF)))|(ONE<<((i7)-(OFF)))|(ONE<<((i8)-(OFF)))|(ONE<<((i9)-(OFF)))|(ONE<<((i10)-(OFF)))|(ONE<<((i11)-(OFF)))|(ONE<<((i12)-(OFF)))|(ONE<<((i13)-(OFF)))|(ONE<<((i14)-(OFF))))
#define SW_BITSET_VA16(ONE,OFF,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15) ((ONE<<((i0)-(OFF)))|(ONE<<((i1)-(OFF)))|(ONE<<((i2)-(OFF)))|(ONE<<((i3)-(OFF)))|(ONE<<((i4)-(OFF)))|(ONE<<((i5)-(OFF)))|(ONE<<((i6)-(OFF)))|(ONE<<((i7)-(OFF)))|(ONE<<((i8)-(OFF)))|(ONE<<((i9)-(OFF)))|(ONE<<((i10)-(OFF)))|(ONE<<((i11)-(OFF)))|(ONE<<((i12)-(OFF)))|(ONE<<((i13)-(OFF)))|(ONE<<((i14)-(OFF)))|(ONE<<((i15)-(OFF))))
#define SW_BITSET_VA(ONE,OFF,...) SW_TOK_CAT2(SW_BITSET_VA,SW_VA_COUNT(__VA_ARGS__))(__VA_ARGS__)

#define SW_BITSET8(...) SW_BITSET_VA(((SwU8)1),0,__VA_ARGS__)
#define SW_BITSET16(...) SW_BITSET_VA(((SwU16)1),0,__VA_ARGS__)
#define SW_BITSET32(...) SW_BITSET_VA(((SwU32)1),0,__VA_ARGS__)
#define SW_BITSET64(...) SW_BITSET_VA(((SwU64)1),0,__VA_ARGS__)

#endif // SW_BIT_API_H_
