CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
TARGET   = Project2
SRCS     = $(wildcard src/*.cpp)

$(TARGET): $(SRCS) $(wildcard include/*.h)
	g++ $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Unit-test drivers: make test TEST=Name_of_test_file.cpp
test:
	g++ $(CXXFLAGS) -o test $(filter-out src/main.cpp,$(SRCS)) testdata/$(TEST)

clean:
	rm -f $(TARGET) test *.o

.PHONY: clean test