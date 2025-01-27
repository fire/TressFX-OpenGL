//---------------------------------------------------------------------------------------
// Calls into engine for non-graphics items: error reporting, memory allocation, ...
//-------------------------------------------------------------------------------------
//
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once



#include "AMD_TressFX.h"



#ifndef TRESSFX_ASSERT
#include <assert.h>
#define TRESSFX_ASSERT assert
#endif

#define EI_Malloc(x) (malloc(x)) //malloc(x);
#define EI_Free(x) (free(x))

#define TressFXLogWarning(msg) (AMD::g_Callbacks.pfError(msg))


#define EI_Read AMD::g_Callbacks.pfRead
#define EI_Seek AMD::g_Callbacks.pfSeek


#ifndef EI_Safe_Free
#define EI_Safe_Free(x) { if(NULL != (x)) { EI_Free(x); (x)=NULL;} }
#endif
