CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra # -Werror

TARGET = smash
OBJS = smash.o commands.o jobs_manager.o signals.o job.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

smash.o: smash.cpp commands.h signals.h jobs_manager.h job.h
	$(CXX) $(CXXFLAGS) -c smash.cpp

commands.o: commands.cpp commands.h jobs_manager.h job.h
	$(CXX) $(CXXFLAGS) -c commands.cpp

jobs_manager.o: jobs_manager.cpp jobs_manager.h job.h
	$(CXX) $(CXXFLAGS) -c jobs_manager.cpp

signals.o: signals.cpp signals.h
	$(CXX) $(CXXFLAGS) -c signals.cpp

job.o: job.cpp job.h
	$(CXX) $(CXXFLAGS) -c job.cpp

clean:
	rm -f $(OBJS) $(TARGET)
