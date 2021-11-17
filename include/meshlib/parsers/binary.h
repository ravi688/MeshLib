
#pragma once

#include <meshlib/defines.h>
#include <calltrace/calltrace.h>
#include <stdbool.h>

typedef struct
{
	const char* bytes;
	u64 length;
	u64 cursor;
} binary_parser_t;


function_signature(void, binary_parser_bind, binary_parser_t* parser);
function_signature_void(void, binary_parser_unbind);
function_signature(binary_parser_t, binary_parser_new, const char* bytes, u64 length);
function_signature(void, binary_parser_skip_bytes, u64 count);
function_signature_void(float, binary_parser_float);
function_signature_void(u8, binary_parser_u8); 
function_signature_void(u16, binary_parser_u16);
function_signature_void(u32, binary_parser_u32);
function_signature_void(u64, binary_parser_u64);


#define binary_parser_bind(...) define_alias_function_macro(binary_parser_bind, __VA_ARGS__)
#define binary_parser_unbind(...) define_alias_function_void_macro(binary_parser_unbind)
#define binary_parser_new(...) define_alias_function_macro(binary_parser_new, __VA_ARGS__)
#define binary_parser_skip_bytes(...) define_alias_function_macro(binary_parser_skip_bytes, __VA_ARGS__)
#define binary_parser_float(...) define_alias_function_void_macro(binary_parser_float)
#define binary_parser_u8(...) define_alias_function_void_macro(binary_parser_u8)
#define binary_parser_u16(...) define_alias_function_void_macro(binary_parser_u16)
#define binary_parser_u32(...) define_alias_function_void_macro(binary_parser_u32)
#define binary_parser_u64(...) define_alias_function_void_macro(binary_parser_u64)
