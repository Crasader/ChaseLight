//
//  ServicePack.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/19.
//
//

#include "ServicePack.hpp"

ServicePack::~ServicePack() {
    _serviceConfig->destroy();
}

bool ServicePack::init() {
    _serviceConfig = ConfigService::getInstance();
    
    return true;
}

void ServicePack::start() {
    _serviceConfig->start();
}

const ConfigInfo* ServicePack::getConfigInfo() {
    return _serviceConfig->getConfigInfo();
}

const ChapterInfo* ServicePack::getChapterInfo(int chapterId) {
    return _serviceConfig->getChapterInfo(chapterId);
}

unsigned int ServicePack::getChapterCapacity() {
    return _serviceConfig->getChapterCapacity();
}

std::string ServicePack::getTextInfo(int textId) {
    return _serviceConfig->getTextInfo(textId);
}

std::map<std::string, TextureInfo*> ServicePack::getTextures() {
    return _serviceConfig->getTextures();
}
