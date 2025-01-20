//
// Created by Tureb on 20.01.2025.
//

#ifndef BOSFS_NATIVE_INFILE_H
#define BOSFS_NATIVE_INFILE_H

#include "filesystem.h"

#ifndef BOSFS_NATIVE_ENDBYTE
#define BOSFS_NATIVE_ENDBYTE 0x19 // end of medium
#endif

namespace bosfs {

    namespace native {
        std::vector<FileSystem *> openFileSystems;
    }

    void saveBlock(const bosfs::FileSystem &fs, const bosfs::Block &block);

    bosfs::Block loadBlock(const bosfs::FileSystem &fs, bosfs::Address address);

    /**
     * This will use a file in the .bosfs directory to store the filesystem data.
     * @param fsName
     * @return
     */
    [[maybe_unused]] FileSystem *startFileSystem(const char *fsName);

    /**
     * Checks if the directory exists and creates it if it does not.
     * @param dir
     */
    void ensureDirectoryExists(const char *dir);

    void closeFileSystem(FileSystem *fs);

    void initializeNativeInfile(FILE *file, FileSystem *fs, unsigned long blocks);
}

#endif //BOSFS_NATIVE_INFILE_H
