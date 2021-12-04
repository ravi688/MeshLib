
#include <meshlib/obj/readers/ascii.h>
#include <meshlib/obj/parse_error.h>
#include <meshlib/obj/parse_callbacks.h>
#include <meshlib/parsers/string.h>
#include <hpml/vec3/header_config.h>
#include <hpml/vec3/vec3.h>
#include <hpml/vec4/header_config.h>
#include <hpml/vec4/vec4.h>
#include <hpml/vec2/header_config.h>
#include <hpml/vec2/vec2.h>


//NOTE: param: length also counts null character
function_signature(void, obj_parse_ascii, const char* text, u64 length, obj_parse_callbacks_t* parse_callbacks)
{
	CALLTRACE_BEGIN();
	string_parser_t p = string_parser_new(text, length); string_parser_bind(&p);

	while(string_parser_count() < (length - 1))
	{
		string_parser_skip_any_whitespace();
		while(string_parser_strcmp("#"))
		{
			string_parser_next_line();
			string_parser_skip_any_whitespace();
		}
		u8 match = 0x00;
		if(string_parser_strcmp_word("v"))
			match |= 1 << 1;	
		else if(string_parser_strcmp_word("vn"))
			match |= 1 << 2;	
		else if(string_parser_strcmp_word("vt"))
			match |= 1 << 3;
		else if(string_parser_strcmp_word("f"))
			match |= 1 << 4;

		switch(match)		
		{
			default:
			string_parser_next_line();
			break;

			//Parse vertex
			case (1 << 1):
			vec3_t(float) v = { string_parser_float(), string_parser_float(), string_parser_float() };
			if(parse_callbacks->vertex_position_callback != NULL)
				parse_callbacks->vertex_position_callback(v, parse_callbacks->user_data);
			break;

			//Parse normal
			case (1 << 2):
			vec3_t(float) n = { string_parser_float(), string_parser_float(), string_parser_float() };
			if(parse_callbacks->vertex_normal_callback != NULL)
				parse_callbacks->vertex_normal_callback(n, parse_callbacks->user_data);
			break;
			
			//Parse texcoord
			case (1 << 3):
			vec2_t(float) t = { string_parser_float(), string_parser_float() };
			if(parse_callbacks->vertex_texcoord_callback != NULL)
				parse_callbacks->vertex_texcoord_callback(t, parse_callbacks->user_data);
			break;
			
			//Parse facet
			case (1 << 4):
			vec4_t(vec3_t(int)) f = 
			{
				{ string_parser_u64(), string_parser_u64(), string_parser_u64() },
				{ string_parser_u64(), string_parser_u64(), string_parser_u64() },
				{ string_parser_u64(), string_parser_u64(), string_parser_u64() },
				{ string_parser_u64(), string_parser_u64(), string_parser_u64() }
			};

			if(parse_callbacks->facet_callback != NULL)
				parse_callbacks->facet_callback(f, parse_callbacks->user_data);
			break;
		}
	}

	CALLTRACE_END();
}

