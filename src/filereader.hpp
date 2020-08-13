#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

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