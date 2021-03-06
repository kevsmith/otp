/*
 * %CopyrightBegin%
 *
 * Copyright Ericsson AB 2004-2011. All Rights Reserved.
 *
 * The contents of this file are subject to the Erlang Public License,
 * Version 1.1, (the "License"); you may not use this file except in
 * compliance with the License. You should have received a copy of the
 * Erlang Public License along with this software. If not, it can be
 * retrieved online at http://www.erlang.org/.
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * %CopyrightEnd%
 */
#ifndef _ERL_DEBUG_H_
#define _ERL_DEBUG_H_
#ifdef DEBUG

#include "erl_term.h"

#ifdef HIPE
#include "hipe_debug.h"
#endif

/* Heap areas will be filled with this value when they are deallocated
 * after a garbage collection. This value used to be 0xff, but that is
 * an immediate and might not crash the system if it is encountered.
 * The value is now 0x01, the cons of death.
 */
#define DEBUG_BAD_BYTE 0x01
#define DEBUG_BAD_WORD 0x01010101

/*
 * VERBOSE. Use the -v option to enable the different categories.
 */
#define VERBOSE(flag, format) (flag & verbose ? erts_printf format : 0)

#define DEBUG_DEFAULT      0x0000    /* No flags are set per default         */
#define DEBUG_SYSTEM       0x0001    /* Misc system info at startup and end  */
#define DEBUG_PRIVATE_GC   0x0002    /* GC of private heaps                  */
#define DEBUG_HYBRID_GC    0x0004    /* GC of the message area               */
#define DEBUG_ALLOCATION   0x0008    /* HAlloc. To find holes in the heap    */
#define DEBUG_MESSAGES     0x0010    /* Message passing                      */
#define DEBUG_THREADS      0x0020    /* Thread-related stuff                 */
#define DEBUG_PROCESSES    0x0040    /* Process creation and removal         */
#define DEBUG_MEMORY       0x0080    /* Display results of memory checks     */

extern Uint32 verbose;

void upp(byte*, size_t);
void pat(Eterm);
void pinfo(void);
void pp(Process*);
void ppi(Eterm);
void pba(Process*, int);
void td(Eterm);
void ps(Process*, Eterm*);

#undef ERTS_OFFHEAP_DEBUG
#define ERTS_OFFHEAP_DEBUG

#else /* Non-debug mode */

#define VERBOSE(flag,format)

#endif /* DEBUG */

#ifdef ERTS_OFFHEAP_DEBUG
#define ERTS_CHK_OFFHEAP(P) erts_check_off_heap((P))
#define ERTS_CHK_OFFHEAP2(P, HT) erts_check_off_heap2((P), (HT))
void erts_check_off_heap(Process *);
void erts_check_off_heap2(Process *, Eterm *);
#else
#define ERTS_CHK_OFFHEAP(P)
#define ERTS_CHK_OFFHEAP2(P, HT)
#endif

/*
 * These functions can be handy when developing, and perhaps useful
 * even outside debugging.
 */
extern void erts_check_off_heap(Process *p);
extern void erts_check_stack(Process *p);
extern void erts_check_heap(Process *p);
extern void erts_check_memory(Process *p, Eterm *start, Eterm *end);
extern void verify_process(Process *p);
extern void verify_everything(void);
extern void print_tagged_memory(Eterm *start, Eterm *end);
extern void print_untagged_memory(Eterm *start, Eterm *end);
extern void print_memory(Process *p);
extern void print_memory_info(Process *p);
#if defined(DEBUG) && !HEAP_ON_C_STACK
extern Eterm *erts_debug_allocate_tmp_heap(int, Process *);
extern void erts_debug_use_tmp_heap(int, Process *);
extern void erts_debug_unuse_tmp_heap(int, Process *);
#endif

#ifdef HYBRID
extern void print_ma_info(void);
extern void print_message_area(void);
extern void check_message_area(void);
#endif

#endif /* _ERL_DEBUG_H_ */
