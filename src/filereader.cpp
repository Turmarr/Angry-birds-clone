#include "filereader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>



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
            else if (line.size() == 1) {
            //std::cout << "con" << std::endl;
            continue;
            }
            else {
                switch (block_no) {
                    case 0:
                        break;
                    case 1:
                        pigs_.push_back(ReadPig(line));
                        //std::cout << "pigs: " << pigs_.size() << std::endl;
                        break;
                    case 2:
                        birds_.push_back(ReadBird(line));
                        break;
                    case 3:
                        objects_.push_back(ReadObject(line));
                        break;
                    case 4:
                        ground_.push_back(ReadGround(line));
                        break;
                    
                }
            }
            
	    }
	}
}

