/*
    Panopticon - Audio/Graphics/Networking Language
    Copyright (C) 2013 Chad McKinney and Curtis McKinney

    All rights reserved.

    This file is part of Panopticon.

    Panopticon is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Panopticon is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Panopticon.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PANOPTICON_H
#define PANOPTICON_H

#include <stdarg.h>
#include <stddef.h>

#include "types.h"

#define PANOPTICON_VERSION_MAJOR       "0"
#define PANOPTICON_VERSION_MINOR       "1"
#define PANOPTICON_VERSION_NUM         0.1
#define PANOPTICON_VERSION_RELEASE     "0"

#define PANOPTICON_VERSION     "Panopticon " PANOPTICON_VERSION_MAJOR "." PANOPTICON_VERSION_MINOR
#define PANOPTICON_RELEASE     PANOPTICON_VERSION "." PANOPTICON_VERSION_RELEASE
#define PANOPTICON_COPYRIGHT   PANOPTICON_RELEASE "  Copyright (C) 2013"
#define PANOPTICON_AUTHORS     "Chad McKinney and Curtis McKinney"

namespace panopticon {

void startup(); // CALL THIS ON STARTUP TO INITIALIZE THE LANGUAGE
void shutdown(); // CALL THIS ON SHUTDOWN TO CLEAN UP!

/*
** state manipulation
*/
State*        (newstate)  (Alloc f, void* ud);
void          (close)     (State* P);
State*        (newthread) (State* P);
CFunction     (atpanic)   (State* P, CFunction panicf);
const Number* (version)   (State* P);


/*
** basic stack manipulation
*/
int   (absindex)   (State* P, int idx);
int   (gettop)     (State* P);
void  (settop)     (State* P, int idx);
void  (pushvalue)  (State* P, int idx);
void  (remove)     (State* P, int idx);
void  (insert)     (State* P, int idx);
void  (replace)    (State* P, int idx);
void  (copy)       (State* P, int fromidx, int toidx);
int   (checkstack) (State* P, int sz);
void  (xmove)      (State* from, State* to, int n);


/*
** access functions (stack -> C)
*/

int         (isnumber)    (State* P, int idx);
int         (isstring)    (State* P, int idx);
int         (iscfunction) (State* P, int idx);
int         (type)        (State* P, int idx);
const char* (ptypename)   (State* P, int tp);
Number      (tonumberx)   (State* P, int idx, int* isnum);
int         (toboolean)   (State* P, int idx);
const char* (tolstring)   (State* P, int idx, size_t* len);
size_t      (rawlen)      (State* P, int idx);
CFunction   (tocfunction) (State* P, int idx);
State*      (tothread)    (State* P, int idx);
const void* (topointer)   (State* P, int idx);



/*
** Comparison and arithmetic functions
*/

#define OPADD       0       /* ORDER TM */
#define OPSUB       1
#define OPMUL       2
#define OPDIV       3
#define OPMOD       4
#define OPPOW       5
#define OPUNM       6

void  (arith) (State* P, int op);

#define OPEQ        0
#define OPLT        1
#define OPLE        2

int   (rawequal) (State* P, int idx1, int idx2);
int   (compare) (State* P, int idx1, int idx2, int op);


/*
** push functions (C -> stack)
*/
void        (pushnil)      (State* P);
void        (pushnumber)   (State* P, Number n);
const char* (pushlstring)  (State* P, const char* s, size_t l);
const char* (pushstring)   (State* P, const char* s);
const char* (pushvfstring) (State* P, const char* fmt, va_list argp);
const char* (pushfstring)  (State* P, const char* fmt, ...);
void        (pushcclosure) (State* P, CFunction fn, int n);
void        (pushboolean)  (State* P, int b);
int         (pushthread)   (State* P);


