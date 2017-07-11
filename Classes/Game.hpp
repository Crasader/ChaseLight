//
//  Game.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/19.
//
//

#ifndef Game_hpp
#define Game_hpp

#include "CCBase.h"
#include "Singleton.hpp"

enum class SceneDirectType {
    Run,
    Replace,
    Push,
    Pop,
    PopToRoot,
};

class Game : public Singleton<Game> {
public:
    bool init() override;
    void start();
    void end();
    
    void enterBackground();
    void enterForeground();
    
    void directScene(cocos2d::Scene* scene=nullptr, SceneDirectType type=SceneDirectType::Replace);
    void enterStartScene();
    void enterChapterScene(int chapterId);
    void exitChapterScene();
    
    void setLatestJournalInfo(const JournalInfo* info) {
        if(!info) return;
        _journal->reason    = info->reason;
        _journal->chapterId = info->chapterId;
        _journal->duration  = info->duration;
        _journal->energy    = info->energy;
        _journal->score     = info->score;
        _journal->distance  = info->distance;
    };
    JournalInfo* getLatestJournalInfo() {
        return _journal;
    }
    
private:
    bool _onChapter = false;
    int  _chapterId = 1;
    JournalInfo* _journal = nullptr;
    
private:
    void loadImages();
    void adaptScreen();
    void addSearchPaths();
};

#endif /* Game_hpp */
