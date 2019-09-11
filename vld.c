/*
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2013 Derick Rethans                               |
   +----------------------------------------------------------------------+
   | This source file is subject to the 2-Clause BSD license which is     |
   | available through the LICENSE file, or online at                     |
   | http://opensource.org/licenses/bsd-license.php                       |
   +----------------------------------------------------------------------+
   | Authors:  Derick Rethans <derick@derickrethans.nl>                   |
   +----------------------------------------------------------------------+
 */
/* $Id: vld.c,v 1.40 2009-03-30 18:36:55 derick Exp $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/standard/url.h"
#include "php_vld.h"
#include "srm_oparray.h"
#include "php_globals.h"
#include "function_table.h"

#include "zlog.h"

#if PHP_VERSION_ID >= 50300
# define APPLY_TSRMLS_CC TSRMLS_CC
# define APPLY_TSRMLS_DC TSRMLS_DC
#else
# define APPLY_TSRMLS_CC
# define APPLY_TSRMLS_DC
#endif

static zend_op_array* (*old_compile_file)(zend_file_handle* file_handle, int type TSRMLS_DC);
static zend_op_array* vld_compile_file(zend_file_handle*, int TSRMLS_DC);

static zend_op_array* (*old_compile_string)(zval *source_string, char *filename TSRMLS_DC);
static zend_op_array* vld_compile_string(zval *source_string, char *filename TSRMLS_DC);

#if PHP_VERSION_ID >= 50500
static void (*old_execute_ex)(zend_execute_data *execute_data TSRMLS_DC);
static void vld_execute_ex(zend_execute_data *execute_data TSRMLS_DC);
static void vld_execute2_ex(zend_execute_data *execute_data TSRMLS_DC);
#else
static void (*old_execute)(zend_op_array *op_array TSRMLS_DC);
static void vld_execute(zend_op_array *op_array TSRMLS_DC);
static void vld_execute2(zend_op_array *op_array TSRMLS_DC);
#endif


zend_function_entry vld_functions[] = {
	{NULL, NULL, NULL}
};


zend_module_entry vld_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"vld",
	vld_functions,
	PHP_MINIT(vld),
	PHP_MSHUTDOWN(vld),
	PHP_RINIT(vld),	
	PHP_RSHUTDOWN(vld),
	PHP_MINFO(vld),
#if ZEND_MODULE_API_NO >= 20010901
	"0.13.0",
#endif
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_VLD
ZEND_GET_MODULE(vld)
#endif

ZEND_DECLARE_MODULE_GLOBALS(vld)

PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("vld.active",            "0", PHP_INI_SYSTEM, OnUpdateBool, active,       zend_vld_globals, vld_globals)
    STD_PHP_INI_ENTRY("vld.skip_prepend",      "0", PHP_INI_SYSTEM, OnUpdateBool, skip_prepend, zend_vld_globals, vld_globals)
    STD_PHP_INI_ENTRY("vld.skip_append",       "0", PHP_INI_SYSTEM, OnUpdateBool, skip_append,  zend_vld_globals, vld_globals)
    STD_PHP_INI_ENTRY("vld.execute",           "1", PHP_INI_SYSTEM, OnUpdateBool, execute,      zend_vld_globals, vld_globals)
    STD_PHP_INI_ENTRY("vld.verbosity",         "1", PHP_INI_SYSTEM, OnUpdateBool, verbosity,    zend_vld_globals, vld_globals)
    STD_PHP_INI_ENTRY("vld.format",            "0", PHP_INI_SYSTEM, OnUpdateBool, format,       zend_vld_globals, vld_globals)
    STD_PHP_INI_ENTRY("vld.col_sep",           "\t", PHP_INI_SYSTEM, OnUpdateString, col_sep,   zend_vld_globals, vld_globals)
	STD_PHP_INI_ENTRY("vld.save_dir",          "/tmp", PHP_INI_SYSTEM, OnUpdateString, save_dir, zend_vld_globals, vld_globals)
	STD_PHP_INI_ENTRY("vld.save_paths",        "0", PHP_INI_SYSTEM, OnUpdateBool, save_paths,   zend_vld_globals, vld_globals)
	STD_PHP_INI_ENTRY("vld.dump_paths",        "1", PHP_INI_SYSTEM, OnUpdateBool, dump_paths,   zend_vld_globals, vld_globals)
	STD_PHP_INI_ENTRY("vld.serialize",         "0", PHP_INI_SYSTEM, OnUpdateBool, serialize,    zend_vld_globals, vld_globals)
	STD_PHP_INI_ENTRY("vld.serialize_dir",     "/tmp", PHP_INI_SYSTEM, OnUpdateString, serialize_dir, zend_vld_globals, vld_globals)
	STD_PHP_INI_ENTRY("vld.network_serialize",         "0", PHP_INI_SYSTEM, OnUpdateBool, network_serialize,    zend_vld_globals, vld_globals)
	STD_PHP_INI_ENTRY("vld.log_path",		   "/tmp/vld.log", PHP_INI_SYSTEM, OnUpdateString, log_path, zend_vld_globals, vld_globals)
PHP_INI_END()
 
static void vld_init_globals(zend_vld_globals *vld_globals)
{
	vld_globals->active       = 0;
	vld_globals->skip_prepend = 0;
	vld_globals->skip_append  = 0;
	vld_globals->execute      = 1;
	vld_globals->format       = 0;
	vld_globals->col_sep	  = "\t";
	vld_globals->path_dump_file = NULL;
	vld_globals->dump_paths   = 1;
	vld_globals->save_paths   = 0;
	vld_globals->verbosity    = 1;
	vld_globals->serialize    = 0;
	vld_globals->serialize_file = NULL;
	vld_globals->network_serialize = 0;
	vld_globals->log_path = NULL;
	vld_globals->logger = NULL;
	
	ZEND_INIT_SYMTABLE_EX(&vld_globals->function_table, 2, 1);
}

PHP_MINIT_FUNCTION(vld)
{
	ZEND_INIT_MODULE_GLOBALS(vld, vld_init_globals, NULL);
	REGISTER_INI_ENTRIES();

	return SUCCESS;
}


PHP_MSHUTDOWN_FUNCTION(vld)
{
	UNREGISTER_INI_ENTRIES();

	zend_compile_file   = old_compile_file;
#if (PHP_MAJOR_VERSION > 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 2)
	zend_compile_string = old_compile_string;
#endif
#if PHP_VERSION_ID >= 50500
	zend_execute_ex     = old_execute_ex;
#else
	zend_execute        = old_execute;
#endif

	zend_hash_destroy(&VLD_G(function_table));
	//FREE_HASHTABLE(&VLD_G(function_table));

	return SUCCESS;
}



PHP_RINIT_FUNCTION(vld)
{
	old_compile_file = zend_compile_file;
#if (PHP_MAJOR_VERSION > 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 2)
	old_compile_string = zend_compile_string;
#endif
#if PHP_VERSION_ID >= 50500
	old_execute_ex = zend_execute_ex;
#else
	old_execute = zend_execute;
#endif

	if (VLD_G(active)) {
		zend_compile_file = vld_compile_file;
#if (PHP_MAJOR_VERSION > 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 2)
		zend_compile_string = vld_compile_string;
#endif
		if (!VLD_G(execute)) {
#if PHP_VERSION_ID >= 50500
			zend_execute_ex = vld_execute_ex;
#else
			zend_execute = vld_execute;
#endif
		} else {
			if (VLD_G(network_serialize)) {
#if PHP_VERSION_ID >= 50500
				zend_execute_ex = vld_execute2_ex;
#else
				zend_execute = vld_execute2;
#endif				
			}
		}
	}

	if (VLD_G(save_paths)) {
		char *filename;

		filename = malloc(strlen("paths.dot") + strlen(VLD_G(save_dir)) + 2);
		sprintf(filename, "%s/%s", VLD_G(save_dir), "paths.dot");

		VLD_G(path_dump_file) = fopen(filename, "w");
		free(filename);

		if (VLD_G(path_dump_file)) {
			fprintf(VLD_G(path_dump_file), "digraph {\n");
		}
	}

	VLD_G(logger) = fopen(VLD_G(log_path), "a+");

	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(vld)
{
	zend_compile_file = old_compile_file;
#if (PHP_MAJOR_VERSION > 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 2)
	zend_compile_string = old_compile_string;
#endif	
#if PHP_VERSION_ID >= 50500
	zend_execute_ex   = old_execute_ex;
#else
	zend_execute      = old_execute;
#endif

	if (VLD_G(path_dump_file)) {
		fprintf(VLD_G(path_dump_file), "}\n");
		fclose(VLD_G(path_dump_file));
	}
	fflush(stderr);

	fclose(VLD_G(logger));		// flushes too

	return SUCCESS;
}


PHP_MINFO_FUNCTION(vld)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "vld support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();

}

struct timeval measure_start()
{
	struct timeval tm;
	gettimeofday(&tm, NULL);
	return tm;
}

void measure_end(struct timeval tm_start, char *name)
{
	struct timeval tm_end;
	gettimeofday(&tm_end, NULL);
	unsigned long long t_diff = 1000 * (tm_end.tv_sec - tm_start.tv_sec) + (tm_end.tv_usec - tm_start.tv_usec) / 1000;
	fprintf(stderr, "%s Took: %llu ms\n", name, t_diff);
}

int vld_printf(FILE *stream, const char* fmt, ...)
{
	char *message;
	int len;
	va_list args;
	int i = 0, j = 0;
	char *ptr;
	const char EOL='\n';
	TSRMLS_FETCH();
	
	va_start(args, fmt);
	len = vspprintf(&message, 0, fmt, args);
	va_end(args);
	if (VLD_G(format)) {
		ptr = message;
		while (j < strlen(ptr)) {
			if (!isspace(ptr[j]) || ptr[j] == EOL) {
				ptr[i++] = ptr[j];
			}
			j++;
		}
		ptr[i] = 0;

		fprintf(stream, "%s%s", VLD_G(col_sep), ptr);
	} else {
		fprintf(stream, "%s", message);
	}

	efree(message);
	
	return len;
}

static int vld_check_fe (zend_op_array *fe, zend_bool *have_fe TSRMLS_DC)
{
	if (fe->type == ZEND_USER_FUNCTION) {
		*have_fe = 1;
	}

	return 0;
}

static int vld_dump_fe (zend_op_array *fe APPLY_TSRMLS_DC, int num_args, va_list args, zend_hash_key *hash_key)
{
#if PHP_VERSION_ID < 50300
	TSRMLS_FETCH()
#endif
	if (fe->type == ZEND_USER_FUNCTION) {
		ZVAL_VALUE_STRING_TYPE *new_str;
		int new_len;

		new_str = php_url_encode(ZHASHKEYSTR(hash_key), ZHASHKEYLEN(hash_key) - 1 PHP_URLENCODE_NEW_LEN(new_len));
		VLD_PRINTF1(0, "FUNCTION %s:\n", ZSTRING_VALUE(new_str));
		if (!check_function_entry(ZSTRING_VALUE(new_str), &VLD_G(function_table))) {
			VLD_PRINTF1(0, "FUNCTION %s IS NEW\n", ZSTRING_VALUE(new_str));
			vld_dump_oparray(fe TSRMLS_CC);
			add_function_entry(ZSTRING_VALUE(new_str), &VLD_G(function_table));
		}
		VLD_PRINTF1(0, "End of FUNCTION %s\n\n", ZSTRING_VALUE(new_str));
		efree(new_str);
	}

	return ZEND_HASH_APPLY_KEEP;
}

#ifdef ZEND_ENGINE_2
static int vld_dump_cle (zend_class_entry **class_entry TSRMLS_DC)
#else
static int vld_dump_cle (zend_class_entry *class_entry TSRMLS_DC)
#endif
{
	zend_class_entry *ce;
	zend_bool have_fe = 0;

#ifdef ZEND_ENGINE_2
	ce = *class_entry;
#else
	ce = class_entry;
#endif

	if (ce->type != ZEND_INTERNAL_CLASS) {	
		if (VLD_G(path_dump_file)) {
			fprintf(VLD_G(path_dump_file), "subgraph cluster_class_%s { label=\"class %s\";\n", ZSTRING_VALUE(ce->name), ZSTRING_VALUE(ce->name));
		}

		zend_hash_apply_with_argument(&ce->function_table, (apply_func_arg_t) vld_check_fe, (void *)&have_fe TSRMLS_CC);
		if (have_fe) {
			VLD_PRINTF1(0, "Class %s:\n", ZSTRING_VALUE(ce->name));
			zend_hash_apply_with_arguments(&ce->function_table APPLY_TSRMLS_CC, (apply_func_args_t) vld_dump_fe, 0);
			VLD_PRINTF1(0, "End of class %s.\n\n", ZSTRING_VALUE(ce->name));
		} else {
			VLD_PRINTF1(0, "Class %s: [no user functions]\n", ZSTRING_VALUE(ce->name));
		}

		if (VLD_G(path_dump_file)) {
			fprintf(VLD_G(path_dump_file), "}\n");
		}
	}

	return ZEND_HASH_APPLY_KEEP;
}

/* {{{ zend_op_array vld_compile_file (file_handle, type)
 *    This function provides a hook for compilation */
