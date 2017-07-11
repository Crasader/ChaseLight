//
//  ConfigService.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#include "ConfigService.hpp"
#include "ClockTimer.hpp"

bool ConfigService::init() {
    _configInstance = nullptr;
    _vecChapterInfo.clear();
    _mapTextInfo.clear();
    _mapTextures.clear();
    
    return true;
}

bool ConfigService::readJsonFromString(const char *data, Document &document) {
    document.Parse<0>(data);
    if(document.HasParseError()){
        return false;
    }
    return true;
}

bool ConfigService::readJsonFromFile(const char *filename, Document &document) {
    auto futils = FileUtils::getInstance();
    if(futils->getFileExtension(filename) != ".json") {
        return false;
    }
    
    if(!futils->isFileExist(filename)){
        return false;
    }
    
    string fullpath = futils->fullPathForFilename(filename);
    string jsonstr = futils->getStringFromFile(fullpath);
    if(!readJsonFromString(jsonstr.c_str(), document)) {
        CCLOG("%s parse error", filename);
        return false;
    }
    
    return true;
}

void ConfigService::start() {
    g_ClockTimer->start(ClockRecord::ServiceDidLauch);
    
    loadConfigInfo();
    loadTextInfo();
    loadChapterInfo();
    loadTextureInfo();
    
    g_ClockTimer->end(ClockRecord::ServiceDidLauch, true);
}

bool ConfigService::loadConfigInfo() {
    Document doc;
    if(readJsonFromFile("config.json", doc)) {
        auto& data = DICTOOL->getSubDictionary_json(doc, "data");
        if(!data.IsObject()) return false;
        if(data.HasMember("debugdraw") &&
           data.HasMember("gravity_y") &&
           data.HasMember("updaterate") &&
           data.HasMember("showFPS")) {
            _configInstance = new ConfigInfo;
            _configInstance->showFPS   = DICTOOL->getBooleanValue_json(data, "showFPS");
            _configInstance->debugdraw = DICTOOL->getBooleanValue_json(data, "debugdraw");
            _configInstance->gravity_y = DICTOOL->getFloatValue_json(data, "gravity_y");
            _configInstance->updaterate= DICTOOL->getIntValue_json(data, "updaterate");
            return true;
        }
    }
    return false;
}

bool ConfigService::loadTextInfo() {
    Document doc;
    if(readJsonFromFile("text.json", doc)) {
        _mapTextInfo.clear();
        
        auto& data = DICTOOL->getSubDictionary_json(doc, "data");
        if(!data.IsArray()) return false;
        auto arr = data.GetArray();
        for (rapidjson::SizeType i = 0; i < arr.Size(); i++) {
            auto dict = arr[i].GetObject();
            if(dict.HasMember("id") && dict.HasMember("text")) {
                auto id = dict["id"].GetInt();
                auto text = dict["text"].GetString();
                _mapTextInfo.insert(std::make_pair(id, text));
            }
        }
        return true;
    }
    
    return false;
}

std::string ConfigService::getTextInfo(int textId) {
    if(_mapTextInfo.find(textId) != _mapTextInfo.end()) {
        return _mapTextInfo.at(textId);
    }
    
    CCLOG("textId : %d not found.", textId);
    return StringUtils::format("[%d]", textId);
}

bool ConfigService::loadChapterInfo() {
    Document doc;
    if(readJsonFromFile("chapter.json", doc)) {
        auto& data = DICTOOL->getSubDictionary_json(doc, "data");
        if(!data.IsArray()) return false;
        
        _vecChapterInfo.clear();
        auto size = data.Size();
        ChapterInfo* info = nullptr;
        for(int i=0; i<size; i++) {
            if(data[i].HasMember("chapter") &&
               data[i].HasMember("text") &&
               data[i].HasMember("light") &&
               data[i].HasMember("coord") &&
               data[i].HasMember("magnitude") &&
               data[i].HasMember("condition_text") &&
               data[i].HasMember("condition"))
            {
                info = new ChapterInfo;
                info->chapterId = DICTOOL->getIntValue_json(data[i], "chapter");
                info->textId = DICTOOL->getIntValue_json(data[i], "text");
                info->light = DICTOOL->getFloatValue_json(data[i], "light", 0);
                auto coord = data[i]["coord"].GetArray();
                info->coord = Vec2(coord[0].GetFloat(), coord[1].GetFloat());
                info->magnitude = DICTOOL->getFloatValue_json(data[i], "magnitude");
                info->condition_text = DICTOOL->getIntValue_json(data[i], "condition_text");
                auto condition = data[i]["condition"].GetArray();
                info->condition_time = condition[0].GetInt();
                info->condition_score = condition[1].GetInt();
                info->condition_energy = condition[2].GetInt();
                
                _vecChapterInfo.push_back(info);
            }
        }
        
        return true;
    }
    return true;
}

bool ConfigService::loadTextureInfo() {
    Document doc;
    if(readJsonFromFile("texture.json", doc)) {
        auto& data = DICTOOL->getSubDictionary_json(doc, "data");
        if(!data.IsArray()) return false;
        
        _mapTextures.clear();
        auto size = data.Size();
        TextureInfo* info = nullptr;
        for(int i=0; i<size; i++) {
            if(data[i].HasMember("path") &&
               data[i].HasMember("key"))
            {
                info = new TextureInfo;
                info->path = DICTOOL->getStringValue_json(data[i], "path");
                info->key = DICTOOL->getStringValue_json(data[i], "key");
                
                _mapTextures.insert(std::make_pair(info->key, info));
            }
        }
        
        return true;
    }
    
    return false;
}
