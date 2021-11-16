
#include <meshlib/readers/stl/ascii.h>
#include <meshlib/readers/stl/vertex.h>
#include <meshlib/parsers/string.h>
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

function_signature(mesh_t, stl_parse_ascii, const char* text)
{
	CALLTRACE_BEGIN();
	mesh_t mesh = mesh_new(stl_vertex_t);
	mesh.user_free = free_normals;
	BUFFER* vertices = mesh.vertices;
	BUFFER* normals = mesh.user_data = BUFcreate(NULL, sizeof(vec3_t(float)), 0, 0);

	string_parser_t p = string_parser_new(text); string_parser_bind(&p);

	string_parser_skip_any_whitespace();

	if(!string_parser_strcmp("solid"))
		stl_parse_error(STL_PARSE_ERROR_SOLID_HEADER_NOT_FOUND, string_parser_line_count());
	
	string_parser_next_line();
	string_parser_skip_whitespaces();

	while(!string_parser_strcmp("endsolid"))
	{	
		if(!string_parser_strcmp("facet"))
			stl_parse_error(STL_PARSE_ERROR_FACET_NOT_FOUND, string_parser_line_count());
		string_parser_skip_whitespaces();
		if(!string_parser_strcmp("normal"))
			stl_parse_error(STL_PARSE_ERROR_NORMAL_NOT_FOUND, string_parser_line_count());

		vec3_t(float) normal =  { string_parser_float(), string_parser_float(), string_parser_float() };
		buf_push(normals, &normal);
	
		string_parser_next_line();
		string_parser_skip_whitespaces();
		
		if(!string_parser_strcmp("outer"))
			stl_parse_error(STL_PARSE_ERROR_OUTER_NOT_FOUND, string_parser_line_count());
		string_parser_skip_whitespaces(); 
		if(!string_parser_strcmp("loop"))
			stl_parse_error(STL_PARSE_ERROR_LOOP_NOT_FOUND, string_parser_line_count());

		for(int i = 0; i < 3; i++)
		{
			string_parser_next_line();
			string_parser_skip_whitespaces();

			if(!string_parser_strcmp("vertex"))
				stl_parse_error(STL_PARSE_ERROR_VERTEX_NOT_FOUND, string_parser_line_count());
		
			stl_vertex_t vertex = 
			{
				.position = { string_parser_float(), string_parser_float(), string_parser_float() }
			};
			buf_push(vertices, &vertex);
		}

		string_parser_next_line(); 
		string_parser_skip_whitespaces(); 

		if(!string_parser_strcmp("endloop"))
			stl_parse_error(STL_PARSE_ERROR_END_LOOP_NOT_FOUND, string_parser_line_count());

		string_parser_next_line(); 
		string_parser_skip_whitespaces();

		if(!string_parser_strcmp("endfacet"))
			stl_parse_error(STL_PARSE_ERROR_END_FACET_NOT_FOUND, string_parser_line_count());

		string_parser_next_line();
		string_parser_skip_whitespaces();
	}

	CALLTRACE_END();
	return mesh;
}