/*
	Representation of classes
*/
Class class_array[] = {
	{"Const",		0},
	{"Byte",		sizeof(Byte)},
	{"Short",		sizeof(Short)},
	{"Int",			sizeof(Int)},
	{"Long",		sizeof(Long)},
	{"Float",		sizeof(Float)},
	{"Double",		sizeof(Double)},
	{"Char",		sizeof(Char)},
	{"String",		{Long, ZString}{Array, List}},
	{"ZString",		{Ptr}},
	{"Ptr",			sizeof(void *)},
	{"Array",		{Class, Long, Ptr}}
	{"List",		{Array}}
	{"Error",		{...}},
	{"Bigint",		{...}},
	{"Ratio",		{Integer, Integer}},
	{"Bigdec",		{...}},
	{"Func",		{...}}, // Function or method ?!? TODO to be seen
	{"Interface"	{...}},
	{"Class"		{Interface}{...}},
	{"Object",		{Class, ...}}
};
