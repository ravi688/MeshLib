
#include <meshlib/parsers/binary.h>

static binary_parser_t* binded_parser = NULL;

function_signature(void, binary_parser_bind, binary_parser_t* parser) { CALLTRACE_BEGIN(); binded_parser = parser; CALLTRACE_END(); }
function_signature_void(void, binary_parser_unbind) { CALLTRACE_BEGIN(); binded_parser = NULL; CALLTRACE_END(); }

function_signature(binary_parser_t, binary_parser_new, const char* bytes, u64 length)
{
	CALLTRACE_BEGIN();
	CALLTRACE_RETURN((binary_parser_t)
	{
		.cursor = 0,
		.length = length, 
		.bytes = bytes
	});
}

function_signature(void, binary_parser_skip_bytes, u64 count)
{
	CALLTRACE_BEGIN();
	binded_parser->bytes += count;
	CALLTRACE_END();
}

function_signature_void(float, binary_parser_float)
{
	CALLTRACE_BEGIN();
	float result = *(float*)binded_parser->bytes;
	binded_parser->bytes += sizeof(float);
	CALLTRACE_RETURN(result);
}

function_signature_void(u8, binary_parser_u8)
{
	CALLTRACE_BEGIN();
	u8 result = *(u8*)binded_parser->bytes;
	binded_parser->bytes += sizeof(u8);
	CALLTRACE_RETURN(result);
}

function_signature_void(u16, binary_parser_u16)
{
	CALLTRACE_BEGIN();
	u16 result = *(u16*)binded_parser->bytes;
	binded_parser->bytes += sizeof(u16);
	CALLTRACE_RETURN(result);
}

function_signature_void(u32, binary_parser_u32)
{
	CALLTRACE_BEGIN();
	u32 result = *(u32*)binded_parser->bytes;
	binded_parser->bytes += sizeof(u32);
	CALLTRACE_RETURN(result);
}

function_signature_void(u64, binary_parser_u64)
{
	CALLTRACE_BEGIN();
	u64 result = *(u64*)binded_parser->bytes;
	binded_parser->bytes += sizeof(u64);
	CALLTRACE_RETURN(result);
}
