#!/bin/bash

PREFIX_PATH=/home/soh/concolic_php
STACK_PATH=/home/soh/.stack/programs/x86_64-linux/ghc-8.6.4

ZLOG_PATH=/home/soh/zlog
ZLOG_CFLAGS="-I${ZLOG_PATH}/include"
ZLOG_LDFLAGS="-L${ZLOG_PAHT}/lib"
ZLOG_LIBS="-Wl,-rpath,${ZLOG_PATH}/lib -L${ZLOG_PATH}/lib -lzlog -lpthread"

XXHASH_PATH=/home/soh/xxHash
XXHASH_CFLAGS="-I${XXHASH_PATH}/include"
XXHASH_LDFLAGS="-L${XXHASH_PATH}/lib"
XXHASH_LIBS="-Wl,-rpath,${XXHASH_PATH}/lib -L${XXHASH_PATH}/lib -lxxhash"

PROTOBUF_CFLAGS="-I/home/soh/protobuf-c/include"
PROTOBUF_LIBS="-L/home/soh/protobuf-c/lib -lprotobuf-c"
PROTOBUF_PROTO_CFLAGS="-I../.."

UCPHP_PATH=/home/soh/git/uc-php
UCPHP_CFLAGS="-I${UCPHP_PATH}/includes"
UCPHP_LDFLAGS="-L${UCPHP_PATH}"
UCPHP_LIBS="-L${UCPHP_PATH} -luc_php -Wl,-rpath,/home/soh/git/uc-php"
UCPHP2_LIBS="-L${UCPHP_PATH} -luc_php2 -Wl,-rpath,/home/soh/git/uc-php"
HASKELL_LIBS="-L${STACK_PATH}/lib/ghc-8.6.4/rts -lHSrts-ghc8.6.4 -Wl,-rpath,${STACK_PATH}/lib/ghc-8.6.4/rts"

CFLAGS="${HASKELL_CFLAGS} ${ZLOG_CFLAGS} ${XXHASH_CFLAGS} ${UCPHP_CFLAGS} ${PROTOBUF_CFLAGS} ${PROTOBUF_PROTO_CFLAGS} -DDISABLE_STRING_INTERNING -ggdb3 --coverage"
LDFLAGS="${HASKELL_LDFLAGS} ${ZLOG_LDFLAGS} ${XXHASH_LDFLAGS} ${PROTOBUF_LIBS} ${UCPHP_LDFLAGS} --coverage"
LIBS="${ZLOG_LIBS} ${XXHASH_LIBS} ${UCPHP_LIBS} ${UCPHP2_LIBS} ${PROTOBUF_LIBS} ${HASKELL_LIBS}"

./configure --prefix=${PREFIX_PATH} --with-php-config=${PREFIX_PATH}/bin/php-config CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}" LIBS="${LIBS}"
