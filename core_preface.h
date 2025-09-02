#ifndef SW_CORE_PREFACE_H_
#define SW_CORE_PREFACE_H_

#include "core_ccflags.h"

// For documentation & easy grep
#define SW_PUBL_API_DECL static
#define SW_PUBL_API_IMPL static
#define SW_PRIV_API_DECL static
#define SW_PRIV_API_IMPL static

// Used to make explicit the default behavior of C switch arms. Usage of fallthrough is generally discouraged, but if needed, explicit is better than implicit.
#define SW_FALLTHROUGH

// The counterpart to the `const` keyword, it exists for explicitly signaling a mutation. Its use is recommended only within a function's signature. 
#define mutable

// Preprocessor Macros
#define SW__TOK_CAT2(a,b) a##b
#define SW_TOK_CAT2(a,b) SW__TOK_CAT2(a,b)
#define SW__TOK_STR(a) #a
#define SW_TOK_STR(a) SW__TOK_STR(a)
// @FIXME: ideally figure out a way for VA_COUNT to return 0 if no args are provided!
#define SW__VA_COUNT(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,count,...) count
#define SW_VA_COUNT(...) SW__VA_COUNT(__VA_ARGS__ __VA_OPT__(,) 16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#define SW_ARR_COUNT(arr) (sizeof(arr)/sizeof((arr)[0]))
#define SW_OFFSET_OF(T,member) ((SwUsz)((SwU8*)&((T*)0)->member - (SwU8*)0))

// Assert Macros
#define SW_LIKELY(x)   (__builtin_expect(!!(x), 1))
#define SW_UNLIKELY(x) (__builtin_expect(!!(x), 0))

#define SW__TRAP() __builtin_trap()
#define SW_ASSERT(cond,...) do { if SW_UNLIKELY(!(cond)) { __builtin_printf(__FILE__ ":" SW_TOK_STR(__LINE__) ":0 ::: %s ::: ASSERT( " #cond " )\n", __func__); __builtin_printf("  " __VA_ARGS__); __builtin_printf("\n\n"); SW__TRAP(); } } while (0)
#define SW_PANIC(...) SW_ASSERT(0,__VA_ARGS__)
#define SW_UNREACHABLE(...) SW_ASSERT(0,__VA_ARGS__)
#if SWCC_DEBUG
#define SW_DASSERT(cond,...) SW_ASSERT(cond, __VA_ARGS__)
#define SW_DEXPAND(...) __VA_ARGS__
#define SW_DEXPAND_OR_1st(arg1st,...) __VA_ARGS__
#else
#define SW_DASSERT(cond,...) (void)0
#define SW_DEXPAND(...)
#define SW_DEXPAND_OR_1st(arg1st,...) arg1st
#endif
#define SW_ENSURE(cond,...) typedef int SW_TOK_CAT2(sw__ensure_line_,__LINE__)[(cond) ? 1 : -1]
#define SW_IMPLY(cond,then) ((!(cond)) || (then))
#define SW_BIMPLY(propA,propB) (SW_IMPLY(propA,propB) && SW_IMPLY(propB,propA))

// Constants
#if __clang__ // clang complains about void* cast, but literal 0 is somehow exempted
#define swNULL (0)
#else
#define swNULL ((void*)0)
#endif
enum { swFALSE = 0, swTRUE = 1 };
enum { swFAIL  = 0, swSUCC = 1 };

// Data Types
#define SwSlice(T,...) T*
#define SwOr(T,...) T
#define SwOrZero(T,...) SwOr(T,(T)0)
#define SwBound(T,...) T

