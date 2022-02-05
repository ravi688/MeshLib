
#pragma once

#include <meshlib/defines.h>
#include <calltrace/calltrace.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	const char* bytes;
	const char* origin;
	u64 length;
} binary_parser_t;

/* binary_parser_bind(binary_parser_t* parser):
 * DESCRIPTION:
 * 		Binds(sets) the parser object to internal parser pointer
 * PARAMS:
 * 		1. parser: parser object to bind
 * RETURNS: 
 * 		Nothing
 * ERROR DESCRIPTIONS:
 *		No Errors
 * MEMORY OPERATION DESCRIPTIONS:
 * 		No heap memory operation
 * NOTE:
 * 		You must bind a parser before calling any user functions of that parser 		
 */
MESHLIB_API function_signature(void, binary_parser_bind, binary_parser_t* parser);

/* binary_parser_unbind():
 * DESCRIPTION:
 * 		sets the internal pointer to NULL
 * PARAMS:
 *		Nothing
 * RETURNS: 
 * 		Nothing
 * ERROR DESCRIPTIONS:
 *		No Errors
 * MEMORY OPERATION DESCRIPTIONS:
 * 		No heap memory operation
 * NOTE:
 * 		You must unbind after you are done. 		
 */
MESHLIB_API function_signature_void(void, binary_parser_unbind);

/* binary_parser_new(const char* bytes, u64 length)
 * DESCRIPTION:
 * 		creates a new binary_parser_t with internal pointer set to "bytes" and length set to "length"
 * 		You need to bind the parser, by calling binary_parser_bind(&parser), after creating it with this function
 * PARAMS:
 * 		1. bytes: pointer to the binary data to be parsed
 * 		2. length: length of the binary buffer/data
 * RETURNS:
 * 		Nothing
 * ERROR DESCRIPTIONS:
 * 		No Errors
 * MEMORY OPERATION DESCRIPTIONS:
 * 		No heap memory operation
 * NOTE:
 * 		1. bytes parameter must point to a valid memory location, otherwise it's behaviour is undefined
 * 		2. length parameter must be less than or equal to the actual memory buffer, otherwise it's behaviour is undefined
 */
MESHLIB_API function_signature(binary_parser_t, binary_parser_new, const char* bytes, u64 length);

/* binary_parser_count():
 * DESCRIPTION:
 * 		Returns how many bytes have been parsed/traversed in the buffer
 * PARAMS:
 * 		Nothing
 * RETURNS:
 * 		the number of bytes have been parsed/traversed in the buffer
 * ERROR DESCRIPTIONS:
 * 		1. binded_parser == NULL, if you haven't binded any parser to the internal pointer by calling binary_parser_bind(pointer to the parser)
 *		7. Out of bound memory access, this is an internal error, it might only happen when there would be segmentation fault due to other things
 * NOTE:
 * 		1. Before calling this function make sure you have binded a parser, otherwise you will get an error.
 */
MESHLIB_API function_signature_void(u64, binary_parser_count);

MESHLIB_API function_signature_void(void, binary_parser_rewind);
MESHLIB_API function_signature(bool, binary_parser_cmp_float, float value);
MESHLIB_API function_signature(bool, binary_parser_cmp_s8, s8 value);
MESHLIB_API function_signature(bool, binary_parser_cmp_s16, s16 value);
MESHLIB_API function_signature(bool, binary_parser_cmp_s32, s32 value);
MESHLIB_API function_signature(bool, binary_parser_cmp_s64, s64 value);
MESHLIB_API function_signature(bool, binary_parser_cmp_u8, u8 value);
MESHLIB_API function_signature(bool, binary_parser_cmp_u16, u16 value);
MESHLIB_API function_signature(bool, binary_parser_cmp_u32, u32 value);
MESHLIB_API function_signature(bool, binary_parser_cmp_u64, u64 value);
MESHLIB_API function_signature(bool, binary_parser_cmp_bytes, void* bytes, u32 count);

/* binary_parser_skip_bytes(u64 count):
 * DESCRIPTION:
 * 		Skips (advances the internal cursor) "count" bytes
 * PARAMS:
 * 		1. count: Number of bytes to skip
 * RETURNS:
 * 		Nothing
 * ERROR DESCRIPTIONS:
 * 		1. binded_parser == NULL, if you haven't binded any parser to the internal pointer by calling binary_parser_bind(pointer to the parser)
 *		7. Out of bound memory access, this is an internal error, it might only happen when there would be segmentation fault due to other things
 * NOTE:
 * 		1. Before calling this function make sure you have binded a parser, otherwise you will get an error.
 */
MESHLIB_API function_signature(void, binary_parser_skip_bytes, u64 count);

/* binary_parser_float():
 * DESCRIPTION:
 * 		Returns a float value, and advances the internal pointer by sizeof(float)
 * PARAMS:
 * 		Nothing
 * RETURNS:
 * 		float value
 * ERROR DESCRIPTIONS:
 * 		1. binded_parser == NULL, if you haven't binded any parser to the internal pointer by calling binary_parser_bind(pointer to the parser)
 *		7. Out of bound memory access, this is an internal error, it might only happen when there would be segmentation fault due to other things
 * NOTE:
 * 		1. Before calling this function make sure you have binded a parser, otherwise you will get an error.
 */
