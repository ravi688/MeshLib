
#include <meshlib/obj/readers/binary.h>
#include <meshlib/assert.h>
#include <hpml/vec3/header_config.h>
#include <hpml/vec3/vec3.h>
#include <hpml/vec2/header_config.h>
#include <hpml/vec2/vec2.h>
#include <hpml/vec4/header_config.h>
#include <hpml/vec4/vec4.h>


instantiate_vec4_struct(vec3_t(int));

static void free_buffer(BUFFER* buffer)
{
	buf_free(buffer);
}

function_signature(mesh_t, obj_parse_binary, const char* bytes, u64 length)
{
	CALLTRACE_BEGIN();
	LOG_FETAL_ERR("obj_parse_binary isn't implemented because the standard binary version doesn't exists\n");
	// binary_parser_t p = binary_parser_new(bytes, length); binary_parser_bind(&p);
	// mesh_t mesh = mesh_new(BUFFER);
	// mesh.vertices->free = (void (*)(void*))free_buffer;
	// {
	// 	BUFFER vertices = buf_create(sizeof(vec3_t(float)), 0, 0);
	// 	BUFFER texcoords = buf_create(sizeof(vec2_t(float)), 0, 0);
	// 	BUFFER normals = buf_create(sizeof(vec3_t(float)), 0, 0);
	// 	BUFFER facets = buf_create(sizeof(vec4_t(vec3_t(int))), 0, 0);
	// 	buf_push(mesh.vertices, &vertices);
	// 	buf_push(mesh.vertices, &texcoords);
	// 	buf_push(mesh.vertices, &normals);
	// 	buf_push(mesh.vertices, &facets);
	// }
	// BUFFER* vertices = buf_getptr_at(mesh.vertices, 0);
	// BUFFER* texcoords = buf_getptr_at(mesh.vertices, 1);
	// BUFFER* normals = buf_getptr_at(mesh.vertices, 2);
	// BUFFER* facets = buf_getptr_at(mesh.vertices, 3);

	// while(binary_parser_count() < length)
	// {

	// }

	CALLTRACE_RETURN();
}