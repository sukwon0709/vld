/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: proto/php_opcode.proto */

#ifndef PROTOBUF_C_proto_2fphp_5fopcode_2eproto__INCLUDED
#define PROTOBUF_C_proto_2fphp_5fopcode_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _ZvalNull ZvalNull;
typedef struct _ZvalLong ZvalLong;
typedef struct _ZvalDouble ZvalDouble;
typedef struct _ZvalString ZvalString;
typedef struct _ZvalArray ZvalArray;
typedef struct _ZvalObject ZvalObject;
typedef struct _ZvalBool ZvalBool;
typedef struct _ZvalResource ZvalResource;
typedef struct _ZvalConst ZvalConst;
typedef struct _ZvalConstAst ZvalConstAst;
typedef struct _Zval Zval;
typedef struct _Znode Znode;
typedef struct _OpcodeList OpcodeList;
typedef struct _Opcode Opcode;


/* --- enums --- */

typedef enum _OpcodeName {
  OPCODE_NAME__NOP = 0,
  OPCODE_NAME__ADD = 1,
  OPCODE_NAME__SUB = 2,
  OPCODE_NAME__MUL = 3,
  OPCODE_NAME__DIV = 4,
  OPCODE_NAME__MOD = 5,
  OPCODE_NAME__SL = 6,
  OPCODE_NAME__SR = 7,
  OPCODE_NAME__CONCAT = 8,
  OPCODE_NAME__BW_OR = 9,
  OPCODE_NAME__BW_AND = 10,
  OPCODE_NAME__BW_XOR = 11,
  OPCODE_NAME__BW_NOT = 12,
  OPCODE_NAME__BOOL_NOT = 13,
  OPCODE_NAME__BOOL_XOR = 14,
  OPCODE_NAME__IS_IDENTICAL = 15,
  OPCODE_NAME__IS_NOT_IDENTICAL = 16,
  OPCODE_NAME__IS_EQUAL = 17,
  OPCODE_NAME__IS_NOT_EQUAL = 18,
  OPCODE_NAME__IS_SMALLER = 19,
  OPCODE_NAME__IS_SMALLER_OR_EQUAL = 20,
  OPCODE_NAME__CAST = 21,
  OPCODE_NAME__QM_ASSIGN = 22,
  OPCODE_NAME__ASSIGN_ADD = 23,
  OPCODE_NAME__ASSIGN_SUB = 24,
  OPCODE_NAME__ASSIGN_MUL = 25,
  OPCODE_NAME__ASSIGN_DIV = 26,
  OPCODE_NAME__ASSIGN_MOD = 27,
  OPCODE_NAME__ASSIGN_SL = 28,
  OPCODE_NAME__ASSIGN_SR = 29,
  OPCODE_NAME__ASSIGN_CONCAT = 30,
  OPCODE_NAME__ASSIGN_BW_OR = 31,
  OPCODE_NAME__ASSIGN_BW_AND = 32,
  OPCODE_NAME__ASSIGN_BW_XOR = 33,
  OPCODE_NAME__PRE_INC = 34,
  OPCODE_NAME__PRE_DEC = 35,
  OPCODE_NAME__POST_INC = 36,
  OPCODE_NAME__POST_DEC = 37,
  OPCODE_NAME__ASSIGN = 38,
  OPCODE_NAME__ASSIGN_REF = 39,
  OPCODE_NAME__ECHO = 40,
  OPCODE_NAME__PRINT = 41,
  OPCODE_NAME__JMP = 42,
  OPCODE_NAME__JMPZ = 43,
  OPCODE_NAME__JMPNZ = 44,
  OPCODE_NAME__JMPZNZ = 45,
  OPCODE_NAME__JMPZ_EX = 46,
  OPCODE_NAME__JMPNZ_EX = 47,
  OPCODE_NAME__CASE = 48,
  OPCODE_NAME__SWITCH_FREE = 49,
  OPCODE_NAME__BRK = 50,
  OPCODE_NAME__CONT = 51,
  OPCODE_NAME__BOOL = 52,
  OPCODE_NAME__INIT_STRING = 53,
  OPCODE_NAME__ADD_CHAR = 54,
  OPCODE_NAME__ADD_STRING = 55,
  OPCODE_NAME__ADD_VAR = 56,
  OPCODE_NAME__BEGIN_SILENCE = 57,
  OPCODE_NAME__END_SILENCE = 58,
  OPCODE_NAME__INIT_FCALL_BY_NAME = 59,
  OPCODE_NAME__DO_FCALL = 60,
  OPCODE_NAME__DO_FCALL_BY_NAME = 61,
  OPCODE_NAME__RETURN = 62,
  OPCODE_NAME__RECV = 63,
  OPCODE_NAME__RECV_INIT = 64,
  OPCODE_NAME__SEND_VAL = 65,
  OPCODE_NAME__SEND_VAR = 66,
  OPCODE_NAME__SEND_REF = 67,
  OPCODE_NAME__NEW = 68,
  OPCODE_NAME__INIT_NS_FCALL_BY_NAME = 69,
  OPCODE_NAME__FREE = 70,
  OPCODE_NAME__INIT_ARRAY = 71,
  OPCODE_NAME__ADD_ARRAY_ELEMENT = 72,
  OPCODE_NAME__INCLUDE_OR_EVAL = 73,
  OPCODE_NAME__UNSET_VAR = 74,
  OPCODE_NAME__UNSET_DIM = 75,
  OPCODE_NAME__UNSET_OBJ = 76,
  OPCODE_NAME__FE_RESET = 77,
  OPCODE_NAME__FE_FETCH = 78,
  OPCODE_NAME__EXIT = 79,
  OPCODE_NAME__FETCH_R = 80,
  OPCODE_NAME__FETCH_DIM_R = 81,
  OPCODE_NAME__FETCH_OBJ_R = 82,
  OPCODE_NAME__FETCH_W = 83,
  OPCODE_NAME__FETCH_DIM_W = 84,
  OPCODE_NAME__FETCH_OBJ_W = 85,
  OPCODE_NAME__FETCH_RW = 86,
  OPCODE_NAME__FETCH_DIM_RW = 87,
  OPCODE_NAME__FETCH_OBJ_RW = 88,
  OPCODE_NAME__FETCH_IS = 89,
  OPCODE_NAME__FETCH_DIM_IS = 90,
  OPCODE_NAME__FETCH_OBJ_IS = 91,
  OPCODE_NAME__FETCH_FUNC_ARG = 92,
  OPCODE_NAME__FETCH_DIM_FUNC_ARG = 93,
  OPCODE_NAME__FETCH_OBJ_FUNC_ARG = 94,
  OPCODE_NAME__FETCH_UNSET = 95,
  OPCODE_NAME__FETCH_DIM_UNSET = 96,
  OPCODE_NAME__FETCH_OBJ_UNSET = 97,
  OPCODE_NAME__FETCH_DIM_TMP_VAR = 98,
  OPCODE_NAME__FETCH_CONSTANT = 99,
  OPCODE_NAME__GOTO = 100,
  OPCODE_NAME__EXT_STMT = 101,
  OPCODE_NAME__EXT_FCALL_BEGIN = 102,
  OPCODE_NAME__EXT_FCALL_END = 103,
  OPCODE_NAME__EXT_NOP = 104,
  OPCODE_NAME__TICKS = 105,
  OPCODE_NAME__SEND_VAR_NO_REF = 106,
  OPCODE_NAME__CATCH = 107,
  OPCODE_NAME__THROW = 108,
  OPCODE_NAME__FETCH_CLASS = 109,
  OPCODE_NAME__CLONE = 110,
  OPCODE_NAME__RETURN_BY_REF = 111,
  OPCODE_NAME__INIT_METHOD_CALL = 112,
  OPCODE_NAME__INIT_STATIC_METHOD_CALL = 113,
  OPCODE_NAME__ISSET_ISEMPTY_VAR = 114,
  OPCODE_NAME__ISSET_ISEMPTY_DIM_OBJ = 115,
  OPCODE_NAME__PRE_INC_OBJ = 132,
  OPCODE_NAME__PRE_DEC_OBJ = 133,
  OPCODE_NAME__POST_INC_OBJ = 134,
  OPCODE_NAME__POST_DEC_OBJ = 135,
  OPCODE_NAME__ASSIGN_OBJ = 136,
  OPCODE_NAME__INSTANCEOF = 138,
  OPCODE_NAME__DECLARE_CLASS = 139,
  OPCODE_NAME__DECLARE_INHERITED_CLASS = 140,
  OPCODE_NAME__DECLARE_FUNCTION = 141,
  OPCODE_NAME__RAISE_ABSTRACT_ERROR = 142,
  OPCODE_NAME__DECLARE_CONST = 143,
  OPCODE_NAME__ADD_INTERFACE = 144,
  OPCODE_NAME__DECLARE_INHERITED_CLASS_DELAYED = 145,
  OPCODE_NAME__VERIFY_ABSTRACT_CLASS = 146,
  OPCODE_NAME__ASSIGN_DIM = 147,
  OPCODE_NAME__ISSET_ISEMPTY_PROP_OBJ = 148,
  OPCODE_NAME__HANDLE_EXCEPTION = 149,
  OPCODE_NAME__USER_OPCODE = 150,
  OPCODE_NAME__JMP_SET = 152,
  OPCODE_NAME__DECLARE_LAMBDA_FUNCTION = 153,
  OPCODE_NAME__ADD_TRAIT = 154,
  OPCODE_NAME__BIND_TRAITS = 155,
  OPCODE_NAME__SEPARATE = 156,
  OPCODE_NAME__QM_ASSIGN_VAR = 157,
  OPCODE_NAME__JMP_SET_VAR = 158,
  OPCODE_NAME__DISCARD_EXCEPTION = 159,
  OPCODE_NAME__YIELD = 160,
  OPCODE_NAME__GENERATOR_RETURN = 161,
  OPCODE_NAME__FAST_CALL = 162,
  OPCODE_NAME__FAST_RET = 163,
  OPCODE_NAME__RECV_VARIADIC = 164,
  OPCODE_NAME__SEND_UNPACK = 165,
  OPCODE_NAME__POW = 166,
  OPCODE_NAME__ASSIGN_POW = 167
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(OPCODE_NAME)
} OpcodeName;
typedef enum _ZnodeType {
  ZNODE_TYPE__IS_CONST = 0,
  ZNODE_TYPE__IS_TMP_VAR = 1,
  ZNODE_TYPE__IS_VAR = 2,
  /*
   * Unused variable 
   */
  ZNODE_TYPE__IS_UNUSED = 3,
  /*
   * Compiled variable 
   */
  ZNODE_TYPE__IS_CV = 4,
  ZNODE_TYPE__EXT_TYPE_UNUSED = 5,
  ZNODE_TYPE__IS_OPNUM = 6,
  ZNODE_TYPE__IS_OPLINE = 7,
  ZNODE_TYPE__IS_CLASS = 8
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(ZNODE_TYPE)
} ZnodeType;
typedef enum _ZvalType {
  ZVAL_TYPE__IS_NULL = 0,
  ZVAL_TYPE__IS_LONG = 1,
  ZVAL_TYPE__IS_DOUBLE = 2,
  ZVAL_TYPE__IS_STRING = 3,
  ZVAL_TYPE__IS_ARRAY = 4,
  ZVAL_TYPE__IS_OBJECT = 5,
  ZVAL_TYPE__IS_RESOURCE = 6,
  ZVAL_TYPE__IS_CONSTANT = 7,
  ZVAL_TYPE__IS_CONSTANT_AST = 8,
  ZVAL_TYPE__IS_BOOL = 9
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(ZVAL_TYPE)
} ZvalType;

