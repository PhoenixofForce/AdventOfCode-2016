day := 09
all:
	@g++ -o main day$(day)/Day$(day).cpp Utils.cpp util/md5.cpp
	@main.exe
	@del main.exe