#ifndef SW_CORE_ITER_API_H_
#define SW_CORE_ITER_API_H_

#include "core_preface.h"

typedef struct { SwUsz index; SwIsz step; } SwIterRange;

SW_PUBL_API_IMPL inline SwIterRange swIterRangeForward(SwUsz n) { return (SwIterRange){ 0, 1 }; }
SW_PUBL_API_IMPL inline SwIterRange swIterRangeBackward(SwUsz n) { return (SwIterRange){ n-1, -1 }; }


#endif  // SW_CORE_ITER_API_H_