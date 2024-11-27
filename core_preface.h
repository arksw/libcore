#ifndef SW_CORE_PREFACE_H_
#define SW_CORE_PREFACE_H_

#include "core_ccflags.h"

// For documentation & easy grep
#define SW_PUBL_API_DECL static
#define SW_PUBL_API_IMPL static
#define SW_PRIV_API_DECL static
#define SW_PRIV_API_IMPL static

// The counterpart to the `const` keyword, it exists for the sake of explicitness. Its use is recommended only within a function's signature. 
#define mutable

// Preprocessor Macros
#define SW__TOK_CAT2(a,b) a##b
#define SW_TOK_CAT2(a,b) SW__TOK_CAT2(a,b)
#define SW__TOK_STR(a) #a
#define SW_TOK_STR(a) SW__TOK_STR(a)
#define SW__VA_COUNT(a1,a2,a3,a4,a5,a6,a7,a8,count,...) count
#define SW_VA_COUNT(...) SW__VA_COUNT(__VA_ARGS__,8,7,6,5,4,3,2,1)
#define SW_ARR_COUNT(arr) (sizeof(arr)/sizeof(*(arr)))

// Assert Macros
#define SW__TRAP() (*(volatile int*)0=0)
#define SW_ASSERT(cond,...) do { if (!(cond)) { __builtin_printf(__FILE__ ":" SW_TOK_STR(__LINE__) ":0 ::: %s ::: ASSERT( " #cond " )\n", __func__); __builtin_printf("  " __VA_ARGS__); SW__TRAP(); } } while (0)
#define SW_PANIC(...) SW_ASSERT(0,__VA_ARGS__)
#define SW_UNREACHABLE(...) SW_ASSERT(0,__VA_ARGS__)
#if SWCC_DEBUG
#define SW_DASSERT(cond,...) SW_ASSERT(cond, __VA_ARGS__)
#else
#define SW_DASSERT(cond,...) (void)0
#endif
#define SW_ENSURE(cond,...) typedef int SW_TOK_CAT2(sw__ensure_line_,__LINE__)[(cond) ? 1 : -1]
#define SW_IMPLY(cond,then) ((!(cond)) || (then))
#define SW_BIMPLY(propA,propB) (SW_IMPLY(propA,propB) && SW_IMPLY(propB,propA))

// Constants
#define swNULL ((void*)0)
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
typedef SwU64  SwUsz; SW_ENSURE(sizeof(SwUsz) >= sizeof(void*));
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

// limits
#define swU8_Max  0xFFllu
#define swU16_Max 0xFFFFllu
#define swU24_Max 0xFFFFFFllu
#define swU32_Max 0xFFFFFFFFllu
#define swU36_Max 0xFFFFFFFFFllu
#define swU40_Max 0xFFFFFFFFFFllu
#define swU48_Max 0xFFFFFFFFFFFFllu
#define swU56_Max 0xFFFFFFFFFFFFFFllu
#define swU64_Max 0xFFFFFFFFFFFFFFFFllu

// helper macros
#define SW_MAX(a,b) (((a) > (b)) ? (a) : (b))
#define SW_MIN(a,b) (((a) < (b)) ? (a) : (b))

#define SW_EQ_ANY2(x,eqA,eqB) (((x)==(eqA))|((x)==(eqB)))
#define SW_EQ_ANY3(x,eqA,eqB,eqC) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC)))
#define SW_EQ_ANY4(x,eqA,eqB,eqC,eqD) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC))|((x)==(eqD)))
#define SW_EQ_ANY5(x,eqA,eqB,eqC,eqD,eqE) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC))|((x)==(eqD))|((x)==(eqE)))
#define SW_EQ_ANY6(x,eqA,eqB,eqC,eqD,eqE,eqF) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC))|((x)==(eqD))|((x)==(eqF)))
#define SW_EQ_ANY7(x,eqA,eqB,eqC,eqD,eqE,eqF,eqG) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC))|((x)==(eqD))|((x)==(eqF))|((x)==(eqG)))
#define SW_EQ_ANY8(x,eqA,eqB,eqC,eqD,eqE,eqF,eqG,eqH) (((x)==(eqA))|((x)==(eqB))|((x)==(eqC))|((x)==(eqD))|((x)==(eqF))|((x)==(eqG))|((x)==(eqH)))
#define SW_EQ_ANY(x,...) SW_TOK_CAT2(SW_EQ_ANY,SW_VA_COUNT(__VA_ARGS__))(x,__VA_ARGS__)

#define SW_IS_ANY2(x,isA,isB) (isA(x)|isB(x))
#define SW_IS_ANY3(x,isA,isB,isC) (isA(x)|isB(x)|isC(x))
#define SW_IS_ANY4(x,isA,isB,isC,isD) (isA(x)|isB(x)|isC(x)|isD(x))
#define SW_IS_ANY5(x,isA,isB,isC,isD,isE) (isA(x)|isB(x)|isC(x)|isD(x)|isE(x))
#define SW_IS_ANY6(x,isA,isB,isC,isD,isE,isF) (isA(x)|isB(x)|isC(x)|isD(x)|isE(x)|isF(x))
#define SW_IS_ANY7(x,isA,isB,isC,isD,isE,isF,isG) (isA(x)|isB(x)|isC(x)|isD(x)|isE(x)|isF(x)|isG(x))
#define SW_IS_ANY8(x,isA,isB,isC,isD,isE,isF,isG,isH) (isA(x)|isB(x)|isC(x)|isD(x)|isE(x)|isF(x)|isG(x)|isH(x))
#define SW_IS_ANY(x,...) SW_TOK_CAT2(SW_IS_ANY,SW_VA_COUNT(__VA_ARGS__))(x,__VA_ARGS__)

#define SW_SPREAD2(s) s[0],s[1]
#define SW_SPREAD4(s) s[0],s[1],s[2],s[3]
#define SW_SPREAD8(s) s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]

#endif  // SW_CORE_PREFACE_H_
