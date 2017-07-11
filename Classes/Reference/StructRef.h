//
//  StructRef.h
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/20.
//
//

#ifndef StructRef_h
#define StructRef_h

#include "cocos2d.h"

//配置
struct ConfigInfo {
    bool showFPS;;
    bool debugdraw;
    float gravity_y;
    int updaterate;
};

//星座配置
struct ChapterInfo {
    int chapterId;
    int textId;
    float light;
    float magnitude;
    int condition_text;
    int condition_time;
    int condition_score;
    int condition_energy;
    cocos2d::Vec2 coord;
};

//纹理配置
struct TextureInfo {
    std::string path;
    std::string key;
};

//旅行结束原因
enum class GameEndReason {
    CompleteJournal,        //成功
    DeadForStarExplosion,   //超新星爆炸
    EnergyRanOut,           //能量耗尽
    PositiveExitJournal,   //主动结束
};

//旅行配置
struct JournalInfo {
    int chapterId;
    int score;
    int energy;
    float duration;
    float distance;
    GameEndReason reason;
};

#endif /* StructRef_h */
