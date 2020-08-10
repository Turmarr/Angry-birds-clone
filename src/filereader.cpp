#include "filereader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

void ReadPigs(std::string line) {
    
}


Filereader::Filereader(std::string filename) {
    std::ifstream file(filename);

    int block_no = 0;

    if (file.rdstate() & (file.failbit | file.badbit)) {
	    // output error to stderr stream
	    std::cerr << "Failed" << std::endl;
	} else {
	    // repeat until end of file
	    while (!file.eof()) {
		    std::string line;
		    std::getline(file, line);
		    std::cout << line << std::endl;
            
            if (line[0] == '#') {
                block_no++;
            }
            else {
                switch (block_no) {
                    case 1:
                        ReadPigs(line);
                    case 2:
                    case 3:
                }
            }



	    }
	}
}

