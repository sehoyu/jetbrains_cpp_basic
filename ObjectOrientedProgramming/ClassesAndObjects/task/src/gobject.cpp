#include "gobject.hpp"

#include "operators.hpp"

void GameObject::move(Point2D vector) {
    // TODO: write your solution here
    Point2D next = getPosition() + vector;
    setPosition(next);
}