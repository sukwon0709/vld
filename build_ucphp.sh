#!/bin/bash

PREFIX_PATH=/home/soh/concolic_php
#PREFIX_PATH=/home/soh/php-5.6.40
STACK_VERSION=8.6.5
STACK_PATH="/home/soh/.stack/programs/x86_64-linux/ghc-${STACK_VERSION}"

ZLOG_PATH=/home/soh/zlog
ZLOG_CFLAGS="-I${ZLOG_PATH}/include"
ZLOG_LDFLAGS="-L${ZLOG_PATH}/lib"
ZLOG_LIBS="${ZLOG_LDFLAGS} -lzlog -lpthread"

XXHASH_PATH=/home/soh/xxHash
XXHASH_CFLAGS="-I${XXHASH_PATH}/include"
XXHASH_LDFLAGS="-L${XXHASH_PATH}/lib"
XXHASH_LIBS="${XXHASH_LDFLAGS} -lxxhash"

UCPHP_PATH=/home/soh/git/uc-php
UCPHP_CFLAGS="-I${UCPHP_PATH}/dependencies/uc-php-ffi/includes -I${STACK_PATH}/lib/ghc-${STACK_VERSION}/include"
UCPHP_LDFLAGS="-L${UCPHP_PATH} -L${STACK_PATH}/lib/ghc-${STACK_VERSION}/rts -Wl,-rpath,${STACK_PATH}/lib/ghc-${STACK_VERSION}/rts"
UCPHP_LIBS="${UCPHP_LDFLAGS} -lucphp_ffi -lHSrts-ghc${STACK_VERSION}"

PROTOBUF_CFLAGS=`pkg-config --cflags protobuf`
PROTOBUF_LIBS=`pkg-config --libs protobuf`
GRPC_LIBS=`pkg-config --libs grpc grpc++`

PROTOBUF_CLIENT_PATH=/home/soh/git/uc-php/dependencies/uc-php-proto-client
PROTOBUF_CLIENT_CFLAGS="-I${PROTOBUF_CLIENT_PATH}/includes"
PROTOBUF_CLIENT_LDFLAGS="-L${PROTOBUF_CLIENT_PATH}"
PROTOBUF_CLIENT_LIBS="${PROTOBUF_CLIENT_LDFLAGS} ${PROTOBUF_LIBS} ${GRPC_LIBS} -lucphp_proto_client -lstdc++"

MM_PATH=/home/soh/git/uc-php/dependencies/uc-php-mm
MM_CFLAGS="-I${MM_PATH}"
MM_LDFLAGS="-L${MM_PATH}"
MM_LIBS="${MM_LDFLAGS} -lucphp_mm -lstdc++"

YAML_PATH=/home/soh/yaml-cpp
YAML_CFLAGS="-I${YAML_PATH}/include"
YAML_LDFLAGS="-L${YAML_PATH}/lib"
YAML_LIBS="${YAML_LDFLAGS} -lyaml-cpp"

TARGETS_PATH=/home/soh/git/uc-php/dependencies/uc-php-targets
TARGETS_CFLAGS="-I${TARGETS_PATH}/includes"
TARGETS_LDFLAGS="-L${TARGETS_PATH}"
TARGETS_LIBS="${TARGETS_LDFLAGS} ${YAML_LIBS} -lucphp_targets -lstdc++"

CFLAGS="${ZLOG_CFLAGS} ${XXHASH_CFLAGS} ${UCPHP_CFLAGS} ${PROTOBUF_CLIENT_CFLAGS} ${MM_CFLAGS} ${TARGETS_CFLAGS} -DDISABLE_STRING_INTERNING -ggdb3"
LDFLAGS="${ZLOG_LDFLAGS} ${XXHASH_LDFLAGS} ${UCPHP_LDFLAGS} ${PROTOBUF_CLIENT_LDFLAGS} ${MM_LDFLAGS} ${TARGETS_LDFLAGS}"
LIBS="${ZLOG_LIBS} ${XXHASH_LIBS} ${UCPHP_LIBS} ${PROTOBUF_CLIENT_LIBS} ${MM_LIBS} ${TARGETS_LIBS}"

./configure --prefix=${PREFIX_PATH} --with-php-config=${PREFIX_PATH}/bin/php-config CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}" LIBS="${LIBS}"
#./configure --prefix=${PREFIX_PATH} --with-php-config=${PREFIX_PATH}/bin/php-config CFLAGS="${XXHASH_CFLAGS} ${PROTOBUF_CLIENT_CFLAGS}" LDFLAGS="${XXHASH_LDFLAGS} ${PROTOBUF_CLIENT_LDFLAGS}" LIBS="${XXHASH_LIBS} ${PROTOBUF_CLIENT_LIBS}"