typedef unsigned char      SwU8;  SW_ENSURE(sizeof(SwU8) == 1);
typedef   signed char      SwI8;  SW_ENSURE(sizeof(SwI8) == 1);
typedef unsigned short     SwU16; SW_ENSURE(sizeof(SwU16) == 2);
typedef   signed short     SwI16; SW_ENSURE(sizeof(SwI16) == 2);
typedef unsigned int       SwU32; SW_ENSURE(sizeof(SwU32) == 4);
typedef   signed int       SwI32; SW_ENSURE(sizeof(SwI32) == 4);
typedef unsigned long long SwU64; SW_ENSURE(sizeof(SwU64) == 8);
typedef   signed long long SwI64; SW_ENSURE(sizeof(SwI64) == 8);
typedef SwU64  SwUsz; SW_ENSURE(sizeof(SwUsz) >= sizeof(void*));  // @FIXME: do not assume 64-bits arch
typedef SwI64  SwIsz; SW_ENSURE(sizeof(SwIsz) >= sizeof(void*));
typedef float  SwF32; SW_ENSURE(sizeof(SwF32) == 4);
typedef double SwF64; SW_ENSURE(sizeof(SwF64) == 8);

typedef SwI8  SwBool8;
typedef SwI16 SwBool16;
typedef SwI32 SwBool32;
typedef SwI64 SwBool64;
typedef SwIsz SwBool;
typedef SwBool SwSuccBool;  // Failure (0) vs Success (1)

typedef SwU8  SwCharA;        // ASCII character (7 bits i.e. 0 to 127 included)
typedef SwU8  SwByteUtf8;     // UTF-8 byte (multiple ones (1+) make up a codepoint)
typedef SwU32 SwCodeptUtf32;  // UTF-32 codepoint (multiple ones (1+) to make up a grapheme cluster)
typedef SwSlice(const SwCharA)       SwStrA;         // may or may not be zero terminated (i.e. a zero byte is still treated as a terminator if encountered), len should therefore be available
typedef SwSlice(const SwByteUtf8)    SwStrUtf8;      // may or may not be zero terminated (i.e. a zero byte is still treated as a terminator if encountered), len should therefore be available
typedef SwSlice(const SwCodeptUtf32) SwStrUtf32;     // may or may not be zero terminated (i.e. a zero byte is still treated as a terminator if encountered), len should therefore be available
typedef SwSlice(const SwCharA,:0)       SwStrAz;     // zero terminated ASCII string, len may or may not be available
typedef SwSlice(const SwByteUtf8,:0)    SwStrUtf8z;  // zero terminated UTF-8 string, len may or may not be available
typedef SwSlice(const SwCodeptUtf32,:0) SwStrUtf32z; // zero terminated UTF-32 string, len may or may not be available

// fixed size strings for common power of two sizes
typedef union { SwU8 strNb[4]; SwU8 str[4]; } SwStr4bA;
typedef union { SwU8 strNb[8]; SwU8 str[8]; } SwStr8bA;
typedef union { SwU8 strNb[16]; SwU8 str[16]; } SwStr16bA;
typedef union { SwU8 strNb[32]; SwU8 str[32]; } SwStr32bA;
typedef union { SwU8 strNb[64]; SwU8 str[64]; } SwStr64bA;
typedef union { SwU8 strNb[128]; SwU8 str[128]; } SwStr128bA;
typedef union { SwU8 strNb[256]; SwU8 str[256]; } SwStr256bA;
typedef union { SwU8 strNb[512]; SwU8 str[512]; } SwStr512bA;

typedef union { SwU8 strNb[4]; SwU8 str[4]; } SwStr4bUtf8;
typedef union { SwU8 strNb[8]; SwU8 str[8]; } SwStr8bUtf8;
typedef union { SwU8 strNb[16]; SwU8 str[16]; } SwStr16bUtf8;
typedef union { SwU8 strNb[32]; SwU8 str[32]; } SwStr32bUtf8;
typedef union { SwU8 strNb[64]; SwU8 str[64]; } SwStr64bUtf8;
typedef union { SwU8 strNb[128]; SwU8 str[128]; } SwStr128bUtf8;
typedef union { SwU8 strNb[256]; SwU8 str[256]; } SwStr256bUtf8;
typedef union { SwU8 strNb[512]; SwU8 str[512]; } SwStr512bUtf8;

