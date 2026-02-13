/*
This is the brain class which serves as a foundational component
for an AI system that models cognitive functions. It is designed to
serve as the internal endpoint for sensory inputs and processing.

The brain contains an internal audio device for receiving audio streams
from sensory inputs like the ear.
*/

#ifndef BRAIN_H
#define BRAIN_H

#include <component.h>
#include <memory>

class Brain {
    public:
        Brain();
        ~Brain();

        // Initialize the brain and its internal audio processing
        bool initialize() {
            if(!initializeAudioComponent()) return false;
            if(!initializeVideoComponent()) return false;
            if(!initializeMemoryComponent()) return false;
            return true;
        }

        // Shutdown the brain
        void shutdown() {
            if (audioInput && audioInput->isActive()) {
                audioInput->shutdown();
            }
            if (videoInput && videoInput->isActive()) {
                videoInput->shutdown();
            }
            if (memoryStore && memoryStore->isActive()) {
                memoryStore->shutdown();
            }
            active = false;
        }
        

        // Display information about the brain
        void info() const;

        // Check if the brain is active
        bool isActive() const { return active; }

    private:
        bool active = false;

        std::unique_ptr<Component> audioInput;
        std::unique_ptr<Component> videoInput;
        std::unique_ptr<Component> memoryStore;

        bool initializeAudioComponent();
        bool initializeVideoComponent();
        bool initializeMemoryComponent();
};

#endif // BRAIN_H