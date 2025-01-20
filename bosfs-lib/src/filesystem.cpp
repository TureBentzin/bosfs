//
// Created by Tureb on 20.01.2025.
//

#include "filesystem.h"


unsigned int bosfs::countFiles(const bosfs::IndexTable &indexTable) {
    unsigned int count = 0;
    for (const auto &file: indexTable.files) {
        if (!checkIfFree(file)) {
            count++;
        }
    }
    return count;
}
