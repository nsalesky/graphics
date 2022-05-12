//
// Created by nicks on 5/12/2022.
//

#include "Util.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::string Util::LoadFile(const std::string &filename) {
    std::ifstream file(filename);

    // Check for errors opening the file
    if(!file.is_open()) {
        std::cerr << "Error loading file \"" << filename << "\"" << std::endl;

        // TODO: is this the right thing to do here?
        throw std::runtime_error("Error loading file");
    }

    // Read the file into a buffer
    std::stringstream buffer;
    buffer << file.rdbuf();

    // Finally, return the buffer as a string
    return buffer.str();
}