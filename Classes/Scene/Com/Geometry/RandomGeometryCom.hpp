//
//  RandomGeometryCom.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/19.
//
//

#ifndef RandomGeometryCom_hpp
#define RandomGeometryCom_hpp

#include <CCBase.h>
#include "Singleton.hpp"

enum GeometryType {
    None = 0,
    Triangle = 1,
    Rectangle = 2,
    Parallelogram = 3,
    Diamond = 4,
    Trapezoidal = 5,
    Pentacle = 6,
    Circle = 7,
    Ellipse = 8
};

enum PointType {
    Left = 0,
    Top = 1,
    Right = 2,
    Bottom = 3,
};

class RandomGeometryCom final : public Singleton<RandomGeometryCom> {
public:
    bool init() override;
    
    static Color3B randomColor3B();
    Color4F randomColor4F();
    static Vec2 randomPointOutScreen();
    Node* randomGeometry(GeometryType type=GeometryType::None);
    static void randomAction(Node* node);
    
    
    void generateTriangle(DrawNode* node);     //三角形
    void generateTrapezoidal(DrawNode* node);  //梯形
    void generatePentacle(DrawNode* node);     //五角星
    void getPentacleVec(DrawNode* node);
private:
    Vec2 _arrayPentacle[10] = {
        Vec2(13.0901,7.7548),
        Vec2(11.9097,4.1221),
        Vec2(14.9999,6.3672),
        Vec2(18.09,4.1221),
        Vec2(16.9097,7.7548),
        Vec2(20,10),
        Vec2(16.1802,10),
        Vec2(15,13.6326),
        Vec2(13.8196,10),
        Vec2(10,10)
    };
    Color3B _ArrayRandomColor[80];
    std::vector<Color3B> _vecRandomColor;
    
};

#endif /* RandomGeometryCom_hpp */
