





typedef struct
{
	struct Node *super;				// superclass of nil
	struct Node	*member_index; 		// Map member id - function index
	struct Node *size				// if member index is nil : size of type
									// else nb of nodes
} Class;
