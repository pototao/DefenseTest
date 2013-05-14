#include "Bullet.h"

#include "data/Consts.h"
Bullet::Bullet(void)
{
}


Bullet::~Bullet(void)
{
}
void Bullet::init(const char* xmlName,int rID,Short1DArray info){
	Role::init(xmlName,rID,info);
	prefix="b";
	this->setContentSize(CCSizeMake(5,5));
	changeState(STAND,STAND);
}

Bullet*Bullet::create(const char* xmlName,int rID,Short1DArray info){
	Bullet* role=new Bullet();
	if(role){
		role->init(xmlName,rID,info);
		role->autorelease();
	}
	return role;
}