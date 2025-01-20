//
// Created by Tureb on 20.01.2025.
//

#ifndef BOSFS_FILESYSTEM_H
#define BOSFS_FILESYSTEM_H


#ifndef BOSFS_BLOCK_SIZE
#define BOSFS_BLOCK_SIZE 64 // 64 bytes
#endif

#ifndef BOSFS_FILE_NAME_MAXLENGTH
#define BOSFS_FILE_NAME_MAXLENGTH 256
#endif

#ifndef BOSFS_FILE_MAXBLOCKS
/*
 * should be a multiple of BOSFS_BLOCK
 * suggested: 10GB / 64B = 160000000 blocks
 */
#define BOSFS_FILE_MAXBLOCKS 160000000
#endif

#ifndef BOSFS_FILE_MAXAMOUNT
#define BOSFS_FILE_MAXAMOUNT BOSFS_FILE_MAXBLOCKS
#endif

#include "mutex"

namespace bosfs {

    /**
     * the filesystem is protected by a lockfile externally and internally by a mutex
     */

    std::mutex mutex;

    /**
     * Typedef for a block of data.
     * This represents the minimum unit of data that can be read or written to the filesystem.
     * The size of a block is defined by BOSFS_BLOCK_SIZE.
     *
     * @see BOSFS_BLOCK_SIZE
     */
    typedef char BlockData[BOSFS_BLOCK_SIZE];

    /**
     * Typedef for a bosfs block.
     * Contains the data of the block and the block number.
     *
     * Block numbers are guaranteed to be unique within the filesystem.
     */
    struct Block {
        BlockData data;
        unsigned int blockNumber;
    };


    /**
     * Typedef for the flag container
     */
#ifndef BOSFS_FILE_FLAGS_EXTENDED
    typedef unsigned short FileFlags;
#else
    typedef unsigned int FileFlags;
#endif


    /**
     * Typedef for a file.
     * Contains the name of the file and the block numbers of the blocks that contain the file's data.
     */
    struct File {
        /**
         * name is stored in following format:
         * /path/to/file.ext
         * terminated by \0
         * the name does not contain the leading / (hidden character)
         */
        char name[BOSFS_FILE_NAME_MAXLENGTH]; // 256 bytes
        FileFlags flags; // 0b00000000 - will be implemented later
        unsigned int startBlock; // 4 bytes
        unsigned int blockCount; // 4 bytes
    };


    /**
     * Index table at the top of the filesystem.
     *
     * Estimated size: 160000000 files * (256 + 4 + 4 + 2) Byte = 42.5 GB
     */
    struct IndexTable {
        File files[BOSFS_FILE_MAXBLOCKS]; // 160000000 files
    };

    /**
     * BOSFS uses virtual addresses to access blocks of data.
     * The address is a 64-bit unsigned integer. (8 bytes)
     *
     * Address describes the address type used in the filesystem.
     */
    typedef unsigned long long Address;


    struct FileSystem {
        IndexTable indexTable;
        unsigned long long startByte; // the start byte of the filesystem (alw

    };



    //inline functions

    /**
     * Checks if the file has the given flag set.
     * Flags can be found in file_flags.h
     * @param file file
     * @param flags
     * @return
     */
    inline bool checkFlag(const File &file, const FileFlags flags) {
        //example: checkFlag(file, 0b00000001) -> checks if the file has the flag 0b00000001 set
        return (file.flags & flags) == flags;
    }

    inline unsigned short setFlag(File &file, const FileFlags flags) {
        //example: setFlag(file, 0b00000001) -> sets the flag 0b00000001 for the file
        return file.flags |= flags;
    }




    // functions

    Block loadBlock(const FileSystem &fs, Address address);

    void saveBlock(const FileSystem &fs, const Block &block);



}

#endif //BOSFS_FILESYSTEM_H
