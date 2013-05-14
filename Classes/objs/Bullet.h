#pragma once
#include "Role.h"
class Bullet :
	public Role
{
public:
	Bullet(void);
	~Bullet(void);
	static Bullet* create(const char* xmlName,int rID,Short1DArray info);
	virtual void init(const char* xmlName,int rID,Short1DArray info);
};