// variably sized strings store their own byte lengths alongside a ptr
// NOTE: the hypothetical zero terminator should never appear before the `byteLen` bytes,
//       however, it does not have to appear right past it either, the str may or may not even be zero terminated!
//       this is typically use-case specific, consider typedef a new str type, if code needs to rely on zero terminator.
typedef struct { union { SwUsz byteLen; SwUsz len; }; SwStrA str; } SwLStrA;
typedef struct { union { SwUsz byteLen; };  SwStrUtf8 str; } SwLStrUtf8;

// limits
#define swUMax64(N) (~0llu >> (64-(N)))
#define swUMax32(N) (~0u >> (32-(N)))

#define swU8_Max  0xFFllu
#define swU12_Max 0xFFFllu
#define swU16_Max 0xFFFFllu
#define swU20_Max 0xFFFFFllu
#define swU24_Max 0xFFFFFFllu
#define swU28_Max 0xFFFFFFFllu
#define swU32_Max 0xFFFFFFFFllu
#define swU36_Max 0xFFFFFFFFFllu
#define swU40_Max 0xFFFFFFFFFFllu
#define swU44_Max 0xFFFFFFFFFFFllu
#define swU48_Max 0xFFFFFFFFFFFFllu
#define swU52_Max 0xFFFFFFFFFFFFFllu
#define swU56_Max 0xFFFFFFFFFFFFFFllu
#define swU60_Max 0xFFFFFFFFFFFFFFFllu
#define swU64_Max 0xFFFFFFFFFFFFFFFFllu
#define swUsz_Max swU64_Max

// helper macros
#define SW_MAX(a,b) (((a) > (b)) ? (a) : (b))
#define SW_MIN(a,b) (((a) < (b)) ? (a) : (b))

#define SW_EQ_ANY1(x,eqA) ((x)==(eqA))
#define SW_EQ_ANY2(x,eqA,eqB) (((x)==(eqA))|((x)==(eqB)))
#define SW_EQ_ANY3(x,eqA,eqB,eqC) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC)))
#define SW_EQ_ANY4(x,eqA,eqB,eqC,eqD) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC))|((x)==(eqD)))
#define SW_EQ_ANY5(x,eqA,eqB,eqC,eqD,eqE) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC))|((x)==(eqD))|((x)==(eqE)))
#define SW_EQ_ANY6(x,eqA,eqB,eqC,eqD,eqE,eqF) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC))|((x)==(eqD))|((x)==(eqE))|((x)==(eqF)))
#define SW_EQ_ANY7(x,eqA,eqB,eqC,eqD,eqE,eqF,eqG) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC))|((x)==(eqD))|((x)==(eqE))|((x)==(eqF))|((x)==(eqG)))
#define SW_EQ_ANY8(x,eqA,eqB,eqC,eqD,eqE,eqF,eqG,eqH) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC))|((x)==(eqD))|((x)==(eqE))|((x)==(eqF))|((x)==(eqG))|((x)==(eqH)))
#define SW_EQ_ANY9(x,eqA,eqB,eqC,eqD,eqE,eqF,eqG,eqH,eqI) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC))|((x)==(eqD))|((x)==(eqE))|((x)==(eqF))|((x)==(eqG))|((x)==(eqH))|((x)==(eqI)))
#define SW_EQ_ANY(x,...) SW_TOK_CAT2(SW_EQ_ANY,SW_VA_COUNT(__VA_ARGS__))(x,__VA_ARGS__)

