
#include <meshlib/readers/stl/ascii.h>
#include <meshlib/readers/stl/vertex.h>
#include <meshlib/assert.h>
#include <hpml/vec3/header_config.h>
#include <hpml/vec3/vec3.h>
#include <string.h>
#include <stdlib.h>

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

typedef struct 
{
	const char* data;
	u64 cursor;
} parser_t;

static parser_t* binded_parser = NULL;

parser_t parser_new(const char* text)
{
	return (parser_t) { .data = text, .cursor = 0 };
}

void parser_bind(parser_t* parser) { binded_parser = parser; }
void parser_unbind() { binded_parser = NULL; }

bool parser_strcmp(const char* str)
{
	u64 length = strlen(str);
	bool result =  strncmp(str, binded_parser->data, length) == 0;
	if(result == true) binded_parser->data += length;
	return result;
}

void parser_next_line()
{
	const char* ptr = strchr(binded_parser->data, '\n');
	if(ptr == NULL) return; 
	binded_parser->data = ptr + 1;
}

u64 parser_line_count() { return 0; }

void parser_skip_whitespaces()
{
	while(strchr(" \t", *(binded_parser->data)) != NULL)
	{
		binded_parser->data += 1;
	}
}

void parser_skip_any_whitespace()
{
	while(strchr(" \t\n", *(binded_parser->data)) != NULL)
	{
		binded_parser->data += 1;
	}
}

float parser_float()
{
	parser_skip_whitespaces();
	char buffer[30]; //30 bytes;
	const char* number_end = strpbrk(binded_parser->data, " \t\n");
	u8 number_length = number_end - binded_parser->data;
	memcpy(buffer, binded_parser->data, number_length); 
	buffer[number_length] = 0;
	binded_parser->data = number_end;
	parser_skip_whitespaces();
	return atof(buffer);
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

	parser_t p = parser_new(text); parser_bind(&p);

	parser_skip_any_whitespace();

	if(!parser_strcmp("solid"))
		stl_parse_error(STL_PARSE_ERROR_SOLID_HEADER_NOT_FOUND, parser_line_count());
	
	parser_next_line();
	parser_skip_whitespaces();

	while(!parser_strcmp("endsolid"))
	{	
		if(!parser_strcmp("facet"))
			stl_parse_error(STL_PARSE_ERROR_FACET_NOT_FOUND, parser_line_count());
		parser_skip_whitespaces();
		if(!parser_strcmp("normal"))
			stl_parse_error(STL_PARSE_ERROR_NORMAL_NOT_FOUND, parser_line_count());

		vec3_t(float) normal =  { parser_float(), parser_float(), parser_float() };
		buf_push(normals, &normal);
	
		parser_next_line();
		parser_skip_whitespaces();
		
		if(!parser_strcmp("outer"))
			stl_parse_error(STL_PARSE_ERROR_OUTER_NOT_FOUND, parser_line_count());
		parser_skip_whitespaces(); 
		if(!parser_strcmp("loop"))
			stl_parse_error(STL_PARSE_ERROR_LOOP_NOT_FOUND, parser_line_count());

		for(int i = 0; i < 3; i++)
		{
			parser_next_line();
			parser_skip_whitespaces();

			if(!parser_strcmp("vertex"))
				stl_parse_error(STL_PARSE_ERROR_VERTEX_NOT_FOUND, parser_line_count());
		
			stl_vertex_t vertex = 
			{
				.position = { parser_float(), parser_float(), parser_float() }
			};
			buf_push(vertices, &vertex);
		}

		parser_next_line(); 
		parser_skip_whitespaces(); 

		if(!parser_strcmp("endloop"))
			stl_parse_error(STL_PARSE_ERROR_END_LOOP_NOT_FOUND, parser_line_count());

		parser_next_line(); 
		parser_skip_whitespaces();

		if(!parser_strcmp("endfacet"))
			stl_parse_error(STL_PARSE_ERROR_END_FACET_NOT_FOUND, parser_line_count());

		parser_next_line();
		parser_skip_whitespaces();
	}

	CALLTRACE_END();
	return mesh;
}