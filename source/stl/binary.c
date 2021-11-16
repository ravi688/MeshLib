
#include <meshlib/readers/stl/binary.h>
#include <meshlib/readers/stl/vertex.h>
#include <meshlib/parsers/binary.h>
#include <meshlib/assert.h>
#include <hpml/vec3/header_config.h>
#include <hpml/vec3/vec3.h>

enum STL_PARSE_ERROR
{
	STL_PARSE_ERROR_SOLID_HEADER_NOT_FOUND,
	STL_PARSE_ERROR_FACET_NOT_FOUND,
	STL_PARSE_ERROR_URECOGNIZED_KEYWORD,
	STL_PARSE_ERROR_INVALID_SINGLE_PRECISION_FLOAT,
	STL_PARSE_ERROR_END_LOOP_NOT_FOUND,
	STL_PARSE_ERROR_END_FACET_NOT_FOUND,
	STL_PARSE_ERROR_NORMAL_NOT_FOUND,
	STL_PARSE_ERROR_OUTER_NOT_FOUND,
	STL_PARSE_ERROR_LOOP_NOT_FOUND,
	STL_PARSE_ERROR_VERTEX_NOT_FOUND,
	STL_PARSE_ERROR_END_SOLID_NOT_FOUND
};

function_signature(static void, stl_parse_error, u64 error_type, u64 line_no);
#define stl_parse_error(...) define_alias_function_macro(stl_parse_error, __VA_ARGS__)

function_signature(static void, stl_parse_error, u64 error_type, u64 line_no)
{
	CALLTRACE_BEGIN();
	switch(error_type) 
	{
		case STL_PARSE_ERROR_SOLID_HEADER_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_SOLID_HEADER_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_FACET_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_FACET_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_URECOGNIZED_KEYWORD: LOG_FETAL_ERR("STL_PARSE_ERROR_URECOGNIZED_KEYWORD\n"); break;
		case STL_PARSE_ERROR_INVALID_SINGLE_PRECISION_FLOAT: LOG_FETAL_ERR("STL_PARSE_ERROR_INVALID_SINGLE_PRECISION_FLOAT\n"); break;
		case STL_PARSE_ERROR_END_LOOP_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_END_LOOP_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_END_FACET_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_END_FACET_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_NORMAL_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_NORMAL_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_OUTER_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_OUTER_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_LOOP_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_LOOP_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_VERTEX_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_VERTEX_NOT_FOUND\n"); break;
		case STL_PARSE_ERROR_END_SOLID_NOT_FOUND: LOG_FETAL_ERR("STL_PARSE_ERROR_END_SOLID_NOT_FOUND\n"); break;
		default: LOG_FETAL_ERR("STL_PARSE_ERROR: Unkown Error\n");
	}
	CALLTRACE_END();
}


static void free_normals(void* buffer)
{
	buf_free(buffer);
}

function_signature(mesh_t, stl_parse_binary, const char* bytes, u64 length)
{
	mesh_t mesh = mesh_new(stl_vertex_t); 
	mesh.user_free = free_normals;
	BUFFER* vertices = mesh.vertices;
	BUFFER* normals = mesh.user_data = BUFcreate(NULL, sizeof(vec3_t(float)), 0, 0);

	binary_parser_t p = binary_parser_new(bytes, length); binary_parser_bind(&p);
	binary_parser_skip_bytes(80);
	u32 triangle_count = binary_parser_u32(); 
	while(triangle_count > 0)
	{
		vec3_t(float) normal = { binary_parser_float(), binary_parser_float(), binary_parser_float() };
		buf_push(normals, &normal);
		for(int i = 0; i < 3; i++)
		{
			vec3_t(float) vertex = { binary_parser_float(), binary_parser_float(), binary_parser_float() };
			buf_push(vertices, &vertex);
			binary_parser_skip_bytes(sizeof(u16));
		}
		--triangle_count;
	}
	return mesh;
}