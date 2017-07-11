//
//  FlowableMoonObject.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/25.
//
//

#ifndef FlowableMoonObject_hpp
#define FlowableMoonObject_hpp

#include "CCBase.h"

class FlowableMoonObject : public Node {
public:
    bool init() override;
    CREATE_FUNC(FlowableMoonObject);
    void moving();
};

#endif /* FlowableMoonObject_hpp */