/* --- messages --- */

struct  _ZvalNull
{
  ProtobufCMessage base;
};
#define ZVAL_NULL__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&zval_null__descriptor) \
     }


struct  _ZvalLong
{
  ProtobufCMessage base;
  int64_t lval;
};
#define ZVAL_LONG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&zval_long__descriptor) \
    , 0 }


struct  _ZvalDouble
{
  ProtobufCMessage base;
  double dval;
};
#define ZVAL_DOUBLE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&zval_double__descriptor) \
    , 0 }


struct  _ZvalString
{
  ProtobufCMessage base;
  char *str;
};
#define ZVAL_STRING__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&zval_string__descriptor) \
    , (char *)protobuf_c_empty_string }


struct  _ZvalArray
{
  ProtobufCMessage base;
};
#define ZVAL_ARRAY__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&zval_array__descriptor) \
     }


struct  _ZvalObject
{
  ProtobufCMessage base;
};
#define ZVAL_OBJECT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&zval_object__descriptor) \
     }


struct  _ZvalBool
{
  ProtobufCMessage base;
  protobuf_c_boolean bval;
};
#define ZVAL_BOOL__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&zval_bool__descriptor) \
    , 0 }


struct  _ZvalResource
{
  ProtobufCMessage base;
};
#define ZVAL_RESOURCE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&zval_resource__descriptor) \
     }


