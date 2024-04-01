#include "math.hpp"

Vector2f vectorNormalize(Vector2f vector) 
{
    float length = sqrt(vector.x * vector.x + vector.y * vector.y);
    return Vector2f{vector.x / length, vector.y / length};
}

float pointDirection(Vector2f vectorA, Vector2f vectorB) {
    return atan2(vectorB.y - vectorA.y, vectorB.x - vectorA.x);
}

float distance(Vector2f point1, Vector2f point2) {
    return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}

float randomFloat()
{
    return (float)(rand()) / (float)(RAND_MAX);
}
 
int randomInt(int a, int b)
{
    if (a > b)
        return randomInt(b, a);
    if (a == b)
        return a;
    return a + (rand() % (b - a));
}
 
float randomFloat(int a, int b)
{
    if (a > b)
        return randomFloat(b, a);
    if (a == b)
        return a;
 
    return (float)randomInt(a, b) + randomFloat();
}

void circularMotion(Vector2f& pos, Vector2f center, float angle)
{
    float temp = pos.x;
    pos.x = center.x + (pos.x - center.x) * cosf(angle) - (pos.y - center.y) * sinf(angle);
    pos.y = center.y + (temp - center.x) * sinf(angle) + (pos.y - center.y) * cosf(angle);
}

void spiralMotion(Vector2f& pos, Vector2f center, float speed, float angle)
{
    angle *= PI * 3;
    pos.x = (angle * 8) * cos(angle) + center.x;
    pos.y = (angle * 8) * sin(angle) + center.y;
}
