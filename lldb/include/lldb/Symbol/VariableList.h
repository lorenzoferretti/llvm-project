//===-- VariableList.h ------------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_VariableList_h_
#define liblldb_VariableList_h_

#include "lldb/Symbol/SymbolContext.h"
#include "lldb/Symbol/Variable.h"
#include "lldb/lldb-private.h"

namespace lldb_private {

class VariableList {
public:
  //------------------------------------------------------------------
  // Constructors and Destructors
  //------------------------------------------------------------------
  //  VariableList(const SymbolContext &symbol_context);
  VariableList();
  virtual ~VariableList();

  void AddVariable(const lldb::VariableSP &var_sp);

  bool AddVariableIfUnique(const lldb::VariableSP &var_sp);

  void AddVariables(VariableList *variable_list);

  void Clear();

  void Dump(Stream *s, bool show_context) const;

  lldb::VariableSP GetVariableAtIndex(size_t idx) const;

  lldb::VariableSP RemoveVariableAtIndex(size_t idx);

  lldb::VariableSP FindVariable(ConstString name,
                                bool include_static_members = true);

  lldb::VariableSP FindVariable(ConstString name,
                                lldb::ValueType value_type,
                                bool include_static_members = true);

  uint32_t FindVariableIndex(const lldb::VariableSP &var_sp);

  size_t AppendVariablesIfUnique(VariableList &var_list);

  // Returns the actual number of unique variables that were added to the list.
  // "total_matches" will get updated with the actually number of matches that
  // were found regardless of whether they were unique or not to allow for
  // error conditions when nothing is found, versus conditions where any
  // variables that match "regex" were already in "var_list".
  size_t AppendVariablesIfUnique(const RegularExpression &regex,
                                 VariableList &var_list, size_t &total_matches);

  size_t AppendVariablesWithScope(lldb::ValueType type, VariableList &var_list,
                                  bool if_unique = true);

  uint32_t FindIndexForVariable(Variable *variable);

  size_t MemorySize() const;

  size_t GetSize() const;
  bool Empty() const { return m_variables.empty(); }

protected:
  typedef std::vector<lldb::VariableSP> collection;
  typedef collection::iterator iterator;
  typedef collection::const_iterator const_iterator;

  collection m_variables;

private:
  //------------------------------------------------------------------
  // For VariableList only
  //------------------------------------------------------------------
  DISALLOW_COPY_AND_ASSIGN(VariableList);
};

} // namespace lldb_private

#endif // liblldb_VariableList_h_
