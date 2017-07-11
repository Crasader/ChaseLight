//
//  LevelDBService.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#include "LevelDBService.hpp"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

bool LevelDBService::init() {
    m_pDatabase = NULL;
    m_eDBCode = LevelDBCode::None;
    
    return true;
}

LevelDBService::~LevelDBService() {
    if(m_pDatabase) {
        disconnect(m_eDBCode);
        m_eDBCode = LevelDBCode::None;
    }
    CC_SAFE_DELETE(m_pDatabase);
    CCLOG("LevelDBService is stopped.");
}

void LevelDBService::start() {
    connect(LevelDBCode::User);
}

leveldb::Status LevelDBService::connect(LevelDBCode code) {
    leveldb::Options options;
    options.create_if_missing = true;
    string fullpath = FileUtils::getInstance()->fullPathForFilename(MapLevelDB.at(code));
    leveldb::Status status = leveldb::DB::Open(options, fullpath, &m_pDatabase);
    if(status.ok()) {
        m_eDBCode = code;
        CCLOG("Database : %s\t connect %s", MapLevelDB.at(code).c_str(), status.ToString().c_str());
    } else {
        CCLOG("!!! [warning] Database : %s\t connect : %s", MapLevelDB.at(code).c_str(), status.ToString().c_str());
    }
    return status;
}


leveldb::Status LevelDBService::insert(const std::string key, const std::string value, bool sync) {
    leveldb::WriteOptions options;
    options.sync = sync;
    leveldb::Status status;
    if(m_pDatabase || connect(m_eDBCode).ok()) {
        status = m_pDatabase->Put(options, key, value);
        CCLOG("Database : %s\t insert $(%s) #(%s)", MapLevelDB.at(m_eDBCode).c_str(), key.c_str(), value.c_str());
    }
    return status;
}

leveldb::Status LevelDBService::remove(const std::string key, bool sync) {
    leveldb::WriteOptions options;
    options.sync = sync;
    leveldb::Status status;
    if(m_pDatabase || connect(m_eDBCode).ok()) {
        status = m_pDatabase->Delete(options, key);
        CCLOG("Database : %s\t delete $(%s)", MapLevelDB.at(m_eDBCode).c_str(), key.c_str());
    }
    return status;
}

leveldb::Status LevelDBService::select(const std::string key, std::string& value) {
    leveldb::ReadOptions options;
    leveldb::Status status;
    if(m_pDatabase || connect(m_eDBCode).ok()) {
        status = m_pDatabase->Get(options, key, &value);
        CCLOG("Database : %s\t seclect $(%s) #(%s)", MapLevelDB.at(m_eDBCode).c_str(), key.c_str(), value.c_str());
    }
    return status;
}

void LevelDBService::disconnect(LevelDBCode code) {
    if(m_eDBCode == code) {
        CC_SAFE_DELETE(m_pDatabase);
        CCLOG("Database : %s\t disconnected", MapLevelDB.at(m_eDBCode).c_str());
    }
}

void LevelDBService::dump() {
    if(m_pDatabase || connect(m_eDBCode).ok()) {
        leveldb::Iterator* it = m_pDatabase->NewIterator(leveldb::ReadOptions());
        CCLOG("Database : %s\t dump", MapLevelDB.at(m_eDBCode).c_str());
        for (it->SeekToFirst(); it->Valid(); it->Next()) {
            CCLOG(" ==> DUMP: $(%s) #(%s)", it->key().ToString().c_str(), it->value().ToString().c_str());
        }
    }
}

void LevelDBService::seek(std::string start, std::string limit) {
    if(m_pDatabase || connect(m_eDBCode).ok()) {
        leveldb::Iterator* it = m_pDatabase->NewIterator(leveldb::ReadOptions());
        
        it->SeekToLast();
        const leveldb::Slice last = it->key();
        if(limit.empty()) {
            limit = last.ToString();
        }
        
        it->SeekToFirst();
        if(!start.empty()) {
            it->Seek(start);
        }
        
        CCLOG("Database : %s\t seek ", MapLevelDB.at(m_eDBCode).c_str());
        
        for( ; it->Valid() && it->key().ToString() < limit; it->Next()) {
            CCLOG(" ==> SEEK: $(%s) #(%s)", it->key().ToString().c_str(), it->value().ToString().c_str());
        }
    }
}

bool LevelDBService::compare(std::string key1, std::string key2) {
    string ret1, ret2;
    select(key1, ret1);
    select(key2, ret2);
    return ret1 == ret2;
}
