SOURCE = main.cpp \
	 GateArray.cpp \
	 NandGateColumn.cpp \
	 tests.cpp

OBJS = $(SOURCE:.cpp=.o)
OUTNAME = SteidlB18
CFLAGS = -Wall -O3
CXXFLAGS = $(CFLAGS)

.PHONY: clean


all:
	g++ $(CXXFLAGS) $(SOURCE) -o $(OUTNAME) 


clean:
	rm -rf *.o *.d $(OUTNAME) 


