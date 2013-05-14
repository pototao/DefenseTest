//
//  MySQLite.cpp
//  MyBox2d
//
//  Created by fang on 12-12-10.
//
//

#include "MySQLite.h"
#include "cocos2d.h"
#include "Util.h"
USING_NS_CC;

MySQLite::MySQLite():errMsg(""),result(SQLITE_OK),pDB(NULL),DBName(""){}

MySQLite::~MySQLite(){}

void MySQLite::init(){}

void MySQLite::setDBName(const char *name){
  DBName=name;
}
MySQLite* MySQLite::create(const char *fileName)
{
    MySQLite *mySQLite = new MySQLite();
    if (mySQLite)
    {   mySQLite->init();
        mySQLite->setDBName(fileName);
        mySQLite->autorelease();
        return mySQLite;
    }
    CC_SAFE_DELETE(mySQLite);
    return NULL;
}
bool MySQLite::open(){
    CCFileUtils *fUtils=CCFileUtils::sharedFileUtils();
	const char* fullname=(fUtils->getWritablePath()+DBName).data();
    CCLog( "fullPath :%s\n" , fullname );
    result = sqlite3_open(fullname, &pDB);
    if( result != SQLITE_OK ){
        CCLog( "打开数据库失败，错误码:%d , 错误原因:%s\n" , result,errMsg );
        return false;
    }
    return true;
}
bool MySQLite::close(){
    result = sqlite3_close(pDB);
    if(result != SQLITE_OK ){
        CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
        return false;
    }        
    return true;
}
bool MySQLite::createTable(const CCString tableName,const CCString sqlStr){
    CCString head="CREATE TABLE IF NOT EXISTS";
    CCString *temp = CCString::createWithFormat("%s %s %s",head.getCString(),tableName.getCString(), sqlStr.getCString());
   
    result=sqlite3_exec( pDB,temp->getCString(), NULL, NULL, &errMsg );
    if( result != SQLITE_OK ){
        CCLog( "创建表失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
        return false;
    }
    return true;

}

bool MySQLite::insert(const CCString tableName,const CCString sqlStr,  sqlite3_callback xCallback,void *pArg){
    CCString head="INSERT OR REPLACE INTO";
    CCString *temp = CCString::createWithFormat("%s %s %s",head.getCString(),tableName.getCString(), sqlStr.getCString());
    result = sqlite3_exec( pDB, temp->getCString(), xCallback, pArg, &errMsg );
    if(result != SQLITE_OK ){
        CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
        return false;
    }
    return true;
}

bool MySQLite::insert(const CCString tableName,const CCString sqlStr,Int2DArray data){
    CCString head="INSERT OR REPLACE INTO";
    CCString *temp = CCString::createWithFormat("%s %s %s",head.getCString(),tableName.getCString(), sqlStr.getCString());
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(pDB, temp->getCString(), -1, &stmt, NULL) == SQLITE_OK)
	{
        for (int i=0; i!=data->length; i++) {
             sqlite3_bind_int(stmt, 1, i);
            for (int j=0; j!=data->value[i]->length; j++) {
                    sqlite3_bind_int(stmt, j+2, data->value[i]->value[j]);
            }
            if(sqlite3_step(stmt) != SQLITE_DONE){
                 CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
                return false;
            }
            sqlite3_reset(stmt);
        }
        
    }

	sqlite3_finalize(stmt);
    return true;
}

void  MySQLite::load(const CCString tableName,const CCString sqlStr,Int2DArray data){
    CCString head="select * from";
    CCString *temp = CCString::createWithFormat("%s %s",head.getCString(),tableName.getCString());
	sqlite3_stmt *stmt;
	if(sqlite3_prepare_v2(pDB, temp->getCString(), -1, &stmt, NULL) != SQLITE_OK)
	{
		 CCLog( "表不存在，错误码:%d ，错误原因:%s\n" , result, errMsg );
		return;
	}
    int cnum=sqlite3_column_count(stmt);
    std::vector< std::vector<int> > des;
    while(sqlite3_step(stmt) == SQLITE_ROW)
	{
        std::vector<int> temp;
        //int index=sqlite3_column_int(stmt,0);//
		for(int i = 1; i < cnum; i++)
		{
            
            int d=sqlite3_column_int(stmt,i);
            temp.push_back(d);
        }
        des.push_back(temp);
        
	}
    data=Util::vector2DToInt2DArray(des);
	sqlite3_finalize(stmt);
}

