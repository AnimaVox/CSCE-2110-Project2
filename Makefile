# ----- Dynamic Swapping of Test Files [Start] ----------
# Use src/main.cpp by default
MAIN_SRC = src/main.cpp
MAIN_OBJ = main.o

# Type 'make TEST=NAME_OF_TEST_FILE.cpp' to override main.cpp and use it for testing.
ifdef TEST
	MAIN_SRC = testdata/$(TEST)
	MAIN_OBJ = test_main.o
endif
# ----- Dynamic Swapping of Test Files [End] ----------

TARGET = Project2

# Link all files together for exe
$(TARGET): $(MAIN_OBJ) Facility.o FacilityManager.o HashTable.o Helpers.o Menu.o
	g++ $(MAIN_OBJ) Facility.o FacilityManager.o HashTable.o Helpers.o Menu.o -o $(TARGET)

# Compile the appropiate main.cpp file.
$(MAIN_OBJ): $(MAIN_SRC) include/FacilityManager.h include/FileLoader.h include/HashTable.h include/Menu.h
	g++ -Wall -Iinclude -c $(MAIN_SRC) -o $(MAIN_OBJ)

# Individual compilation rules for core files
Facility.o: src/Facility.cpp include/Facility.h
	g++ -Wall -Iinclude -c src/Facility.cpp

FacilityManager.o: src/FacilityManager.cpp include/FacilityManager.h
	g++ -Wall -Iinclude -c src/FacilityManager.cpp

HashTable.o: src/HashTable.cpp include/HashTable.h
	g++ -Wall -Iinclude -c src/HashTable.cpp

Helpers.o: src/Helpers.cpp include/Helpers.h
	g++ -Wall -Iinclude -c src/Helpers.cpp

Menu.o: src/Menu.cpp include/Menu.h
	g++ -Wall -Iinclude -c src/Menu.cpp

# Clean build files
clean:
	del /f /q *.o $(TARGET)

.PHONY: clean