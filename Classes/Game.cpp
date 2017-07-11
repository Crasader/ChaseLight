//
//  Game.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/19.
//
//

#include "Game.hpp"
#include "ServicePack.hpp"
#include "AudioMonitor.hpp"
#include "StartScene.hpp"
#include "ClockTimer.hpp"
#include "ChapterScene.hpp"

const char* ProjectName = "RollingGeometry";

static cocos2d::Size designRS = cocos2d::Size(480, 320);
static cocos2d::Size smallRS  = cocos2d::Size(480, 320);
static cocos2d::Size mediumRS = cocos2d::Size(1024, 768);
static cocos2d::Size largeRS  = cocos2d::Size(2048, 1536);

bool Game::init() {
    _onChapter = false;
    _journal = new JournalInfo();
    
    return true;
}

void Game::adaptScreen() {
    auto glview = g_Director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect(ProjectName, cocos2d::Rect(0, 0, designRS.width, designRS.height));
#else
        glview = GLViewImpl::create(ProjectName);
#endif
        g_Director->setOpenGLView(glview);
    }
    
    auto config = g_Service->getConfigInfo();
    g_Director->setDisplayStats(config->showFPS);
    g_Director->setAnimationInterval(1.0f/60);
    glview->setDesignResolutionSize(designRS.width, designRS.height, ResolutionPolicy::FIXED_HEIGHT);
    auto factor = 0.f;
    auto frameSize = glview->getFrameSize();
    if (frameSize.height > mediumRS.height) {
        factor = MIN(largeRS.height/designRS.height, largeRS.width/designRS.width);
    } else if (frameSize.height > smallRS.height) {
        factor = MIN(mediumRS.height/designRS.height, mediumRS.width/designRS.width);
    } else {
        factor = MIN(smallRS.height/designRS.height, smallRS.width/designRS.width);
    }
    g_Director->setContentScaleFactor(factor);
}

void Game::addSearchPaths() {
    std::vector<std::string> paths = {
        "images",
        "config",
        "shader"
    };
    FileUtils::getInstance()->setSearchPaths(paths);
}

void Game::loadImages() {
    auto cache = g_Director->getTextureCache();
    auto textures = g_Service->getTextures();
    for(auto t : textures) {
        cache->addImage(t.second->path);
    }
}

void Game::start() {
    g_ClockTimer->start(ClockRecord::GameDidFinish);
    
    _onChapter = false;
    
    addSearchPaths();
    g_Service->start();
    g_User->start();
    g_Audio->monitor();
    loadImages();
    adaptScreen();
    enterStartScene();
}

void Game::directScene(Scene* scene, SceneDirectType type) {
    do {
        switch (type) {
            case SceneDirectType::Run :
            {
                CC_BREAK_IF(!scene);
                g_Director->runWithScene(scene);
            }
                break;
            case SceneDirectType::Replace :
            {
                CC_BREAK_IF(!scene);
                g_Director->replaceScene(scene);
            }
                break;
            case SceneDirectType::Push :
            {
                CC_BREAK_IF(!scene);
                g_Director->pushScene(scene);
            }
                break;
            case SceneDirectType::Pop :
            {
                g_Director->popScene();
            }
                break;
            case SceneDirectType::PopToRoot :
            {
                g_Director->popToRootScene();
            }
                break;
        }
    } while(0);
}

void Game::enterChapterScene(int chapterId) {
    _onChapter = true;
    g_User->setCurPlayChapter(chapterId);
    auto chapter = ChapterScene::create();
    auto scene = TransitionSlideInB::create(.5f, chapter);
    g_Director->pushScene(scene);
}

void Game::exitChapterScene() {
    _onChapter = false;
    g_Director->popToRootScene();
}

void Game::enterStartScene() {
    auto scene = TransitionFade::create(.2f, StartScene::create());
    g_Director->runWithScene(scene);
}

void Game::end() {
    g_ClockTimer->end(ClockRecord::GameDidFinish, true);
    
    g_Audio->end();
    ClockTimer::destroy();
    ServicePack::destroy();
    
    g_Director->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Game::enterBackground() {
    g_Director->stopAnimation();
    g_Audio->pauseAll();
    if(_onChapter) {
        CCLOG("在游戏场景中进入后台");
    }
}

void Game::enterForeground() {
    g_Director->startAnimation();
    g_Audio->resumeAll();
}


