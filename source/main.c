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
#include <calltrace/calltrace.h>

#include <safe_memory/safe_memory.h>

#include <disk_manager/file_reader.h>
#include <disk_manager/file_writer.h>

#include <meshlib/stl/readers/ascii.h>
#include <meshlib/stl/readers/binary.h>
#include <meshlib/stl/parse_callbacks.h>

#include <meshlib/obj/readers/ascii.h>
#include <meshlib/obj/readers/binary.h>
#include <meshlib/obj/parse_callbacks.h>

#include <string.h>


void print_normal(float* normal, void* ptr)
{
	printf("NORMAL -> (%f, %f, %f)\n", normal[0], normal[1], normal[2]);
}

void print_position(float* position, void* ptr)
{
	printf("POSITION -> (%f, %f, %f)\n", position[0], position[1], position[2]);
}

void print_texcoord(float* texcoord, void* ptr)
{
	printf("TEXCOORD -> (%f, %f)\n", texcoord[0], texcoord[1]);
}

void print_facet(u32* facet, u32 attrib_count, u32 face_vertex_count, void* ptr)
{
	printf("FACET -> ");
	for(int i = 0; i < face_vertex_count; i++)
	{
		printf("(");
		for(int j = 0; j < attrib_count; j++)
			printf(" %u", facet[i * attrib_count + j]);
		printf(" ) ");
	}
	puts("");
}

int main(int argc, char** argv)
{
	safe_memory_init();

	BUFFER* stl_data = load_text_from_file("resource/ASCII-box.stl");
	BUFFER* stl_binary = load_binary_from_file("resource/Binary-box.stl");
	stl_parse_callbacks_t stl_callbacks =
	{
		.vertex_normal_callback = print_normal,
		.vertex_position_callback = print_position
	};
	puts("STL-ASCII");
	stl_parse_ascii(stl_data->bytes, stl_data->element_count, &stl_callbacks);

	puts("\nSTL-BINARY");
	stl_parse_binary(stl_binary->bytes, stl_binary->element_count, &stl_callbacks);
	
	buf_free(stl_binary);
	buf_free(stl_data);

	printf("Value: %d\n", strtoul("\t\t     456///", NULL, 0));

	BUFFER* obj_ascii_data = load_text_from_file("resource/Sphere.obj");
	obj_parse_callbacks_t obj_callbacks =
	{
		.vertex_position_callback = print_position,
		.vertex_normal_callback = print_normal,
		.vertex_texcoord_callback = print_texcoord,
		.facet_callback = print_facet
	};
	puts("\nOBJ-ASCII");
	obj_parse_ascii(obj_ascii_data->bytes, obj_ascii_data->element_count, &obj_callbacks);
	buf_free(obj_ascii_data);

	safe_memory_terminate();
	return 0;
}