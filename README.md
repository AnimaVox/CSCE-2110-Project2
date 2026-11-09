# CSCE-2110-Project-2

## To complie please run one of the following commands in the root directory:

1) g++ -o name_of_program src/*.cpp
2) make

Replace 'name_of_program' as desired.
### Alternatively, if you wish to complie using one of the testing files (.cpp), change the command to:
- make test TEST=Name_of_file
  - e.g. _make test TEST=HashTableTEST.cpp_
  
_Testing files are lables as 'Name_of_FileTEST'_

This will cause the test file to replace main.cpp and create ./test for you to run.
Please run this ./test for an isolated demo of the given test file and nothing else.
When running ./test you cannot pass in an argument for the data directory.

### If you wish to run the program with an argument for the data directoy, you may use:
1) ./name_of_program
   - loads files from the default 'data' directory
   -  e.g _./Project2_
3) ./name_of_program name_of_directory
   - loads from the given directory
   - e.g. _./Project2 testdata/badrecords_

Relplace 'name_of_directory' as needed.

Use this to test data in the /testdata directories that isn't a .cpp test file or to simply run the program.

Each data directory must contain:
- buildings.txt
- connections.txt
- facilities.txt
- departments.txt

_Missing files are reported and treated as empty._
