//
//  ConfigService.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#ifndef ConfigService_hpp
#define ConfigService_hpp

#include "Singleton.hpp"
#include "CCBase.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "StructRef.h"


USING_NS_CC;
using namespace std;
using namespace rapidjson;

class ConfigService : public Singleton<ConfigService> {
public:
    bool init() override;
    void start();

private:
    /*以字符串格式读取配置*/
    bool readJsonFromString(const char* data, rapidjson::Document &document);
    
    /*载入文件以读取配置*/
    bool readJsonFromFile(const char* filename, rapidjson::Document &document);

    
/*基本配置*/
public:
    inline const ConfigInfo* getConfigInfo() {
        return _configInstance;
    };
    
private:
    ConfigInfo* _configInstance;
    bool loadConfigInfo();

    
/*文本配置*/
public:
    std::string getTextInfo(int textId);
    
private:
    bool loadTextInfo();
    std::map<int, std::string> _mapTextInfo;
    
    
/*地图配置*/
public:
    inline const ChapterInfo* getChapterInfo(int chapterId) {
        auto size = _vecChapterInfo.size();
        if(size == 0) {
            return nullptr;
        }
        for(auto chapter : _vecChapterInfo) {
            if(chapter->chapterId == chapterId) {
                return chapter;
            }
        }
        return nullptr;
    }
    inline unsigned int getChapterCapacity() {
        return (unsigned int)_vecChapterInfo.size();
    }
    
private:
    std::vector<const ChapterInfo*> _vecChapterInfo;
    bool loadChapterInfo();
    

/*纹理配置*/
public:
    inline const std::map<std::string, TextureInfo*> getTextures() {
        return _mapTextures;
    }
    
private:
    std::map<std::string, TextureInfo*> _mapTextures;
    bool loadTextureInfo();
    
    
};


#endif /* ConfigService_hpp */
