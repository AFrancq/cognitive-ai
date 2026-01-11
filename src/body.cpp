/*
Body class implementation

The Body manages the collection of body parts and the brain.
*/

#include "body.h"
#include <iostream>

Body::Body() : brain(std::make_shared<Brain>()), initialized(false) {
}

Body::~Body() {
    shutdown();
}

bool Body::initialize() {
    if (initialized) {
        std::cout << "Body: Already initialized" << std::endl;
        return true;
    }

    std::cout << "Body: Initializing..." << std::endl;

    // Initialize the brain first
    if (!brain->initialize()) {
        std::cerr << "Body: Failed to initialize brain" << std::endl;
        return false;
    }

    // Initialize all body parts
    for (auto& part : bodyparts) {
        if (!part->initialize()) {
            std::cerr << "Body: Failed to initialize a body part" << std::endl;
            return false;
        }
    }

    initialized = true;
    std::cout << "Body: Initialization complete" << std::endl;
    return true;
}

void Body::shutdown() {
    if (!initialized) {
        return;
    }

    std::cout << "Body: Shutting down..." << std::endl;

    // Shutdown body parts first
    for (auto& part : bodyparts) {
        part->shutdown();
    }

    // Shutdown the brain last
    brain->shutdown();

    initialized = false;
    std::cout << "Body: Shutdown complete" << std::endl;
}

void Body::info() const {
    std::cout << "=== Body Information ===" << std::endl;
    std::cout << "Status: " << (initialized ? "Initialized" : "Not Initialized") << std::endl;
    std::cout << "Number of Body Parts: " << bodyparts.size() << std::endl;
    std::cout << std::endl;

    brain->info();
    std::cout << std::endl;

    for (const auto& part : bodyparts) {
        part->info();
        std::cout << std::endl;
    }
    std::cout << "========================" << std::endl;
}

void Body::addBodypart(std::shared_ptr<Bodypart> part) {
    // Connect the body part to the brain
    part->setBrain(brain);
    bodyparts.push_back(part);
    std::cout << "Body: Added new body part" << std::endl;
}
