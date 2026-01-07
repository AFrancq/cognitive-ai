/*
Bodypart class header file

Virtual class representing a body part.
*/

#ifndef BODYPART_H
#define BODYPART_H

#include <vector>

class Bodypart {
    public:
        Bodypart();
        virtual ~Bodypart();

        virtual void info() = 0;
        virtual void initialize() = 0;
        virtual void shutdown() = 0;
    private:
        unsigned int id;
};

#endif // BODYPART_H