struct  _ZvalConst
{
  ProtobufCMessage base;
  char *str;
};
#define ZVAL_CONST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&zval_const__descriptor) \
    , (char *)protobuf_c_empty_string }


struct  _ZvalConstAst
{
  ProtobufCMessage base;
};
#define ZVAL_CONST_AST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&zval_const_ast__descriptor) \
     }


typedef enum {
  ZVAL__VAL__NOT_SET = 0,
  ZVAL__VAL_NULL = 2,
  ZVAL__VAL_LONG = 3,
  ZVAL__VAL_DOUBLE = 4,
  ZVAL__VAL_STRING = 5,
  ZVAL__VAL_ARRAY = 6,
  ZVAL__VAL_OBJECT = 7,
  ZVAL__VAL_BOOL = 8,
  ZVAL__VAL_RESOURCE = 9,
  ZVAL__VAL_CONST = 10,
  ZVAL__VAL_CONST_AST = 11
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(ZVAL__VAL)
} Zval__ValCase;

struct  _Zval
{
  ProtobufCMessage base;
  ZvalType type;
  Zval__ValCase val_case;
  union {
    ZvalNull *null;
    ZvalLong *long_;
    ZvalDouble *double_;
    ZvalString *string;
    ZvalArray *array;
    ZvalObject *object;
    ZvalBool *bool_;
    ZvalResource *resource;
    ZvalConst *const_;
    ZvalConstAst *constast;
  };
};
#define ZVAL__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&zval__descriptor) \
    , ZVAL_TYPE__IS_NULL, ZVAL__VAL__NOT_SET, {0} }


