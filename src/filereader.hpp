#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct Pig {
    std::string type;
};

struct Bird {
    int x;
    int y;
    std::string type;
};

struct Box {
    int x;
    int y;
    std::string type;
};

class Filereader {
    public:
        Filereader(std::string filename);

        std::vector<std::vector<std::string>>& GetPigs() const;

        std::vector<std::vector<std::string>>& GetBirds() const;

        std::vector<std::vector<std::string>>& GetObjects() const;

    private:
        std::vector<struct Pig> pigs_;
        std::vector<struct Bird> birds_;
        std::vector<struct Box> objects_;
};