#can be overriden in command line

CC=/Users/saschavancauwelaert/gcc_461/bin/g++
#CC = /opt-clang/bin/clang++

INCLUDE=/usr/local/include
#INCLUDE=/opt-cprel/include

LIBS=/usr/local/lib
#LIBS=/opt-cprel/lib

all : join
		
join: join.cpp
				$(CC) join.cpp -o join -I$(INCLUDE) -I$(INCLUDE)/cudd -I$(INCLUDE)/mtr -I$(INCLUDE)/epd -std=c++0x -L$(LIBS) -lgecodekernel -lgecodeint -lgecodesearch -lgecodesupport -lgecodeset -lgecodecprel -lbdddomain -lgecodegist -lgecodeminimodel -lgecodeflatzinc -lgecodedriver -lgecodegist -lgecodesearch -lgecodeminimodel -lgecodeset -lgecodeint -lgecodekernel -lgecodesupport -lmtr -lst -lutil -lepd -lcudd -lcuddobj

