/*
This is the brain class which serves as a foundational component
for an AI system that models cognitive functions. It is designed to
serve as the internal endpoint for sensory inputs and processing.

The brain contains an internal audio device for receiving audio streams
from sensory inputs like the ear.
*/

#ifndef BRAIN_H
#define BRAIN_H

#include <RtAudio.h>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>
#include <string>

class Brain {
    public:
        Brain();
        ~Brain();

        // Initialize the brain and its internal audio processing
        bool initialize();

        // Shutdown the brain
        void shutdown();

        // Display information about the brain
        void info() const;

        // Check if the brain is active
        bool isActive() const { return active; }

        // Receive audio data from sensory inputs (like ears)
        // This is the callback target for audio streams
        void receiveAudioData(const float* inputBuffer, unsigned int nFrames, 
                              unsigned int nChannels, double streamTime);

        // Get the sample rate used for internal processing
        unsigned int getSampleRate() const { return sampleRate; }

        // Get the buffer size used for internal processing
        unsigned int getBufferFrames() const { return bufferFrames; }

        // Register a callback for when audio data is processed
        using AudioProcessCallback = std::function<void(const std::vector<float>&)>;
        void setAudioProcessCallback(AudioProcessCallback callback);

    private:
        bool active = false;

        // Audio processing parameters
        unsigned int sampleRate = 44100;
        unsigned int bufferFrames = 512;
        unsigned int numChannels = 1;

        // Audio buffer for storing incoming data
        std::queue<std::vector<float>> audioQueue;
        std::mutex audioMutex;

        // Callback for processed audio
        AudioProcessCallback audioProcessCallback;

        // Process queued audio data
        void processAudioQueue();
};

#endif // BRAIN_H