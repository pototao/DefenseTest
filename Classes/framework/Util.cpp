#include "Util.h"
#include "cocos2d.h"
#include "DataType.h"
USING_NS_CC;
Util::Util()
{

}
Util::~Util()
{

}
void Util::setRandomSeed()

{

	cc_timeval psv;

	CCTime::gettimeofdayCocos2d(&psv, NULL);

	unsigned long int seed = psv.tv_sec*1000 + psv.tv_usec/1000;

	srand(seed);



}

int Util::getRandom(int number)

{

	return CCRANDOM_0_1()*number;

}

int Util::getRandom(int startN,int endN)

{

	CCAssert(endN>startN, "");

	return CCRANDOM_0_1()*(endN-startN)+startN;

}

const char* Util::getPath(const cocos2d::CCString path){
    CCLOG("Util::getPath()=%s",path.getCString());
	return CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(path.getCString(),path.getCString());
}


long Util::millisecondNow()
{
    struct cocos2d::cc_timeval now;
    cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

vector<short> Util::loadShort1DToVector(DataInputStream*dis){
   
    vector<short> des;
	short length1 = dis->readShort();
	short singleDataLength =dis->readShort();
	for (int i = 0; i < (length1 * singleDataLength); i++) {
		des.push_back(dis->readShort());
	}
	return des;
}


vector< vector<short> > Util::loadShort2DToVector(DataInputStream*dis){
    vector< vector<short> > des;
	short length1 =dis->readShort();
	short singleDataLength = dis->readShort();
	des.resize(length1);
	for (int i = 0; i < length1; i++) {
		short length2 =dis->readShort();
		for (int j = 0; j < (length2 * singleDataLength); j++) {
			des[i].push_back(dis->readShort());
		}
	}
	return des;
}

int Util::strToNum(string s)
{   
	int num;
	stringstream ss(s);
	ss>>num;
	return num;
}

Short2DArray Util::formatData(Short1DArray data,int size)
{
	if (data == NULL) {
		return NULL;
	}
	Short2DArray des = (Short2DArray)malloc(sizeof(Short2DArrayStruct));
	des->value = (Short1DArray*)malloc(sizeof(Short1DArray) * size);
	des->length = size;
	for (int i = 0; i < des->length; i ++) {
		des->value[i]=NULL;
	}
	short tempdata[4] = {0,0,0,0};
	for (int i = 0; i < data->length / 5; i ++) {
		tempdata[0] = data->value[i * 5 + 1];
		tempdata[1] = data->value[i * 5 + 2];
		tempdata[2] = data->value[i * 5 + 3];
		tempdata[3] = data->value[i * 5 + 4];
		des->value[data->value[i*5]] = Util::arrayAppend(des->value[data->value[i*5]],tempdata,4);
	}
	return des;
}

Short1DArray Util::arrayAppend(Short1DArray src,short* add,int size)
{
	int pos = 0;
	int len = 0;
	Short1DArray temp;
	if (src != NULL) 
	{
		pos = src->length;
	}
	len = pos + size;
	temp = (Short1DArray)malloc(sizeof(Short1DArrayStruct));
	temp->value=(short*)malloc(sizeof(short)*len);
	temp->length=len;
	if (src != NULL) 
	{
		for (int i = 0; i < src->length; i ++) {
			temp->value[i] = src->value[i];
		}
	}
	for (int i = 0; i < size; i ++) {
		temp->value[i + pos] = add[i];
	}
	return temp;
}

Int2DArray Util::vector2DToInt2DArray(vector< vector<int> > vector2D)
{
	Int2DArray temp=(Int2DArray)malloc(sizeof(Int2DArrayStruct));
	temp->length=vector2D.size();
	temp->value=(Int1DArray*)malloc(sizeof(Int1DArray)*vector2D.size());
	int m=vector2D.size();
	for (int i=0;i<m;i++)
	{
		temp->value[i]=(Int1DArray)malloc(sizeof(Int1DArrayStruct));
		temp->value[i]->value=(int*)malloc(sizeof(int)*vector2D.at(i).size());
		temp->value[i]->length=vector2D.at(i).size();
		int n=vector2D.at(i).size();
		for (int j=0;j<n;j++)
		{
			temp->value[i]->value[j]=vector2D.at(i).at(j);
		}
	}
	return temp;
}

Short1DArray Util::vector1DtoShort1DArray(vector<short> vector1D)
{
	Short1DArray temp=(Short1DArray)malloc(sizeof(Short1DArrayStruct));
	temp->length=vector1D.size();
	temp->value=(short*)malloc(sizeof(short)*vector1D.size());
	int n=vector1D.size();
	for (int i=0;i<n;i++)
	{
		temp->value[i]=vector1D.at(i);
	}
	return temp;
}

Short2DArray Util::vector1DtoShort2DArray(vector<short> vector1D,int count)
{
	Short2DArray temp=(Short2DArray)malloc(sizeof(Short2DArrayStruct));
	int size=vector1D.size()/count;
	temp->length=size;
	temp->value=(Short1DArray*)malloc(sizeof(Short1DArray)*size);
	for (int i=0;i<size;i++)
	{
		temp->value[i]=(Short1DArray)malloc(sizeof(Short1DArrayStruct));
		temp->value[i]->value=(short*)malloc(sizeof(short)*count);
		temp->value[i]->length=count;
		for (int j=0;j<count;j++)
		{
			temp->value[i]->value[j]=vector1D.at(i*count+j);
		}
	}
	return temp;
}
Short2DArray Util::vector2DtoShort2DArray(vector< vector<short> > vector2D,int count)
{
	Short2DArray temp=(Short2DArray)malloc(sizeof(Short2DArrayStruct));
	temp->length=vector2D.size();
	temp->value=(Short1DArray*)malloc(sizeof(Short1DArray)*vector2D.size());
	int m=vector2D.size();
	for (int i=0;i<m;i++)
	{
		temp->value[i]=(Short1DArray)malloc(sizeof(Short1DArrayStruct));
		temp->value[i]->value=(short*)malloc(sizeof(short)*vector2D.at(i).size());
		temp->value[i]->length=vector2D.at(i).size();
		int n=vector2D.at(i).size();
		for (int j=0;j<n;j++)
		{
			temp->value[i]->value[j]=vector2D.at(i).at(j);
		}
	}
	return temp;
}
Int2DArray Util::vector2DToInt2DArray(vector< vector<int> > vector2D,int count)
{
	Int2DArray temp=(Int2DArray)malloc(sizeof(Int2DArrayStruct));
	temp->length=vector2D.size();
	temp->value=(Int1DArray*)malloc(sizeof(Int1DArray)*vector2D.size());
	int m=vector2D.size();
	for (int i=0;i<m;i++)
	{
		temp->value[i]=(Int1DArray)malloc(sizeof(Int1DArrayStruct));
		temp->value[i]->value=(int*)malloc(sizeof(int)*vector2D.at(i).size());
		temp->value[i]->length=vector2D.at(i).size();
		int n=vector2D.at(i).size();
		for (int j=0;j<n;j++)
		{
			temp->value[i]->value[j]=vector2D.at(i).at(j);
		}
	}
	return temp;
}
Short2DArray Util::read2DShortData(const cocos2d::CCString path){
    Short2DArray temp=NULL;
    DataInputStream*dis=DataInputStream::create(path.getCString());
    temp=(Short2DArray)malloc(sizeof(Short2DArrayStruct));
    temp->length=dis->readInt();
    temp->value=(Short1DArray*)malloc(sizeof(Short1DArrayStruct)*temp->length);
    for (int i=0; i<temp->length;i++) {
 		temp->value[i]=(Short1DArray)malloc(sizeof(Short1DArrayStruct));
        int n=dis->readInt();;
        temp->value[i]->length=n;
		temp->value[i]->value=(short*)malloc(sizeof(short)*n);
		for (int j=0;j<n;j++)
		{
			temp->value[i]->value[j]=dis->readShort();

		}

    }
    dis->close();
    return temp;
}
Int2DArray Util::read2DIntData(const cocos2d::CCString path){
    Int2DArray temp=NULL;
    DataInputStream*dis=DataInputStream::create(path.getCString());
    temp=(Int2DArray)malloc(sizeof(Int2DArrayStruct));
    temp->length=dis->readInt();
    temp->value=(Int1DArray*)malloc(sizeof(Int1DArrayStruct)*temp->length);
    for (int i=0; i<temp->length;i++) {
 		temp->value[i]=(Int1DArray)malloc(sizeof(Int1DArrayStruct));
        int n=dis->readInt();;
        temp->value[i]->length=n;
		temp->value[i]->value=(int*)malloc(sizeof(int)*n);
		for (int j=0;j<n;j++)
		{
			temp->value[i]->value[j]=dis->readInt();

		}

    }
    dis->close();
    return temp;
}
Byte2DArray Util::read2DByteData(const cocos2d::CCString path){
    Byte2DArray temp=NULL;
    DataInputStream*dis=DataInputStream::create(path.getCString());
    temp=(Byte2DArray)malloc(sizeof(Byte2DArrayStruct));
    temp->length=dis->readInt();
    temp->value=(Byte1DArray*)malloc(sizeof(Byte1DArrayStruct)*temp->length);
    for (int i=0; i<temp->length;i++) {
 		temp->value[i]=(Byte1DArray)malloc(sizeof(Byte1DArrayStruct));
        int n=dis->readInt();
        temp->value[i]->length=n;
		temp->value[i]->value=(char*)malloc(sizeof(char)*n);
		for (int j=0;j<n;j++)
		{
			temp->value[i]->value[j]=dis->readByte();
		}
    }
    dis->close();
    return temp;
}
CCString* Util::getString(const cocos2d::CCString path){
    DataInputStream*dis=DataInputStream::create(path.getCString());
    unsigned const char* buffer=dis->readUTF();
    
    unsigned long len=dis->getLength();
    CCString *temp=CCString::createWithData(buffer,len);
//    CCLog("getString %s len %d ",temp->getCString(),len);
    dis->close();
    return temp;
}

/**
 *
 * @param str
 * @param tag
 * @return String1DArray
 */
String1DArray Util::getStrArray(CCString* str,const char* tag) {//tag 例如“\n” 这种
    CCArray*  array =new  CCArray;
    array->autorelease();
    int start = 0;
    int end =0;
    while ((end=Util::indexOf(str,tag, start)) != -1) {
       // CCLog(" %s  ",Util::substring(str,start, end)->getCString());
       // CCLog("start: %d end:%d  ",start,end);
        array->addObject(Util::substring(str,start, end));
        start = end+2 ;
    }
    int len=array->count();
    String1DArray temp=(String1DArray)malloc(sizeof(String1DArrayStruct));
    temp->value=(const char**)malloc(sizeof(const char*)*len);
    temp->length=len;
    for (int i=0;i<len;i++)
    {
        CCString* t=(CCString*)array->objectAtIndex(i);
        temp->value[i]=t->getCString();
    }
    array->removeAllObjects();
    return temp;
}


