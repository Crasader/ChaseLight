//
//  Singleton.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/19.
//
//

#ifndef Singleton_hpp
#define Singleton_hpp

#define has_member(s) \
template<typename T>\
struct has_member_##s{\
template <typename _T>static auto check(_T)->typename std::decay<decltype(_T::s)>::type;\
static void check(...);\
using type=decltype(check(std::declval<T>()));\
enum{value=!std::is_void<type>::value};\
};

template<class S>
class Singleton {
public:
    static S* getInstance() {
        if (instance == nullptr) {
            instance = new S();
            instance->init();
        }
        return instance;
    };
    static void destroy() {
        CC_SAFE_DELETE(instance);
    }
    virtual bool init() {
        return true;
    };
    
public:
    Singleton(){};
    virtual ~Singleton(){};
    
private:
    static S* instance;
    Singleton(const Singleton & ){};
    Singleton & operator = ( const Singleton & rhs ){};
};

template<class T> T* Singleton<T>::instance = nullptr;

#endif /* Singleton_hpp */
