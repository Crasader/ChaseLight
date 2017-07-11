//
//  UserDataService.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/24.
//
//

#ifndef UserDataService_hpp
#define UserDataService_hpp

#include "cocos2d.h"
#include "Singleton.hpp"
USING_NS_CC;
using namespace std;

#define VALID_CHAPTERID(id) (id>=1 && id<=7)

namespace UserDataKey {
    static const char* CurrentPlayChapater  = "CurrentPlayChapater";
    static const char* CurrentMaxChapater   = "CurrentMaxChapater";
    static const char* EveryChapterRecord   = "EveryChapterRecord";
}

struct ChapterUserData {
    int ChapterId;
    int HighestScore;
    float UseTime;
    float RemainDistance;
    
    ChapterUserData() {
        ChapterId = 1;
        HighestScore = 0;
        UseTime = 0.f;
        RemainDistance = 0.f;
    }
};

class UserDataService : public Singleton<UserDataService> {
public:
    bool init() override;
    void start();
    
    int getCurMaxChapter();
    void setCurMaxChapter(int chapterId);
    
    int getCurPlayChapter();
    void setCurPlayChapter(int chapterId);
    
    ChapterUserData* getChapterRecord(int chapterId);
    void setChapterRecord(int chapterId, int score, float time, float distance);
    
private:
    void loadChapterRecords(std::string records);
    void writeChapterRecords();
    
private:
    int _curMaxChapter;     //当前可玩的最高章节
    int _curPlayChapter;    //上次玩的章节
    std::map<int,ChapterUserData*> _mapChapterUserData; //所有章节记录数据
};

#endif /* UserDataService_hpp */
