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

#include <hpml/vec3/header_config.h>
#include <hpml/vec3/vec3.h>

#include <hpml/vec4/header_config.h>
#include <hpml/vec4/vec4.h>

#include <hpml/vec2/header_config.h>
#include <hpml/vec2/vec2.h>

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


void print_normal(vec3_t(float) normal, void* ptr)
{
	printf("NORMAL -> (%f, %f, %f)\n", normal.x, normal.y, normal.z);
}

void print_position(vec3_t(float) position, void* ptr)
{
	printf("POSITION -> (%f, %f, %f)\n", position.x, position.y, position.z);
}

void print_texcoord(vec2_t(float) texcoord, void* ptr)
{
	printf("TEXCOORD -> (%f, %f)\n", texcoord.x, texcoord.y);
}

void print_facet(vec4_t(vec3_t(int)) facet, void* ptr)
{
	printf("FACET -> (%d, %d, %d) (%d, %d, %d) (%d, %d, %d) (%d, %d, %d)\n",
		facet.x.x, facet.x.y, facet.x.z,
		facet.y.x, facet.y.y, facet.y.z,
		facet.z.x, facet.z.y, facet.z.z,
		facet.w.x, facet.w.y, facet.w.z);
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
	stl_parse_ascii(stl_data->bytes, &stl_callbacks);
	stl_parse_binary(stl_binary->bytes, stl_binary->element_count, &stl_callbacks);
	
	buf_free(stl_binary);
	buf_free(stl_data);

	BUFFER* obj_ascii_data = load_text_from_file("resource/Box.obj");
	obj_parse_callbacks_t obj_callbacks =
	{
		.vertex_position_callback = print_position,
		.vertex_normal_callback = print_normal,
		.vertex_texcoord_callback = print_texcoord,
		.facet_callback = print_facet
	};
	obj_parse_ascii(obj_ascii_data->bytes, obj_ascii_data->element_count, &obj_callbacks);
	buf_free(obj_ascii_data);

	safe_memory_terminate();
	return 0;
}