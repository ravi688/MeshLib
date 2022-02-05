
#pragma once

/*for stack trace*/
#include <calltrace/calltrace.h>

/*for u64*/
#include <meshlib/defines.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct stl_parse_callbacks_t stl_parse_callbacks_t;

/* stl_parse_ascii(const char* text, u64 length, stl_parse_callbacks_t* parse_callbacks):
 * DESCRIPTION:
 *		Parses a string containg ASCII stl data, and calls appropriate functions using parse_callbacks foreach parsed vertex and normal
 * PARAMS:
 * 		1. text: ASCII stl text/string in memory, note: this is not the file path
 * 		2. length: length of the text
 *		3. parse_callbacks: contains pointers to functions to be called foreach parsed vertex and normal, and a pointer to user_data
 * RETURNS:
 *		Nothing
 * ERROR DESCRIPTIONS:
 * 		1. OBJ_PARSE_ERROR_VERTEX_NOT_FOUND, if there is something wrong with the string containing ASCII stl
 *		2. OBJ_PARSE_ERROR_UNRECOGNIZED_KEYWORD, if there is something wrong with the string containing ASCII stl
 *		3. OBJ_PARSE_ERROR_TEXCOORD_NOT_FOUND, if there is something wrong with the string containing ASCII stl
 *		4. OBJ_PARSE_ERROR_NORMAL_NOT_FOUND, if there is something wrong with the string containing ASCII stl
 *		5. OBJ_PARSE_ERROR_FACET_NOT_FOUND, if there is something wrong with the string containing ASCII stl
 *		6. OBJ_PARSE_ERROR: Unkown Error, if there is something wrong with the string containing ASCII stl
 *		7. Out of bound memory access, this is an internal error, it might only happen when there would be segmentation fault due to other things
 *		8. binded_parser == NULL, this is an internal error, it might only happen when there would be segmentation fault due to other things
 * MEMORY OPERATION DESCRIPTIONS:
 * 		1. No heap memory allocations, nor freed.
 * NOTE:
 * 		1. This function doesn't check for precondition, such as text shouldn't be NULL or length shouldn't be zero
 * 		2. text must be a valid string containing a valid ASCII stl data
 * 		3. length must be the length of the passed text inclusive of the null character
 * 		4. function pointers in parse_callbacks could be NULL, this function checks for NULL before calling them.
 * EXAMPLES:
 * 		#include <disk_manager/file_reader.h>
 *      #include <meslib/stl/readers/ascii.h>
 * 		static void print_position(vec3_t(float) position, void* user_data) { printf("POSITION: %f, %f, %f\n", position.x, position.y, position.z); }
 *      static void print_normal(vec3_t(float) normal, void* user_data) { printf("NORMAL: %f, %f, %f\n", normal.x, normal.y, normal.z); }
 * 		//some scope
 * 		BUFFER* stl_file_data = load_text_from_file("resource/ASCII-box.stl");
 *      stl_parse_callbacks_t callbacks = { .user_data = NULL, .vertex_position_callback = print_position, .vertex_normal_callback = print_normal; };
 *      stl_parse_ascii(stl_file_data->bytes, stl_file_data->element_count, &callbacks);
 *		buf_free(stl_file_data);
 */
MESHLIB_API function_signature(void, stl_parse_ascii, const char* text, u64 length, stl_parse_callbacks_t* parse_callbacks);
#define stl_parse_ascii(...) define_alias_function_macro(stl_parse_ascii, __VA_ARGS__)

#ifdef __cplusplus
}
#endif
