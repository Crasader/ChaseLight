//
//  DATA_VERSION.h
//  4399suitang
//
//  Created by 06 4399 on 12-7-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _DATA_VERSION_h
#define _DATA_VERSION_h

#include <string>

#pragma mark - 
#pragma DATA_VERSION
struct DATA_VERSION{
    DATA_VERSION(int main_ver = 0, int sub_ver = 0, int compile_ver = 0){
        clear();
        set(main_ver, sub_ver, compile_ver);
    }
    
    DATA_VERSION(const char* ver_str){
        clear();
        set(ver_str);
    }
    
    void clear(){
        for (int i=0; i!=3; ++i)
            m_value[i] = 0;
        m_verString = "0.0.0";
    }
    
    void set(int main_ver = 0, int sub_ver = 0, int compile_ver = 0){
        m_value[0] = main_ver;
        m_value[1] = sub_ver;
        m_value[2] = compile_ver;
        char c_ver_str[128];
        snprintf(c_ver_str, 128, "%d.%d.%d",m_value[0],m_value[1],m_value[2]);
        m_verString = c_ver_str;
    }
    
    void set(const char* ver_str){
        if (NULL==ver_str) {
            return;
        }
        std::string ver_string(ver_str);
        size_t last_end = 0;
        for (int i=0; i!=3; ++i) {
            size_t end = ver_string.find('.', last_end);
            std::string sub_str = ver_string.substr(last_end, end==std::string::npos?end:(end-last_end));
            m_value[i] = atoi(sub_str.c_str());
            last_end = end+1;
        }
        char c_ver_str[128];
        snprintf(c_ver_str, 128, "%d.%d.%d",m_value[0],m_value[1],m_value[2]);
        m_verString = c_ver_str;
    }
    
    const char* strValue()const{
        return m_verString.c_str();
    }
    
    bool operator==(const DATA_VERSION &other)const{
        for (int i=0; i!=3; ++i)
            if (m_value[i] != other.m_value[i])
                return false;
        return true;
    }
    
    bool operator==(const std::string &other)const{
        return (m_verString == other);
    }
    
    bool operator==(const char* other)const{
        return (m_verString == other);
    }
    
    bool operator!=(const DATA_VERSION &other)const{
        return !(*this == other);
    }
    
    bool operator!=(const std::string &other)const{
        return !(*this == other);
    }
    
    bool operator!=(const char* other)const{
        return !(*this == other);
    }
    
    bool operator<(const DATA_VERSION &other) const{
        for (int i=0; i!=3; ++i) {
            if (m_value[i] == other.m_value[i])
                continue;
            else if (m_value[i]<other.m_value[i])
                return true;
            else
                return false;
        }
        return false;
    }
    
    bool operator<(const char* other) const{
        DATA_VERSION other_ver;
        other_ver.set(other);
        return (*this) < other_ver;
    }
    
    bool operator>(const DATA_VERSION &other) const{
        return other < (*this);
    }
    
    bool operator>(const char* other) const{
        DATA_VERSION other_ver;
        other_ver.set(other);
        return other_ver < (*this);
    }
    
    bool operator<=(const DATA_VERSION &other) const{
        return !(other < (*this));
    }
    
    bool operator<=(const char* other) const{
        DATA_VERSION other_ver;
        other_ver.set(other);
        return (*this) <= other_ver;
    }
    
    bool operator>=(const DATA_VERSION &other) const{
        return !((*this) < other);
    }
    
    bool operator>=(const char* other) const{
        DATA_VERSION other_ver;
        other_ver.set(other);
        return (*this) >= other_ver;
    }
    
    int m_value[3];
    std::string m_verString;
};


#endif
