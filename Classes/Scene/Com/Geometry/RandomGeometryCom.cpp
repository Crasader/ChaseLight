//
//  RandomGeometryCom.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/19.
//
//

#include "RandomGeometryCom.hpp"
#define RANDOM_COLOR_SIZE 80
#define MIN_RADIUS_F (20.f)
#define MIN_RADIUS_I (20)

bool RandomGeometryCom::init() {
    Color3B arrayRandomColor[RANDOM_COLOR_SIZE] = {
        Color3B::LIGHTPINK,
        Color3B::PINK,
        Color3B::CRIMSON,
        Color3B::LAVENDERBLUSH,
        Color3B::HOTPINK,
        Color3B::DEEPPINK,
        Color3B::ORCHID,
        Color3B::VIOLET,
        Color3B::MAGENTA,
        Color3B::FUCHSIA,
        Color3B::MEDIUMORCHID,
        Color3B::DARKVOILET,
        Color3B::DARKORCHID,
        Color3B::BLUEVIOLET,
        Color3B::MEDIUMPURPLE,
        Color3B::MEDIUMSLATEBLUE,
        Color3B::SLATEBLUE,
        Color3B::DARKSLATEBLUE,
        Color3B::LAVENDER,
        Color3B::GHOSTWHITE,
        Color3B::ROYALBLUE,
        Color3B::CORNFLOWERBLUE,
        Color3B::LIGHTSTEELBLUE,
        Color3B::LIGHTSLATEGRAY,
        Color3B::SLATEGRAY,
        Color3B::DODERBLUE,
        Color3B::ALICEBLUE,
        Color3B::STEELBLUE,
        Color3B::LIGHTSKYBLUE,
        Color3B::LIGHTBLUE,
        Color3B::POWDERBLUE,
        Color3B::CADETBLUE,
        Color3B::AZURE,
        Color3B::LIGHTCYAN,
        Color3B::AQUA,
        Color3B::DARKTURQUOISE,
        Color3B::AUQAMARIN,
        Color3B::MEDIUMSPRINGGREEN,
        Color3B::MINTCREAM,
        Color3B::SPRINGGREEN,
        Color3B::HONEYDEW,
        Color3B::PALEGREEN,
        Color3B::DARKSEAGREEN,
        Color3B::FORESTGREEN,
        Color3B::CHARTREUSE,
        Color3B::GREENYELLOW,
        Color3B::BEIGE,
        Color3B::LIGHTGOLDENRODYELLOW,
        Color3B::IVORY,
        Color3B::LIGHTYELLOW,
        Color3B::LEMONCHIFFON,
        Color3B::PALEGODENROD,
        Color3B::KHAKI,
        Color3B::GOLD,
        Color3B::CORNISLK,
        Color3B::FLORALWHITE,
        Color3B::OLDLACE,
        Color3B::WHEAT,
        Color3B::MOCCASIN,
        Color3B::ORANGE,
        Color3B::PAPAYAWHIP,
        Color3B::BLANCHEDALMOND,
        Color3B::NAVAJOWHITE,
        Color3B::ANTIQUEWHITE,
        Color3B::BISQUE,
        Color3B::DARKORANGE,
        Color3B::LINEN,
        Color3B::PEACHPUFF,
        Color3B::SANDYBROWN,
        Color3B::SEASHELL,
        Color3B::LIGHTSALMON,
        Color3B::CORAL,
        Color3B::ORANGERED,
        Color3B::TOMATO,
        Color3B::SALMON,
        Color3B::SNOW,
        Color3B::LIGHTCORAL,
        Color3B::INDIANRED,
        Color3B::WHITESMOKE,
        Color3B::GAINSBORO
    };

    
    _vecRandomColor.clear();
    for (int i=0; i<RANDOM_COLOR_SIZE; i++) {
        _vecRandomColor.push_back(arrayRandomColor[i]);
    }
    
    return true;
}

Color4F RandomGeometryCom::randomColor4F() {
    auto r = RandomHelper::random_int(0, RANDOM_COLOR_SIZE-1);
    float a = RandomHelper::random_real(0.2f, 1.0f);
    Color3B c = _vecRandomColor[r];
    return Color4F(c, a);
}

Color3B RandomGeometryCom::randomColor3B() {
    auto r = RandomHelper::random_int(0, 255);
    auto g = RandomHelper::random_int(0, 255);
    auto b = RandomHelper::random_int(0, 255);
    return Color3B(r, g, b);
}

Vec2 RandomGeometryCom::randomPointOutScreen() {
    Vec2 v = Vec2::ZERO;
    
    auto size = SCREEN_SIZE;
    auto margin = 200.f;
    
    int r = RandomHelper::random_int(4, 4444) % 4;
    PointType type = (PointType)r;
    switch (type) {
        case PointType::Left :
        {
            auto x = RandomHelper::random_real(-margin, 0.f);
            auto y = RandomHelper::random_real(-margin, 2*margin+size.height);
            v = Vec2(x,y);
        }
            break;
 
        case PointType::Top :
        {
            auto x = RandomHelper::random_real(-margin, size.width+margin);
            auto y = size.height + RandomHelper::random_real(0.f, margin);
            v = Vec2(x,y);
        }
            break;
            
        case PointType::Right :
        {
            auto x = size.width + RandomHelper::random_real(0.f, margin);
            auto y = RandomHelper::random_real(-margin, 2*margin+size.height);
            v = Vec2(x,y);
        }
            break;
            
        case PointType::Bottom :
        {
            auto x = RandomHelper::random_real(-margin, size.width+margin);
            auto y = -RandomHelper::random_real(0.f, margin);
            v = Vec2(x,y);
        }
            break;
    }
    
    CCLOG("PointType : %d, Pos(%.1f, %.1f)", r, v.x, v.y);
    
    return v;
}

