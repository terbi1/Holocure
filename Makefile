all:
	g++ -static -c src/*.cpp -std=c++17 -g -Wall -m64 -I include -I C:/mingw64/include && g++ *.o -o bin/debug/main -L C:/mingw64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer && ./bin/debug/main
	
start:
	start bin/release/main
test:
	./bin/debug/main
