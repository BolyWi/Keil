#ifndef __INC_52_H__
#define __INC_52_H__
#include "REG52.H"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "io.h"
#ifdef TEST_01
#include "interrupt/interrupt.h"
#elif defined(TEST_02)
#include "scomm/scomm.h"
#elif defined(TEST_03)
#else

#endif

#endif //__INC_52_H__