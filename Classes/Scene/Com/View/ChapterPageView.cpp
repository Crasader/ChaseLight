//
//  ChapterPageView.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/24.
//
//

#include "ChapterPageView.hpp"
#include "VerticalTextNode.hpp"

bool ChapterPageView::init() {
    if(!PageView::init()) {
        return false;
    }
    
    auto size = SCREEN_SIZE;
    setSizeType(cocos2d::ui::Widget::SizeType::ABSOLUTE);
    setContentSize(size);
//    setIndicatorEnabled(true);
//    reload();
    
    _eventDispatcher->addCustomEventListener(CustomEventCode::UnlockNewChapter, [=](EventCustom* event) {
        if(!event->isStopped()) {
            this->reload();
        }
    });
    
    return true;
}

void ChapterPageView::addChapter(int chapterId) {
    auto center = SCREEN_CENTER;
    auto size = SCREEN_SIZE;
    auto page = Layout::create();
    page->setContentSize(size);
    
    auto chapterInfo = g_Service->getChapterInfo(chapterId);
    auto file = StringUtils::format("star_b%d.png", chapterId);
    auto light = ImageView::create(file);
    auto py = size.height * chapterInfo->light;
    light->setPosition(Vec2(center.x, py));
    light->runAction(RepeatForever::create(RotateBy::create(10.f, 360)));
    light->setTouchEnabled(true);
    light->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        if(type == Widget::TouchEventType::ENDED) {
            g_Game->enterChapterScene(chapterId);
        }
    });
    page->addChild(light);
    
    addPage(page);
}

void ChapterPageView::reloadChapterData(int chapterId) {
    auto page = getItem(chapterId-1);
    auto chapterData  = g_User->getChapterRecord(chapterId);
    auto highestScore = chapterData ? chapterData->HighestScore : 0;
    auto score_str = StringUtils::format(g_GetTextInfo(2).c_str(), highestScore);
    score_str = StringUtils::format("%s %s", g_GetTextInfo(10+chapterId).c_str(), score_str.c_str());
    auto scoreLab = Label::createWithTTF(score_str.c_str(), FontMonitor::GAMEFONT, 14);
    scoreLab->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    scoreLab->setAlignment(cocos2d::TextHAlignment::RIGHT);
    scoreLab->setPosition(SCREEN_WIDTH-10, SCREEN_HEIGHT-10);
    scoreLab->setTag(1);
    auto lab = page->getChildByTag(1);
    if(lab) lab->removeFromParent();
    page->addChild(scoreLab, 2);
}

void ChapterPageView::reload() {
    int chapter = g_User->getCurMaxChapter();
    for (int i=(int)_items.size()+1; i<=chapter; i++) {
        addChapter(i);
    }
    for (int i=1; i<=chapter; i++) {
        reloadChapterData(i);
    }
}

void ChapterPageView::setChapter(int chapterId) {
    if(chapterId <= 0 && chapterId > _items.size())
        return;
    setCurrentPageIndex(chapterId-1);
}

void ChapterPageView::cleanup() {
    _eventDispatcher->removeCustomEventListeners(CustomEventCode::UnlockNewChapter);
    PageView::cleanup();
}