struct  _Znode
{
  ProtobufCMessage base;
  ZnodeType type;
  Zval *zv;
};
#define ZNODE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&znode__descriptor) \
    , ZNODE_TYPE__IS_CONST, NULL }


struct  _OpcodeList
{
  ProtobufCMessage base;
  size_t n_codes;
  Opcode **codes;
};
#define OPCODE_LIST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&opcode_list__descriptor) \
    , 0,NULL }


struct  _Opcode
{
  ProtobufCMessage base;
  OpcodeName name;
  Znode *op1;
  Znode *op2;
};
#define OPCODE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&opcode__descriptor) \
    , OPCODE_NAME__NOP, NULL, NULL }


/* ZvalNull methods */
void   zval_null__init
                     (ZvalNull         *message);
size_t zval_null__get_packed_size
                     (const ZvalNull   *message);
size_t zval_null__pack
                     (const ZvalNull   *message,
                      uint8_t             *out);
size_t zval_null__pack_to_buffer
                     (const ZvalNull   *message,
                      ProtobufCBuffer     *buffer);
ZvalNull *
       zval_null__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   zval_null__free_unpacked
                     (ZvalNull *message,
                      ProtobufCAllocator *allocator);
/* ZvalLong methods */
void   zval_long__init
                     (ZvalLong         *message);
size_t zval_long__get_packed_size
                     (const ZvalLong   *message);
size_t zval_long__pack
                     (const ZvalLong   *message,
                      uint8_t             *out);
size_t zval_long__pack_to_buffer
                     (const ZvalLong   *message,
                      ProtobufCBuffer     *buffer);
ZvalLong *
       zval_long__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   zval_long__free_unpacked
                     (ZvalLong *message,
                      ProtobufCAllocator *allocator);
/* ZvalDouble methods */
void   zval_double__init
                     (ZvalDouble         *message);
size_t zval_double__get_packed_size
                     (const ZvalDouble   *message);
size_t zval_double__pack
                     (const ZvalDouble   *message,
                      uint8_t             *out);
size_t zval_double__pack_to_buffer
                     (const ZvalDouble   *message,
                      ProtobufCBuffer     *buffer);
