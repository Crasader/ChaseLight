#include "AppDelegate.h"
#include "Game.hpp"

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate()  {
    Game::getInstance()->end();
}

void AppDelegate::initGLContextAttrs() {
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages() {
    return 0;
}

bool AppDelegate::applicationDidFinishLaunching() {
    register_all_packages();
    Game::getInstance()->start();
    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Game::getInstance()->enterBackground();
}

void AppDelegate::applicationWillEnterForeground() {
    Game::getInstance()->enterForeground();
}
