CC = gcc
CPP = g++
CFLAGS = -g -Wall
CPPFLAGS = -g -Wall
OBJS = smash.o commands.o signals.o
RM = rm -f

# Creating the executable
smash: $(OBJS)
	$(CPP) -o smash $(OBJS)

# Creating the object files
commands.o: commands.cpp commands.h
	$(CPP) $(CPPFLAGS) -c commands.cpp

smash.o: smash.cpp commands.h signals.h
	$(CPP) $(CPPFLAGS) -c smash.cpp

signals.o: signals.cpp signals.h
	$(CPP) $(CPPFLAGS) -c signals.cpp

# Cleaning old files before new make
clean:
	$(RM) smash $(OBJS) *~ "#"* core.*
