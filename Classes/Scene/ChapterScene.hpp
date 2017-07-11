//
//  ChapterScene.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#ifndef MapScene_hpp
#define MapScene_hpp

#include "CCBase.h"
#include "ObjectPool.hpp"
#include "FloatStarObject.hpp"
#include "GameEndLayer.hpp"
#include "RandomGeometryCom.hpp"
#include "FloatStarObject.hpp"
#include "StarHelper.hpp"

class ChapterScene : public Scene {
protected:
    ~ChapterScene();
public:
    ChapterScene();
    CREATE_FUNC(ChapterScene);
    bool init() override;
    void onEnter() override;
    void onExit() override;
    void update(float dt) override;
    void generateStars(int num);
    
private:
    void initPhysicsParams();   //初始化物理世界
    void initBackGroundLayer(); //初始化背景层
    void initCollisionLayer();  //初始化碰撞层
    void initStackedLayer();    //初始化层堆
    void initJoyStick();        //初始化手柄层
    void initPauseControl();    //初始化暂停控件
    void initMainStar();        //初始化主星（玩家操作对象）
    void initDipperStar();      //初始化目标（北斗七星之一）
    void initMotionStreak();    //初始化游戏尾巴
    void initEnergyBar();       //初始化能量条
    void updateEnergyBar();     //刷新能量条
    void onListenContact();     //开始碰撞监听
    void unListenContact();     //关闭碰撞监听
    void openGameTargetLayer(); //打开游戏目标层
    void registerCustomEvent(); //注册自定义监听事件
    void openGameEndLayer(GameEndReason reason); //打开游戏结束层
    
    //定时器
    void onUpdateTimeCost();
    void unUpdateTimeCost();
    inline float getTimerCost() {
        return _journalPeriod;
    }
    
    
private:
    int _updateCount = 0;
    int _updateNum   = 1;
    float _journalPeriod = .0f;
    
    Node* _barContainer     = nullptr;
    Layer* _collisionLayer  = nullptr;
    Layer* _stackedLayer    = nullptr;
    MainStar* _mainStar     = nullptr;
    DipperStar* _dipperStar = nullptr;
    EventListenerPhysicsContact* _contactListener = nullptr;
};

#endif /* MapScene_hpp */
