#include <meshlib/parsers/string.h>
#include <string.h>
#include <stdlib.h>


static string_parser_t* binded_parser = NULL;

function_signature(string_parser_t, string_parser_new, const char* text)
{
	CALLTRACE_BEGIN();
	CALLTRACE_RETURN((string_parser_t) { .data = text, .cursor = 0 });
}

function_signature(void, string_parser_bind, string_parser_t* string_parser) { CALLTRACE_BEGIN(); binded_parser = string_parser; CALLTRACE_END(); }
function_signature_void(void, string_parser_unbind) { CALLTRACE_BEGIN(); binded_parser = NULL;  CALLTRACE_END(); }

function_signature(bool, string_parser_strcmp, const char* str)
{
	CALLTRACE_BEGIN();
	u64 length = strlen(str);
	bool result =  strncmp(str, binded_parser->data, length) == 0;
	if(result == true) binded_parser->data += length;
	CALLTRACE_RETURN(result);
}

function_signature_void(void, string_parser_next_line)
{
	CALLTRACE_BEGIN();
	const char* ptr = strchr(binded_parser->data, '\n');
	if(ptr == NULL) CALLTRACE_RETURN(); 
	binded_parser->data = ptr + 1;
	CALLTRACE_END();
}

function_signature_void(u64, string_parser_line_count) { CALLTRACE_BEGIN(); CALLTRACE_RETURN(0); }

function_signature_void(void, string_parser_skip_whitespaces)
{
	CALLTRACE_BEGIN();
	while(strchr(" \t", *(binded_parser->data)) != NULL)
	{
		binded_parser->data += 1;
	}
	CALLTRACE_END();
}

function_signature_void(void, string_parser_skip_any_whitespace)
{
	CALLTRACE_BEGIN();
	while(strchr(" \t\n", *(binded_parser->data)) != NULL)
	{
		binded_parser->data += 1;
	}
	CALLTRACE_END();
}

function_signature_void(float, string_parser_float)
{
	CALLTRACE_BEGIN();
	string_parser_skip_whitespaces();
	char buffer[30]; //30 bytes;
	const char* number_end = strpbrk(binded_parser->data, " \t\n");
	u8 number_length = number_end - binded_parser->data;
	memcpy(buffer, binded_parser->data, number_length); 
	buffer[number_length] = 0;
	binded_parser->data = number_end;
	string_parser_skip_whitespaces();
	CALLTRACE_RETURN(atof(buffer));
}
