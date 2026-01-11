/*
Bodypart class implementation
*/

#include "bodypart.h"
#include "brain.h"

// Initialize static member
unsigned int Bodypart::nextId = 0;

Bodypart::Bodypart() : brain(nullptr), active(false), id(nextId++), name("Unnamed Bodypart") {
}

void Bodypart::setBrain(std::shared_ptr<Brain> brainRef) {
    brain = brainRef;
}
