//
//  MySQLite.h
//  MyBox2d
//
//  Created by fang on 12-12-10.
//
//
/*author cgw 20121212
 url:http://www.cnblogs.com/kfqcome/archive/2011/06/27/2136999.html
 url:http://4137613.blog.51cto.com/4127613/772518
 */
#ifndef __MyBox2d__MySQLite__
#define __MyBox2d__MySQLite__
#include "cocos2d.h"
#include <iostream>
#include "sqlite3.h"
#include "DataType.h"
class MySQLite :public cocos2d::CCObject{
private:
    const char* DBName;
    sqlite3 *pDB;
    char * errMsg;
    int result;
   
public:
    MySQLite();
    ~MySQLite();
    void init();
    void setDBName(const char *name);
    static MySQLite* create(const char *name);
    bool createTable(const cocos2d::CCString tableName,const cocos2d::CCString sqlStr);
    bool open();
    bool close();
    bool insert(const cocos2d::CCString tableName,const cocos2d::CCString sqlStr,Int2DArray data);
    bool insert(const cocos2d::CCString tableName,const cocos2d::CCString sqlStr,Int1DArray data);
    bool insert(const cocos2d::CCString tableName,const cocos2d::CCString sqlStr,String1DArray data);
    bool insert(const cocos2d::CCString tableName,const cocos2d::CCString sqlStr,  sqlite3_callback xCallback,void *pArg);
    bool selectAll(const cocos2d::CCString tableName,sqlite3_callback xCallback,void *pArg);
    void load(const cocos2d::CCString tableName,const cocos2d::CCString sqlStr,Int2DArray data);
    void load(const cocos2d::CCString tableName,const cocos2d::CCString sqlStr,Int1DArray data);
    void load(const cocos2d::CCString tableName,const cocos2d::CCString sqlStr,String1DArray data);

};
#endif /* defined(__MyBox2d__MySQLite__) */
