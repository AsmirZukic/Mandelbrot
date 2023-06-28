#include "../include/Fractal.h"

#include <vector>

Fractal::Fractal(int width, int height)
    : width(width), height(height), offsetX(0.0), offsetY(0.0) {}

void Fractal::updateOffset(int deltaX, int deltaY) 
{
    offsetX += deltaX;
    offsetY += deltaY;
}

std::vector<unsigned int> Fractal::generate() 
{
    std::vector<unsigned int> pixels(width * height);

    double minR = -2.0;
    double maxR = 1.0;
    double minI = -1.5;
    double maxI = 1.5;

    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            double zx = 0.0;
            double zy = 0.0;
            double cX = map(x, 0, width, minR, maxR) + offsetX;
            double cY = map(y, 0, height, minI, maxI) + offsetY;
            int iteration = 0;
            int maxIteration = 1000;

            while (zx * zx + zy * zy < 4.0 && iteration < maxIteration) 
            {
                double xtemp = zx * zx - zy * zy + cX;
                zy = 2.0 * zx * zy + cY;
                zx = xtemp;
                iteration++;
            }

            unsigned int color = getColor(iteration, maxIteration);
            pixels[y * width + x] = color;
        }
    }

    return pixels;
}

double Fractal::map(int value, int start1, int stop1, double start2, double stop2) 
{
    double t = static_cast<double>(value - start1) / static_cast<double>(stop1 - start1);
    return start2 + t * (stop2 - start2);
}

unsigned int Fractal::getColor(int value, int max) 
{
    if (value == max)
        return 0x000000; // Black for points in the set
    else 
    {
        double t = static_cast<double>(value) / static_cast<double>(max);
        int r = static_cast<int>(9 * (1 - t) * t * t * t * 255);
        int g = static_cast<int>(15 * (1 - t) * (1 - t) * t * t * 255);
        int b = static_cast<int>(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
        return (r << 16) | (g << 8) | b;
    }
}