#define SW_EQ_SEQ1(x,eq0) ((x)[0]==(eq0))
#define SW_EQ_SEQ2(x,eq0,eq1) (((x)[0]==(eq0))&&((x)[1]==(eq1)))
#define SW_EQ_SEQ3(x,eq0,eq1,eq2) (((x)[0]==(eq0))&&((x)[1]==(eq1))&&((x)[2]==(eq2)))
#define SW_EQ_SEQ4(x,eq0,eq1,eq2,eq3) (((x)[0]==(eq0))&&((x)[1]==(eq1))&&((x)[2]==(eq2))&&((x)[3]==(eq3)))
#define SW_EQ_SEQ5(x,eq0,eq1,eq2,eq3,eq4) (((x)[0]==(eq0))&&((x)[1]==(eq1))&&((x)[2]==(eq2))&&((x)[3]==(eq3))&&((x)[4]==(eq4)))
#define SW_EQ_SEQ6(x,eq0,eq1,eq2,eq3,eq4,eq5) (((x)[0]==(eq0))&&((x)[1]==(eq1))&&((x)[2]==(eq2))&&((x)[3]==(eq3))&&((x)[4]==(eq4))&&((x)[5]==(eq5)))
#define SW_EQ_SEQ7(x,eq0,eq1,eq2,eq3,eq4,eq5,eq6) (((x)[0]==(eq0))&&((x)[1]==(eq1))&&((x)[2]==(eq2))&&((x)[3]==(eq3))&&((x)[4]==(eq4))&&((x)[5]==(eq5))&&((x)[6]==(eq6)))
#define SW_EQ_SEQ8(x,eq0,eq1,eq2,eq3,eq4,eq5,eq6,eq7) (((x)[0]==(eq0))&&((x)[1]==(eq1))&&((x)[2]==(eq2))&&((x)[3]==(eq3))&&((x)[4]==(eq4))&&((x)[5]==(eq5))&&((x)[6]==(eq6))&&((x)[7]==(eq7)))
#define SW_EQ_SEQ9(x,eq0,eq1,eq2,eq3,eq4,eq5,eq6,eq7,eq8) (((x)[0]==(eq0))&&((x)[1]==(eq1))&&((x)[2]==(eq2))&&((x)[3]==(eq3))&&((x)[4]==(eq4))&&((x)[5]==(eq5))&&((x)[6]==(eq6))&&((x)[7]==(eq7))&&((x)[8]==(eq8)))
#define SW_EQ_SEQ(x,...) SW_TOK_CAT2(SW_EQ_SEQ,SW_VA_COUNT(__VA_ARGS__))(x,__VA_ARGS__)

#define SW_IS_ANY1(x,isA) (isA(x))
#define SW_IS_ANY2(x,isA,isB) (isA(x)|isB(x))
#define SW_IS_ANY3(x,isA,isB,isC) (isA(x)|isB(x)|isC(x))
#define SW_IS_ANY4(x,isA,isB,isC,isD) (isA(x)|isB(x)|isC(x)|isD(x))
#define SW_IS_ANY5(x,isA,isB,isC,isD,isE) (isA(x)|isB(x)|isC(x)|isD(x)|isE(x))
#define SW_IS_ANY6(x,isA,isB,isC,isD,isE,isF) (isA(x)|isB(x)|isC(x)|isD(x)|isE(x)|isF(x))
#define SW_IS_ANY7(x,isA,isB,isC,isD,isE,isF,isG) (isA(x)|isB(x)|isC(x)|isD(x)|isE(x)|isF(x)|isG(x))
#define SW_IS_ANY8(x,isA,isB,isC,isD,isE,isF,isG,isH) (isA(x)|isB(x)|isC(x)|isD(x)|isE(x)|isF(x)|isG(x)|isH(x))
#define SW_IS_ANY9(x,isA,isB,isC,isD,isE,isF,isG,isH,isI) (isA(x)|isB(x)|isC(x)|isD(x)|isE(x)|isF(x)|isG(x)|isH(x)|isI(x))
#define SW_IS_ANY(x,...) SW_TOK_CAT2(SW_IS_ANY,SW_VA_COUNT(__VA_ARGS__))(x,__VA_ARGS__)

