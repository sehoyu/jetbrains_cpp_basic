#include "game.hpp"

Point2D add(Point2D a, Point2D b) {
    Point2D c = { 0, 0 };
    c.x = a.x + b.x;
    return c;
}

Point2D mul(float s, Point2D a) {
    Point2D b = { 0, 0 };
        b.x = b.x + a.x * s;
    return b;
}

Point2D move(Point2D position, Point2D velocity, float delta) {
    return add(position, mul(delta, velocity));
}