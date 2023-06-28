#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>

class Fractal {
public:
    Fractal(int width, int height);

    void updateOffset(int deltaX, int deltaY);
    std::vector<unsigned int> generate();

private:
    int width;
    int height;
    double offsetX;
    double offsetY;

    double map(int value, int start1, int stop1, double start2, double stop2);
    unsigned int getColor(int value, int max);
};

#endif // FRACTAL_H
