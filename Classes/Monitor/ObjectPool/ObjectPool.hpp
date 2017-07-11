//
//  ObjectPool.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/23.
//
//

#ifndef ObjectPool_hpp
#define ObjectPool_hpp

#include "CCBase.h"
#include "Singleton.hpp"

template<class T, int T_SIZE>
class ObjectPool {
private:
    void preload() {
        for (int i = 0; i < _capacity; ++i) {
            auto pObj = T::create();
//            pObj->autorelease();
            pObj->retain();
            _objects.push_back(pObj);
        }
    }
    
public:
    ObjectPool() {
        _capacity = T_SIZE;
        preload();
    }
    
    ~ObjectPool() {
        for (auto iter = _objects.begin(); iter != _objects.end(); iter++) {
            (*iter)->release();
        }
        _objects.clear();
    }
    
    //get a object
    T* getObject() {
        if (_objects.empty()) {
            preload();
        }
        auto obj = _objects.back();
        _objects.pop_back();
        return obj;
    }
    
    // free a object
    void freeObject(T *obj) {
        //recycle part of pool
        if (_objects.size() >= (1.5 * _capacity)) {
            for (int i = 0; i < _capacity / 2; ++i) {
                auto obj = _objects.back();
                obj->release();
                _objects.pop_back();
            }
        }
        _objects.push_back(obj);
    }
    
private:
    std::list<T*> _objects;
    int _capacity = 256;
};

#endif /* ObjectPool_hpp */
