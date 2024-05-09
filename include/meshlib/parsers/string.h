
#pragma once

#include <meshlib/defines.h>
#include <calltrace/calltrace.h>

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct 
{
	const char* data;
	const char* origin;
	u64 length;
} string_parser_t;

MESHLIB_API function_signature(string_parser_t, string_parser_new, const char* text, u64 length);
MESHLIB_API function_signature(void, string_parser_next_line, string_parser_t* parser);
MESHLIB_API function_signature(void, string_parser_skip_whitespaces, string_parser_t* parser);
MESHLIB_API function_signature(void, string_parser_skip_any_whitespace, string_parser_t* parser);
MESHLIB_API function_signature(void, string_parser_skip_not_digits, string_parser_t* parser);
MESHLIB_API function_signature(u64, string_parser_count, string_parser_t* parser);
MESHLIB_API function_signature(bool, string_parser_chcmp, string_parser_t* parser, const char ch);
MESHLIB_API function_signature(bool, string_parser_strcmp, string_parser_t* parser, const char* str);
MESHLIB_API function_signature(bool, string_parser_strcmp_word, string_parser_t* parser, const char* word);
MESHLIB_API function_signature(u64, string_parser_line_count, string_parser_t* parser);
// __attribute__((warning("string_parser_float should not be used when parsing stl ascii because of its particular case implementation")))
MESHLIB_API function_signature(float, string_parser_float, string_parser_t* parser);
MESHLIB_API function_signature(u64, string_parser_u64, string_parser_t* parser);

#define string_parser_new(...) define_alias_function_macro(string_parser_new, __VA_ARGS__)
#define string_parser_bind(...) define_alias_function_macro(string_parser_bind, __VA_ARGS__)
#define string_parser_unbind(...) define_alias_function_macro(string_parser_unbind, __VA_ARGS__)
#define string_parser_next_line(...) define_alias_function_macro(string_parser_next_line, __VA_ARGS__)
#define string_parser_skip_whitespaces(...) define_alias_function_macro(string_parser_skip_whitespaces, __VA_ARGS__)
#define string_parser_skip_any_whitespace(...) define_alias_function_macro(string_parser_skip_any_whitespace, __VA_ARGS__)
#define string_parser_chcmp(...) define_alias_function_macro(string_parser_chcmp, __VA_ARGS__)
#define string_parser_strcmp(...) define_alias_function_macro(string_parser_strcmp, __VA_ARGS__)
#define string_parser_strcmp_word(...) define_alias_function_macro(string_parser_strcmp_word, __VA_ARGS__)
#define string_parser_line_count(...) define_alias_function_macro(string_parser_line_count, __VA_ARGS__)
#define string_parser_float(...) define_alias_function_macro(string_parser_float, __VA_ARGS__)
#define string_parser_skip_not_digits(...) define_alias_function_macro(string_parser_skip_not_digits, __VA_ARGS__)
#define string_parser_u64(...) define_alias_function_macro(string_parser_u64, __VA_ARGS__)
#define string_parser_count(...) define_alias_function_macro(string_parser_count, __VA_ARGS__)

static inline void string_parser_skip_to_digit(string_parser_t* parser) { string_parser_skip_not_digits(parser); }

#ifdef __cplusplus
}
#endif