static zend_op_array *vld_compile_file(zend_file_handle *file_handle, int type TSRMLS_DC)
{
	zend_op_array *op_array;

	if (!VLD_G(execute) &&
		((VLD_G(skip_prepend) && PG(auto_prepend_file) && PG(auto_prepend_file)[0] && PG(auto_prepend_file) == file_handle->filename) ||
	     (VLD_G(skip_append)  && PG(auto_append_file)  && PG(auto_append_file)[0]  && PG(auto_append_file)  == file_handle->filename)))
	{
		zval nop;
#if PHP_VERSION_ID >= 70000
		zend_op_array *ret;
		ZVAL_STRINGL(&nop, "RETURN ;", 8);
		ret = compile_string(&nop, "NOP" TSRMLS_CC);
		zval_dtor(&nop);
		return ret;
#else
		ZVAL_STRINGL(&nop, "RETURN ;", 8, 0);
		return compile_string(&nop, "NOP" TSRMLS_CC);
#endif
	}

	op_array = old_compile_file (file_handle, type TSRMLS_CC);

	if (VLD_G(path_dump_file)) {
		fprintf(VLD_G(path_dump_file), "subgraph cluster_file_%08x { label=\"file %s\";\n", op_array, op_array->filename ? ZSTRING_VALUE(op_array->filename) : "__main");
	}
	if (op_array) {
		struct timeval tm_start = measure_start();
		vld_dump_oparray (op_array TSRMLS_CC);
		measure_end(tm_start, "vld_dump_oparray1");
	}

	// I think Zend compiles function and class definitions and stores them to compiler globals (CG) when compiling the overall scripts.
	// They are looked up during function calls and their opcode arrays are retrieved.
	zend_hash_apply_with_arguments (CG(function_table) APPLY_TSRMLS_CC, (apply_func_args_t) vld_dump_fe, 0);
	zend_hash_apply (CG(class_table), (apply_func_t) vld_dump_cle TSRMLS_CC);

	if (VLD_G(path_dump_file)) {
		fprintf(VLD_G(path_dump_file), "}\n");
	}

	return op_array;
}
/* }}} */

