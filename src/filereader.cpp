#include "filereader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Cannonc ReadCannon(std::string line) {
    Cannonc cannon;
    std::stringstream ss;
    ss.str(line);
    ss >> cannon.x >> cannon.y;
    return cannon;
}

Pigc ReadPig(std::string line) {
    Pigc pig;
    std::stringstream ss;
    ss.str(line);
    ss >> pig.type >> pig.pos;
    //std::cout << x.pos << x.type << std::endl;
    return pig;
        
}

Birdc ReadBird(std::string line) {
    Birdc bird;
    std::stringstream ss;
    ss.str(line);
    ss >> bird.type >> bird.x >> bird.y;
    return bird;
}

Objectc ReadObject(std::string line) {
    Objectc object;
    std::stringstream ss;
    ss.str(line);
    ss >> object.type >> object.material >> object.x >> object.y >> object.radius >> object.width >> object.height;
    return object;
}

Groundc ReadGround(std::string line) {
    Groundc ground;
    std::stringstream ss;
    ss.str(line);
    ss >> ground.x >> ground.y >> ground.width >> ground.height;
    return ground;
}

int ReadLevel(std::string line) {
    int level;
    std::stringstream ss;
    ss.str(line);
    ss >> level;
    return level;
}

std::string ReadHighScoreFile(std::string line) {
    std::string file;
    std::stringstream ss;
    ss.str(line);
    ss >> file;
    return file;
}

Stars ReadStars(std::string line) {
    Stars star;
    std::stringstream ss;
    ss.str(line);
    ss >> star.second >> star.third;
    return star;
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
            else if (line[0] =='/') {
                continue;
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
                    case 6:
                        level_ = ReadLevel(line);
                        break;
                    case 7:
                        stars_ = ReadStars(line);
                        break;
                    case 8:
                        highscore_file_ = ReadHighScoreFile(line);
                        break;
                    default:
                        break;
                    
                }
            }
            
	    }
	}
}

