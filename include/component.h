/*
Component class header file

Virtual class representing a component.
Each component has a reference to the brain for sending sensory data.
*/

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <memory>

// Forward declaration
class Brain;

class Component {
    public:
        Component();
        virtual ~Component() = default;

        // Display information about the component
        virtual void info() const = 0;

        // Initialize the component
        virtual bool initialize() = 0;

        // Shutdown the component
        virtual void shutdown() = 0;

        // Check if the component is active
        virtual bool isActive() const { return active; }

        // Set the brain reference for sending data
        void setBrain(std::shared_ptr<Brain> brain);

    protected:
        std::shared_ptr<Brain> brain;
        bool active = false;
        unsigned int id;
        std::string name;
};

#endif // COMPONENT_H