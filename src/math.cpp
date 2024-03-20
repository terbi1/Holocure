#include "math.hpp"

Vector2f vectorNormalize(Vector2f vector) {
    float length = sqrt(vector.x * vector.x + vector.y * vector.y);
    return Vector2f{vector.x / length, vector.y / length};
}

float pointDirection(Vector2f vectorA, Vector2f vectorB) {
    return atan2(vectorB.y - vectorA.y, vectorB.x - vectorA.x);
}

float distance(Vector2f point1, Vector2f point2) {
    return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}