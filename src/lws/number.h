/****
    Number : Integer and Decimal

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NUMBERS_H
#define NUMBERS_H

typedef struct
{
	long integer;
} Integer;

typedef struct
{
	double decimal;
} Decimal;

Node    *integer(long value);
Integer number_integer(Node * node);
Node    *integer_Q_(Node * node);

Node    *decimal(double value);
Decimal number_decimal(Node * node);
Node    *decimal_Q_(Node * node);

#endif
