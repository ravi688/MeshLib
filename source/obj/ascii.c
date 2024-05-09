
#include <meshlib/obj/readers/ascii.h>
#include <meshlib/obj/parse_error.h>
#include <meshlib/obj/parse_callbacks.h>
#include <meshlib/parsers/string.h>
#include <stdlib.h>


//NOTE: param: length also counts null character
MESHLIB_API function_signature(void, obj_parse_ascii, const char* text, u64 length, obj_parse_callbacks_t* parse_callbacks)
{
	CALLTRACE_BEGIN();
	string_parser_t p = string_parser_new(text, length);

	while(string_parser_count(&p) < (length - 1))
	{
		string_parser_skip_any_whitespace(&p);
		while(string_parser_strcmp(&p, "#"))
			string_parser_next_line(&p);
		u8 match = 0x00;
		if(string_parser_strcmp_word(&p, "v"))
			match |= 1 << 1;	
		else if(string_parser_strcmp_word(&p, "vn"))
			match |= 1 << 2;	
		else if(string_parser_strcmp_word(&p, "vt"))
			match |= 1 << 3;
		else if(string_parser_strcmp_word(&p, "f"))
			match |= 1 << 4;

		switch(match)		
		{
			default:
			string_parser_next_line(&p);
			break;

			//Parse vertex
			case (1 << 1):
			float v[3] = { string_parser_float(&p), string_parser_float(&p), string_parser_float(&p) };
			if(parse_callbacks->vertex_position_callback != NULL)
				parse_callbacks->vertex_position_callback(&v[0], parse_callbacks->user_data);
			break;

			//Parse normal
			case (1 << 2):
			float n[3] = { string_parser_float(&p), string_parser_float(&p), string_parser_float(&p) };
			if(parse_callbacks->vertex_normal_callback != NULL)
				parse_callbacks->vertex_normal_callback(&n[0], parse_callbacks->user_data);
			break;
			
			//Parse texcoord
			case (1 << 3):
			float t[2] = { string_parser_float(&p), string_parser_float(&p) };
			if(parse_callbacks->vertex_texcoord_callback != NULL)
				parse_callbacks->vertex_texcoord_callback(&t[0], parse_callbacks->user_data);
			break;
			
			//Parse facet
			case (1 << 4):
			u32 facet[16] = { };
			u32 face_vertex_count = 0;
			const char* ptr = p.data;
			u32 value = 0;
			u32 attrib_count = 0;
			char* endptr = NULL;
			u32 prev_attrib_count = 0;
			while((value = strtoul(ptr, &endptr, 0)))
			{
				ptr = endptr;
				facet[prev_attrib_count * face_vertex_count + attrib_count] = value;
				++attrib_count;
				if((*ptr) == '/')
				{
					while((*ptr) == '/') ptr++;
					continue;
				}
				else if(((*ptr) == ' ') || ((*ptr) == '\t') || ((*ptr) == '\n'))
				{
					face_vertex_count++;
					prev_attrib_count = attrib_count;
					attrib_count = 0;
					continue;
				}
			}
			p.data = ptr;
			if(parse_callbacks->facet_callback != NULL)
				parse_callbacks->facet_callback((u32*)facet, prev_attrib_count, face_vertex_count, parse_callbacks->user_data);
			break;
		}
	}

	CALLTRACE_END();
}

