
#pragma once

#include <calltrace/calltrace.h>

#ifdef __cplusplus
extern "C" {
#endif

enum obj_parse_error_t
{
	OBJ_PARSE_ERROR_VERTEX_NOT_FOUND,
	OBJ_PARSE_ERROR_UNRECOGNIZED_KEYWORD,
	OBJ_PARSE_ERROR_TEXCOORD_NOT_FOUND,
	OBJ_PARSE_ERROR_NORMAL_NOT_FOUND,
	OBJ_PARSE_ERROR_FACET_NOT_FOUND
};


function_signature(void, obj_parse_error, u64 error_type, u64 line_no);
#define obj_parse_error(...) define_alias_function_macro(obj_parse_error, __VA_ARGS__)


#ifdef __cplusplus
}
#endif
