#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#ifndef FILE_READER
#define FILE_READER
/*
The files to be read must be placed into the builds folder.

Function:
The information is read into specific structures to make it easier to keep track of all the
information. If the program is unable to open the file it throws a file_exception to communicate with the
main program.

File structure:
# starts a new block the blocks are in order:
1 Cannon
2 Pigs
3 Birds
4 Objects
5 groundpoints (maybe not necessary)

It doesn't matter what is after the # as it only watches for the first character of each line, but
it has to be the first character. It is possible to leave blocks away, then the vectors will just be empty.
If a block in the middle is empty the # has to be present to tick the counter to the correct block. Empty lines
are possible but on them there must not be any characters except for "\n".

On every line the information is separated by blank spaces.

Cannon:
"position on x-axis" "position on y-axis"

Pigs:
"type of pig" "how manieth it is to be shot"

Birds:
"type of bird" "position on x-axis" "position on y-axis"

Objects:
"type of object(box/ball)" "material of object" "position on x-axis" "position on y-axis" "radius(whatever if box)"
    ..."width(whatever if ball)" "height(whatever if ball)"

Groundboxes:
"position on x-axis" "position on y-axis" "width" "height"

Level
"Which level it is"
*/

class file_exception : public std::exception {
    	const char * what () const throw ()
    {
    	return "Failed to read file";
    }
};

struct Cannonc {
    int x;
    int y;
};

struct Pigc {
    std::string type;
    int pos;
};

struct Birdc {
    float x;
    float y;
    std::string type;
};

struct Objectc {
    float x;
    float y;
    std::string type;
    std::string material;
    float width;
    float height;
    float radius;
};

struct Groundc {
    float x;
    float y;
    float width;
    float height;
};

class Filereader {
    public:
        Filereader(std::string filename);

        std::vector<struct Pigc> GetPigs() const {
            return pigs_;
        }

        std::vector<struct Birdc> GetBirds() const {
            return birds_;
        }

        std::vector<struct Objectc> GetObjects() const {
            return objects_;
        }

        std::vector<struct Groundc> GetGround() const {
            return ground_;
        }

        Cannonc GetCannon() const {
            return cannon_;
        }

        int GetLevel() const {
            return level_;
        }

    private:
        std::vector<struct Pigc> pigs_;
        std::vector<struct Birdc> birds_;
        std::vector<struct Objectc> objects_;
        std::vector<struct Groundc> ground_;
        struct Cannonc cannon_;
        int level_;
};

#endif