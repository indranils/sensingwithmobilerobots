CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall

OBJS_Z3 = basics.o primitive.o readinputs.o writeconstraints.o extractoutput.o definepropositions.o generatecoverageconstraints.o coveragemotionplanning.o

all: tool_z3


tool_z3 : $(OBJS_Z3)
	$(CC) $(LFLAGS) $(OBJS_Z3) -o tool_z3

basics.o : basics.h
	$(CC) $(CFLAGS) basics.cpp

primitive.o : basics.h primitive.h primitive.cpp
	$(CC) $(CFLAGS) primitive.cpp

readinputs.o : primitive.h readinputs.h readinputs.cpp
	$(CC) $(CFLAGS) readinputs.cpp

writeconstraints.o : primitive.h readinputs.h writeconstraints.h writeconstraints.cpp
	$(CC) $(CFLAGS) writeconstraints.cpp

extractOutput.o : extractoutput.h extractoutput.cpp
	$(CC) $(CFLAGS) extractoutput.cpp

definepropositions.o : primitive.h readinputs.h definepropositions.h definepropositions.cpp
	$(CC) $(CFLAGS) definepropositions.cpp

generatecoverageconstraints.o : primitive.h readinputs.h definepropositions.h generatecoverageconstraints.h generatecoverageconstraints.cpp
	$(CC) $(CFLAGS) generatecoverageconstraints.cpp

coveragemotionplanning.o : primitive.h readinputs.h extractoutput.h writeconstraints.h generatecoverageconstraints.h definepropositions.h coveragemotionplanning.cpp
	$(CC) $(CFLAGS) coveragemotionplanning.cpp


.PHONY: clean
clean : 
	rm -f *.o
	rm -f tool_*
