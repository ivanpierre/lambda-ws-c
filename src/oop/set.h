/****
	Set class

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#define LOOKUP 32

struct Set;

#define STRUCT_SET \
	STRUCT_OBJECT; \
	WS_BYTE		size; \
	WS_BYTE		shift; \
	struct Set	*root; \
	Object		*leaf[LOOKUP]

typedef struct Set
{
	STRUCT_SET;
} Set;
