#include <new>

#include "../include/animal.hpp"

Cat* createCat(char* memory) {
    // create Cat object with the name Tom in the given memory block
    Cat* cat = new (memory) Cat("Tom");
    return cat;
}

void destroyCat(char* memory) {
    // destroy Cat object stored in the given memory block
    Cat* cat = reinterpret_cast<Cat*>(memory);
    if (cat) {
        cat->~Cat();
    }
}

Mouse* createMouse(char* memory) {
    // create Mouse object with the name Jerry in the given memory block
    Mouse* mouse = new (memory) Mouse("Jerry");
    return mouse;
}

void destroyMouse(char* memory) {
    // destroy Mouse object stored in the given memory block
    Mouse* cat = reinterpret_cast<Mouse*>(memory);
    if (cat) {
        cat->~Mouse();
    }
}