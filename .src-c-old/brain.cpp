/*
Brain class implementation

The brain serves as the central hub for sensory processing,
receiving audio data from ears and other sensory inputs.
*/

#include "brain.h"
#include <iostream>

Brain::Brain() : active(false), audioProcessCallback(nullptr) {
}

Brain::~Brain() {
    shutdown();
}

bool Brain::initialize() {
    if (active) {
        std::cerr << "Brain: Already initialized" << std::endl;
        return true;
    }

    std::cout << "Brain: Initializing with sample rate " << sampleRate 
              << " Hz, buffer size " << bufferFrames << " frames" << std::endl;

    active = true;
    std::cout << "Brain: Initialization complete" << std::endl;
    return true;
}

void Brain::shutdown() {
    if (!active) {
        return;
    }

    std::cout << "Brain: Shutting down..." << std::endl;

    // Clear any queued audio data
    {
        std::lock_guard<std::mutex> lock(audioMutex);
        while (!audioQueue.empty()) {
            audioQueue.pop();
        }
    }

    active = false;
    std::cout << "Brain: Shutdown complete" << std::endl;
}

void Brain::info() const {
    std::cout << "=== Brain Information ===" << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Sample Rate: " << sampleRate << " Hz" << std::endl;
    std::cout << "Buffer Frames: " << bufferFrames << std::endl;
    std::cout << "Channels: " << numChannels << std::endl;
    std::cout << "Audio Queue Size: " << audioQueue.size() << " buffers" << std::endl;
    std::cout << "=========================" << std::endl;
}

void Brain::receiveAudioData(const float* inputBuffer, unsigned int nFrames, 
                              unsigned int nChannels, double streamTime) {
    if (!active) {
        return;
    }

    // Copy the audio data into a vector
    std::vector<float> audioData(inputBuffer, inputBuffer + (nFrames * nChannels));

    // Queue the audio data for processing
    {
        std::lock_guard<std::mutex> lock(audioMutex);
        audioQueue.push(std::move(audioData));
    }

    // Process the queue
    processAudioQueue();
}

void Brain::setAudioProcessCallback(AudioProcessCallback callback) {
    audioProcessCallback = callback;
}

void Brain::processAudioQueue() {
    std::lock_guard<std::mutex> lock(audioMutex);

    while (!audioQueue.empty()) {
        std::vector<float> audioData = std::move(audioQueue.front());
        audioQueue.pop();

        // If a callback is registered, invoke it with the audio data
        if (audioProcessCallback) {
            audioProcessCallback(audioData);
        }

        // TODO: Add more audio processing logic here
        // For example: speech recognition, sound classification, etc.
    }
}
