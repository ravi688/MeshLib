
#pragma once

#include <meshlib/defines.h>
#include <calltrace/calltrace.h>

#ifdef __cplusplus
#	include <cstdbool>
#else
#	include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


typedef struct 
{
	const char* data;
	const char* origin;
	u64 length;
} string_parser_t;

function_signature(string_parser_t, string_parser_new, const char* text, u64 length);
function_signature(void, string_parser_bind, string_parser_t* string_parser);
function_signature_void(void, string_parser_unbind);
function_signature_void(void, string_parser_next_line);
function_signature_void(void, string_parser_skip_whitespaces);
function_signature_void(void, string_parser_skip_any_whitespace);
function_signature_void(void, string_parser_skip_not_digits);
function_signature_void(u64, string_parser_count);
function_signature(bool, string_parser_chcmp, const char ch);
function_signature(bool, string_parser_strcmp, const char* str);
function_signature(bool, string_parser_strcmp_word, const char* word);
function_signature_void(u64, string_parser_line_count);
// __attribute__((warning("string_parser_float should not be used when parsing stl ascii because of its particular case implementation")))
function_signature_void(float, string_parser_float);
function_signature_void(u64, string_parser_u64);

#define string_parser_new(...) define_alias_function_macro(string_parser_new, __VA_ARGS__)
#define string_parser_bind(...) define_alias_function_macro(string_parser_bind, __VA_ARGS__)
#define string_parser_unbind(...) define_alias_function_void_macro(string_parser_unbind)
#define string_parser_next_line(...) define_alias_function_void_macro(string_parser_next_line)
#define string_parser_skip_whitespaces(...) define_alias_function_void_macro(string_parser_skip_whitespaces)
#define string_parser_skip_any_whitespace(...) define_alias_function_void_macro(string_parser_skip_any_whitespace)
#define string_parser_chcmp(...) define_alias_function_macro(string_parser_chcmp, __VA_ARGS__)
#define string_parser_strcmp(...) define_alias_function_macro(string_parser_strcmp, __VA_ARGS__)
#define string_parser_strcmp_word(...) define_alias_function_macro(string_parser_strcmp_word, __VA_ARGS__)
#define string_parser_line_count(...) define_alias_function_void_macro(string_parser_line_count)
#define string_parser_float(...) define_alias_function_void_macro(string_parser_float)
#define string_parser_skip_not_digits(...) define_alias_function_void_macro(string_parser_skip_not_digits)
#define string_parser_u64(...) define_alias_function_void_macro(string_parser_u64)
#define string_parser_count(...) define_alias_function_void_macro(string_parser_count)

#ifdef __cplusplus
}
#endif

