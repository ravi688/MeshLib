
#pragma once

#include <hpml/vec4/header_config.h>
#include <hpml/vec4/vec4.h>
#include <hpml/vec3/header_config.h>
#include <hpml/vec3/vec3.h>
#include <hpml/vec2/header_config.h>
#include <hpml/vec2/vec2.h>

#ifndef VEC4_VEC3
instantiate_vec4_struct(vec3_t(int));
#define VEC4_VEC3
#endif

typedef struct obj_parse_callbacks_t
{
	void* user_data;
	void (*vertex_position_callback)(vec3_t(float) position, void* user_data);
	void (*vertex_normal_callback)(vec3_t(float) normal, void* user_data);
	void (*vertex_texcoord_callback)(vec2_t(float) texcoord, void* user_data);
	void (*facet_callback)(vec4_t(vec3_t(int)) facet, void* user_data);
} obj_parse_callbacks_t;

