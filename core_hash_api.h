#ifndef SW_CORE_HASH_API_H_
#define SW_CORE_HASH_API_H_

#include "core_preface.h"
#include "core_str_api.h"

// Opaque Hash64, guaranteed unsignedness and hash function agnostic
typedef SwU64 SwHash64;
// Opaque Hash32, guaranteed unsignedness and hash function agnostic
typedef SwU32 SwHash32;


//
// FNV1a-32
//
#define SW_HASH_OFFSET_FNV1A32 0x811C9DC5u
#define SW_HASH_PRIME_FNV1A32 0x1000193u

typedef struct SwHashFnv1a32 {
    SwU32 asU32;
#if SWCC_DEBUG
    SwU32 initCheck;
#endif
} SwHashFnv1a32;

SW_PUBL_API_DECL SwHashFnv1a32 swHashFnv1a32(void);
SW_PUBL_API_DECL void          swHashByteFnv1a32(mutable SwHashFnv1a32* hashMut, SwU8 byte);
SW_PUBL_API_DECL SwHashFnv1a32 swHashBytesFnv1a32(SwUsz nBytes, const SwU8* bytes);
SW_PUBL_API_DECL SwHashFnv1a32 swHashStr8zFnv1a32(const SwStrUtf8z str8z);
#define swHashStr8Fnv1a32 swHashBytesFnv1a32

SW_PUBL_API_IMPL inline SwHashFnv1a32 swHashFnv1a32(void) {
    return (SwHashFnv1a32){
        SW_HASH_OFFSET_FNV1A32,
    #if SWCC_DEBUG
        .initCheck = SW_HASH_OFFSET_FNV1A32,
    #endif
    };
}
SW_PUBL_API_IMPL inline void swHashByteFnv1a32(mutable SwHashFnv1a32* hashMut, SwU8 byte) {
    SW_DASSERT(hashMut->initCheck == SW_HASH_OFFSET_FNV1A32);
    hashMut->asU32 ^= (SwU32)byte;
    hashMut->asU32 *= SW_HASH_PRIME_FNV1A32;
}
SW_PUBL_API_IMPL inline SwHashFnv1a32 swHashBytesFnv1a32(SwUsz nBytes, const SwU8* bytes) {
    SwHashFnv1a32 hash = swHashFnv1a32();
    for (SwUsz i = 0; i < nBytes; ++i) {
        swHashByteFnv1a32(&hash, bytes[i]);
    }
    return hash;
}
SW_PUBL_API_IMPL inline SwHashFnv1a32 swHashStr8zFnv1a32(const SwStrUtf8z str) {
    SwHashFnv1a32 hash = swHashFnv1a32();
    for (const SwU8* ptr = str; *ptr != 0; ++ptr) {
        swHashByteFnv1a32(&hash, *ptr);
    }
    return hash;
}

//
// FNV1a-64
//
#define SW_HASH_OFFSET_FNV1A64 0xCBF29CE484222325ull
#define SW_HASH_PRIME_FNV1A64 0x100000001B3ull

typedef struct SwHashFnv1a64 {
    SwU64 asU64;
#if SWCC_DEBUG
    SwU64 initCheck;
#endif
} SwHashFnv1a64;

SW_PUBL_API_DECL SwHashFnv1a64 swHashFnv1a64(void);
SW_PUBL_API_DECL void          swHashByteFnv1a64(mutable SwHashFnv1a64* hashMut, SwU8 byte);
SW_PUBL_API_DECL SwHashFnv1a64 swHashBytesFnv1a64(SwUsz nBytes, const SwU8* bytes);
SW_PUBL_API_DECL SwHashFnv1a64 swHashStr8zFnv1a64(const SwStrUtf8z str8z);
#define swHashStr8Fnv1a64 swHashBytesFnv1a64

SW_PUBL_API_IMPL inline SwHashFnv1a64 swHashFnv1a64(void) {
    return (SwHashFnv1a64){
        SW_HASH_OFFSET_FNV1A64,
    #if SWCC_DEBUG
        .initCheck = SW_HASH_OFFSET_FNV1A64,
    #endif
    };
}
SW_PUBL_API_IMPL inline void swHashByteFnv1a64(mutable SwHashFnv1a64* hashMut, SwU8 byte) {
    SW_DASSERT(hashMut->initCheck == SW_HASH_OFFSET_FNV1A64);
    SwU64 h = hashMut->asU64 ^ (SwU64)byte;
    // this is supposedly faster than 64-bits imul with fnv1a prime (according to fnv1a website)
    h += (h<<1)+(h<<4)+(h<<5)+(h<<7)+(h<<8)+(h<<40);
    // asserting it is equivalent to the imul mentioned because paranoia
    SW_DASSERT(((hashMut->asU64 ^ (SwU64)byte) * SW_HASH_PRIME_FNV1A64) == h);
    hashMut->asU64 = h;
}
SW_PUBL_API_IMPL inline SwHashFnv1a64 swHashBytesFnv1a64(SwUsz nBytes, const SwU8* bytes) {
    SwHashFnv1a64 hash = swHashFnv1a64();
    for (SwUsz i = 0; i < nBytes; ++i) {
        swHashByteFnv1a64(&hash, bytes[i]);
    }
    return hash;
}
SW_PUBL_API_IMPL inline SwHashFnv1a64 swHashStr8zFnv1a64(const SwStrUtf8z str) {
    SwHashFnv1a64 hash = swHashFnv1a64();
    for (const SwU8* ptr = str; *ptr != 0; ++ptr) {
        swHashByteFnv1a64(&hash, *ptr);
    }
    return hash;
}

//
// FNV1a-N
//

// Xor-Folding is a simple process to obtain `N`-bits hashes from their power of two counterparts (used for e.g. to reduce a hash64 to a hash48)
SW_PUBL_API_IMPL inline SwBound(SwHash64, swUMax64(N)) swHashXorFold64(SwHash64 hash, SwU64 N_BitsTarget) { SW_DASSERT(N_BitsTarget > 0 && N_BitsTarget < 64); SwU64 hiBits = hash >> (64 - N_BitsTarget); return (hiBits ^ hash) & swBitLo64(N_BitsTarget); }
SW_PUBL_API_IMPL inline SwBound(SwHash32, swUMax32(N)) swHashXorFold32(SwHash32 hash, SwU32 N_BitsTarget) { SW_DASSERT(N_BitsTarget > 0 && N_BitsTarget < 32); SwU64 hiBits = hash >> (32 - N_BitsTarget); return (hiBits ^ hash) & swBitLo32(N_BitsTarget); }


#endif  // SW_CORE_HASH_API_H_
