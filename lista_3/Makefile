CFLAGS = -Wall -Wextra -std=c++17 -O3 -pedantic

all: dijkstra, dial, radix

dijkstra: main.cpp dijkstra.cpp graph.cpp
	g++ $(CFLAGS) main.cpp dijkstra.cpp graph.cpp -o dijkstra

dial: main2.cpp dial.cpp graph.cpp
	g++ $(CFLAGS) main2.cpp dial.cpp graph.cpp -o dial

radix: main3.cpp radix.cpp graph.cpp
	g++ $(CFLAGS) main3.cpp radix.cpp graph.cpp -o radix