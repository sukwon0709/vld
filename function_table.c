#include "php.h"
#include "function_table.h"

// adds an entry about function
void add_function_entry(const char *function_name, HashTable *ht)
{
    int val = 0;        // dummy value to insert for every key.

    // strlen returns number of characters until NULL, excluding NULL.
    zend_symtable_update(ht, function_name, strlen(function_name)+1, &val, sizeof(int), NULL);
}

// returns 1 if the function entry is found; 0 otherwise.
int check_function_entry(const char *function_name, HashTable *ht)
{    
    return zend_symtable_exists(ht, function_name, strlen(function_name) + 1);
}