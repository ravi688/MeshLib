
#pragma once

#include <meshlib/defines.h>
#include <calltrace/calltrace.h>
#include <stdbool.h>

typedef struct 
{
	const char* data;
	u64 cursor;
} string_parser_t;

function_signature(string_parser_t, string_parser_new, const char* text);
function_signature(void, string_parser_bind, string_parser_t* string_parser);
function_signature_void(void, string_parser_unbind);
function_signature_void(void, string_parser_next_line);
function_signature_void(void, string_parser_skip_whitespaces);
function_signature_void(void, string_parser_skip_any_whitespace);
function_signature(bool, string_parser_strcmp, const char* str);
function_signature_void(u64, string_parser_line_count);
function_signature_void(float, string_parser_float);


#define string_parser_new(...) define_alias_function_macro(string_parser_new, __VA_ARGS__)
#define string_parser_bind(...) define_alias_function_macro(string_parser_bind, __VA_ARGS__)
#define string_parser_unbind(...) define_alias_function_void_macro(string_parser_unbind)
#define string_parser_next_line(...) define_alias_function_void_macro(string_parser_next_line)
#define string_parser_skip_whitespaces(...) define_alias_function_void_macro(string_parser_skip_whitespaces)
#define string_parser_skip_any_whitespace(...) define_alias_function_void_macro(string_parser_skip_any_whitespace)
#define string_parser_strcmp(...) define_alias_function_macro(string_parser_strcmp, __VA_ARGS__)
#define string_parser_line_count(...) define_alias_function_void_macro(string_parser_line_count)
#define string_parser_float(...) define_alias_function_void_macro(string_parser_float)
