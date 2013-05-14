//
//  DataInputStream.h
//  MyBox2d
//
//  Created by  陈广文 on 12-12-21.
//
//

#ifndef __MyBox2d__DataInputStream__
#define __MyBox2d__DataInputStream__

#include <iostream>
#include "cocos2d.h"
class DataInputStream:public cocos2d::CCObject{
public:
    DataInputStream();
    ~DataInputStream();
    static DataInputStream* create(const char* path);
    bool open(const char*path);
    int   readInt();
    short readShort();
    char  readByte();
    unsigned const char* readUTF();
    void close();
    int getLength();
private:
    unsigned char * buffer;
	int pvrlen ;
	int position ;
    
};
#endif /* defined(__MyBox2d__DataInputStream__) */
