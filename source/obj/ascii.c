
#include <meshlib/obj/readers/ascii.h>
#include <meshlib/obj/parse_error.h>
#include <meshlib/obj/obj.h>
#include <meshlib/parsers/string.h>

#include <hpml/vec3/header_config.h>
#include <hpml/vec3/vec3.h>
#include <hpml/vec4/header_config.h>
#include <hpml/vec4/vec4.h>
#include <hpml/vec2/header_config.h>
#include <hpml/vec2/vec2.h>

instantiate_vec4_struct(vec3_t(int));

static void free_buffer(BUFFER* buffer)
{
	buf_free(buffer);
}

function_signature(mesh_t, obj_parse_ascii, const char* text, u64 length)
{
	CALLTRACE_BEGIN();
	string_parser_t p = string_parser_new(text); string_parser_bind(&p);
	mesh_t mesh = mesh_new(BUFFER);
	mesh.vertices->free = (void (*)(void*))free_buffer;
	{
		BUFFER vertices = buf_create(sizeof(vec3_t(float)), 0, 0);
		BUFFER texcoords = buf_create(sizeof(vec2_t(float)), 0, 0);
		BUFFER normals = buf_create(sizeof(vec3_t(float)), 0, 0);
		BUFFER facets = buf_create(sizeof(vec4_t(vec3_t(int))), 0, 0);
		buf_push(mesh.vertices, &vertices);
		buf_push(mesh.vertices, &texcoords);
		buf_push(mesh.vertices, &normals);
		buf_push(mesh.vertices, &facets);
	}
	BUFFER* vertices = buf_getptr_at(mesh.vertices, 0);
	BUFFER* texcoords = buf_getptr_at(mesh.vertices, 1);
	BUFFER* normals = buf_getptr_at(mesh.vertices, 2);
	BUFFER* facets = buf_getptr_at(mesh.vertices, 3);

	while(string_parser_count() < length)
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
			buf_push(vertices, &v);
			printf("Vertex: (%f, %f, %f)\n", v.x, v.y, v.z);
			break;

			//Parse normal
			case (1 << 2):
			vec3_t(float) n = { string_parser_float(), string_parser_float(), string_parser_float() };
			buf_push(normals, &n);
			printf("Normal: (%f, %f, %f)\n", n.x, n.y, n.z);
			break;
			
			//Parse texcoord
			case (1 << 3):
			vec2_t(float) t = { string_parser_float(), string_parser_float() };
			buf_push(texcoords, &t);
			printf("TexCoord: (%f, %f)\n", t.x, t.y);
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
			
			printf("Facet: %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", 
				f.x.x, f.x.y, f.x.z, f.y.x, f.y.y, f.y.z, f.z.x, f.z.y, f.z.z, f.w.x, f.w.y, f.w.z);
			break;
		}
	}

	CALLTRACE_RETURN(mesh);
}

