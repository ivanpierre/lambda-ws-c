/****
    number : manage 32 bits Integers

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "number.h"

//* helper functions *****
// Table of all numeric funtion with 1 argument
static Node *(**num_funct1[])(Node *arg1) =
			{
				&byte_funct1;
				&int_funct1;
				&long_funct1;
				&bigint_funct1;
				&ratio_funct1;
				&float_funct1;
				&double_funct1;
				&bigdec_funct1;
			};

// Table of all numeric funtion pointer with 2 argument
static Node *(**num_funct2[])(Node *arg1, Node *arg2)[];
			{
				&byte_funct2;
				&int_funct2;
				&long_funct2;
				&bigint_funct2;
				&ratio_funct2;
				&float_funct2;
				&double_funct2;
				&bigdec_funct2;
			};

/**
	Heloper functions
*/
static int max_type(Node *arg1, Node *arg2)
{
	TYPE type1 = arg1.type;
	TYPE type2 = arg2.type;
	if (type1 > type2)
		return type1 - BYTE;
	else
		return type2 - BYTE;
}

static Node *num_operator1(Node *x, int function)
{
	START_FUN1;
	res = (*num_func1[function][arg.type - BYTE])(arg);
	END_FUN1;
}

static Node *num_operator2(Node *x, Node *y, int function)
{
	START_FUN2;
	res = (*num_func1[function][arg.type - BYTE])(arg);
	END_FUN2;
}

//* test ***************
Node    *is_num					(Node *x)
{
	START_INT_FUN1;

	END_FUN1;
}

Node	*num_is_zero			(Node *x);
{
	return num_operator1(node, IS_ZERO)
}

Node	*num_is_neg				(Node *x);
{

}

Node	*num_is_pos				(Node *x);
{

}


// coerce
Node 	*num_coerce				(Node *x, TYPE type);
{

}


//* operators *************
Node 	*num_add				(Node *x, Node *y);
{

}

Node 	*num_addP				(Node *x, Node *y);
{

}


Node 	*num_multiply			(Node *x, Node *y);
{

}

Node 	*num_multiplyP			(Node *x, Node *y);
{

}


Node 	*num_divide				(Node *x, Node *y);
{

}


Node 	*num_quotient			(Node *x, Node *y);
{

}


Node 	*num_remainder			(Node *x, Node *y);
{

}


Node 	*num_equiv				(Node *x, Node *y);
{

}


Node 	*num_lt					(Node *x, Node *y);
{

}

Node 	*num_lte				(Node *x, Node *y);
{

}

Node 	*num_gte				(Node *x, Node *y);
{

}


Node 	*num_negate				(Node *x);
{

}

Node 	*num_negateP			(Node *x);
{

}


Node 	*num_inc				(Node *x);
{

}

Node 	*num_incP				(Node *x);
{

}


Node 	*num_dec				(Node *x);
{

}

Node 	*num_decP				(Node *x);
{

}
