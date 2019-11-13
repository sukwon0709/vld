#ifndef DUMP_PROTOBUF_H_
#define DUMP_PROTOBUF_H_

#include "UCPHPCClient.h"

#include "branchinfo.h"
#include "php_vld.h"

BranchInfo*
ucphp_dump_branch(vld_branch_info* branch_info);

OpcodeList*
ucphp_dump_opcodes(zend_op_array* opa);

void ucphp_dump(TSRMLS_D);

#endif // DUMP_PROTOBUF_H_