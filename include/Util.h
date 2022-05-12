//
// Created by nicks on 5/12/2022.
//

#ifndef GRAPHICS_UTIL_H
#define GRAPHICS_UTIL_H

#include <string>

/**
 * A place to store any useful utility functions that don't fit elsewhere!
 */
namespace Util {
    /**
     * Loads the contents of the specified file.
     * @param filename the filename of the file to read
     * @return the file's string contents
     */
    std::string LoadFile(const std::string& filename);
}

#endif //GRAPHICS_UTIL_H
