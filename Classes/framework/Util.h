#ifndef _UTIL_H_
#define _UTIL_H_

#include "cocos2d.h"
#include "framework/DataType.h"
#include "framework/DataInputStream.h"
#include "data/Consts.h"
using namespace std;
class Util
{
public:
	Util();
	~Util();
	static void setRandomSeed();//设置随机种子
	//在使用getRandom之前调用setRandomSeed。
	static int getRandom(int number);
	static int getRandom(int startN,int endN);
    static long millisecondNow();//获取系统的毫秒时间

	//将字符串转换成数字。
	static int strToNum(string s);
	//通过相对路径获取完整途径
	static const char* getPath(const cocos2d::CCString path);

	//用于读取xls表中的数据
	static Short2DArray read2DShortData(const cocos2d::CCString path);
	static Int2DArray   read2DIntData(const cocos2d::CCString path);
	static Byte2DArray  read2DByteData(const cocos2d::CCString path);

	static cocos2d::CCString* getString(const cocos2d::CCString path);
	static String1DArray getStrArray(cocos2d::CCString* str,const char* tag);
	static int indexOf(cocos2d::CCString* str,const char* ch,int fromIndex){
		return str->m_sString.find(ch, fromIndex);
	}
	static cocos2d::CCString* substring(cocos2d::CCString*str,int startIndex,int endIndex){
		return cocos2d::CCString::create(str->m_sString.substr(startIndex,endIndex-startIndex));
	}
	static cocos2d::CCString* substring(cocos2d::CCString*str,int startIndex){
		return cocos2d::CCString::create(str->m_sString.substr(startIndex,str->m_sString.length()-startIndex));
	}	


	static Short2DArray formatData(Short1DArray data,int size);
	static Short1DArray arrayAppend(Short1DArray src,short* add,int size);
	static vector<short> loadShort1DToVector(DataInputStream* dis);
	static vector< vector<short> > loadShort2DToVector(DataInputStream* dis);
	static Short1DArray vector1DtoShort1DArray(vector<short> vector1D);
	static Short2DArray vector1DtoShort2DArray(vector<short> vector1D,int count);
    static Int2DArray   vector2DToInt2DArray(vector< vector<int> > vector2D);
	static Short2DArray vector2DtoShort2DArray(vector< vector<short> > vector2D,int count);
    static Int2DArray   vector2DToInt2DArray(vector< vector<int> > vector2D,int count);
    
    
    


};

#endif
