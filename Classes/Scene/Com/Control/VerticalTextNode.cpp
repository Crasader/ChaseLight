//
//  VerticalTextNode.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#include "VerticalTextNode.hpp"

bool VerticalTextNode::init() {
    if(!Node::init()) {
        return false;
    }
    
    _vecLabs.clear();
    setContentSize(Size::ZERO);
    
    return true;
}

void VerticalTextNode::setText(std::string text) {
    _vecLabs.clear();
    this->removeAllChildren();
    setContentSize(Size::ZERO);
    
    if(text.empty()) {
        return;
    }
    
    std::vector<std::string> splitText;
    Console::Utility::split(text, ' ', splitText);
    
    float all_width = 0.f;
    float max_height = 0.f;
    for (auto seg : splitText) {
        auto labSeg = Label::createWithTTF(seg, FontMonitor::GAMEFONT, _fontsize);
        auto width = labSeg->getLetter(0)->getContentSize().width;
        labSeg->enableWrap(true);
        labSeg->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        labSeg->setMaxLineWidth(width);
        labSeg->setColor(_fontcolor);
        auto px = _direction == VerticalTextDirection::LEFT_TO_RIGHT ? all_width : -all_width;
        labSeg->setPosition(px, 0.f);
        all_width += width+_linespace;
        addChild(labSeg);
        
        max_height = MAX(max_height, labSeg->getContentSize().height);
        _vecLabs.push_back(labSeg);
    }
    
    if(_direction == VerticalTextDirection::RIGHT_TO_LEFT) {
        for(auto item : _vecLabs) {
            item->setPositionX(item->getPositionX()+all_width-_linespace);
        }
    }
    
    this->setContentSize(Size(all_width, max_height));
}

void VerticalTextNode::randomText() {
    setText(g_GetTextInfo(RandomHelper::random_int(100, 150)));
}

void VerticalTextNode::fade() {
    auto fat = 0.f, step = .225f;
    for(auto lab : _vecLabs) {
        auto size = lab->getStringLength();
        for (int i=0; i<size; i++) {
            auto letter = lab->getLetter(i);
            letter->setOpacity(0);
            letter->setOpacityModifyRGB(true);
            auto seq = Sequence::create(DelayTime::create(fat), FadeTo::create(step, 255), NULL);
            letter->runAction(seq);
            fat += step;
        }
    }
    
    _duration = fat;
}
