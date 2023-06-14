CFLAGS = -Wall -Wextra -std=c++17 -O3 -pedantic

all: dijkstra, dial, radix

dijkstra: main.cpp dijkstra.cpp graph.cpp
	g++ $(CFLAGS) main.cpp dijkstra.cpp graph.cpp -o dijkstra

dial: main.cpp dial.cpp graph.cpp
	g++ $(CFLAGS) main.cpp dial.cpp graph.cpp -o dial

radix: main.cpp radix.cpp graph.cpp
	g++ $(CFLAGS) main.cpp radix.cpp graph.cpp -o radix