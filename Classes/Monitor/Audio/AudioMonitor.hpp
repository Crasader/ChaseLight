//
//  AudioMonitor.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#ifndef AudioMonitor_hpp
#define AudioMonitor_hpp

#include "CCBase.h"
#include "Singleton.hpp"
#include "audio/include/AudioEngine.h"

class AudioMonitor final : public Singleton<AudioMonitor> {
public:
    bool init() override;
    void monitor();

protected:
    ~AudioMonitor() override;
    
private:
    struct AudioInfo {
        int keyId;
        int audioId;
        string key;
        string path;
    };
    std::map<int, AudioInfo> _mapAudioInfo;
    
private:
    void preload(const AudioInfo& audioInfo);
    
public:
    // 开关
    void switchState(bool onoff);
    void updateState();
    
    void playMelody();
    void stopMelody();
    void pauseMolody();
    void resumeMelody();
    void uncacheMelody();
    
    void preloadSound();
    void playSound();
    void stopSound();
    void pauseSound();
    void resumeSound();
    void uncacheSound();
    
    void stopAll();
    void pauseAll();
    void resumeAll();
    void uncacheAll();

    void end();
    
};

#endif /* AudioMonitor_hpp */
