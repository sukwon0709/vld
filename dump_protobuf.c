#include "dump_protobuf.h"

ZEND_EXTERN_MODULE_GLOBALS(vld)

BranchInfo*
ucphp_dump_branch(vld_branch_info* branch_info)
{
  BranchInfo* branch_info_proto = new_branch_info();

  for (int i = 0; i < branch_info->starts->size; i++) {
    if (vld_set_in(branch_info->starts, i)) {
      // create branch
      Branch* branch_proto = add_new_branch(branch_info_proto);
      set_branch_start_op(branch_proto, i);
      set_branch_end_op(branch_proto, branch_info->branches[i].end_op);
      set_branch_start_lineno(branch_proto,
                              branch_info->branches[i].start_lineno);
      set_branch_end_lineno(branch_proto, branch_info->branches[i].end_lineno);

      // record all entry points
      if (vld_set_in(branch_info->entry_points, i)) {
        add_new_entry_point(branch_info_proto, i);
      }

      // record both branch targets (t/f)
      set_branch_out_op1(branch_proto, branch_info->branches[i].out[0]);
      set_branch_out_op2(branch_proto, branch_info->branches[i].out[1]);
    }
  }

  return branch_info_proto;
}

OpcodeList*
ucphp_dump_opcodes(zend_op_array* opa)
{
  OpcodeList* opcode_list_proto = add_new_opcode_list(VLD_G(opcode_dump));

  for (int i = 0; i < opa->last; i++) {
    const zend_op op = opa->opcodes[i];
    Opcode* op_proto = add_new_opcode(opcode_list_proto);
    set_opcode_id(op_proto, i);
    set_opcode_name_(op_proto, op.opcode);
    if (op.extended_value == ZEND_EVAL) {
      set_opcode_as_eval(op_proto);
    }
  }

  const char* filename = opa->filename ? ZSTRING_VALUE(opa->filename) : "";
  const char* scopename = opa->scope ? ZSTRING_VALUE(opa->scope->name) : "";
  const char* funcname =
    opa->function_name ? ZSTRING_VALUE(opa->function_name) : "";

  set_opcode_list_location(opcode_list_proto, filename, scopename, funcname);

  return opcode_list_proto;
}

void ucphp_dump(TSRMLS_D)
{
  write_opcode_list(VLD_G(dump_proto_path), VLD_G(opcode_dump));
}