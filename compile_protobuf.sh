#!/bin/bash

protoc -I../uc-php-proto --cpp_out=. ../uc-php-proto/php_opcode.proto
