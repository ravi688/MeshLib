
#include <meshlib/obj/readers/binary.h>
#include <hpml/vec3.h>
#include <hpml/vec2.h>
#include <hpml/vec4.h>

#include <meshlib/assert.h>


MESHLIB_API function_signature(void, obj_parse_binary, const char* bytes, u64 length, obj_parse_callbacks_t* parse_callbacks)
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

	CALLTRACE_END();
}