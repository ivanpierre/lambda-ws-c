/****
	IndexObj class

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef INDEXOBJ_H
#define INDEXOBJ_H

#define STRUCT_INDEX_OBJ \
	STRUCT_OBJECT; \
	WS_INT			index; \
	void 			*obj

typedef struct IndexObj
{
	STRUCT_INDEX_OBJ;
} IndexObj;

extern void *CLASS_INDEX_OBJ;

// Class constructors
extern void index_obj_static();

extern void index_obj_functions();

// constructor for indexobjs
extern void *index_obj(WS_INT index, void *obj);

// functions
extern void *func(void *set, WS_INT index);
extern WS_INT add_func(void *set, MethodDesc *func);
extern WS_INT import_funcs(void *set_to, void *set_from);

// Methods
void *index_obj_finalize(void *index_obj);

void *index_obj_to_string(void *index_obj);

#endif