/* {{{ zend_op_array vld_compile_string (source_string, filename)
 *    This function provides a hook for compilation */
static zend_op_array *vld_compile_string(zval *source_string, char *filename TSRMLS_DC)
{
	zend_op_array *op_array;

	op_array = old_compile_string (source_string, filename TSRMLS_CC);

	if (op_array) {
		struct timeval tm_start = measure_start();
		vld_dump_oparray (op_array TSRMLS_CC);
		measure_end(tm_start, "vld_dump_oparray2");

		zend_hash_apply_with_arguments (CG(function_table) APPLY_TSRMLS_CC, (apply_func_args_t) vld_dump_fe, 0);
		zend_hash_apply (CG(class_table), (apply_func_t) vld_dump_cle TSRMLS_CC);
	}

	return op_array;
}
/* }}} */

/* {{{
 *    PHP >= 5.5.0
 *        void vld_execute_ex(zend_execute_data *execute_data TSRMLS_DC)
 *    PHP <= 5.4.x
 *        void vld_execute(zend_op_array *op_array TSRMLS_DC)
 *    This function provides a hook for execution */
#if PHP_VERSION_ID >= 50500
static void vld_execute_ex(zend_execute_data *execute_data TSRMLS_DC)
#else
static void vld_execute(zend_op_array *op_array TSRMLS_DC)
#endif
{
	// nothing to do
}

