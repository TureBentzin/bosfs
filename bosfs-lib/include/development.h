//
// Created by Tureb on 20.01.2025.
//

#ifndef BOSFS_DEVELOPMENT_H
#define BOSFS_DEVELOPMENT_H

#include <iostream>

#warning "This is a development version of the library. Do not use in production."

#ifdef _WIN32
#    ifdef BOSFS_LIB_EXPORTS
#        define BOSFS_API __declspec(dllexport)
#    else
#        define BOSFS_API __declspec(dllimport)
#    endif
#else
#    define BOSFS_API
#endif

namespace bosfs {
    void printWelcomeMessage();
}

#endif //BOSFS_DEVELOPMENT_H
