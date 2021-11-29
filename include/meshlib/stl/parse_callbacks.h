
#pragma once

#include <hpml/vec3/header_config.h>
#include <hpml/vec3/vec3.h>

typedef struct stl_parse_callbacks_t
{
	void* user_data;
	void (*vertex_position_callback)(vec3_t(float), void*);
	void (*vertex_normal_callback)(vec3_t(float), void*);
} stl_parse_callbacks_t;
