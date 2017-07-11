//
//  VerticalTextNode.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#ifndef VerticalTextNode_hpp
#define VerticalTextNode_hpp

#include "CCBase.h"

enum class VerticalTextDirection {
    LEFT_TO_RIGHT,
    RIGHT_TO_LEFT
};

class VerticalTextNode : public Node {
public:
    CREATE_FUNC(VerticalTextNode);
    bool init() override;
    
    void setText(std::string text);
    inline void setFontSize(int fontsize) {
        _fontsize = fontsize;
    }
    inline void setFontColor(const Color3B& color) {
        _fontcolor = color;
    }
    inline void setLineSpace(float linespace) {
        _linespace = linespace;
    }
    inline void setDirection(VerticalTextDirection direction) {
        _direction = direction;
    }
    void randomText();
    void fade();
    inline float getDuration() {
        return _duration;
    }
    
private:
    float _duration = .0f;
    VerticalTextDirection _direction = VerticalTextDirection::LEFT_TO_RIGHT;
    std::vector<Label*> _vecLabs;
    float _linespace = 0.f;
    int _fontsize = 16;
    Color3B _fontcolor = Color3B::WHITE;
};

#endif /* VerticalTextNode_hpp */
