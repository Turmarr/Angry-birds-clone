#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

/*
The files to be read must be placed into the builds folder.

Function:
The information is read into specific structures to make it easier to keep track of all the
information. If the program is unable to open the file it throws a file_exception to communicate with the
main program.

File structure:
# starts a new block the blocks are in order:
1 Pigs
2 Birds
3 Objects
4 groundpoints (maybe not necessary)

It doesn't matter what is after the # as it only watches for the first character of each line, but
it has to be the first character. It is possible to leave blocks away, then the vectors will just be empty.
If a block in the middle is empty the # has to be present to tick the counter to the correct block.

On every line the information is separated by blank spaces.

Pigs:
"type of pig" "how manieth it is to be shot"

Birds:
"type of bird" "position on x-axis" "position on y-axis"

Objects:
"type of object" "position on x-axis" "position on y-axis"

Groundpoint: (This will be utilized if box2d custom ground is implemented)
"position on x-axis" "position on y-axis"
*/

class file_exception : public std::exception {
    	const char * what () const throw ()
    {
    	return "Failed to read file";
    }
};

struct Pig {
    std::string type;
    int pos;
};

struct Bird {
    int x;
    int y;
    std::string type;
};

struct Object {
    int x;
    int y;
    std::string type;
};

struct Ground {
    int x;
    int y;
};

class Filereader {
    public:
        Filereader(std::string filename);

        std::vector<struct Pig> GetPigs() const {
            return pigs_;
        }

        std::vector<struct Bird> GetBirds() const {
            return birds_;
        }

        std::vector<struct Object> GetObjects() const {
            return objects_;
        }

        std::vector<struct Ground> GetGround() const {
            return ground_;
        }

    private:
        std::vector<struct Pig> pigs_;
        std::vector<struct Bird> birds_;
        std::vector<struct Object> objects_;
        std::vector<struct Ground> ground_;
};