/*
** get functions (Panopticon -> stack)
*/
void  (getglobal)    (State* P, const char* var);
void  (gettable)     (State* P, int idx);
void  (getfield)     (State* P, int idx, const char* k);
void  (rawget)       (State* P, int idx);
void  (rawgeti)      (State* P, int idx, int n);
void  (rawgetp)      (State* P, int idx, const void* p);
void  (createtable)  (State* P, int narr, int nrec);
void* (newuserdata)  (State* P, size_t sz);
int   (getmetatable) (State* P, int objindex);
void  (getuservalue) (State* P, int idx);


/*
** set functions (stack -> Panopticon)
*/
void  (setglobal)    (State* P, const char* var);
void  (settable)     (State* P, int idx);
void  (setfield)     (State* P, int idx, const char* k);
void  (rawset)       (State* P, int idx);
void  (rawseti)      (State* P, int idx, int n);
void  (rawsetp)      (State* P, int idx, const void* p);
int   (setmetatable) (State* P, int objindex);
void  (setuservalue) (State* P, int idx);


/*
** 'load' and 'call' functions (load and run Panopticon code)
*/
void (callk)  (State* P, int nargs, int nresults, int ctx, CFunction k);
int  (getctx) (State* P, int* ctx);
int  (pcallk) (State* P, int nargs, int nresults, int errfunc, int ctx, CFunction k);
// int  (load)   (State* P, Reader reader, void* dt, const char* chunkname, const char* mode);
// int  (dump)   (State* P, Writer writer, void* data);

#define call(P,n,r) callk(P, (n), (r), 0, NULL)
#define pcall(P,n,r,f) pcallk(P, (n), (r), (f), 0, NULL)

/*
** coroutine functions
*/
int  (yieldk) (State* P, int nresults, int ctx, CFunction k);
int  (resume) (State* P, State* from, int narg);
int  (status) (State* P);

#define yield(P,n) yieldk(P, (n), 0, NULL)

/*
** garbage-collection function and options
*/

#define GCSTOP              0
#define GCRESTART           1
#define GCCOLLECT           2
#define GCCOUNT             3
#define GCCOUNTB            4
#define GCSTEP              5
#define GCSETPAUSE          6
#define GCSETSTEPMUL        7
#define GCSETMAJORINC       8
#define GCISRUNNING         9
#define GCGEN               10
#define GCINC               11

int (gc) (State* P, int what, int data);


/*
** miscellaneous functions
*/

int   (error)     (State* P);
int   (next)      (State* P, int idx);
void  (concat)    (State* P, int n);
void  (len)       (State* P, int idx);
Alloc (getallocf) (State* P, void* *ud);
void  (setallocf) (State* P, Alloc f, void* ud);



/*
** ===============================================================
** some useful macros
** ===============================================================
*/

#define tonumber(P,i)       tonumberx(P,i,NULL)
#define tointeger(P,i)      tointegerx(P,i,NULL)
#define tounsigned(P,i)     tounsignedx(P,i,NULL)

#define pop(P,n)            settop(P, -(n)-1)

#define newtable(P)         createtable(P, 0, 0)

#define register(P,n,f) (pushcfunction(P, (f)), setglobal(P, (n)))

#define pushcfunction(P,f)  pushcclosure(P, (f), 0)

#define isfunction(P,n)     (type(P, (n)) == FUNCTION)
#define isarray(P,n)        (type(P, (n)) == ARRAY)
#define isnil(P,n)          (type(P, (n)) == TNIL)
#define isboolean(P,n)      (type(P, (n)) == TBOOLEAN)
#define isthread(P,n)       (type(P, (n)) == TTHREAD)
#define isnone(P,n)         (type(P, (n)) == TNONE)
#define isnoneornil(P, n)   (type(P, (n)) <= 0)

#define pushliteral(P, s)   \
        pushlstring(P, "" s, (sizeof(s)/sizeof(char))-1)

#define pushglobaltable(P)  \
        rawgeti(P, REGISTRYINDEX, RIDX_GLOBALS)

#define tostring(P,i) topstring(P, (i), NULL)

} // panopticon namespace

namespace pn = panopticon;

#endif // PANOPTICON_H
