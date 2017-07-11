//
//  UserDataService.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/24.
//
//

#include "UserDataService.hpp"
using Utility = Console::Utility;

static UserDefault* USER = UserDefault::getInstance();

bool UserDataService::init() {
    _mapChapterUserData.clear();
    _curMaxChapter = 1;
    _curPlayChapter = 1;
    
    return true;
}

void UserDataService::start() {
    _curMaxChapter = USER->getIntegerForKey(UserDataKey::CurrentMaxChapater, 1);
    _curPlayChapter = USER->getIntegerForKey(UserDataKey::CurrentPlayChapater, 1);
    std::string chapterRecords = USER->getStringForKey(UserDataKey::EveryChapterRecord, "");
    loadChapterRecords(chapterRecords);
}

void UserDataService::loadChapterRecords(std::string records) {
    if(records.empty()) {
        return;
    }
    
    std::vector<std::string> vecChapters;
    Utility::split(records, ';', vecChapters);
    if(vecChapters.empty()) {
        return;
    }
    
    for(auto chapter : vecChapters) {
        std::vector<std::string> vecRecord;
        Utility::split(chapter, ',', vecRecord);
        if(vecRecord.size() != 4) {
            return;
        }
        auto data = new ChapterUserData();
        data->ChapterId      = atoi(vecRecord[0].c_str());
        data->HighestScore   = atoi(vecRecord[1].c_str());
        data->UseTime        = atof(vecRecord[2].c_str());
        data->RemainDistance = atof(vecRecord[3].c_str());
        _mapChapterUserData.insert(std::make_pair(data->ChapterId, data));
    }
}

int UserDataService::getCurMaxChapter() {
    return _curMaxChapter;
}

void UserDataService::setCurMaxChapter(int chapterId) {
    if(!VALID_CHAPTERID(chapterId)) {
        return;
    }
    _curMaxChapter = chapterId;
    USER->setIntegerForKey(UserDataKey::CurrentMaxChapater, _curMaxChapter);
}

int UserDataService::getCurPlayChapter() {
    return _curPlayChapter;
}

void UserDataService::setCurPlayChapter(int chapterId) {
    if(!VALID_CHAPTERID(chapterId)) {
        return;
    }
    _curPlayChapter = chapterId;
    USER->setIntegerForKey(UserDataKey::CurrentPlayChapater, _curPlayChapter);
}

ChapterUserData* UserDataService::getChapterRecord(int chapterId) {
    auto find = _mapChapterUserData.find(chapterId);
    if(find != _mapChapterUserData.end()) {
        return find->second;
    }
    
    return nullptr;
}

void UserDataService::setChapterRecord(int chapterId, int score, float time, float distance) {
    if(!VALID_CHAPTERID(chapterId)) {
        return;
    }
    
    if(_mapChapterUserData.find(chapterId) == _mapChapterUserData.end()) {
        ChapterUserData* data = new ChapterUserData();
        data->ChapterId = chapterId;
        data->HighestScore = score;
        data->UseTime = time;
        data->RemainDistance = distance;
        _mapChapterUserData.insert(std::make_pair(chapterId, data));
    } else {
        auto data = _mapChapterUserData.at(chapterId);
        data->ChapterId = chapterId;
        data->HighestScore = score;
        data->UseTime = time;
        data->RemainDistance = distance;
        _mapChapterUserData.insert(std::make_pair(chapterId, data));
    }
    
    writeChapterRecords();
}

void UserDataService::writeChapterRecords() {
    if(_mapChapterUserData.empty()) {
        return;
    }
    
    auto text = std::string("");
    for(auto it : _mapChapterUserData) {
        auto data = it.second;
        text += StringUtils::format("%d,%d,%.2f,%.0f;",
                                    data->ChapterId,
                                    data->HighestScore,
                                    data->UseTime,
                                    data->RemainDistance);
    }
    
    USER->setStringForKey(UserDataKey::EveryChapterRecord, text);
}

