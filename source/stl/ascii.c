
#include <meshlib/stl/readers/ascii.h>
#include <meshlib/stl/parse_error.h>
#include <meshlib/stl/parse_callbacks.h>
#include <meshlib/parsers/string.h>
#include <meshlib/assert.h>

MESHLIB_API function_signature(void, stl_parse_ascii, const char* text, u64 length, stl_parse_callbacks_t* parse_callbacks)
{
	CALLTRACE_BEGIN();
	string_parser_t p = string_parser_new(text, length); string_parser_bind(&p);

	string_parser_skip_any_whitespace();

	if(!string_parser_strcmp("solid"))
		stl_parse_error(STL_PARSE_ERROR_SOLID_HEADER_NOT_FOUND, string_parser_line_count());

	string_parser_next_line();	
	string_parser_skip_any_whitespace();	

	while(!string_parser_strcmp("endsolid"))
	{	
		if(!string_parser_strcmp("facet"))
			stl_parse_error(STL_PARSE_ERROR_FACET_NOT_FOUND, string_parser_line_count());
		string_parser_skip_whitespaces();
		if(!string_parser_strcmp("normal"))
			stl_parse_error(STL_PARSE_ERROR_NORMAL_NOT_FOUND, string_parser_line_count());

		float normal[3] =  { string_parser_float(), string_parser_float(), string_parser_float() };
		if(parse_callbacks->vertex_normal_callback != NULL)
			parse_callbacks->vertex_normal_callback(&normal[0], parse_callbacks->user_data);
	
		string_parser_skip_any_whitespace();
		
		if(!string_parser_strcmp("outer"))
			stl_parse_error(STL_PARSE_ERROR_OUTER_NOT_FOUND, string_parser_line_count());
		string_parser_skip_whitespaces(); 
		if(!string_parser_strcmp("loop"))
			stl_parse_error(STL_PARSE_ERROR_LOOP_NOT_FOUND, string_parser_line_count());

		for(int i = 0; i < 3; i++)
		{
			string_parser_skip_any_whitespace();

			if(!string_parser_strcmp("vertex"))
				stl_parse_error(STL_PARSE_ERROR_VERTEX_NOT_FOUND, string_parser_line_count());
		
			float position[3] = { string_parser_float(), string_parser_float(), string_parser_float() };
			if(parse_callbacks->vertex_position_callback != NULL)
				parse_callbacks->vertex_position_callback(&position[0], parse_callbacks->user_data);
		}

		string_parser_skip_any_whitespace();

		if(!string_parser_strcmp("endloop"))
			stl_parse_error(STL_PARSE_ERROR_END_LOOP_NOT_FOUND, string_parser_line_count());

		string_parser_skip_any_whitespace();

		if(!string_parser_strcmp("endfacet"))
			stl_parse_error(STL_PARSE_ERROR_END_FACET_NOT_FOUND, string_parser_line_count());

		string_parser_skip_any_whitespace();
	}

	CALLTRACE_END();
}

