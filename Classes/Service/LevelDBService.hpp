//
//  LevelDBService.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//  Comment: 现在是单一数据库，后续看情况是否需要扩展

#ifndef DBService_hpp
#define DBService_hpp

#include "Singleton.hpp"
#include <leveldb/db.h>

enum class LevelDBCode: unsigned char {
    None,
    User,
    Item,
};

const std::map<LevelDBCode, const std::string> MapLevelDB = {
    {LevelDBCode::None, "leveldb/temp"},
    {LevelDBCode::User, "leveldb/user"},
    {LevelDBCode::Item, "leveldb/prop"},
};

class LevelDBService : public Singleton<LevelDBService> {
private:
    leveldb::DB* m_pDatabase;
    LevelDBCode m_eDBCode;

public:
    ~LevelDBService() override;
    
public:
    bool init() override;
    void start();
    
    leveldb::Status connect(LevelDBCode code);
    leveldb::Status insert(const std::string key, const std::string value, bool sync=false);
    leveldb::Status remove(const std::string key, bool sync=false);
    leveldb::Status select(const std::string key, std::string& value);
    void disconnect(LevelDBCode code);
    void seek(std::string start="", std::string limit="");
    bool compare(std::string key1, std::string key2);
    void dump();

};

#endif /* LevelDBService_hpp */
