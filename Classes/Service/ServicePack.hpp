//
//  ServicePack.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/19.
//
//

#ifndef ServicePack_hpp
#define ServicePack_hpp

#include "ConfigService.hpp"
#include "StructRef.h"
#include "Singleton.hpp"

class ConfigService;

class ServicePack : public Singleton<ServicePack> {
public:
    virtual bool init() override;
    void start();
    
    const ConfigInfo* getConfigInfo();
    const ChapterInfo* getChapterInfo(int chapterId);
    unsigned int getChapterCapacity();
    std::string getTextInfo(int textId);
    std::map<std::string, TextureInfo*> getTextures();
    
public:
    ~ServicePack() override;
    
private:
    ConfigService* _serviceConfig = nullptr;
};


#endif /* ServicePack_hpp */
