/****
	inode class

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#define LOOKUP 32

struct
{
	WS_BYTE		size;
	WS_BYTE		shift;
	Object		*leaf[LOOKUP];
} PersistantINode;

struct
{
	WS_BYTE		size;
	WS_BYTE		shift;
	Object		*root_node;
	Object		*leaf[LOOKUP];
} TransientINode;
