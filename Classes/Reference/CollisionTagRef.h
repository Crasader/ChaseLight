//
//  CollisionTagRef.h
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#ifndef CollisionTagRef_h
#define CollisionTagRef_h

//碰撞标记
namespace CollisionTag {
    static const int MainStar       = 1;    // 主星
    static const int RoundStar      = 3;    // 圆星
    static const int SquareStar     = 5;    // 四角星
    static const int CosmicDust     = 7;    // 宇宙尘埃物质
    static const int PlanetStar     = 9;    // 行星
    static const int StellarStar    = 11;   // 恒星
    static const int DipperStar     = 13;   // 北斗七星
    static const int MeteorStar     = 15;   // 流星
}

//碰撞掩码
namespace CollisionBit {
    static const int MainStar       = 0x0001;    // 主星
    static const int RoundStar      = 0x0011;    // 圆星
    static const int SquareStar     = 0x0021;    // 四角星
    static const int CosmicDust     = 0x0031;    // 宇宙尘埃物质
    static const int PlanetStar     = 0x0041;    // 行星
    static const int StellarStar    = 0x0051;    // 恒星
    static const int DipperStar     = 0x0061;    // 北斗七星
    static const int MeteorStar     = 0x0071;    // 流星
}

// 星体质量
namespace StarMass {
    static const float MainStar       = 1.f;   // 主星
    static const float RoundStar      = 1.f;   // 圆星
    static const float SquareStar     = 1.f;   // 四角星
    static const float CosmicDust     = .1f;   // 宇宙尘埃物质
    static const float PlanetStar     = 5.f;   // 行星
    static const float StellarStar    = 8.f;   // 恒星
    static const float DipperStar     = 2.f;   // 北斗七星
    static const float MeteorStar     = .5f;   // 流星
}

#endif /* CollisionTagRef_h */
