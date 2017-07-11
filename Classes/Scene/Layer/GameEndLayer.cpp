//
//  GameEndLayer.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#include "GameEndLayer.hpp"
#include "VerticalTextNode.hpp"
#include "TimeUtilRef.h"

bool GameEndLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    //目标
    auto chapterId = g_User->getCurPlayChapter();
    auto labTarget = Label::createWithTTF(g_GetTextInfo(chapterId+70), FontMonitor::GAMEFONT, 24);
    addChild(labTarget);
    _labTarget = labTarget;
    
    //箴言
    auto vertical = VerticalTextNode::create();
    vertical->setFontSize(12);
    vertical->setLineSpace(12.f);
    vertical->setDirection(VerticalTextDirection::RIGHT_TO_LEFT);
    vertical->randomText();
    auto vsize = vertical->getContentSize();
    vertical->setPosition(SCREEN_WIDTH-vsize.width-20.f, (SCREEN_HEIGHT+vsize.height)*.5f);
    vertical->fade();
    addChild(vertical);
    
    //延时可触摸
    auto duration = vertical->getDuration() + .2f;
    scheduleOnce([=](float dt) {
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [=](Touch* touch, Event* event) {
            return true;
        };
        listener->onTouchEnded = [=](Touch* touch, Event* event) {
            g_Game->exitChapterScene();
        };
        _listener = listener;
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
        
        _labTwinkle->fade();
    }, duration, SchedulerCode::OnceEnableEndClick);
    
    //点击屏幕以继续
    auto labTwinkle = TwinkleTextNode::create();
    addChild(labTwinkle);
    _labTwinkle = labTwinkle;
    
    return true;
}

void GameEndLayer::onEnter() {
    Layer::onEnter();
}

void GameEndLayer::onExit() {
    _eventDispatcher->removeEventListener(_listener);
    Layer::onExit();
}

void GameEndLayer::open() {
    JournalInfo* info = g_Game->getLatestJournalInfo();
    
    auto reason = info->reason;
    std::string reason_str = "";
    if(reason == GameEndReason::EnergyRanOut) {
        reason_str = g_GetTextInfo(41);
    } else if (reason == GameEndReason::DeadForStarExplosion) {
        reason_str = g_GetTextInfo(42);
    } else if (reason == GameEndReason::PositiveExitJournal) {
        reason_str = g_GetTextInfo(43);
    } else if (reason == GameEndReason::CompleteJournal) {
        reason_str = g_GetTextInfo(44);
    }
    
    //预备数据
    auto chapterId = g_User->getCurPlayChapter();
    auto chapterInfo = g_Service->getChapterInfo(chapterId);
    CCASSERT(chapterInfo!=nullptr, "chapter config must not be empty");
    auto isSuccess = reason == GameEndReason::CompleteJournal;
    auto chapterData  = g_User->getChapterRecord(chapterId);
    auto highestScore = chapterData ? chapterData->HighestScore : 0;
    auto isNewRecord  = info->score > highestScore;
    auto isNewestChapter = chapterId == g_User->getCurMaxChapter() && chapterId < 7;
    auto isInLimitTime = info->duration <= chapterInfo->condition_time;
    auto isInLimitScore = info->score >= chapterInfo->condition_score;
//    auto isInLimitEnergy = chapterInfo->condition_energy >= info->energy;
    auto isNewUnlock  = (isSuccess && isNewestChapter && isInLimitTime && isInLimitScore);
    
    //原因
    auto size = SCREEN_SIZE;
    auto labReason = Label::createWithTTF(reason_str, FontMonitor::GAMEFONT, 14);
    labReason->setColor(isSuccess ? Color3B(0,199,140) : Color3B(255,69,0));
    addChild(labReason);
    
    //用时
    auto time_str = g_GetTextInfo(5)+std::string(TimeUtil::format(info->duration+.5f));
    auto labTime = Label::createWithTTF(time_str, FontMonitor::GAMEFONT, 16);
    labTime->setColor(isInLimitTime ? Color3B::GREEN : Color3B::RED);
    addChild(labTime);
    
    //得分
    auto score_str = StringUtils::format(g_GetTextInfo(8).c_str(), info->score);
    auto labScore = Label::createWithTTF(score_str, FontMonitor::GAMEFONT, 16);
    labScore->setColor(isInLimitScore ? Color3B::GREEN : Color3B::RED);
    addChild(labScore);
    
    //对屏幕居中对齐的文本标签
    std::vector<Node*> labels = {
        _labTarget,
        labReason,
        labTime,
        labScore
    };
    
    //新纪录
    if(isNewRecord) {
        g_User->setChapterRecord(chapterId, info->score, info->duration, info->distance);
        
        auto labRecord = Label::createWithTTF(g_GetTextInfo(6), FontMonitor::GAMEFONT, 14);
        auto tint = TintBy::create(.5f, 255, 0, 0);
        auto seq = Sequence::create(tint, tint->reverse(), NULL);
        labRecord->runAction(RepeatForever::create(seq));
        addChild(labRecord);
        labels.push_back(labRecord);
    }
    
    //解锁新章节
    if(isNewUnlock) {
        g_User->setCurMaxChapter(chapterId+1);
        
        _eventDispatcher->dispatchCustomEvent(CustomEventCode::UnlockNewChapter);
        auto new_str = StringUtils::format(g_GetTextInfo(9).c_str(), g_GetTextInfo(chapterId+11).c_str());
        auto labNew = Label::createWithTTF(new_str, FontMonitor::GAMEFONT, 20);
        auto tint = TintBy::create(.5f, 255, 255, 0);
        auto seq = Sequence::create(tint, tint->reverse(), NULL);
        labNew->runAction(RepeatForever::create(seq));
        addChild(labNew);
        labels.push_back(labNew);
    }
    
    
    g_AlignScreenCenter(labels, 10.f);
}
