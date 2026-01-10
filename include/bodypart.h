/*
Bodypart class header file

Virtual class representing a body part.
Each body part has a reference to the brain for sending sensory data.
*/

#ifndef BODYPART_H
#define BODYPART_H

#include <string>
#include <memory>

// Forward declaration
class Brain;

class Bodypart {
    public:
        Bodypart();
        virtual ~Bodypart() = default;

        // Display information about the body part
        virtual void info() const = 0;

        // Initialize the body part
        virtual bool initialize() = 0;

        // Shutdown the body part
        virtual void shutdown() = 0;

        // Check if the body part is active
        virtual bool isActive() const { return active; }

        // Set the brain reference for sending data
        void setBrain(std::shared_ptr<Brain> brain);

    protected:
        std::shared_ptr<Brain> brain;
        bool active = false;
        unsigned int id;
        std::string name;

    private:
        static unsigned int nextId;
};

#endif // BODYPART_H