#include <meshlib/parsers/string.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <meshlib/assert.h>

MESHLIB_API function_signature(string_parser_t, string_parser_new, const char* text, u64 length)
{
	CALLTRACE_BEGIN();
	CALLTRACE_RETURN((string_parser_t) { .data = text, .origin = text, .length = length });
}

static bool string_parser_is_end(string_parser_t* parser)
{
	return parser->data >= (parser->origin + parser->length);
}

static void string_parser_increment(string_parser_t* parser, u32 count)
{
	if(string_parser_is_end(parser))
		return;
	parser->data += count;
}

MESHLIB_API function_signature(bool, string_parser_chcmp, string_parser_t* parser, const char ch)
{
	CALLTRACE_BEGIN();
	if(string_parser_is_end(parser))
		return false;
	bool result = *(parser->data) == ch;
	if(result == true)
		string_parser_increment(parser, 1);
	CALLTRACE_RETURN(result);
}

static u32 string_parser_get_end_distance(string_parser_t* parser)
{
	if(parser->data > (parser->origin + parser->length))
		return 0;
	return (parser->origin + parser->length) - parser->data;
}

static bool strnncmp(const char* str1, u32 len1, const char* str2, u32 len2)
{
	if(len1 > len2)
		return false;
	return strncmp(str1, str2, len1) == 0;
}

MESHLIB_API function_signature(bool, string_parser_strcmp, string_parser_t* parser, const char* str)
{
	CALLTRACE_BEGIN();
	ASSERT(parser != NULL, "parser == NULL\n");
	u64 length = strlen(str);
	bool result = strnncmp(str, length, parser->data, string_parser_get_end_distance(parser));
	if(result == true) string_parser_increment(parser, length);
	CALLTRACE_RETURN(result);
}

static bool string_parser_is_null_terminated(string_parser_t* parser)
{
	return *(parser->origin + parser->length - 1) == 0;
}

MESHLIB_API function_signature(bool, string_parser_strcmp_word, string_parser_t* parser, const char* word)
{
	CALLTRACE_BEGIN();
	ASSERT(parser != NULL, "parser == NULL\n");
	string_parser_skip_any_whitespace(parser);
	bool result; 
	ASSERT(string_parser_is_null_terminated(parser), "data in the string_parser_t is not null terminated");
	if(string_parser_is_end(parser))
		return false;
	const char* word_end = strpbrk(parser->data, " \t\n");
	u64 length = 0;
	if(word_end == NULL)
		length = strlen(word);
	else
		length = (u64)(word_end - parser->data);
	result = strnncmp(word, length, parser->data, string_parser_get_end_distance(parser));
	if(result == true)
		string_parser_increment(parser, length);
	CALLTRACE_RETURN(result);
}

MESHLIB_API function_signature(void, string_parser_next_line, string_parser_t* parser)
{
	CALLTRACE_BEGIN();
	ASSERT(parser != NULL, "parser == NULL\n");
	ASSERT(string_parser_is_null_terminated(parser), "data in the string_parser_t is not null terminated");
	if(string_parser_is_end(parser))
		return;
	const char* ptr = strchr(parser->data, '\n');
	if(ptr == NULL) CALLTRACE_RETURN(); 
	string_parser_increment(parser, ptr - parser->data + 1);
	CALLTRACE_END();
}

MESHLIB_API function_signature(u64, string_parser_line_count, string_parser_t* parser) { CALLTRACE_BEGIN(); CALLTRACE_RETURN(0); }

MESHLIB_API function_signature(void, string_parser_skip_whitespaces, string_parser_t* parser)
{
	CALLTRACE_BEGIN();
	ASSERT(parser != NULL, "parser == NULL\n");
	while((!string_parser_is_end(parser)) && (strchr(" \t", *(parser->data)) != NULL))
		string_parser_increment(parser, 1);
	CALLTRACE_END();
}

MESHLIB_API function_signature(void, string_parser_skip_any_whitespace, string_parser_t* parser)
{
	CALLTRACE_BEGIN();
	ASSERT(parser != NULL, "parser == NULL\n");
	while((!string_parser_is_end(parser)) && (strchr(" \t\n", *(parser->data)) != NULL))
		string_parser_increment(parser, 1);
	CALLTRACE_END();
}

static inline bool string_parser_is_start(string_parser_t* parser)
{
	return parser->data == parser->origin;
}

MESHLIB_API function_signature(void, string_parser_skip_not_digits, string_parser_t* parser)
{
	CALLTRACE_BEGIN();
	ASSERT(parser != NULL, "parser == NULL\n");
	while((!string_parser_is_end(parser)) && (!isdigit(*parser->data))) string_parser_increment(parser, 1);
	if((!string_parser_is_end(parser)) && isdigit(*parser->data))
	{
		if((!string_parser_is_start(parser)) && ((*(parser->data - 1)) == '-'))
			parser->data -= 1;
	}
	CALLTRACE_END();
}

MESHLIB_API function_signature(float, string_parser_float, string_parser_t* parser)
{
	CALLTRACE_BEGIN();
	ASSERT(parser != NULL, "parser == NULL\n");
	string_parser_skip_whitespaces(parser);
	ASSERT(string_parser_is_null_terminated(parser), "data in the string_parser_t is not null terminated");
	if(string_parser_is_end(parser))
		return 0.0f;
	char buffer[30]; //30 bytes;
	const char* number_end = strpbrk(parser->data, " \t\n");
	u8 number_length = number_end - parser->data;
	memcpy(buffer, parser->data, number_length); 
	buffer[number_length] = 0;
	string_parser_increment(parser, number_length);
	CALLTRACE_RETURN(atof(buffer));
}

MESHLIB_API function_signature(u64, string_parser_count, string_parser_t* parser)
{
	CALLTRACE_BEGIN();
	ASSERT(parser != NULL, "parser == NULL\n");
	CALLTRACE_RETURN(parser->data - parser->origin);
}

MESHLIB_API function_signature(u64, string_parser_u64, string_parser_t* parser)
{
	CALLTRACE_BEGIN();
	ASSERT(parser != NULL, "parser == NULL\n");
	string_parser_skip_whitespaces(parser);
	string_parser_skip_not_digits(parser);
	if(string_parser_is_end(parser))
		return 0U;
	char buffer[64]; 	//64 bytes;
	const char* number_start = parser->data;
	while((!string_parser_is_end(parser)) && (isdigit(*parser->data) || ((*parser->data) == '-')))
		string_parser_increment(parser, 1);
	u8 number_length = parser->data - number_start;
	memcpy(buffer, number_start, number_length);
	buffer[number_length] = 0;
	CALLTRACE_RETURN(strtoul(buffer, NULL, 0));
}
