# CSCE-2110-Project-2

To complie please run one of the following commands in the root directory:

1) g++ -o name_of_program src/*.cpp
2) make

Alternatively, if you wish to complie using one of the testing files (.cpp), change the command to:
make test TEST=Name_of_file
    e.g. make test TEST=HashTableTEST.cpp
This will cause the test file to replace main.cpp and create ./test for you to run.
Please run this ./test for an isolated demo of the given test file and nothing else.
When running ./test you cannot pass in an argument for the data directory.

If you wish to run the program with a argument for the data directoy, you may use:
1) ./name_of_program                        # loads files from the default 'data' directory
    e.g ./Project2
2) ./name_of_program name_of_directory      # loads from the given directory
    e.g. ./Project2 testdata/badrecords
Use this to test data in the /testdata directories that isn't a .cpp test file or to simply run the program.

Each data directory must contain:
buildings.txt
connections.txt
facilities.txt
departments.txt.
Missing files are reported and treated as empty.