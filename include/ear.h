#ifndef EAR_H
#define EAR_H

#include <RtAudio.h>
#include "bodypart.h"

class Ear : public Bodypart {
    public:
        Ear(RtAudio* audio, RtAudio::DeviceInfo deviceInfo);
        ~Ear();
    
    private:
        RtAudio* audio;
        RtAudio::DeviceInfo deviceInfo;
        RtAudio::StreamOptions streamOptions;
        RtAudio::StreamParameters streamParams;

        unsigned int deviceId;
        std::string deviceName;
};

#endif // EAR_H