#if PHP_VERSION_ID >= 50500
static void vld_execute2_ex(zend_execute_data *execute_data TSRMLS_DC)
#else
static void vld_execute2(zend_op_array *op_array TSRMLS_DC)
#endif
{
	if (UC(concolic_enabled)) {
		const char *filename = estrdup(execute_data->op_array->filename);
		const char *scopename = execute_data->op_array->scope ? estrdup(execute_data->op_array->scope->name): NULL;
		const char *funcname = execute_data->op_array->function_name ? estrdup(execute_data->op_array->function_name) : NULL;

		zlog_debug(EG(vldcat), "SEND_START_OF_SCRIPT: %s - %s - %s", filename, scopename, funcname);
		send_start_of_script(UC(ucphp_request), filename, scopename, funcname);

		// zlog_debug(EG(vldcat), "SEND_EXEUTED_OPCODE_LIST_AND_MAKE_NEW1");
		UC(current_executed_opcode_list) = new_executed_opcode_list(UC(ucphp_request)); // send_executed_opcode_list_and_make_new(UC(current_executed_opcode_list));

		zlog_debug(EG(vldcat), "START EXECUTING OPCODES!");
#if PHP_VERSION_ID >= 50500
		old_execute_ex(execute_data TSRMLS_CC);
#else
		old_execute (op_array TSRMLS_CC);
#endif	

		// zlog_debug(EG(vldcat), "SEND_EXECUTED_OPCODE_LIST_AND_MAKE_NEW2");		// seems to be expensive point here...
		// UC(current_executed_opcode_list) = send_executed_opcode_list_and_make_new(UC(current_executed_opcode_list));
		// UC(current_executed_opcode_list) = new_executed_opcode_list(UC(ucphp_request));

		zlog_debug(EG(vldcat), "SEND_END_OF_SCRIPT: %s - %s - %s", filename, scopename, funcname);
		send_end_of_script(UC(ucphp_request), filename, scopename, funcname);

		efree(filename);
		if (scopename) efree(scopename);
		if (funcname) efree(funcname);

	} else {
#if PHP_VERSION_ID >= 50500
		old_execute_ex(execute_data TSRMLS_CC);
#else
		old_execute (op_array TSRMLS_CC);
#endif			
	}
}
/* }}} */
