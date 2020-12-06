SOURCE = b18.cpp \
	 GateArray.cpp \
	 NandGateColumn.cpp \
	 tests.cpp

OBJS = $(SOURCE:.cpp=.o)
OUTNAME = b18
CFLAGS = -Wall -O3
CXXFLAGS = $(CFLAGS)

.PHONY: clean


all:
	g++ $(CXXFLAGS) $(SOURCE) -o $(OUTNAME) 


clean:
	rm -rf *.o *.d $(OUTNAME) 


