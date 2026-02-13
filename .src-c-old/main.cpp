/*
Have You Heard of Chef?

An AI sous chef with sensory capabilities.
This demo initializes the brain and ear, then captures audio for a short period.
*/

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <csignal>
#include <cmath>

#include "brain.h"
// #include "ear.h"

static volatile bool running = true;

// Async audio processor to store signals for later analysis
// bool initializeAudioProcessor(std::shared_ptr<Brain> brain) {
//     // Set up a callback to monitor incoming audio
//     brain->setAudioProcessCallback([](const std::vector<float>& audioData) {
//         // Calculate simple audio level (RMS)
//         float sum = 0.0f;
//         for (const float& sample : audioData) {
//             sum += sample * sample;
//         }
//         float rms = std::sqrt(sum / audioData.size());

//         // Display a simple level meter
//         int level = static_cast<int>(rms * 50);
//         std::cout << "\rAudio Level: [";
//         for (int i = 0; i < 25; i++) {
//             std::cout << (i < level ? "#" : "-");
//         }
//         std::cout << "] " << std::flush;
//     });

//     return true;
// }

void signalHandler(int signum) {
    std::cout << "\nInterrupt received, shutting down..." << std::endl;
    running = false;
}

int main(int argc, char **argv) {
    std::cout << "=== AI Assistant ===" << std::endl;
    std::cout << std::endl;
    
    // Setup signal handler for graceful shutdown
    std::signal(SIGINT, signalHandler);
    
    // Create the brain - the central processing hub
    auto brain = std::make_shared<Brain>();
    
    // Initialize the brain
    if (!brain->initialize()) {
        std::cerr << "Failed to initialize brain" << std::endl;
        return 1;
    }
    
    brain->info();

    // Run until interrupted
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Cleanup
    std::cout << "\nShutting down..." << std::endl;
    brain->shutdown();

    std::cout << "Goodbye!" << std::endl;
    return 0;
    // // Initialize audio processing
    // if (!initializeAudioProcessor(brain)) {
    //     std::cerr << "Failed to initialize audio processor" << std::endl;
    //     return 1;
    // }

    // List available input devices
    // std::cout << "\nAvailable input devices:" << std::endl;
    // auto devices = Ear::getAvailableInputDevices();
    // for (size_t i = 0; i < devices.size(); i++) {
    //     std::cout << "  [" << i << "] " << devices[i].name 
    //               << " (" << devices[i].inputChannels << " channels)" << std::endl;
    // }
    // std::cout << std::endl;

    // Create an ear (audio input)
    // Ear ear;  // Uses default input device
    // ear.setBrain(brain);

    // Initialize the ear
    // if (!ear.initialize()) {
    //     std::cerr << "Failed to initialize ear" << std::endl;
    //     return 1;
    // }
    // ear.info();

    // // Start the audio stream
    // std::cout << "\nStarting audio capture... (Press Ctrl+C to stop)" << std::endl;
    // if (!ear.startStream()) {
    //     std::cerr << "Failed to start audio stream" << std::endl;
    //     return 1;
    // }

}