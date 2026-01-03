#ifndef EAR_H
#define EAR_H

#include <RtAudio.h>

class Ear {
    public:
        Ear(RtAudio* audio);
        ~Ear();
    
    private:
        RtAudio* audio;
        RtAudio::DeviceInfo* deviceInfo;
        RtAudio::StreamOptions* streamOptions;
        RtAudio::StreamParameters* streamParams;
        
    
        
};

#endif // EAR_H