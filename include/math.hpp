#pragma once

#include <iostream>
#include <cmath>

const float PI = 3.14159274101257324219;

struct Vector2f
{
    Vector2f()
        : x(0.0f), y(0.0f)
    {
    }

    Vector2f(float p_x, float p_y)
        : x(p_x), y(p_y)
    {
    }

    void print()
    {
        std::cout << x << ", " << y << '\n';
    }

    float x, y;
    Vector2f operator+(Vector2f other)
    {
        return Vector2f{x + other.x, y + other.y};
    }

    void operator+=(Vector2f other)
    {
        x += other.x;
        y += other.y;
    }

    Vector2f operator-(Vector2f other)
    {
        return Vector2f{x - other.x, y - other.y};
    }

    void operator-=(Vector2f other)
    {
        x -= other.x;
        y -= other.y;
    }

    Vector2f operator*(Vector2f other)
    {
        return Vector2f{x * other.x, y * other.y};
    }

    Vector2f operator*(float scalar)
    {
        return Vector2f{x * scalar, y * scalar};
    }

    void operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    Vector2f operator/(Vector2f other)
    {
        return Vector2f{x / other.x, y / other.y};
    }

    void operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
    }
};

struct Circle 
{
    Vector2f center{0,0};
    float radius{0};
};

Vector2f vectorNormalize(Vector2f vector);

float pointDirection(Vector2f vectorA, Vector2f vectorB);

float distance(Vector2f point1, Vector2f point2);

float randomFloat();
 
int randomInt(int a, int b);

float randomFloat(int a, int b);

void circularMotion(Vector2f& pos, Vector2f center, float angle);

void spiralMotion(Vector2f& pos, Vector2f center, float speed, float angle);