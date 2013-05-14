#ifndef _TYPE_DATA_H_
#define _TYPE_DATA_H_


typedef struct{
	int x;
	int y;
}*Size,SizeStruct;

inline Size MakeSize(int p1,int p2){
	Size s=(Size)malloc(sizeof(SizeStruct));
	s->x=p1;
	s->y=p2;
	return s;
}

typedef unsigned char byte;

typedef struct
{
	char* value;
	int length;
}*Byte1DArray, Byte1DArrayStruct;
typedef struct
{
	short* value;
	int length;
}*Short1DArray, Short1DArrayStruct;

typedef struct
{
	int* value;
	int length;
}*Int1DArray, Int1DArrayStruct;


typedef struct
{
	Short1DArray *value;
	int length;
}*Short2DArray, Short2DArrayStruct;
typedef struct
{
	Byte1DArray *value; 
	int length;
}*Byte2DArray, Byte2DArrayStruct;

typedef struct
{
	Int1DArray *value; 
	int length;
}*Int2DArray, Int2DArrayStruct;

typedef struct{
	const char** value;
	int length;
}*String1DArray,String1DArrayStruct;

typedef struct{
	String1DArray value;
	int length;
}*String2DArray,String2DArrayStruct;
#endif
