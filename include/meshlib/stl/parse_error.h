

#pragma once

#include <calltrace/calltrace.h>
#include <meshlib/defines.h>

#ifdef __cplusplus
extern "C" {
#endif


enum stl_parse_error_t
{
	STL_PARSE_ERROR_SOLID_HEADER_NOT_FOUND,
	STL_PARSE_ERROR_FACET_NOT_FOUND,
	STL_PARSE_ERROR_URECOGNIZED_KEYWORD,
	STL_PARSE_ERROR_INVALID_SINGLE_PRECISION_FLOAT,
	STL_PARSE_ERROR_END_LOOP_NOT_FOUND,
	STL_PARSE_ERROR_END_FACET_NOT_FOUND,
	STL_PARSE_ERROR_NORMAL_NOT_FOUND,
	STL_PARSE_ERROR_OUTER_NOT_FOUND,
	STL_PARSE_ERROR_LOOP_NOT_FOUND,
	STL_PARSE_ERROR_VERTEX_NOT_FOUND,
	STL_PARSE_ERROR_END_SOLID_NOT_FOUND
};

function_signature(void, stl_parse_error, u64 error_type, u64 line_no);
#define stl_parse_error(...) define_alias_function_macro(stl_parse_error, __VA_ARGS__)

#ifdef __cplusplus
}
#endif