bool MySQLite::insert(const CCString tableName,const CCString sqlStr,Int1DArray data){
    CCString head="INSERT OR REPLACE INTO";
    CCString *temp = CCString::createWithFormat("%s %s %s",head.getCString(),tableName.getCString(), sqlStr.getCString());
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(pDB, temp->getCString(), -1, &stmt, NULL) == SQLITE_OK){
        return false;
    }
        sqlite3_bind_int(stmt, 1, 0);
        for (int j=0; j!=data->length; j++) {
            sqlite3_bind_int(stmt, j+2, data->value[j]);
        }
        if(sqlite3_step(stmt) != SQLITE_DONE){
            CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
            return false;
        }

	sqlite3_finalize(stmt);
    return true;
}

void  MySQLite::load(const CCString tableName,const CCString sqlStr,Int1DArray data){
    CCString head="select * from";
    CCString *temp = CCString::createWithFormat("%s %s",head.getCString(),tableName.getCString());
	sqlite3_stmt *stmt;
	if(sqlite3_prepare_v2(pDB, temp->getCString(), -1, &stmt, NULL) != SQLITE_OK)
	{
        CCLog( "表不存在，错误码:%d ，错误原因:%s\n" , result, errMsg );
		return;
	}
    int cnum=sqlite3_column_count(stmt);
    if(sqlite3_step(stmt) == SQLITE_ROW) //
	{
        std::vector<int> temp;
        //int index=sqlite3_column_int(stmt,0);//
		for(int i = 1; i < cnum; i++)
		{            
            int d=sqlite3_column_int(stmt,i);
            temp.push_back(d);
        }
        
	}
	sqlite3_finalize(stmt);
}

bool MySQLite::insert(const CCString tableName,const CCString sqlStr,String1DArray data){
    CCString head="INSERT OR REPLACE INTO";
    CCString *temp = CCString::createWithFormat("%s %s %s",head.getCString(),tableName.getCString(), sqlStr.getCString());
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(pDB, temp->getCString(), -1, &stmt, NULL) == SQLITE_OK){
        return false;
    }
    sqlite3_bind_int(stmt, 1, 0);//
    for (int j=0; j!=data->length; j++) {
        sqlite3_bind_text(stmt, j+2, data->value[j],strlen(data->value[j]),SQLITE_STATIC);
    }
    if(sqlite3_step(stmt) != SQLITE_DONE){
        CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
        return false;
    }
    
	sqlite3_finalize(stmt);
    return true;
}

void  MySQLite::load(const CCString tableName,const CCString sqlStr,String1DArray data){
    CCString head="select * from";
    CCString *temp = CCString::createWithFormat("%s %s",head.getCString(),tableName.getCString());
	sqlite3_stmt *stmt;
	if(sqlite3_prepare_v2(pDB, temp->getCString(), -1, &stmt, NULL) != SQLITE_OK)
	{
        CCLog( "表不存在，错误码:%d ，错误原因:%s\n" , result, errMsg );
		return;
	}
    int cnum=sqlite3_column_count(stmt);
    if(sqlite3_step(stmt) == SQLITE_ROW) //
	{
        std::vector<const unsigned char* > temp;
        //int index=sqlite3_column_int(stmt,0);//
		for(int i = 1; i < cnum; i++)
		{
            const unsigned char* d=sqlite3_column_text(stmt,i);
            temp.push_back(d);
        }
        
	}

	sqlite3_finalize(stmt);
}

bool MySQLite::selectAll(const CCString tableName,sqlite3_callback xCallback,void *pArg){
    CCString head="select * from";
    CCString *temp = CCString::createWithFormat("%s %s",head.getCString(),tableName.getCString());
    result = sqlite3_exec( pDB, temp->getCString(), xCallback, pArg, &errMsg );
    if(result != SQLITE_OK ){
        CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
        return false;
    }
    return true;
}