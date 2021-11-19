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

#include <meshlib/stl/readers/ascii.h>
#include <meshlib/stl/readers/binary.h>

#include <meshlib/obj/readers/ascii.h>
#include <meshlib/obj/readers/binary.h>

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
	
	buf_free(stl_binary);
	buf_free(stl_data);
	mesh_destroy(asciiBox);
	mesh_destroy(binaryBox);

	BUFFER* obj_ascii_data = load_text_from_file("resource/Box.obj");
	mesh_t obj_asciiBox = obj_parse_ascii(obj_ascii_data->bytes, obj_ascii_data->element_count);
	buf_free(obj_ascii_data);

	// BUFFER* obj_binary_data = load_binary_from_file("resource/Binary-Box.obj");
	// mesh_t obj_binaryBox = obj_parse_binary(obj_binary_data->bytes, obj_binary_data->element_count);
	// buf_free(obj_binary_data);

	safe_memory_terminate();
	return 0;
}