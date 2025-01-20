//
// Created by Tureb on 20.01.2025.
//

#ifdef BOSFS_SOLUTION_NATIVE_INFILE

#include <cstdio>

#include "vector"
#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem> // C++17

#include "native-infile.h"

#include "bosfs_exceptions.h"
#include "filesystem.h"


/*
 * This file contains the implementation of the two primary filesystem functions.
 * loadBlock and saveBlock.
 *
 * This implementation will use a simple file to store the filesystem data.
 */

namespace bosfs {

    // native fs implementation
    void saveBlock(const bosfs::FileSystem &fs, const bosfs::Block &block) {
        native::Container &container = native::getContainer(fs);
        FILE *file = container.file;
        fseek(file, fs.startByte + block.blockNumber * BOSFS_BLOCK_SIZE, SEEK_SET);
        fwrite(block.data, BOSFS_BLOCK_SIZE, 1, file);
    }

    //native fs implementation
    bosfs::Block loadBlock(const bosfs::FileSystem &fs, bosfs::Address address) {
        native::Container &container = native::getContainer(fs);
        FILE *file = container.file;
        fseek(file, fs.startByte + address * BOSFS_BLOCK_SIZE, SEEK_SET);
        Block block;
        fread(block.data, BOSFS_BLOCK_SIZE, 1, file);
        block.blockNumber = address;
        return block;
    }

    /**
     * This will use a file in the .bosfs directory to store the filesystem data.
     * @param fsName
     * @return
     */
    [[maybe_unused]] FileSystem *startFileSystem(const char *fsName, unsigned long blocks) {
        ensureDirectoryExists(".bosfs");

        std::filesystem::path path(".bosfs");
        path.append(fsName);
        path.replace_extension(".bosfs");

        const wchar_t *cPath = path.native().c_str();
        char pathChar[260];
        wcstombs(pathChar, cPath, 260);
        auto *fs = new FileSystem();
        FILE *file = fopen(pathChar, "rb+");
        if (file == nullptr) {
            //initialize file
            file = fopen(pathChar, "wb+");

            initializeNativeInfile(file, fs, blocks);
        }

        if (file == nullptr) {
            throw BosfsFileSystemException("Could not open or create filesystem file");
        }


        strcpy(fs->fsName, fsName);

        return fs;

    }



    void initializeNativeInfile(FILE *file, FileSystem *fs, unsigned long blocks) {
        //check if file is empty
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        if (size == 0) {
            //initialize filesystem
            fs->startByte = sizeof(FileSystem);
            fs->indexTable = IndexTable();
            fwrite(fs, sizeof(FileSystem), 1, file);

            //write
            fputc(BOSFS_NATIVE_STARTBYTE, file);

            // write empty blocks
            for (unsigned long i = 0; i < blocks; i++) {
                BlockData data{0b00};
                fwrite(data, BOSFS_BLOCK_SIZE, 1, file);
            }

            //write endbyte
            fputc(BOSFS_NATIVE_ENDBYTE, file);
        }
    }


    /**
     * Checks if the directory exists and creates it if it does not.
     * @param dir
     */
    void ensureDirectoryExists(const char *dir) {
        std::filesystem::path path(dir);
        std::filesystem::create_directories(path);
    }

    void closeFileSystem(FileSystem *fs) {

    }

    native::Container &native::getContainer(const FileSystem &fs) {
        for (auto &container: openFileSystems) {
            if (container.fs == &fs) { //compare by address
                return container;
            }
        }
        throw BosfsFileSystemException("Filesystem not found");
    }
}


#endif
