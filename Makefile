day := 01
all:
	@g++ -o main day$(day)/Day$(day).cpp Utils.cpp
	@main.exe
	@del main.exe