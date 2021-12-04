#include <meshlib/parsers/string.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <meshlib/assert.h>

static string_parser_t* binded_parser = NULL;

#ifdef GLOBAL_DEBUG
#	define CHECK(ptr) check(ptr)
#else
#	define CHECK(ptr) ptr
#endif

#define check(...) define_alias_function_macro(check, __VA_ARGS__)
function_signature(static void, check, const char* ptr)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	ASSERT(ptr < (binded_parser->origin + binded_parser->length), "Out of bound memory access\n");
	CALLTRACE_END();
}

function_signature(string_parser_t, string_parser_new, const char* text, u64 length)
{
	CALLTRACE_BEGIN();
	CALLTRACE_RETURN((string_parser_t) { .data = text, .origin = text, .length = length });
}

function_signature(void, string_parser_bind, string_parser_t* string_parser) { CALLTRACE_BEGIN(); binded_parser = string_parser; CALLTRACE_END(); }
function_signature_void(void, string_parser_unbind) { CALLTRACE_BEGIN(); binded_parser = NULL;  CALLTRACE_END(); }

function_signature(bool, string_parser_chcmp, const char ch)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	bool result = *(binded_parser->data) == ch;
	if(result == true)
		CHECK(binded_parser->data += 1);
	CALLTRACE_RETURN(result);
}

function_signature(bool, string_parser_strcmp, const char* str)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	u64 length = strlen(str);
	bool result =  strncmp(str, binded_parser->data, length) == 0;
	if(result == true) CHECK(binded_parser->data += length);
	CALLTRACE_RETURN(result);
}

function_signature(bool, string_parser_strcmp_word, const char* word)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	string_parser_skip_whitespaces();
	bool result; 
	const char* word_end = strpbrk(binded_parser->data, " \t\n");
	u64 length = 0;
	if(word_end == NULL)
		length = strlen(word);
	else
		length = (u64)(word_end - binded_parser->data);
	result = !strncmp(word, binded_parser->data, length);
	if(result == true)
	{
		CHECK(binded_parser->data += length);
	}
	CALLTRACE_RETURN(result);
}

function_signature_void(void, string_parser_next_line)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	const char* ptr = strchr(binded_parser->data, '\n');
	if(ptr == NULL) CALLTRACE_RETURN(); 
	CHECK(binded_parser->data = ptr + 1);
	CALLTRACE_END();
}

function_signature_void(u64, string_parser_line_count) { CALLTRACE_BEGIN(); CALLTRACE_RETURN(0); }

function_signature_void(void, string_parser_skip_whitespaces)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	while(strchr(" \t", *(binded_parser->data)) != NULL)
	{
		CHECK(binded_parser->data += 1);
	}
	CALLTRACE_END();
}

function_signature_void(void, string_parser_skip_any_whitespace)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	while(strchr(" \t\n", *(binded_parser->data)) != NULL)
	{
		CHECK(binded_parser->data += 1);
	}
	CALLTRACE_END();
}

function_signature_void(void, string_parser_skip_not_digits)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	const char* ptr = binded_parser->data;
	while(!isdigit(*ptr)) ptr++;
	CHECK(binded_parser->data = ptr);
	CALLTRACE_END();
}

function_signature_void(float, string_parser_float)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	string_parser_skip_whitespaces();
	char buffer[30]; //30 bytes;
	const char* number_end = strpbrk(binded_parser->data, " \t\n");
	u8 number_length = number_end - binded_parser->data;
	memcpy(buffer, binded_parser->data, number_length); 
	buffer[number_length] = 0;
	CHECK(binded_parser->data = number_end);
	CALLTRACE_RETURN(atof(buffer));
}

function_signature_void(u64, string_parser_count)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	CALLTRACE_RETURN(binded_parser->data - binded_parser->origin);
}

function_signature_void(u64, string_parser_u64)
{
	CALLTRACE_BEGIN();
	ASSERT(binded_parser != NULL, "binded_parser == NULL\n");
	string_parser_skip_whitespaces();
	string_parser_skip_not_digits();
	char buffer[30]; 	//30 bytes;
	const char* number_end = binded_parser->data; 
	while(isdigit(*number_end) || (*number_end == '-'))
		CHECK(++number_end);
	u8 number_length = number_end - binded_parser->data;
	memcpy(buffer, binded_parser->data, number_length);
	buffer[number_length] = 0;
	CHECK(binded_parser->data = number_end);
	CALLTRACE_RETURN(strtoul(buffer, NULL, 0));
}
