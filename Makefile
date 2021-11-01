CC=g++
CFLAGS= -c -Wall
SDL2= -w -lSDL2

all: Mandelbrot

Mandelbrot: main.o engine.o renderer.o window.o pixel.o
	$(CC) main.o engine.o renderer.o window.o pixel.o $(SDL2) -o Mandelbrot

main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp

engine.o: src/engine.cpp
	$(CC) $(CFLAGS) src/engine.cpp

renderer.o: src/renderer.cpp
	$(CC) $(CFLAGS) src/renderer.cpp

window.o: src/window.cpp
	$(CC) $(CFLAGS) src/window.cpp

pixel.o: src/pixel.cpp
	$(CC) $(CFLAGS) src/pixel.cpp

clean:
	rm *.o
