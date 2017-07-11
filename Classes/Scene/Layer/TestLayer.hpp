//
//  TestLayer.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#ifndef TestLayer_hpp
#define TestLayer_hpp

#include "CCBase.h"

class TestLayer : public Layer {
public:
    CREATE_FUNC(TestLayer);
    bool init() override;
    
};

#endif /* TestLayer_hpp */
