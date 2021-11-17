
#include <meshlib/stl/parse_error.h>
#include <meshlib/assert.h>

function_signature(void, stl_parse_error, u64 error_type, u64 line_no)
{
	CALLTRACE_BEGIN();
	switch(error_type) 
	{
		case STL_PARSE_ERROR_SOLID_HEADER_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_SOLID_HEADER_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_FACET_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_FACET_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_URECOGNIZED_KEYWORD: LOG_FETAL_ERR("STL_PARSE_ERROR_URECOGNIZED_KEYWORD\n"); break;
		case STL_PARSE_ERROR_INVALID_SINGLE_PRECISION_FLOAT: LOG_FETAL_ERR("STL_PARSE_ERROR_INVALID_SINGLE_PRECISION_FLOAT\n"); break;
		case STL_PARSE_ERROR_END_LOOP_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_END_LOOP_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_END_FACET_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_END_FACET_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_NORMAL_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_NORMAL_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_OUTER_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_OUTER_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_LOOP_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_LOOP_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_VERTEX_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_VERTEX_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_END_SOLID_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_END_SOLID_NOT_FOUND\n"); break;
		default: LOG_FETAL_ERR("STL_PARSE_ERROR: Unkown Error\n");
	}
	CALLTRACE_END();
}
