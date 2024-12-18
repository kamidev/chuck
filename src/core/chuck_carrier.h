/*----------------------------------------------------------------------------
  ChucK Strongly-timed Audio Programming Language
    Compiler, Virtual Machine, and Synthesis Engine

  Copyright (c) 2003 Ge Wang and Perry R. Cook. All rights reserved.
    http://chuck.stanford.edu/
    http://chuck.cs.princeton.edu/

  This program is free software; you can redistribute it and/or modify
  it under the dual-license terms of EITHER the MIT License OR the GNU
  General Public License (the latter as published by the Free Software
  Foundation; either version 2 of the License or, at your option, any
  later version).

  This program is distributed in the hope that it will be useful and/or
  interesting, but WITHOUT ANY WARRANTY; without even the implied warranty
  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  MIT Licence and/or the GNU General Public License for details.

  You should have received a copy of the MIT License and the GNU General
  Public License (GPL) along with this program; a copy of the GPL can also
  be obtained by writing to the Free Software Foundation, Inc., 59 Temple
  Place, Suite 330, Boston, MA 02111-1307 U.S.A.
-----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// file: chuck_carrier.h
// desc: carrier of things associated with each ChucK instance
//       REFACTOR-2017
//
// author: Ge Wang (http://www.gewang.com/)
//         Jack Atherton (lja@ccrma.stanford.edu)
//         Spencer Salazar (spencer@ccrma.stanford.edu)
// date: fall 2017
//-----------------------------------------------------------------------------
#ifndef __CHUCK_CARRIER_H__
#define __CHUCK_CARRIER_H__

#include "chuck_def.h"
#ifndef __DISABLE_OTF_SERVER__
#include "util_thread.h"
#endif

#include <map>




// forward references (C++)
class  ChucK;
struct Chuck_Compiler;
struct Chuck_VM;
struct Chuck_Env;
struct Chuck_IO_Chout;
struct Chuck_IO_Cherr;

// forward references ("C")
struct ck_socket_;
typedef struct ck_socket_ * ck_socket;

// forward references (STK-specific)
class WvOut;
class XWriteThread;




//-----------------------------------------------------------------------------
// name: struct Chuck_Carrier
// desc: carrier of per-ChucK-instance things; each
//-----------------------------------------------------------------------------
struct Chuck_Carrier
{
    ChucK * chuck;
    Chuck_Compiler * compiler;
    Chuck_Env * env;
    Chuck_VM * vm;
    Chuck_IO_Chout * chout;
    Chuck_IO_Cherr * cherr;

    #ifndef __DISABLE_OTF_SERVER__
    // OTF programming things
    ck_socket otf_socket;
    t_CKINT otf_port;
    CHUCK_THREAD otf_thread;
    #endif

    // STK-specific
    #ifndef __DISABLE_WVOUT__
    XWriteThread * stk_writeThread;
    std::map<WvOut *, WvOut *> stk_wvOutMap;
    #endif

    // constructor
    Chuck_Carrier() :
        chuck(NULL),
        compiler( NULL ),
        env( NULL ),
        vm( NULL ),
        chout( NULL ),
        cherr( NULL ),
        #ifndef __DISABLE_OTF_SERVER__
        otf_socket( NULL ),
        otf_port( 0 ),
        otf_thread( 0 ),
        #endif
        #ifndef __DISABLE_WVOUT__
        stk_writeThread( NULL )
        #endif
    { }

    // get hint: is realtime audio?
    t_CKBOOL hintIsRealtimeAudio();
};




#endif