MESHLIB_API function_signature_void(float, binary_parser_float);

/* binary_parser_u8():
 * DESCRIPTION:
 * 		Returns a u8 value, and advances the internal pointer by sizeof(u8)
 * PARAMS:
 * 		Nothing
 * RETURNS:
 * 		u8 value
 * ERROR DESCRIPTIONS:
 * 		1. binded_parser == NULL, if you haven't binded any parser to the internal pointer by calling binary_parser_bind(pointer to the parser)
 *		7. Out of bound memory access, this is an internal error, it might only happen when there would be segmentation fault due to other things
 * NOTE:
 * 		1. Before calling this function make sure you have binded a parser, otherwise you will get an error.
 */
MESHLIB_API function_signature_void(u8, binary_parser_u8); 

/* binary_parser_u16():
 * DESCRIPTION:
 * 		Returns a u16 (aka. unsigned short) value, and advances the internal pointer by sizeof(u16)
 * PARAMS:
 * 		Nothing
 * RETURNS:
 * 		u16 value
 * ERROR DESCRIPTIONS:
 * 		1. binded_parser == NULL, if you haven't binded any parser to the internal pointer by calling binary_parser_bind(pointer to the parser)
 *		7. Out of bound memory access, this is an internal error, it might only happen when there would be segmentation fault due to other things
 * NOTE:
 * 		1. Before calling this function make sure you have binded a parser, otherwise you will get an error.
 */
MESHLIB_API function_signature_void(u16, binary_parser_u16);

/* binary_parser_u32():
 * DESCRIPTION:
 * 		Returns a u32 value, and advances the internal pointer by sizeof(u32)
 * PARAMS:
 * 		Nothing
 * RETURNS:
 * 		u32 value
 * ERROR DESCRIPTIONS:
 * 		1. binded_parser == NULL, if you haven't binded any parser to the internal pointer by calling binary_parser_bind(pointer to the parser)
 *		7. Out of bound memory access, this is an internal error, it might only happen when there would be segmentation fault due to other things
 * NOTE:
 * 		1. Before calling this function make sure you have binded a parser, otherwise you will get an error.
 */
MESHLIB_API function_signature_void(u32, binary_parser_u32);

/* binary_parser_u64():
 * DESCRIPTION:
 * 		Returns a u64 value, and advances the internal pointer by sizeof(u64)
 * PARAMS:
 * 		Nothing
 * RETURNS:
 * 		u64 value
 * ERROR DESCRIPTIONS:
 * 		1. binded_parser == NULL, if you haven't binded any parser to the internal pointer by calling binary_parser_bind(pointer to the parser)
 *		7. Out of bound memory access, this is an internal error, it might only happen when there would be segmentation fault due to other things
 * NOTE:
 * 		1. Before calling this function make sure you have binded a parser, otherwise you will get an error.
 */
MESHLIB_API function_signature_void(u64, binary_parser_u64);


#define binary_parser_bind(...) define_alias_function_macro(binary_parser_bind, __VA_ARGS__)
#define binary_parser_unbind(...) define_alias_function_void_macro(binary_parser_unbind)
#define binary_parser_new(...) define_alias_function_macro(binary_parser_new, __VA_ARGS__)
#define binary_parser_count(...) define_alias_function_void_macro(binary_parser_count)
#define binary_parser_skip_bytes(...) define_alias_function_macro(binary_parser_skip_bytes, __VA_ARGS__)
#define binary_parser_float(...) define_alias_function_void_macro(binary_parser_float)
#define binary_parser_u8(...) define_alias_function_void_macro(binary_parser_u8)
#define binary_parser_u16(...) define_alias_function_void_macro(binary_parser_u16)
#define binary_parser_u32(...) define_alias_function_void_macro(binary_parser_u32)
#define binary_parser_u64(...) define_alias_function_void_macro(binary_parser_u64)

#define binary_parser_rewind() define_alias_function_void_macro(binary_parser_rewind)
#define binary_parser_cmp_float(...) define_alias_function_macro(binary_parser_cmp_float, __VA_ARGS__)
#define binary_parser_cmp_s8(...) define_alias_function_macro(binary_parser_cmp_s8, __VA_ARGS__)
#define binary_parser_cmp_s16(...) define_alias_function_macro(binary_parser_cmp_s16, __VA_ARGS__)
#define binary_parser_cmp_s32(...) define_alias_function_macro(binary_parser_cmp_s32, __VA_ARGS__)
#define binary_parser_cmp_s64(...) define_alias_function_macro(binary_parser_cmp_s64, __VA_ARGS__)
#define binary_parser_cmp_u8(...) define_alias_function_macro(binary_parser_cmp_u8, __VA_ARGS__)
#define binary_parser_cmp_u16(...) define_alias_function_macro(binary_parser_cmp_u16, __VA_ARGS__)
#define binary_parser_cmp_u32(...) define_alias_function_macro(binary_parser_cmp_u32, __VA_ARGS__)
#define binary_parser_cmp_u64(...) define_alias_function_macro(binary_parser_cmp_u64, __VA_ARGS__)
#define binary_parser_cmp_bytes(...) define_alias_function_macro(binary_parser_cmp_bytes, __VA_ARGS__)

#ifdef __cplusplus
}
#endif
