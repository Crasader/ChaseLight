//
//  AudioMonitor.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#include "AudioMonitor.hpp"

AudioMonitor::~AudioMonitor() {
    end();
}

bool AudioMonitor::init() {
    
    return true;
}

void AudioMonitor::monitor() {
    
}

void AudioMonitor::switchState(bool onoff) {
    AudioEngine::setEnabled(onoff);
    updateState();
}

void AudioMonitor::updateState() {
    if(AudioEngine::isEnabled()) {
        playMelody();
    }
}

void AudioMonitor::preload(const AudioInfo& audioInfo) {
    auto audio = audioInfo.path;
    AudioEngine::preload(audio, [audio] (bool success) {
        if(success)
            CCLOG("audio %s is preloaded", audio.c_str());
        else
            CCLOG("audio %s is not preloaded", audio.c_str());
    });
}

void AudioMonitor::playMelody() {
    
}

void AudioMonitor::stopMelody() {
    
}

void AudioMonitor::pauseMolody() {
    
}

void AudioMonitor::resumeMelody() {
    
}

void AudioMonitor::uncacheMelody() {
//    AudioEngine::uncache(filePath);
}

void AudioMonitor::playSound() {
//    AudioEngine::play2d(filePath, bool loop = false, float volume = 1.0f, const AudioProfile *profile = nullptr);
}

void AudioMonitor::stopSound() {
//    AudioEngine::stop(audioID);
}

void AudioMonitor::pauseSound() {
//    AudioEngine::pause(audioID);
}

void AudioMonitor::resumeSound() {
//    AudioEngine::resume(audioID);
}

void AudioMonitor::uncacheSound() {
//    AudioEngine::uncache(filePath);
}

void AudioMonitor::stopAll() {
    AudioEngine::stopAll();
}

void AudioMonitor::pauseAll() {
    AudioEngine::pauseAll();
}

void AudioMonitor::resumeAll() {
    AudioEngine::resumeAll();
}

void AudioMonitor::uncacheAll() {
    AudioEngine::uncacheAll();
}

void AudioMonitor::end() {
    AudioEngine::end();
}
