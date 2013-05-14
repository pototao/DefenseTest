#ifndef _GAME_DATA_
#define _GAME_DATA_
#include "cocos2d.h"
#include "framework/DataType.h"
const byte LOGO=0,MAIN_MENU=1,PUT_PLANE=2,SET_BOMB=3,CLICK_BOMB=4,GAME_OVER=5,GAME_WIN=6,SUMMARY=7;
const float bigBackLayerX=330;
const float bigBackLayerY=50;
const float bigBackLayerW=560;
const float smallBackLayerX=10;
const float smallBackLayerY=300;
const float smallBackLayerW=320;
const float SCALE=0.5;
const int LEFT_POINT=6,TOP_POINT=1,RIGHT_POINT=16,BOTTOM_POINT=11;
const int NUM=100;
const int bigW=56,smallW=32;
const int LAYER_NUM=5;
const int OBJ_NUM=10;
const std::string TMX_MAP_NAME[LAYER_NUM]={"tileMap.tmx","","","","",};
const std::string ENERMY_NAME[LAYER_NUM]={"e0.xml","e1.xml","","","",};
const std::string TOWER_NAME[LAYER_NUM]={"t0.xml","t1.xml","","","",};
const std::string BULLET_NAME[LAYER_NUM]={"b0.xml","b1.xml","","","",};
const std::string LAYER_NAME[LAYER_NUM]={"","","","","",};
//cocos2d::CCString BUTTON="button";
const std::string OBJECTS_NAME[LAYER_NUM][OBJ_NUM]={
    {"plane0","plane1","plane2","label0","label1","label2","shop","home","set","next",},
    {""},
    {""},
    {""},
    {""},
};
const cocos2d::CCString PATH_PERSON_INFO="planeInfo.data";
const cocos2d::CCString PATH_BOMB_INFO="bombInfo.data";
const cocos2d::CCString datePath[][3] = {
	"plane0.data","1","planes",
	"plane1.data","1","planes",
	"plane2.data","1","planes",
    "bomb0.data","1","bomb",
};
const cocos2d::CCString  rolePath[1][12] = {
	{"nvrenzhe.data","12","nvrenzhe","6","1","nvrenzhe_w","4","1","nvrenzhe_t","5","1","nvrenzhe_tz"},
    
    
};


#endif
