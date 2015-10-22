



typedef struct
{
	struct Node *name;				// ZString
	struct Node	*interfaces; 		// Array of interfaces and classes
	struct Node	*method_index;		// Map function id - function index
	struct Node	*method; 			// Array of functions
} Interface;

extern bool isa_type (Node *type, Node *isa);
