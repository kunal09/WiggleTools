// Copyright (c) 2013, Daniel Zerbino
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// 
// (1) Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer. 
// 
// (2) Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in
// the documentation and/or other materials provided with the
// distribution.  
// 
// (3)The name of the author may not be used to
// endorse or promote products derived from this software without
// specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef _WIGGLETOOLS_DEF_
#define _WIGGLETOOLS_DEF_

#ifndef true
typedef int bool;
#define true 1
#define false 0
#endif

typedef struct wiggleIterator_st WiggleIterator;

// Creators
WiggleIterator * WigOrBigWigReader(char *);
WiggleIterator * WiggleReader(char *);
WiggleIterator * BigWiggleReader(char *);

// Algebraic operations
WiggleIterator * SumWiggleIterator (WiggleIterator *, WiggleIterator *);
WiggleIterator * ScaleWiggleIterator (WiggleIterator *, double);
WiggleIterator * NaturalLogWiggleIterator (WiggleIterator *);
WiggleIterator * LogWiggleIterator (WiggleIterator * , double);
WiggleIterator * NaturalExpWiggleIterator (WiggleIterator *);
WiggleIterator * ExpWiggleIterator (WiggleIterator *, double);
WiggleIterator * PowerWiggleIterator (WiggleIterator *, double);
WiggleIterator * ProductWiggleIterator (WiggleIterator * , WiggleIterator * );

// Convenience operators
WiggleIterator * sum(WiggleIterator** iters, int count);
WiggleIterator * product(WiggleIterator** iters, int count);
WiggleIterator * mean(WiggleIterator** iters, int count);

// Output
void toFile(WiggleIterator *, char *);
void toStdout(WiggleIterator *);
double AUC(WiggleIterator *);

// Cleaning up
void destroyWiggleIterator(WiggleIterator *);

#endif