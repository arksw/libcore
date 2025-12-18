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

SW_PUBL_API_IMPL inline SwU8 swBitClz8(SwU8 u) { return swBitClz32((SwU32)u << 24); }
SW_PUBL_API_IMPL inline SwU8 swBitCtz8(SwU8 u) { return swBitCtz8((SwU32)u); }
SW_PUBL_API_IMPL inline SwU16 swBitClz16(SwU16 u) { return swBitClz16((SwU32)u << 16); }
SW_PUBL_API_IMPL inline SwU16 swBitCtz16(SwU16 u) { return swBitCtz16((SwU32)u); }


// Reference for future implementation (multi-bit read/write straddling): https://fgiesen.wordpress.com/2018/02/19/reading-bits-in-far-too-many-ways-part-1/
// BIT_LAYOUT_DEF[`Fw64LSb0`]: forward indexing in the `U64[]`, starts numbering bit from the `LSb-0` bit in each.
// Schematically, looks like:
// ```
// [    [0],     [1], ...,   [N-1]]
// [    U64,     U64, ...,     U64]
// [63 .. 0, 63 .. 0, ..., 63 .. 0]
// [63 .. 0, 127..64, ..., 64*N..64*(N-1)]
// ```
// For example, bit index 64 would refer to the lowest bit (LSb-0) in the U64 at index 1.
SW_PUBL_API_IMPL inline SwU64 swBitArrReadBitFw64LSb0   (const   SwU64* bit_array, SwU64 bit_index) { return (bit_array[bit_index >> 6] >> (bit_index & 63)) & 0x1; }
SW_PUBL_API_IMPL inline void  swBitArrFlipBitFw64LSb0   (mutable SwU64* bit_array, SwU64 bit_index) { bit_array[bit_index >> 6] ^= ((SwU64)1 << (bit_index & 63)); }
SW_PUBL_API_IMPL inline void  swBitArrTurnOnBitFw64LSb0 (mutable SwU64* bit_array, SwU64 bit_index) { bit_array[bit_index >> 6] |= ((SwU64)1 << (bit_index & 63)); }
SW_PUBL_API_IMPL inline void  swBitArrTurnOffBitFw64LSb0(mutable SwU64* bit_array, SwU64 bit_index) { bit_array[bit_index >> 6] &=~((SwU64)1 << (bit_index & 63)); }
SW_PUBL_API_IMPL inline void  swBitArrWriteBitFw64LSb0  (mutable SwU64* bit_array, SwU64 bit_index, SwU64 bit_value) { SW_DASSERT(bit_value <= 1); SwU64 slot_index = bit_index >> 6; SwU64 bit_offset = bit_index & 63; SwU64 clear_mask = ((SwU64)1 << bit_offset); bit_array[slot_index] = (bit_array[slot_index] & ~clear_mask) | (bit_value << bit_offset);  }

#define swBitOffsetOf(x) __builtin_ctzll(x)
#define swBitSizeOf(x) (sizeof(x)<<3)
#define swBitsetContains(s1,s2) (((s1)&(s2))==(s2))

