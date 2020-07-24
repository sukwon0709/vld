#!/bin/bash

PREFIX_PATH=/home/soh/concolic_php

ZLOG_PATH=/home/soh/zlog
ZLOG_CFLAGS="-I${ZLOG_PATH}/include"
ZLOG_LDFLAGS="-L${ZLOG_PATH}/lib"
ZLOG_LIBS="${ZLOG_LDFLAGS} -lzlog -lpthread"

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

CFLAGS="${ZLOG_CFLAGS} ${PROTOBUF_CLIENT_CFLAGS} ${MM_CFLAGS} -DDISABLE_STRING_INTERNING -ggdb3"
LDFLAGS="${ZLOG_LDFLAGS} ${PROTOBUF_CLIENT_LDFLAGS} ${MM_LDFLAGS}"
LIBS="${ZLOG_LIBS} ${PROTOBUF_CLIENT_LIBS} ${MM_LIBS}"

./configure --prefix=${PREFIX_PATH} --with-php-config=${PREFIX_PATH}/bin/php-config CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}" LIBS="${LIBS}"
#./configure --prefix=${PREFIX_PATH} --with-php-config=${PREFIX_PATH}/bin/php-config CFLAGS="${XXHASH_CFLAGS} ${PROTOBUF_CLIENT_CFLAGS}" LDFLAGS="${XXHASH_LDFLAGS} ${PROTOBUF_CLIENT_LDFLAGS}" LIBS="${XXHASH_LIBS} ${PROTOBUF_CLIENT_LIBS}"
