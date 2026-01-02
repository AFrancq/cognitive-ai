#ifndef EARS_H
#define EARS_H

#include <RtAudio.h>

class Ears {
    public:
        Ears();
        ~Ears();
    
    private:
        RtAudio audio;
        
};

#endif // EARS_H