all:
	g++ -std=c++11 TimeCode.cpp TimeCodeTests.cpp -o tct
	g++ -std=c++11 NasaLaunchAnalysis.cpp TimeCode.cpp -o nasa
	g++ -std=c++11 PaintDryTimer.cpp TimeCode.cpp -o pdt
run:
	./tct
	./nasa
	./pdt

try: all run