Node* RandomGeometryCom::randomGeometry(GeometryType type) {
    if(type == GeometryType::None) {
        type = (GeometryType)(RandomHelper::random_int(0, 100) % 9);
    }

    auto node = DrawNode::create();
    switch (type) {
        case GeometryType::Triangle :
        {
            generateTriangle(node);
        }
            break;
            
        case GeometryType::Rectangle :
        {
            auto w = RandomHelper::random_int(MIN_RADIUS_I, MIN_RADIUS_I*2);
            auto h = RandomHelper::random_int(MIN_RADIUS_I, MIN_RADIUS_I*2);
            node->drawSolidRect(Vec2::ZERO, Vec2(w,h), randomColor4F());
        }
            break;
            
        case GeometryType::Parallelogram :
        {
            auto w = RandomHelper::random_int(MIN_RADIUS_I, MIN_RADIUS_I*2);
            auto h = RandomHelper::random_int(MIN_RADIUS_I, MIN_RADIUS_I*2);
            node->drawSolidRect(Vec2::ZERO, Vec2(w,h), randomColor4F());
            auto skew = RandomHelper::random_real(.2f, .8f);
            node->setSkewX(skew);
        }
            break;
            
        case GeometryType::Diamond :
        {
            auto w = RandomHelper::random_int(MIN_RADIUS_I, MIN_RADIUS_I*2);
            auto h = RandomHelper::random_int(MIN_RADIUS_I, MIN_RADIUS_I*2);
            node->drawSolidRect(Vec2::ZERO, Vec2(w,h), randomColor4F());
            node->setSkewX(45);
        }
            break;
            
        case GeometryType::Trapezoidal :
        {
            generateTrapezoidal(node);
        }
            break;
            
        case GeometryType::Pentacle :
        {
            generatePentacle(node);
        }
            break;
            
        case GeometryType::Circle :
        {
            auto radius = RandomHelper::random_real(MIN_RADIUS_F/2, MIN_RADIUS_F*2);
            node->drawSolidCircle(Vec2::ZERO, radius, 0, radius*2, randomColor4F());
        }
            break;
            
        case GeometryType::Ellipse :
        {
            auto radius = RandomHelper::random_real(MIN_RADIUS_F/2, MIN_RADIUS_F*2);
            node->drawSolidCircle(Vec2::ZERO, radius, 0, radius*2, randomColor4F());
            auto sx = RandomHelper::random_real(.5f, 1.5f);
            auto sy = RandomHelper::random_real(.5f, 1.5f);
            node->setScale(sx, sy);
        }
            break;
            
        case GeometryType::None:
        default:
            break;
    }
    
    randomAction(node);
    
    return node;
}

void RandomGeometryCom::randomAction(Node* node) {
    if(!node) return;
    
    node->setRotation(RandomHelper::random_real(0.f, 180.f));
    Vec2 from = randomPointOutScreen();
    Vec2 to = randomPointOutScreen();
    node->setPosition(from);
    float period = RandomHelper::random_real(5.f, 8.f);
    node->runAction(Sequence::create(MoveTo::create(period, to), RemoveSelf::create(), NULL));
}

void RandomGeometryCom::generateTriangle(DrawNode* node) {
    if(!node) return;
    
    Vec2 v0 = Vec2::ZERO, v1, v2;
    int length = RandomHelper::random_int(MIN_RADIUS_F, 2*MIN_RADIUS_F);
    int height = RandomHelper::random_int(length/2, length);
    v1 = Vec2(length, length);
    v2 = Vec2(height, height);
    
    node->drawTriangle(v0, v1, v2, randomColor4F());
}

void RandomGeometryCom::generateTrapezoidal(DrawNode* node) {
    if(!node) return;
    
    int width = RandomHelper::random_int(MIN_RADIUS_I, 2*MIN_RADIUS_I);
    int height = RandomHelper::random_int(MIN_RADIUS_I, 2*MIN_RADIUS_I);
    int offset = RandomHelper::random_int(MIN_RADIUS_I/2, MIN_RADIUS_I);
    Vec2 v[4];
    Vec2 vb = randomPointOutScreen();
    v[0] = vb;
    v[1] = vb + Vec2(offset, height);
    v[2] = vb + Vec2(offset+width, height);
    v[3] = vb + Vec2(2*offset+width, 0);
    
    node->drawSolidPoly(v, 4, randomColor4F());
}

void RandomGeometryCom::generatePentacle(DrawNode* node) {
    if(!node) return;
    
    auto scale = RandomHelper::random_real(1.f, 6.f);
    Vec2 vb = randomPointOutScreen();
    Vec2 v[10];
    memcpy(v, _arrayPentacle, sizeof(v));
    for(int i=0; i<10; i++) {
        v[i] = vb + v[i] * scale;
    }
    node->drawSolidPoly(v, 10, randomColor4F());
}

void RandomGeometryCom::getPentacleVec(DrawNode* node) {
    if(!node) return;
    
    auto scale = RandomHelper::random_real(1.f, 2.f);
    Vec2 v[10];
    memcpy(v, _arrayPentacle, sizeof(v));
    for(int i=0; i<10; i++) {
        v[i] *= scale;
    }
    node->drawSolidPoly(v, 10, randomColor4F());
}

