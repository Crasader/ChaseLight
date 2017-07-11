//
//  YJMultiTouchHelper.mm
//  4399zmxyx
//
//  Created by mimicry on 12/8/12.
//  Copyright (c) 2012 4399 ios. All rights reserved.
//

#include "EAGLView.h"
#include "YJMultiTouchHelper.h"

void yjSetMultiTouchEnabled(bool enabled) {
    [[EAGLView sharedEGLView] setMultipleTouchEnabled:!!enabled];
}

bool yjIsMultiTouchEnabled() {
    return [[EAGLView sharedEGLView] isMultipleTouchEnabled];
}