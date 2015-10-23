/****
    Named : Symbol and keyword header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef WRITER_H
#define WRITER_H

/*
    Writer
*/
typedef struct
{
    FILE            *file;
} Writer;

extern char *(*print_ptr)(Object *node, bool readable);

// to current printer
Object *PRINT(Object *node);
Object *PR(Object *node);
Object *PRINTLN(Object *node);
Object *PRN(Object *node);

// to string printers
char *print(Object *node);
char *pr(Object *node);

// to node printers
Object *node_print(Object *node);
Object *node_pr(Object *node);

// constructors
Object *writer(FILE *file);
Object *writer_open_file(Object *name);
Object *writer_stdout();
Object *writer_stderr();

// Set and close currect output
// TODO in appropriate variable
Object *writer_curr(Object *writer);
Object *writer_curr_close();

// Get unnoded data
void *WRITER_FILE(Object *filename);

// Clobal currect writer for now
// TODO manage some other way threoug a language variable...
extern Object *curr;

#endif

