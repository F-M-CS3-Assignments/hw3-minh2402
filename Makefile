all:
	g++ -std=c++11 TimeCode.cpp TimeCodeTests.cpp -o tct

run: 
	./tct

try: all run
