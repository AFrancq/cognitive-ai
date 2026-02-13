/*
Ear class implementation

The Ear class manages audio input devices and streams audio data
to the Brain for processing.
*/

#include "ear.h"
#include "brain.h"
#include <iostream>
#include <stdexcept>

Ear::Ear(unsigned int deviceId) 
    : Bodypart(), deviceId(deviceId), streaming(false) {
    name = "Ear";
    
    try {
        audio = std::make_unique<RtAudio>();
    } catch (RtAudioErrorType& e) {
        std::cerr << "Ear: Failed to create RtAudio instance" << std::endl;
        throw;
    }
}

Ear::~Ear() {
    shutdown();
}

void Ear::info() const {
    std::cout << "=== Ear Information ===" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Device ID: " << deviceId << std::endl;
    std::cout << "Device Name: " << deviceName << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Streaming: " << (streaming ? "Yes" : "No") << std::endl;
    std::cout << "Sample Rate: " << sampleRate << " Hz" << std::endl;
    std::cout << "Buffer Frames: " << bufferFrames << std::endl;
    std::cout << "Channels: " << numChannels << std::endl;
    
    if (active) {
        std::cout << "Input Channels Available: " << deviceInfo.inputChannels << std::endl;
        std::cout << "Default Sample Rate: " << deviceInfo.preferredSampleRate << std::endl;
    }
    std::cout << "=======================" << std::endl;
}

bool Ear::initialize() {
    if (active) {
        std::cout << "Ear: Already initialized" << std::endl;
        return true;
    }

    if (!audio) {
        std::cerr << "Ear: RtAudio instance is null" << std::endl;
        return false;
    }

    unsigned int deviceCount = audio->getDeviceCount();
    if (deviceCount == 0) {
        std::cerr << "Ear: No audio devices found" << std::endl;
        return false;
    }

    std::cout << "Ear: Found " << deviceCount << " audio device(s)" << std::endl;

    // If deviceId is 0, use the default input device
    if (deviceId == 0) {
        deviceId = audio->getDefaultInputDevice();
        std::cout << "Ear: Using default input device ID: " << deviceId << std::endl;
    }

    // Get device info
    deviceInfo = audio->getDeviceInfo(deviceId);
    
    if (deviceInfo.inputChannels == 0) {
        std::cerr << "Ear: Device " << deviceId << " has no input channels" << std::endl;
        return false;
    }

    deviceName = deviceInfo.name;
    std::cout << "Ear: Initialized with device '" << deviceName << "'" << std::endl;

    // Setup stream parameters
    streamParams.deviceId = deviceId;
    streamParams.nChannels = std::min(numChannels, deviceInfo.inputChannels);
    streamParams.firstChannel = 0;

    // Setup stream options
    streamOptions.flags = RTAUDIO_MINIMIZE_LATENCY;
    streamOptions.numberOfBuffers = 2;
    streamOptions.streamName = "ChefEar";

    active = true;
    return true;
}

void Ear::shutdown() {
    if (streaming) {
        stopStream();
    }

    if (audio && audio->isStreamOpen()) {
        audio->closeStream();
    }

    active = false;
    std::cout << "Ear: Shutdown complete" << std::endl;
}

bool Ear::startStream() {
    if (!active) {
        std::cerr << "Ear: Cannot start stream - ear not initialized" << std::endl;
        return false;
    }

    if (streaming) {
        std::cout << "Ear: Stream already running" << std::endl;
        return true;
    }

    if (!brain) {
        std::cerr << "Ear: Cannot start stream - no brain connected" << std::endl;
        return false;
    }

    try {
        // Open the audio stream
        audio->openStream(
            nullptr,            // No output parameters (input only)
            &streamParams,      // Input parameters
            RTAUDIO_FLOAT32,    // Sample format
            sampleRate,         // Sample rate
            &bufferFrames,      // Buffer frames (may be modified by RtAudio)
            &Ear::audioCallback,// Callback function
            this,               // User data (this pointer)
            &streamOptions      // Stream options
        );

        // Start the stream
        audio->startStream();
        streaming = true;

        std::cout << "Ear: Stream started successfully" << std::endl;
        std::cout << "  Sample Rate: " << sampleRate << " Hz" << std::endl;
        std::cout << "  Buffer Frames: " << bufferFrames << std::endl;
        std::cout << "  Channels: " << streamParams.nChannels << std::endl;

        return true;

    } catch (RtAudioErrorType& e) {
        std::cerr << "Ear: Failed to start stream" << std::endl;
        return false;
    }
}

void Ear::stopStream() {
    if (!streaming) {
        return;
    }

    try {
        if (audio->isStreamRunning()) {
            audio->stopStream();
        }
        if (audio->isStreamOpen()) {
            audio->closeStream();
        }
        streaming = false;
        std::cout << "Ear: Stream stopped" << std::endl;

    } catch (RtAudioErrorType& e) {
        std::cerr << "Ear: Error stopping stream" << std::endl;
    }
}

std::vector<RtAudio::DeviceInfo> Ear::getAvailableInputDevices() {
    std::vector<RtAudio::DeviceInfo> inputDevices;
    
    try {
        RtAudio tempAudio;
        unsigned int deviceCount = tempAudio.getDeviceCount();

        for (unsigned int i = 0; i < deviceCount; i++) {
            RtAudio::DeviceInfo info = tempAudio.getDeviceInfo(i);
            if (info.inputChannels > 0) {
                inputDevices.push_back(info);
            }
        }
    } catch (RtAudioErrorType& e) {
        std::cerr << "Ear: Error enumerating audio devices" << std::endl;
    }

    return inputDevices;
}

int Ear::audioCallback(void* outputBuffer, void* inputBuffer,
                       unsigned int nFrames, double streamTime,
                       RtAudioStreamStatus status, void* userData) {
    Ear* ear = static_cast<Ear*>(userData);
    return ear->handleAudioInput(inputBuffer, nFrames, streamTime, status);
}

int Ear::handleAudioInput(void* inputBuffer, unsigned int nFrames, 
                          double streamTime, RtAudioStreamStatus status) {
    if (status) {
        std::cerr << "Ear: Stream overflow detected" << std::endl;
    }

    if (inputBuffer == nullptr) {
        return 0;
    }

    // Cast the input buffer to float
    const float* input = static_cast<const float*>(inputBuffer);

    // Send the audio data to the brain for processing
    if (brain) {
        brain->receiveAudioData(input, nFrames, streamParams.nChannels, streamTime);
    }

    return 0;  // Continue streaming
}
