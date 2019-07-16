#ifndef __VLD_FUNCTION_TABLE_h
#define __VLD_FUNCTION_TABLE_h

#include "php_vld.h"

void add_function_entry(const char *function_name, HashTable *ht);
int check_function_entry(const char *function_name, HashTable *ht);

#endif