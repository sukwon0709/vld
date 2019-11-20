#!/bin/bash

PREFIX_PATH=/home/soh/concolic_php
STACK_PATH=/home/soh/.stack/programs/x86_64-linux/ghc-8.6.4

ZLOG_PATH=/home/soh/zlog
ZLOG_CFLAGS="-I${ZLOG_PATH}/include"
ZLOG_LDFLAGS="-L${ZLOG_PATH}/lib"
ZLOG_LIBS="${ZLOG_LDFLAGS} -lzlog -lpthread"

XXHASH_PATH=/home/soh/xxHash
XXHASH_CFLAGS="-I${XXHASH_PATH}/include"
XXHASH_LDFLAGS="-L${XXHASH_PATH}/lib"
XXHASH_LIBS="${XXHASH_LDFLAGS} -lxxhash"

UCPHP_PATH=/home/soh/git/uc-php
UCPHP_CFLAGS="-I${UCPHP_PATH}/dependencies/uc-php-ffi/includes -I${STACK_PATH}/lib/ghc-8.6.4/include"
UCPHP_LDFLAGS="-L${UCPHP_PATH} -L${STACK_PATH}/lib/ghc-8.6.4/rts -Wl,-rpath,${STACK_PATH}/lib/ghc-8.6.4/rts"
UCPHP_LIBS="${UCPHP_LDFLAGS} -lucphp_ffi -lHSrts-ghc8.6.4"

PROTOBUF_CLIENT_PATH=/home/soh/git/uc-php/dependencies/uc-php-proto-client
PROTOBUF_CLIENT_CFLAGS="-I${PROTOBUF_CLIENT_PATH}/includes"
PROTOBUF_CLIENT_LDFLAGS="-L${PROTOBUF_CLIENT_PATH}"
PROTOBUF_CLIENT_LIBS="${PROTOBUF_CLIENT_LDFLAGS} -lprotobuf -lgrpc -lgrpc++ -lucphp_proto_client -lstdc++"

MM_PATH=/home/soh/git/uc-php/dependencies/uc-php-mm
MM_CFLAGS="-I${MM_PATH}"
MM_LDFLAGS="-L${MM_PATH}"
MM_LIBS="${MM_LDFLAGS} -lucphp_mm -lstdc++"

CFLAGS="${ZLOG_CFLAGS} ${XXHASH_CFLAGS} ${UCPHP_CFLAGS} ${PROTOBUF_CLIENT_CFLAGS} ${MM_CFLAGS} -DDISABLE_STRING_INTERNING -ggdb3"
LDFLAGS="${ZLOG_LDFLAGS} ${XXHASH_LDFLAGS} ${UCPHP_LDFLAGS} ${PROTOBUF_CLIENT_LDFLAGS} ${MM_LDFLAGS}"
LIBS="${ZLOG_LIBS} ${XXHASH_LIBS} ${UCPHP_LIBS} ${PROTOBUF_CLIENT_LIBS} ${MM_LIBS}"

./configure --prefix=${PREFIX_PATH} --with-php-config=${PREFIX_PATH}/bin/php-config CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}" LIBS="${LIBS}"
