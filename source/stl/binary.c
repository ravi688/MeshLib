
#include <meshlib/stl/readers/binary.h>
#include <meshlib/stl/parse_error.h>
#include <meshlib/stl/parse_callbacks.h>
#include <meshlib/parsers/binary.h>
#include <meshlib/assert.h>
#include <hpml/vec3/header_config.h>
#include <hpml/vec3/vec3.h>

function_signature(void, stl_parse_binary, const char* bytes, u64 length, stl_parse_callbacks_t* parse_callbacks)
{
	CALLTRACE_BEGIN();
	binary_parser_t p = binary_parser_new(bytes, length); binary_parser_bind(&p);
	binary_parser_skip_bytes(80);
	u32 triangle_count = binary_parser_u32(); 
	while((triangle_count > 0) && (binary_parser_count() < length))
	{
		vec3_t(float) normal = { binary_parser_float(), binary_parser_float(), binary_parser_float() };
		if(parse_callbacks->vertex_normal_callback != NULL)
			parse_callbacks->vertex_normal_callback(normal, parse_callbacks->user_data);
		for(int i = 0; i < 3; i++)
		{
			vec3_t(float) vertex = { binary_parser_float(), binary_parser_float(), binary_parser_float() };
			if(parse_callbacks->vertex_position_callback != NULL)
				parse_callbacks->vertex_position_callback(vertex, parse_callbacks->user_data);
		}
		binary_parser_skip_bytes(sizeof(u16));
		--triangle_count;
	}
	binary_parser_unbind();
	CALLTRACE_END();
}