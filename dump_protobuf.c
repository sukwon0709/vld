#include "dump_protobuf.h"
#include "ext/standard/info.h"
#include "ext/standard/url.h"
#include "php.h"
#include "php_globals.h"
#include "php_ini.h"
#include "zend_hash.h"

ZEND_EXTERN_MODULE_GLOBALS(vld)

#if PHP_VERSION_ID >= 50300
#define APPLY_TSRMLS_CC TSRMLS_CC
#define APPLY_TSRMLS_DC TSRMLS_DC
#else
#define APPLY_TSRMLS_CC
#define APPLY_TSRMLS_DC
#endif

// Stores a table of user defined functions.
static HashTable *user_defined_table;
static zend_op *call_stack[100] = {NULL};
static int call_stack_top = 0;           // index for next element.
static int init_call_by_name_called = 0; // flag to distinguish call approach

char *toLower(const char *str, int len) {
  char *str2 = emalloc(sizeof(char) * len + 1);

  for (int i = 0; i < len; i++) {
    str2[i] = tolower(str[i]);
  }
  str2[len] = '\0';

  return str2;
}

static int save_fe(zend_op_array *fe APPLY_TSRMLS_DC, int num_args,
                   va_list args, zend_hash_key *hash_key) {
#if PHP_VERSION_ID < 50300
  TSRMLS_FETCH()
#endif
  if (fe->type == ZEND_USER_FUNCTION) {
    ZVAL_VALUE_STRING_TYPE *new_str;
    int new_len;
    char *lowerStr = toLower(ZHASHKEYSTR(hash_key), ZHASHKEYLEN(hash_key) - 1);
    /* zval *fname; */

    /* MAKE_STD_ZVAL(fname); */
    /* ZVAL_STRINGL(fname, ZHASHKEYSTR(hash_key), ZHASHKEYLEN(hash_key)) */

    new_str = php_url_encode(ZHASHKEYSTR(hash_key),
                             ZHASHKEYLEN(hash_key) -
                                 1 PHP_URLENCODE_NEW_LEN(new_len));
    vld_printf(stderr, "Function %s:\n", ZSTRING_VALUE(new_str));
    zend_hash_update(user_defined_table, ZHASHKEYSTR(hash_key),
                     ZHASHKEYLEN(hash_key), &fe, sizeof(zend_op_array *), NULL);
    zend_hash_update(user_defined_table, lowerStr, ZHASHKEYLEN(hash_key), &fe,
                     sizeof(zend_op_array *), NULL);
    vld_printf(stderr, "End of function %s\n\n", ZSTRING_VALUE(new_str));
    efree(lowerStr);
    efree(new_str);
  }

  return ZEND_HASH_APPLY_KEEP;
}

