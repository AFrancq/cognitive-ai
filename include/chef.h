/*
The chef class represents a chef who can have multiple ears and a voice.
This is intended as a header class for an AI system that models a chef's 
sensory and vocal capabilities.
*/

#ifndef CHEF_H
#define CHEF_H

#include <set>
#include "ear.h"
#include "voice.h"

class Chef {
    public:
        Chef();
        ~Chef();

    protected:
        void addEar(const Ear& ear);
        void addVoice(const Voice& voice);

    private:
        std::set<Ear> ears;
        Voice voice;
};

#endif // CHEF_H