ZvalDouble *
       zval_double__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   zval_double__free_unpacked
                     (ZvalDouble *message,
                      ProtobufCAllocator *allocator);
/* ZvalString methods */
void   zval_string__init
                     (ZvalString         *message);
size_t zval_string__get_packed_size
                     (const ZvalString   *message);
size_t zval_string__pack
                     (const ZvalString   *message,
                      uint8_t             *out);
size_t zval_string__pack_to_buffer
                     (const ZvalString   *message,
                      ProtobufCBuffer     *buffer);
ZvalString *
       zval_string__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   zval_string__free_unpacked
                     (ZvalString *message,
                      ProtobufCAllocator *allocator);
/* ZvalArray methods */
void   zval_array__init
                     (ZvalArray         *message);
size_t zval_array__get_packed_size
                     (const ZvalArray   *message);
size_t zval_array__pack
                     (const ZvalArray   *message,
                      uint8_t             *out);
size_t zval_array__pack_to_buffer
                     (const ZvalArray   *message,
                      ProtobufCBuffer     *buffer);
ZvalArray *
       zval_array__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   zval_array__free_unpacked
                     (ZvalArray *message,
                      ProtobufCAllocator *allocator);
/* ZvalObject methods */
void   zval_object__init
                     (ZvalObject         *message);
size_t zval_object__get_packed_size
                     (const ZvalObject   *message);
size_t zval_object__pack
                     (const ZvalObject   *message,
                      uint8_t             *out);
size_t zval_object__pack_to_buffer
                     (const ZvalObject   *message,
                      ProtobufCBuffer     *buffer);
ZvalObject *
       zval_object__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   zval_object__free_unpacked
                     (ZvalObject *message,
                      ProtobufCAllocator *allocator);
/* ZvalBool methods */
void   zval_bool__init
                     (ZvalBool         *message);
size_t zval_bool__get_packed_size
                     (const ZvalBool   *message);
size_t zval_bool__pack
                     (const ZvalBool   *message,
                      uint8_t             *out);
size_t zval_bool__pack_to_buffer
                     (const ZvalBool   *message,
                      ProtobufCBuffer     *buffer);
ZvalBool *
       zval_bool__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   zval_bool__free_unpacked
                     (ZvalBool *message,
                      ProtobufCAllocator *allocator);
/* ZvalResource methods */
void   zval_resource__init
                     (ZvalResource         *message);
size_t zval_resource__get_packed_size
                     (const ZvalResource   *message);
size_t zval_resource__pack
                     (const ZvalResource   *message,
                      uint8_t             *out);
size_t zval_resource__pack_to_buffer
                     (const ZvalResource   *message,
                      ProtobufCBuffer     *buffer);
ZvalResource *
       zval_resource__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   zval_resource__free_unpacked
                     (ZvalResource *message,
                      ProtobufCAllocator *allocator);
/* ZvalConst methods */
void   zval_const__init
                     (ZvalConst         *message);
size_t zval_const__get_packed_size
                     (const ZvalConst   *message);
size_t zval_const__pack
                     (const ZvalConst   *message,
                      uint8_t             *out);
size_t zval_const__pack_to_buffer
                     (const ZvalConst   *message,
                      ProtobufCBuffer     *buffer);
ZvalConst *
       zval_const__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   zval_const__free_unpacked
                     (ZvalConst *message,
                      ProtobufCAllocator *allocator);
/* ZvalConstAst methods */
void   zval_const_ast__init
                     (ZvalConstAst         *message);
size_t zval_const_ast__get_packed_size
                     (const ZvalConstAst   *message);
size_t zval_const_ast__pack
                     (const ZvalConstAst   *message,
                      uint8_t             *out);
size_t zval_const_ast__pack_to_buffer
                     (const ZvalConstAst   *message,
                      ProtobufCBuffer     *buffer);
ZvalConstAst *
       zval_const_ast__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   zval_const_ast__free_unpacked
                     (ZvalConstAst *message,
                      ProtobufCAllocator *allocator);
/* Zval methods */
void   zval__init
                     (Zval         *message);
size_t zval__get_packed_size
                     (const Zval   *message);
size_t zval__pack
                     (const Zval   *message,
                      uint8_t             *out);
