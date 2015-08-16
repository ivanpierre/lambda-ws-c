/****
    Number : Integer and Decimal

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NUMBERS_H
#define NUMBERS_H

// Integer
Node        *integer(Integer value);
Integer     number_integer(Node *node);
Node        *integer_Q_(Node *node);

// Decimal
Node        *decimal(Decimal value);
Decimal     number_decimal(Node *node);
Node        *decimal_Q_(Node *node);

#endif
