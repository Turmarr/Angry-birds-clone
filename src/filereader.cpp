#include "filereader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Cannon ReadCannon(std::string line) {
    Cannon cannon;
    std::stringstream ss;
    ss.str(line);
    ss >> cannon.x >> cannon.y;
    return cannon;
}

Pig ReadPig(std::string line) {
    Pig pig;
    std::stringstream ss;
    ss.str(line);
    ss >> pig.type >> pig.pos;
    //std::cout << x.pos << x.type << std::endl;
    return pig;
        
}

Bird ReadBird(std::string line) {
    Bird bird;
    std::stringstream ss;
    ss.str(line);
    ss >> bird.type >> bird.x >> bird.y;
    return bird;
}

Object ReadObject(std::string line) {
    Object object;
    std::stringstream ss;
    ss.str(line);
    ss >> object.type >> object.x >> object.y;
    return object;
}

Ground ReadGround(std::string line) {
    Ground ground;
    std::stringstream ss;
    ss.str(line);
    ss >> ground.x >> ground.y;
    return ground;
}

Filereader::Filereader(std::string filename) {
    std::ifstream file(filename);

    int block_no = 0;
    
    if (file.rdstate() & (file.failbit | file.badbit)) {
	    // output error to stderr stream
	    //std::cerr << "Failed" << std::endl;
        throw file_exception();

	} else {
	    // repeat until end of file
	    while (!file.eof()) {
		    std::string line;
		    std::getline(file, line);
		    //std::cout << line << std::endl;
            
            if (line[0] == '#') {
                block_no++;
            }
            else if (line.size() == 0) {
            //std::cout << "con" << std::endl;
            continue;
            }
            else {
                switch (block_no) {
                    //case 0:
                        //break;
                    case 1:
                        cannon_ = ReadCannon(line);
                        break;
                    case 2:
                        pigs_.push_back(ReadPig(line));
                        //std::cout << "pigs: " << pigs_.size() << std::endl;
                        break;
                    case 3:
                        birds_.push_back(ReadBird(line));
                        break;
                    case 4:
                        objects_.push_back(ReadObject(line));
                        break;
                    case 5:
                        ground_.push_back(ReadGround(line));
                        break;

                    default:
                        break;
                    
                }
            }
            
	    }
	}
}

