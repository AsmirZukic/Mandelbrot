#include "../include/engine.h"
#include "../include/pixel.hpp"
#include <vector>

//Ranges of the mandelbrot set
const long double MIN_X = -2;
const long double MAX_X = 0.47;
const long double MIN_Y = -1.12;
const long double MAX_Y = 1.12;

//maximum number of iterations
const int maxIterations = 200;

//Function to scale the pixels to the mandelbrot radius
long double map( long double x, long double in_min, long double in_max, long double out_min, long double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Mandelbrot function
void Mandelbrot(std::vector<Pixel*> &Cords)
{
  //For each pixel on the screen
  for( int i = 0; i < 640; i++)
  {
    for( int j = 0; j < 480; j++)
    {
      //Scaled x and y cooridnate of pixel
       long double x0 = map( (long double) i, 0.0, (long double) 640 , MIN_X, MAX_X );
       long double y0 = map( (long double) j, 0.0, (long double) 480 , MIN_Y, MAX_Y );


       double x = 0.0;
       double y = 0.0;

       double x2 = 0;
       double y2 = 0;

       //Keeping track of iterations
       int iterations = 0;

       //While the absolute value of the complex number is less than 2
       while ( ( x2*x2 + y2*y2 <= 4 ) && iterations <= maxIterations )
       {
         y = 2 * x * y + y0;
         x = x2 - y2 + x0;

         x2 = x * x;
         y2 = y * y;

         iterations++;
       }

      //If the loop finished early we know the point lies withing the mandelbrot set
      if( x2* x2 + y2 * y2 > 4 )
      {
        Cords.push_back( new Pixel( i , j ) );
      }

    }
  }
}

int main( int argc, char* argv[] )
{
  Engine engine;

  std::vector<Pixel*> pixels;
  Mandelbrot(pixels);

  while( engine.isRunning() )
  {
    engine.handleInput();
    engine.render();

    //Rendere each individual pixels
    for( auto &it : pixels )
    {
      it->render( 255, 255, 255, 255 );
    }

    engine.draw();
  }

  //Delete each pixel so it doesn't leak memory
  for( auto &it: pixels )
  {
    delete it;
  }

}
