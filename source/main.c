/*
TODO: 
1. Make buf_free() more secure
2. Modify safe_memory.c; look at this
	function_signature(void*, register_stack_allocation, void* basePtr, u64 size)
{
	HEAD_BYTE(basePtr) = 0;		//stack allocation
	return register_allocation(basePtr, size);
}

*/



#include <stdio.h>
#include <meshlib/data_structures.h>
#include <calltrace/calltrace.h>

#include <hpml/vec3/header_config.h>
#include <hpml/vec3/vec3.h>

#include <hpml/vec4/header_config.h>
#include <hpml/vec4/vec4.h>

#include <hpml/vec2/header_config.h>
#include <hpml/vec2/vec2.h>


#include <disk_manager/file_reader.h>
#include <disk_manager/file_writer.h>
#include <meshlib/readers/stl/ascii.h>
#include <meshlib/readers/stl/binary.h>


#include <string.h>

typedef struct 
{
	vec4_t(float) color;
	vec3_t(float) position;
	vec3_t(float) normal;
	vec2_t(float) uv;
} vertex3d_t;

int main(int argc, char** argv)
{
	safe_memory_init();

	BUFFER* stl_data = load_text_from_file("resource/ASCII-box.stl");
	BUFFER* stl_binary = load_binary_from_file("resource/Binary-box.stl");
	mesh_t asciiBox = stl_parse_ascii(stl_data->bytes);
	mesh_t binaryBox = stl_parse_binary(stl_binary->bytes, stl_binary->element_count);
	BUFFER* normals = asciiBox.user_data;
	puts("ASCII: ");
	for(int i = 0; i < buf_get_element_count(normals); i++)
	{
		vec3_t(float) normal; 
		buf_get_at(normals, i, &normal);
		printf("\tnormal: (%f, %f, %f)\n", normal.x, normal.y, normal.z);
		
	}
	puts("Binary: ");
	for(int i = 0; i < buf_get_element_count(binaryBox.user_data); i++)
	{
		vec3_t(float) normal; 
		buf_get_at(binaryBox.user_data, i, &normal);
		printf("\tnormal: (%f, %f, %f)\n", normal.x, normal.y, normal.z);	
	}

	write_binary_to_file("Copy-Binary-box.stl", stl_binary->bytes, stl_binary->element_count);
	buf_free(stl_binary);
	buf_free(stl_data);
	mesh_destroy(asciiBox);
	mesh_destroy(binaryBox);
	// mesh_t mesh = mesh_new(vertex3d_t);
	// vertex3d_t vertices[2] = 
	// {
	// 	{ { 1, 1, 1, 1 }, { 0, 0, 0 }, { 0, 1, 0 }, { 1, 0 } },
	// 	{ { 1, 1, 1, 1 }, { 0, 0, 0 }, { 0, 1, 0 }, { 1, 0 } }
	// };
	// mesh_vertex_add(mesh, &vertices[0]);
	// mesh_vertex_addv(mesh, vertices, 2);
	// vertex3d_t* __vertices = mesh_vertices(vertex3d_t, mesh);

	// for(int i = 0; i < buf_get_element_count(mesh.vertices); i++)
	// {
	// 	vertex3d_t vertex = __vertices[i];
	// 	log_msg("vertex[%u]: color(%.2f, %.2f, %.2f, %.2f), position(%.2f, %.2f, %.2f), normal(%.2f, %.2f, %.2f), uv(%.2f, %.2f)\n",
	// 		i,
	// 		vertex.color.x, vertex.color.y, vertex.color.z, vertex.color.w,
	// 		vertex.position.x, vertex.position.y, vertex.position.z,
	// 		vertex.normal.x, vertex.normal.y, vertex.normal.z,
	// 		vertex.uv.x, vertex.uv.y);
	// }
	// mesh_vertices_clear(mesh);
	// mesh_destroy(mesh);
	safe_memory_terminate();
	return 0;
}