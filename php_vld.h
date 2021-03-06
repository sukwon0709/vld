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
/* $Id: php_vld.h,v 1.9 2009-03-30 18:22:15 derick Exp $ */

#ifndef PHP_VLD_H
#define PHP_VLD_H

#include "php.h"
#include "UCPHPCClient.h"
#include "map.h"

extern zend_module_entry vld_module_entry;
#define phpext_vld_ptr &vld_module_entry

#ifdef PHP_WIN32
#define PHP_VLD_API __declspec(dllexport)
#else
#define PHP_VLD_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(vld);
PHP_MSHUTDOWN_FUNCTION(vld);
PHP_RINIT_FUNCTION(vld);
PHP_RSHUTDOWN_FUNCTION(vld);
PHP_MINFO_FUNCTION(vld);

ZEND_BEGIN_MODULE_GLOBALS(vld)
	int active;
	int skip_prepend;
	int skip_append;
	int execute;
	int verbosity;
	int format;
	char *col_sep;
	int save_paths;
	char *save_dir;
	FILE *path_dump_file;
	int dump_paths;
	int serialize;					// dumps opcodes to serialize_file
	char *serialize_dir;
	FILE *serialize_file;
	int network_serialize;								// sends opcodes to remote server for analysis
	char *network_serialize_name;						// remote server host:port

	int enable_logging;								// enables logging
	char *log_path;										// log path
	FILE *logger;											// log handle
ZEND_END_MODULE_GLOBALS(vld) 

int vld_printf(FILE *stream, const char* fmt, ...);

#ifdef ZTS
#define VLD_G(v) TSRMG(vld_globals_id, zend_vld_globals *, v)
#else
#define VLD_G(v) (vld_globals.v)
#endif
#define VLD_PRINT(v,args) if (VLD_G(verbosity) >= (v)) { vld_printf(stderr, args); }
#define VLD_PRINT1(v,args,x) if (VLD_G(verbosity) >= (v)) { vld_printf(stderr, args, (x)); }
#define VLD_PRINT2(v,args,x,y) if (VLD_G(verbosity) >= (v)) { vld_printf(stderr, args, (x), (y)); }
#define VLD_PRINT3(v,args,x,y,z) if (VLD_G(verbosity) >= (v)) { vld_printf(stderr, args, (x), (y), (z)); }

#define VLD_PRINTF(v,args) if (VLD_G(verbosity) >= (v)) { vld_printf(VLD_G(logger), args); }
#define VLD_PRINTF1(v,args,x) if (VLD_G(verbosity) >= (v)) { vld_printf(VLD_G(logger), args, (x)); }
#define VLD_PRINTF2(v,args,x,y) if (VLD_G(verbosity) >= (v)) { vld_printf(VLD_G(logger), args, (x), (y)); }
#define VLD_PRINTF3(v,args,x,y,z) if (VLD_G(verbosity) >= (v)) { vld_printf(VLD_G(logger), args, (x), (y), (z)); }

#define SERIALIZE_MODE (VLD_G(serialize) || VLD_G(network_serialize))

#if PHP_VERSION_ID >= 70000
# define ZHASHKEYSTR(k) ((k)->key->val)
# define ZHASHKEYLEN(k) ((k)->key->len)
# define PHP_URLENCODE_NEW_LEN(v)

# define ZVAL_VALUE_TYPE                zend_value
# define ZVAL_VALUE_STRING_TYPE         zend_string
# define ZVAL_STRING_VALUE(s)           (s.str)->val
# define ZVAL_STRING_LEN(s)             (s.str)->len
# define ZSTRING_VALUE(s)               (s)->val
# define OPARRAY_VAR_NAME(v)            (v)->val
#else
# define ZHASHKEYSTR(k) ((k)->arKey)
# define ZHASHKEYLEN(k) ((k)->nKeyLength)
# define PHP_URLENCODE_NEW_LEN(v) , &(v)

# define ZVAL_VALUE_TYPE                zvalue_value
# define ZVAL_VALUE_STRING_TYPE         char
# define ZVAL_STRING_VALUE(s)           (s.str.val)
# define ZVAL_STRING_LEN(s)             (s.str.len)
# define ZSTRING_VALUE(s)               (s)
# define OPARRAY_VAR_NAME(v)            (v).name
#endif

#endif


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
