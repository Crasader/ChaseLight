//
//  ChapterPageView.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/24.
//
//

#ifndef ChapterPageView_hpp
#define ChapterPageView_hpp

#include "CCBase.h"

class ChapterPageView final : public PageView {
public:
    CREATE_FUNC(ChapterPageView);
    bool init() override;
    void reload();
    void reloadChapterData(int chapterId);
    void addChapter(int chapterId);
    void setChapter(int chapterId);
    void cleanup() override;
};

#endif /* ChapterPageView_hpp */
