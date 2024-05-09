
#include <meshlib/stl/readers/ascii.h>
#include <meshlib/stl/parse_error.h>
#include <meshlib/stl/parse_callbacks.h>
#include <meshlib/parsers/string.h>
#include <meshlib/assert.h>

MESHLIB_API function_signature(void, stl_parse_ascii, const char* text, u64 length, stl_parse_callbacks_t* parse_callbacks)
{
	CALLTRACE_BEGIN();
	string_parser_t p = string_parser_new(text, length);

	string_parser_skip_any_whitespace(&p);

	if(!string_parser_strcmp(&p, "solid"))
		stl_parse_error(STL_PARSE_ERROR_SOLID_HEADER_NOT_FOUND, string_parser_line_count(&p));

	string_parser_next_line(&p);	
	string_parser_skip_any_whitespace(&p);	

	while(!string_parser_strcmp(&p, "endsolid"))
	{	
		if(!string_parser_strcmp(&p, "facet"))
			stl_parse_error(STL_PARSE_ERROR_FACET_NOT_FOUND, string_parser_line_count(&p));
		string_parser_skip_whitespaces(&p);
		if(!string_parser_strcmp(&p, "normal"))
			stl_parse_error(STL_PARSE_ERROR_NORMAL_NOT_FOUND, string_parser_line_count(&p));

		float normal[3] =  { string_parser_float(&p), string_parser_float(&p), string_parser_float(&p) };
		if(parse_callbacks->vertex_normal_callback != NULL)
			parse_callbacks->vertex_normal_callback(&normal[0], parse_callbacks->user_data);
	
		string_parser_skip_any_whitespace(&p);
		
		if(!string_parser_strcmp(&p, "outer"))
			stl_parse_error(STL_PARSE_ERROR_OUTER_NOT_FOUND, string_parser_line_count(&p));
		string_parser_skip_whitespaces(&p); 
		if(!string_parser_strcmp(&p, "loop"))
			stl_parse_error(STL_PARSE_ERROR_LOOP_NOT_FOUND, string_parser_line_count(&p));

		for(int i = 0; i < 3; i++)
		{
			string_parser_skip_any_whitespace(&p);

			if(!string_parser_strcmp(&p, "vertex"))
				stl_parse_error(STL_PARSE_ERROR_VERTEX_NOT_FOUND, string_parser_line_count(&p));
		
			float position[3] = { string_parser_float(&p), string_parser_float(&p), string_parser_float(&p) };
			if(parse_callbacks->vertex_position_callback != NULL)
				parse_callbacks->vertex_position_callback(&position[0], parse_callbacks->user_data);
		}

		string_parser_skip_any_whitespace(&p);

		if(!string_parser_strcmp(&p, "endloop"))
			stl_parse_error(STL_PARSE_ERROR_END_LOOP_NOT_FOUND, string_parser_line_count(&p));

		string_parser_skip_any_whitespace(&p);

		if(!string_parser_strcmp(&p, "endfacet"))
			stl_parse_error(STL_PARSE_ERROR_END_FACET_NOT_FOUND, string_parser_line_count(&p));

		string_parser_skip_any_whitespace(&p);
	}

	CALLTRACE_END();
}