BranchInfo *ucphp_dump_branch(vld_branch_info *branch_info) {
  BranchInfo *branch_info_proto = new_branch_info();

  for (int i = 0; i < branch_info->starts->size; i++) {
    if (vld_set_in(branch_info->starts, i)) {
      // create branch
      Branch *branch_proto = add_new_branch(branch_info_proto);
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

OpcodeList *ucphp_dump_opcodes(zend_op_array *opa) {
  OpcodeList *opcode_list_proto = add_new_opcode_list(VLD_G(opcode_dump));

  // Get information on user-defined functions.
  ALLOC_HASHTABLE(user_defined_table);
  zend_hash_init(user_defined_table, 10000, NULL, NULL, 0);
  zend_hash_apply_with_arguments(CG(function_table) APPLY_TSRMLS_CC,
                                 (apply_func_args_t)save_fe, 0);

  for (int i = 0; i < opa->last; i++) {
    const zend_op op = opa->opcodes[i];
    Opcode *op_proto = add_new_opcode(opcode_list_proto);
    set_opcode_id(op_proto, i);
    set_opcode_name_(op_proto, op.opcode);
    set_base_opcode(op_proto);
    // setup function call or file include here...
    if (op.opcode == ZEND_DO_FCALL) {
      if (op.op1_type == IS_CONST) {
        zend_op_array **fe;
        if (zend_hash_find(user_defined_table, Z_STRVAL_P(op.op1.zv),
                           Z_STRLEN_P(op.op1.zv) + 1,
                           (void **)&fe) == SUCCESS) {
          set_user_defined_function_call_opcode(op_proto, (*fe)->function_name);
          printf("USER-DEFINED DO_FCALL::  %s\n", (*fe)->function_name);
        } else {
          set_builtin_function_call_opcode(op_proto, Z_STRVAL_P(op.op1.zv));
          printf("DO_FCALL::  %s\n", Z_STRVAL_P(op.op1.zv));
        }
      } else {
        set_unknown_function_call_opcode(op_proto);
        printf("UNKNOWN DO_FCALL\n");
      }
    } else if (op.opcode == ZEND_INIT_FCALL_BY_NAME) {
      call_stack[call_stack_top++] = &opa->opcodes[i];
      init_call_by_name_called = 1;
    } else if (op.opcode == ZEND_DO_FCALL_BY_NAME) {
      if (init_call_by_name_called == 1) {
        zend_op fop = *call_stack[--call_stack_top];
        init_call_by_name_called = 0;
        if (fop.op1_type == IS_UNUSED && fop.op2_type == IS_CONST) {
          // user-defined?
          set_user_defined_function_call_opcode(op_proto,
                                                Z_STRVAL_P(fop.op2.zv));
          printf("DO_FCALL_BY_NAME:: %s\n", Z_STRVAL_P(fop.op2.zv));
        } else {
          set_unknown_function_call_opcode(op_proto);
          printf("UNKNOWN DO_FCALL_BY_NAME\n");
        }
      }
    } else if (op.opcode == ZEND_INCLUDE_OR_EVAL) {
      switch (op.extended_value) {
      case ZEND_INCLUDE_ONCE:
        if (op.op1_type == IS_CONST) {
          set_file_include_once_opcode(op_proto, Z_STRVAL_P(op.op1.zv),
                                       opa->filename);
          printf("INCLUDE_ONCE:: %s from %s\n", Z_STRVAL_P(op.op1.zv),
                 opa->filename);
        } else {
          set_unknown_file_include_once_opcode(op_proto, opa->filename);
          printf("UNKNOWN_INCLUDE_ONCE\n");
        }
        break;
      case ZEND_REQUIRE_ONCE:
        if (op.op1_type == IS_CONST) {
          set_file_require_once_opcode(op_proto, Z_STRVAL_P(op.op1.zv),
                                       opa->filename);
          printf("REQUIRE_ONCE:: %s from %s\n", Z_STRVAL_P(op.op1.zv),
                 opa->filename);
        } else {
          set_unknown_file_require_once_opcode(op_proto, opa->filename);
          printf("UNKNOWN_REQUIRE_ONCE\n");
        }
        break;
      case ZEND_INCLUDE:
        if (op.op1_type == IS_CONST) {
          set_file_include_opcode(op_proto, Z_STRVAL_P(op.op1.zv),
                                  opa->filename);
          printf("INCLUDE:: %s from %s\n", Z_STRVAL_P(op.op1.zv),
                 opa->filename);
        } else {
          set_unknown_file_include_opcode(op_proto, opa->filename);
          printf("UNKNOWN_INCLUDE\n");
        }
        break;
      case ZEND_REQUIRE:
        if (op.op1_type == IS_CONST) {
          set_file_require_opcode(op_proto, Z_STRVAL_P(op.op1.zv),
                                  opa->filename);
          printf("REQUIRE:: %s from %s\n", Z_STRVAL_P(op.op1.zv),
                 opa->filename);
        } else {
          set_unknown_file_require_opcode(op_proto, opa->filename);
          printf("UNKNOWN_REQUIRE\n");
        }
        break;
      case ZEND_EVAL:
        set_eval_opcode(op_proto, opa->filename);
        printf("EVAL:: from %s\n", opa->filename);
        break;
      }
    }
  }

  const char *filename = opa->filename ? ZSTRING_VALUE(opa->filename) : "";
  const char *scopename = opa->scope ? ZSTRING_VALUE(opa->scope->name) : "";
  const char *funcname =
      opa->function_name ? ZSTRING_VALUE(opa->function_name) : "";

  zend_hash_destroy(user_defined_table);
  FREE_HASHTABLE(user_defined_table);

  set_opcode_list_location(opcode_list_proto, filename, scopename, funcname);

  return opcode_list_proto;
}

void ucphp_dump(TSRMLS_D) {
  write_opcode_dump(VLD_G(dump_proto_path), VLD_G(opcode_dump));
}
