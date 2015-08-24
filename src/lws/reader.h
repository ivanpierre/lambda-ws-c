/****
    Reader

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef READER_H
#define READER_H

/*
    Reader
*/
typedef struct
{
    int             (*getc)();
} Reader;

#endif
