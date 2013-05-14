//
//  DataInputStream.cpp
//  MyBox2d
//
//  Created by  陈广文 on 12-12-21.
//
//

#include "DataInputStream.h"
#include "cocos2d.h"
#include "Util.h"
USING_NS_CC;
DataInputStream::DataInputStream(){
}
DataInputStream::~DataInputStream(){}
DataInputStream*DataInputStream::create(const char *path){
    DataInputStream* temp=new DataInputStream();
    if(temp){
        temp->open(path);
        temp->autorelease();
    }
    return temp;
}

unsigned const char* DataInputStream::readUTF(){
//    if(encode=="GBK"){
    return buffer;
//    }else{
//        
//    }
    
}
int DataInputStream::getLength(){
    return pvrlen;
}
bool DataInputStream::open(const char *path){
    buffer=NULL;
    pvrlen = 1;
    position = 0;
	CCFileUtils *fUtils=CCFileUtils::sharedFileUtils();
	buffer = fUtils->getFileData(Util::getPath(path), "rb", (unsigned long *)(&pvrlen));
	if(pvrlen == 0)
	{
		return false;
	}
    return true;
}
int DataInputStream::readInt(){
	int temp = 0;
	for(int i = 0;i < 4;i++){
		int shift = (4-1-i)  * 8;
		temp |= (buffer[(position)] & 0x000000ff) << shift;
        
		(position)++;
	}
	return temp;
}

short DataInputStream::readShort(){
	short temp = 0;
	temp = buffer[(position)] << 8;
	(position)++;
	temp |= (buffer[(position)] & 0xff);
	(position)++;
	return temp;
}

char DataInputStream::readByte(){
	char temp = 0;
	temp =(buffer[(position)] & 0xff);
	(position)++;
    return temp;
}
void DataInputStream::close(){

}