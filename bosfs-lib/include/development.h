//
// Created by Tureb on 20.01.2025.
//

#ifndef BOSFS_DEVELOPMENT_H
#define BOSFS_DEVELOPMENT_H

#include <iostream>

#warning "This is a development version of the library. Do not use in production."

namespace bosfs {
    [[maybe_unused]] inline void printWelcomeMessage() {
        std::cout << "You are using bosfs-lib" << std::endl;
    }
}

#endif //BOSFS_DEVELOPMENT_H
