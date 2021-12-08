
#pragma once


#include <calltrace/calltrace.h>

typedef struct stl_parse_callbacks_t stl_parse_callbacks_t;

/* stl_parse_binary(const char* bytes, u64 length, stl_parse_callbacks_t* parse_callbacks):
 * DESCRIPTION:
 *		Parses a binary data containg stl data, and calls appropriate functions using parse_callbacks foreach parsed vertex and normal
 * PARAMS:
 * 		1. bytes: pointer to the binary data in memory
 * 		2. length: length of the binary data (buffer)
 *		3. parse_callbacks: contains pointers to functions to be called foreach parsed vertex and normal, and a pointer to user_data
 * RETURNS:
 *		Nothing
 * ERROR DESCRIPTIONS:
 *		1. Out of bound memory access, this is an internal error, it might only happen when there would be segmentation fault due to other things
 *		2. binded_parser == NULL, this is an internal error, it might only happen when there would be segmentation fault due to other things
 * MEMORY OPERATION DESCRIPTIONS:
 * 		1. No heap memory allocations, nor freed.
 * NOTE:
 * 		1. This function doesn't check for precondition, such as bytes shouldn't be NULL or length shouldn't be zero
 * 		2. bytes must be a valid binary data containing a valid stl data, although it is not mandatory but you will get unexpected parsed data
 * 		3. length must be the length of the passed bytes
 * 		4. function pointers in parse_callbacks could be NULL, this function checks for NULL before calling them.
 * EXAMPLES:
 * 		#include <disk_manager/file_reader.h>
 *      #include <meslib/stl/readers/binary.h>
 * 		static void print_position(vec3_t(float) position, void* user_data) { printf("POSITION: %f, %f, %f\n", position.x, position.y, position.z); }
 *      static void print_normal(vec3_t(float) normal, void* user_data) { printf("NORMAL: %f, %f, %f\n", normal.x, normal.y, normal.z); }
 * 		//some scope
 * 		BUFFER* stl_file_data = load_binary_from_file("resource/Binary-box.stl");
 *      stl_parse_callbacks_t callbacks = { .user_data = NULL, .vertex_position_callback = print_position, .vertex_normal_callback = print_normal; };
 *      stl_parse_binary(stl_file_data->bytes, stl_file_data->element_count, &callbacks);
 *		buf_free(stl_file_data);
 */
function_signature(void, stl_parse_binary, const char* bytes, u64 length, stl_parse_callbacks_t* parse_callbacks);
#define stl_parse_binary(...) define_alias_function_macro(stl_parse_binary, __VA_ARGS__)