size_t zval__pack_to_buffer
                     (const Zval   *message,
                      ProtobufCBuffer     *buffer);
Zval *
       zval__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   zval__free_unpacked
                     (Zval *message,
                      ProtobufCAllocator *allocator);
/* Znode methods */
void   znode__init
                     (Znode         *message);
size_t znode__get_packed_size
                     (const Znode   *message);
size_t znode__pack
                     (const Znode   *message,
                      uint8_t             *out);
size_t znode__pack_to_buffer
                     (const Znode   *message,
                      ProtobufCBuffer     *buffer);
Znode *
       znode__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   znode__free_unpacked
                     (Znode *message,
                      ProtobufCAllocator *allocator);
/* OpcodeList methods */
void   opcode_list__init
                     (OpcodeList         *message);
size_t opcode_list__get_packed_size
                     (const OpcodeList   *message);
size_t opcode_list__pack
                     (const OpcodeList   *message,
                      uint8_t             *out);
size_t opcode_list__pack_to_buffer
                     (const OpcodeList   *message,
                      ProtobufCBuffer     *buffer);
OpcodeList *
       opcode_list__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   opcode_list__free_unpacked
                     (OpcodeList *message,
                      ProtobufCAllocator *allocator);
/* Opcode methods */
void   opcode__init
                     (Opcode         *message);
size_t opcode__get_packed_size
                     (const Opcode   *message);
size_t opcode__pack
                     (const Opcode   *message,
                      uint8_t             *out);
size_t opcode__pack_to_buffer
                     (const Opcode   *message,
                      ProtobufCBuffer     *buffer);
Opcode *
       opcode__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   opcode__free_unpacked
                     (Opcode *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*ZvalNull_Closure)
                 (const ZvalNull *message,
                  void *closure_data);
typedef void (*ZvalLong_Closure)
                 (const ZvalLong *message,
                  void *closure_data);
typedef void (*ZvalDouble_Closure)
                 (const ZvalDouble *message,
                  void *closure_data);
typedef void (*ZvalString_Closure)
                 (const ZvalString *message,
                  void *closure_data);
typedef void (*ZvalArray_Closure)
                 (const ZvalArray *message,
                  void *closure_data);
typedef void (*ZvalObject_Closure)
                 (const ZvalObject *message,
                  void *closure_data);
typedef void (*ZvalBool_Closure)
                 (const ZvalBool *message,
                  void *closure_data);
typedef void (*ZvalResource_Closure)
                 (const ZvalResource *message,
                  void *closure_data);
typedef void (*ZvalConst_Closure)
                 (const ZvalConst *message,
                  void *closure_data);
typedef void (*ZvalConstAst_Closure)
                 (const ZvalConstAst *message,
                  void *closure_data);
typedef void (*Zval_Closure)
                 (const Zval *message,
                  void *closure_data);
typedef void (*Znode_Closure)
                 (const Znode *message,
                  void *closure_data);
typedef void (*OpcodeList_Closure)
                 (const OpcodeList *message,
                  void *closure_data);
typedef void (*Opcode_Closure)
                 (const Opcode *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    opcode_name__descriptor;
extern const ProtobufCEnumDescriptor    znode_type__descriptor;
extern const ProtobufCEnumDescriptor    zval_type__descriptor;
extern const ProtobufCMessageDescriptor zval_null__descriptor;
extern const ProtobufCMessageDescriptor zval_long__descriptor;
extern const ProtobufCMessageDescriptor zval_double__descriptor;
extern const ProtobufCMessageDescriptor zval_string__descriptor;
extern const ProtobufCMessageDescriptor zval_array__descriptor;
extern const ProtobufCMessageDescriptor zval_object__descriptor;
extern const ProtobufCMessageDescriptor zval_bool__descriptor;
extern const ProtobufCMessageDescriptor zval_resource__descriptor;
extern const ProtobufCMessageDescriptor zval_const__descriptor;
extern const ProtobufCMessageDescriptor zval_const_ast__descriptor;
extern const ProtobufCMessageDescriptor zval__descriptor;
extern const ProtobufCMessageDescriptor znode__descriptor;
extern const ProtobufCMessageDescriptor opcode_list__descriptor;
extern const ProtobufCMessageDescriptor opcode__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_proto_2fphp_5fopcode_2eproto__INCLUDED */
