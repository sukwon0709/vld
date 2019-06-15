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

/* --- messages --- */

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
};
#define OPCODE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&opcode__descriptor) \
    , OPCODE_NAME__NOP }


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

typedef void (*OpcodeList_Closure)
                 (const OpcodeList *message,
                  void *closure_data);
typedef void (*Opcode_Closure)
                 (const Opcode *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    opcode_name__descriptor;
extern const ProtobufCMessageDescriptor opcode_list__descriptor;
extern const ProtobufCMessageDescriptor opcode__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_proto_2fphp_5fopcode_2eproto__INCLUDED */