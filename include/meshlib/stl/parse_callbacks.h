
#pragma once

typedef struct stl_parse_callbacks_t
{
	void* user_data;
	void (*vertex_position_callback)(float* position, void*);
	void (*vertex_normal_callback)(float* normal, void*);
} stl_parse_callbacks_t;
