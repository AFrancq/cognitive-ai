/*
Audio class header file

The Audio class represents an audio input device that captures sound
and streams it to the Brain for processing.
*/

#ifndef AUDIO_H
#define AUDIO_H

#include <RtAudio.h>
#include <memory>
#include <string>
#include "component.h"

class Audio : public Component {
    public:
        // Constructor with device ID (uses default device if not specified)
        Audio(unsigned int deviceId = 0);
        ~Audio() override;

        // Component interface implementation
        void info() const override;
        bool initialize() override;
        void shutdown() override;

        // Start capturing audio and streaming to brain
        bool startStream();

        // Stop the audio stream
        void stopStream();

        // Check if currently streaming
        bool isStreaming() const { return streaming; }

        // Get available input devices
        static std::vector<RtAudio::DeviceInfo> getAvailableInputDevices();

        // Get the device info for this ear
        RtAudio::DeviceInfo getDeviceInfo() const { return deviceInfo; }

        // Set audio parameters
        void setSampleRate(unsigned int rate) { sampleRate = rate; }
        void setBufferFrames(unsigned int frames) { bufferFrames = frames; }
        void setNumChannels(unsigned int channels) { numChannels = channels; }

    private:
        // RtAudio instance for this ear
        std::unique_ptr<RtAudio> audio;

        // Device information
        RtAudio::DeviceInfo deviceInfo;
        RtAudio::StreamParameters streamParams;
        RtAudio::StreamOptions streamOptions;

        unsigned int deviceId;
        std::string deviceName;

        // Stream parameters
        unsigned int sampleRate = 44100;
        unsigned int bufferFrames = 512;
        unsigned int numChannels = 1;

        bool streaming = false;

        // Static callback for RtAudio - forwards to instance method
        static int audioCallback(void* outputBuffer, void* inputBuffer,
                                 unsigned int nFrames, double streamTime,
                                 RtAudioStreamStatus status, void* userData);

        // Instance method to handle audio data
        int handleAudioInput(void* inputBuffer, unsigned int nFrames, 
                             double streamTime, RtAudioStreamStatus status);
};

#endif // EAR_H