#define SW_IS_CONSECUTIVE2(a0,a1) (((a0)+1)==(a1))
#define SW_IS_CONSECUTIVE3(a0,a1,a2) ((((a0)+1)==(a1))&(((a1)+1)==(a2)))
#define SW_IS_CONSECUTIVE4(a0,a1,a2,a3) ((((a0)+1)==(a1))&(((a1)+1)==(a2))&(((a2)+1)==(a3)))
#define SW_IS_CONSECUTIVE5(a0,a1,a2,a3,a4) ((((a0)+1)==(a1))&(((a1)+1)==(a2))&(((a2)+1)==(a3))&(((a3)+1)==(a4)))
#define SW_IS_CONSECUTIVE6(a0,a1,a2,a3,a4,a5) ((((a0)+1)==(a1))&(((a1)+1)==(a2))&(((a2)+1)==(a3))&(((a3)+1)==(a4))&(((a4)+1)==(a5)))
#define SW_IS_CONSECUTIVE7(a0,a1,a2,a3,a4,a5,a6) ((((a0)+1)==(a1))&(((a1)+1)==(a2))&(((a2)+1)==(a3))&(((a3)+1)==(a4))&(((a4)+1)==(a5))&(((a5)+1)==(a6)))
#define SW_IS_CONSECUTIVE8(a0,a1,a2,a3,a4,a5,a6,a7) ((((a0)+1)==(a1))&(((a1)+1)==(a2))&(((a2)+1)==(a3))&(((a3)+1)==(a4))&(((a4)+1)==(a5))&(((a5)+1)==(a6))&(((a6)+1)==(a7)))
#define SW_IS_CONSECUTIVE9(a0,a1,a2,a3,a4,a5,a6,a7,a8) ((((a0)+1)==(a1))&(((a1)+1)==(a2))&(((a2)+1)==(a3))&(((a3)+1)==(a4))&(((a4)+1)==(a5))&(((a5)+1)==(a6))&(((a6)+1)==(a7))&(((a7)+1)==(a8)))
#define SW_IS_CONSECUTIVE10(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9) ((((a0)+1)==(a1))&(((a1)+1)==(a2))&(((a2)+1)==(a3))&(((a3)+1)==(a4))&(((a4)+1)==(a5))&(((a5)+1)==(a6))&(((a6)+1)==(a7))&(((a7)+1)==(a8))&(((a8)+1)==(a9)))
#define SW_IS_CONSECUTIVE(...) SW_TOK_CAT2(SW_IS_CONSECUTIVE,SW_VA_COUNT(__VA_ARGS__))(__VA_ARGS__)

#define SW_SPREAD1(s) s[0]
#define SW_SPREAD2(s) s[0],s[1]
#define SW_SPREAD3(s) s[0],s[1],s[2]
#define SW_SPREAD4(s) s[0],s[1],s[2],s[3]
#define SW_SPREAD5(s) s[0],s[1],s[2],s[3],s[4]
#define SW_SPREAD6(s) s[0],s[1],s[2],s[3],s[4],s[5]
#define SW_SPREAD7(s) s[0],s[1],s[2],s[3],s[4],s[5],s[6]
#define SW_SPREAD8(s) s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]
#define SW_SPREAD9(s) s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8]

#define SW_STR_UNPACK8z(s) (unsigned)swStrByteLen8z((SwStrUtf8z)s), (const char*)(s)
#define SW_STR_UNPACK(s) swStrNbOrLStr__ByteLen(s), (const char*)(s->str)
#define swStrNbOrLStr__ByteLen(s) ((sizeof(*s)==sizeof(s->str)) ? ((SwUsz)swStrNbByteLenOrCap8z(s)) : ((SwUsz)((SwLStrUtf8*)s)->byteLen))
#define swStrNbByteLenOrCap8z(s) swStrByteLenOrCap8z(sizeof(s->strNb), s->strNb)

#endif // SW_CORE_PREFACE_H_
