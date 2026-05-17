#include "game.hpp"

Point2D operator+(Point2D a, Point2D b) {
    // TODO: write your solution here
    return {a.x + b.x, a.y + b.y};
}

Point2D operator-(Point2D a) {
    // TODO: write your solution here
    return {-a.x, -a.y};
}

Point2D operator-(Point2D a, Point2D b) {
    // TODO: write your solution here
    return {a.x - b.x, a.y - b.y};
}

Point2D operator*(float s, Point2D a) {
    // TODO: write your solution here
    return {a.x * s, a.y * s};
}

Circle operator+(Circle c, Point2D v) {
    // TODO: write your solution here
    Circle d = {
        {c.center.x, c.center.y},
        c.radius
    };

    d.center.x += v.x;
    d.center.y += v.y;

    return d;
}

Circle operator-(Circle c, Point2D v) {
    // TODO: write your solution here
    Circle d = {
        {c.center.x, c.center.y},
        c.radius
    };

    d.center.x -= v.x;
    d.center.y -= v.y;

    return d;
}

Rectangle operator+(Rectangle r, Point2D v) {
    // TODO: write your solution here
    Rectangle a = {
        r.topLeft,
        r.botRight
    };

    a.topLeft.x += v.x;
    a.topLeft.y += v.y;
    a.botRight.x += v.x;
    a.botRight.y += v.y;

    return a;
}

Rectangle operator-(Rectangle r, Point2D v) {
    // TODO: write your solution here
    Rectangle a = {
        r.topLeft,
        r.botRight
    };

    a.topLeft.x -= v.x;
    a.topLeft.y -= v.y;
    a.botRight.x -= v.x;
    a.botRight.y -= v.y;

    return a;

}

Circle operator*(float s, Circle c) {
    // TODO: write your solution here
    Circle d = {
        {c.center.x, c.center.y},
        c.radius
    };

    d.radius *= s;

    return d;
}

Rectangle operator*(float s, Rectangle r) {
    // TODO: write your solution here
    Rectangle a = {
        r.topLeft,
        r.botRight
    };

    float w = width(a) * s;
    float h = height(a) * s;
    a.botRight.y = a.topLeft.y + h;
    a.botRight.x = a.topLeft.x + w;
    // a.botRight.y += h;
    // a.botRight.x += w;

    return a;
}