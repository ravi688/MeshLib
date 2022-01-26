
#pragma once

#include <meshlib/defines.h>

typedef struct obj_parse_callbacks_t
{
	void* user_data;
	void (*vertex_position_callback)(float* position, void* user_data);
	void (*vertex_normal_callback)(float* normal, void* user_data);
	void (*vertex_texcoord_callback)(float* texcoord, void* user_data);
	void (*facet_callback)(u32* facet, u32 attribute_count, u32 face_vertex_count, void* user_data);
} obj_parse_callbacks_t;

