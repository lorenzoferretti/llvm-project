//===-- dwarf.h -------------------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef DebugBase_dwarf_h_
#define DebugBase_dwarf_h_

#include "lldb/Utility/RangeMap.h"
#include <stdint.h>

// Get the DWARF constant definitions from llvm
#include "llvm/BinaryFormat/Dwarf.h"

// and stuff them in our default namespace
using namespace llvm::dwarf;

typedef uint32_t dw_uleb128_t;
typedef int32_t dw_sleb128_t;
typedef uint16_t dw_attr_t;
typedef uint16_t dw_form_t;
typedef uint16_t dw_tag_t;
typedef uint64_t dw_addr_t; // Dwarf address define that must be big enough for
                            // any addresses in the compile units that get
                            // parsed

#ifdef DWARFUTILS_DWARF64
#define DWARF_REF_ADDR_SIZE 8
typedef uint64_t dw_offset_t; // Dwarf Debug Information Entry offset for any
                              // offset into the file
#else
#define DWARF_REF_ADDR_SIZE 4
typedef uint32_t dw_offset_t; // Dwarf Debug Information Entry offset for any
                              // offset into the file
#endif

/* Constants */
#define DW_INVALID_OFFSET (~(dw_offset_t)0)
#define DW_INVALID_INDEX 0xFFFFFFFFul

// #define DW_ADDR_none 0x0

#define DW_EH_PE_MASK_ENCODING 0x0F

//// The following are used only internally within lldb - don't
//// document them in the llvm Dwarf.h header file, we won't see
//// them in executable files anywhere.
//// These constants fit between DW_OP_lo_user (0xe0) and DW_OP_hi_user (0xff).
//
//#define DW_OP_APPLE_array_ref     0xEE // first pops index, then pops array;
//pushes array[index]
//#define DW_OP_APPLE_extern        0xEF // ULEB128 index of external object
//(i.e., an entity from the program that was used in the expression)
#define DW_OP_APPLE_uninit                                                     \
  0xF0 // This is actually generated by some apple compilers in locations lists
//#define DW_OP_APPLE_assign        0xF1 // pops value off and assigns it to
//second item on stack (2nd item must have assignable context)
//#define DW_OP_APPLE_address_of    0xF2 // gets the address of the top stack
//item (top item must be a variable, or have value_type that is an address
//already)
//#define DW_OP_APPLE_value_of      0xF3 // pops the value off the stack and
//pushes the value of that object (top item must be a variable, or expression
//local)
//#define DW_OP_APPLE_deref_type    0xF4 // gets the address of the top stack
//item (top item must be a variable, or a clang type)
//#define DW_OP_APPLE_expr_local    0xF5 // ULEB128 expression local index
//#define DW_OP_APPLE_constf        0xF6 // 1 byte float size, followed by
//constant float data
//#define DW_OP_APPLE_scalar_cast   0xF7 // Cast top of stack to 2nd in stack's
//type leaving all items in place
//#define DW_OP_APPLE_clang_cast    0xF8 // pointer size clang::Type * off the
//stack and cast top stack item to this type
//#define DW_OP_APPLE_clear         0xFE // clears the entire expression stack,
//ok if the stack is empty
//#define DW_OP_APPLE_error         0xFF // Stops expression evaluation and
//returns an error (no args)

typedef lldb_private::RangeArray<dw_addr_t, dw_addr_t, 2> DWARFRangeList;

#endif // DebugBase_dwarf_h_
