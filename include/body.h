/*
Body class header file

The Body class serves as a container for all body parts including
the brain and sensory organs. It manages the lifecycle of all components.
*/

#ifndef BODY_H
#define BODY_H

#include <memory>
#include <vector>
#include "brain.h"
#include "bodypart.h"

class Body {
    public:
        Body();
        ~Body();

        // Initialize all body parts
        bool initialize();

        // Shutdown all body parts
        void shutdown();

        // Display information about the body
        void info() const;

        // Get the brain
        std::shared_ptr<Brain> getBrain() const { return brain; }

        // Add a body part (automatically connects to brain)
        void addBodypart(std::shared_ptr<Bodypart> part);

        // Get all body parts
        const std::vector<std::shared_ptr<Bodypart>>& getBodyparts() const { return bodyparts; }

    private:
        std::shared_ptr<Brain> brain;
        std::vector<std::shared_ptr<Bodypart>> bodyparts;
        bool initialized = false;
};

#endif // BODY_H
