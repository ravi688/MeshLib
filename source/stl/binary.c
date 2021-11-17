
#include <meshlib/stl/readers/binary.h>
#include <meshlib/stl/parse_error.h>
#include <meshlib/stl/stl.h>
#include <meshlib/parsers/binary.h>
#include <meshlib/assert.h>
#include <hpml/vec3/header_config.h>
#include <hpml/vec3/vec3.h>

static void free_normals(void* buffer)
{
	buf_free(buffer);
}

function_signature(mesh_t, stl_parse_binary, const char* bytes, u64 length)
{
	mesh_t mesh = mesh_new(stl_vertex_t); 
	mesh.user_free = free_normals;
	BUFFER* vertices = mesh.vertices;
	BUFFER* normals = mesh.user_data = BUFcreate(NULL, sizeof(vec3_t(float)), 0, 0);

	binary_parser_t p = binary_parser_new(bytes, length); binary_parser_bind(&p);
	binary_parser_skip_bytes(80);
	u32 triangle_count = binary_parser_u32(); 
	while(triangle_count > 0)
	{
		vec3_t(float) normal = { binary_parser_float(), binary_parser_float(), binary_parser_float() };
		buf_push(normals, &normal);
		for(int i = 0; i < 3; i++)
		{
			vec3_t(float) vertex = { binary_parser_float(), binary_parser_float(), binary_parser_float() };
			buf_push(vertices, &vertex);
		}
		binary_parser_skip_bytes(sizeof(u16));
		--triangle_count;
	}
	return mesh;
}