// macro for constructing bitsets by OR-joining multiple arguments (e.g. ```SwBitset32 vowels = SW_BITSET_VA('A', 1u, 'A','E','I','O','U');```)
#define SW_BITSET_VA1(OFFSET,ONE,i0) (((ONE)<<((i0)-(OFFSET))))
#define SW_BITSET_VA2(OFFSET,ONE,i0,i1) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET))))
#define SW_BITSET_VA3(OFFSET,ONE,i0,i1,i2) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET))))
#define SW_BITSET_VA4(OFFSET,ONE,i0,i1,i2,i3) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET))))
#define SW_BITSET_VA5(OFFSET,ONE,i0,i1,i2,i3,i4) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET)))|((ONE)<<((i4)-(OFFSET))))
#define SW_BITSET_VA6(OFFSET,ONE,i0,i1,i2,i3,i4,i5) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET)))|((ONE)<<((i4)-(OFFSET)))|((ONE)<<((i5)-(OFFSET))))
#define SW_BITSET_VA7(OFFSET,ONE,i0,i1,i2,i3,i4,i5,i6) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET)))|((ONE)<<((i4)-(OFFSET)))|((ONE)<<((i5)-(OFFSET)))|((ONE)<<((i6)-(OFFSET))))
#define SW_BITSET_VA8(OFFSET,ONE,i0,i1,i2,i3,i4,i5,i6,i7) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET)))|((ONE)<<((i4)-(OFFSET)))|((ONE)<<((i5)-(OFFSET)))|((ONE)<<((i6)-(OFFSET)))|((ONE)<<((i7)-(OFFSET))))
#define SW_BITSET_VA9(OFFSET,ONE,i0,i1,i2,i3,i4,i5,i6,i7,i8) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET)))|((ONE)<<((i4)-(OFFSET)))|((ONE)<<((i5)-(OFFSET)))|((ONE)<<((i6)-(OFFSET)))|((ONE)<<((i7)-(OFFSET)))|((ONE)<<((i8)-(OFFSET))))
#define SW_BITSET_VA10(OFFSET,ONE,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET)))|((ONE)<<((i4)-(OFFSET)))|((ONE)<<((i5)-(OFFSET)))|((ONE)<<((i6)-(OFFSET)))|((ONE)<<((i7)-(OFFSET)))|((ONE)<<((i8)-(OFFSET)))|((ONE)<<((i9)-(OFFSET))))
#define SW_BITSET_VA11(OFFSET,ONE,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET)))|((ONE)<<((i4)-(OFFSET)))|((ONE)<<((i5)-(OFFSET)))|((ONE)<<((i6)-(OFFSET)))|((ONE)<<((i7)-(OFFSET)))|((ONE)<<((i8)-(OFFSET)))|((ONE)<<((i9)-(OFFSET)))|((ONE)<<((i10)-(OFFSET))))
#define SW_BITSET_VA12(OFFSET,ONE,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET)))|((ONE)<<((i4)-(OFFSET)))|((ONE)<<((i5)-(OFFSET)))|((ONE)<<((i6)-(OFFSET)))|((ONE)<<((i7)-(OFFSET)))|((ONE)<<((i8)-(OFFSET)))|((ONE)<<((i9)-(OFFSET)))|((ONE)<<((i10)-(OFFSET)))|((ONE)<<((i11)-(OFFSET))))
#define SW_BITSET_VA13(OFFSET,ONE,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET)))|((ONE)<<((i4)-(OFFSET)))|((ONE)<<((i5)-(OFFSET)))|((ONE)<<((i6)-(OFFSET)))|((ONE)<<((i7)-(OFFSET)))|((ONE)<<((i8)-(OFFSET)))|((ONE)<<((i9)-(OFFSET)))|((ONE)<<((i10)-(OFFSET)))|((ONE)<<((i11)-(OFFSET)))|((ONE)<<((i12)-(OFFSET))))
#define SW_BITSET_VA14(OFFSET,ONE,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET)))|((ONE)<<((i4)-(OFFSET)))|((ONE)<<((i5)-(OFFSET)))|((ONE)<<((i6)-(OFFSET)))|((ONE)<<((i7)-(OFFSET)))|((ONE)<<((i8)-(OFFSET)))|((ONE)<<((i9)-(OFFSET)))|((ONE)<<((i10)-(OFFSET)))|((ONE)<<((i11)-(OFFSET)))|((ONE)<<((i12)-(OFFSET)))|((ONE)<<((i13)-(OFFSET))))
#define SW_BITSET_VA15(OFFSET,ONE,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET)))|((ONE)<<((i4)-(OFFSET)))|((ONE)<<((i5)-(OFFSET)))|((ONE)<<((i6)-(OFFSET)))|((ONE)<<((i7)-(OFFSET)))|((ONE)<<((i8)-(OFFSET)))|((ONE)<<((i9)-(OFFSET)))|((ONE)<<((i10)-(OFFSET)))|((ONE)<<((i11)-(OFFSET)))|((ONE)<<((i12)-(OFFSET)))|((ONE)<<((i13)-(OFFSET)))|((ONE)<<((i14)-(OFFSET))))
#define SW_BITSET_VA16(OFFSET,ONE,i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15) (((ONE)<<((i0)-(OFFSET)))|((ONE)<<((i1)-(OFFSET)))|((ONE)<<((i2)-(OFFSET)))|((ONE)<<((i3)-(OFFSET)))|((ONE)<<((i4)-(OFFSET)))|((ONE)<<((i5)-(OFFSET)))|((ONE)<<((i6)-(OFFSET)))|((ONE)<<((i7)-(OFFSET)))|((ONE)<<((i8)-(OFFSET)))|((ONE)<<((i9)-(OFFSET)))|((ONE)<<((i10)-(OFFSET)))|((ONE)<<((i11)-(OFFSET)))|((ONE)<<((i12)-(OFFSET)))|((ONE)<<((i13)-(OFFSET)))|((ONE)<<((i14)-(OFFSET)))|((ONE)<<((i15)-(OFFSET))))
#define SW_BITSET_VA(OFFSET,ONE,...) SW_TOK_CAT2(SW_BITSET_VA,SW_VA_COUNT(__VA_ARGS__))(__VA_ARGS__)

#define SW_BITSET8(...)  SW_BITSET_VA(0u, ((SwU8) 1), __VA_ARGS__)
#define SW_BITSET16(...) SW_BITSET_VA(0u, ((SwU16)1), __VA_ARGS__)
#define SW_BITSET32(...) SW_BITSET_VA(0u, ((SwU32)1), __VA_ARGS__)
#define SW_BITSET64(...) SW_BITSET_VA(0u, ((SwU64)1), __VA_ARGS__)

#endif // SW_CORE_BIT_API_H_
