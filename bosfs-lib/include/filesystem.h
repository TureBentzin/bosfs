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
#define BOSFS_FILE_MAXAMOUNT 256 //default: 256 files
#endif

#ifndef BOSFS_FILESYSTEM_NAME_MAXLENGTH
#define BOSFS_FILESYSTEM_NAME_MAXLENGTH 256
#endif

#include "mutex"

namespace bosfs {


    /**
     * Typedef for a block of data.
     * This represents the minimum unit of data that can be read or written to the filesystem.
     * The size of a block is defined by BOSFS_BLOCK_SIZE.
     *
     * @see BOSFS_BLOCK_SIZE
     */
    typedef char BlockData[BOSFS_BLOCK_SIZE];

    /**
     * BOSFS uses virtual addresses to access blocks of data.
     * The address is a 64-bit unsigned integer. (8 bytes)
     *
     * Address describes the address type used in the filesystem.
     */
    typedef unsigned long long Address;

    /**
     * Typedef for a bosfs block.
     * Contains the data of the block and the block number.
     *
     * Block numbers are guaranteed to be unique within the filesystem.
     */
    struct Block {
        BlockData data{};
        Address blockNumber;

        Block() {
            blockNumber = 0;
            for (char &i: data) {
                i = '\0';
            }
        }
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
    public:
        File() { // default constructor generates an empty file
            name[0] = '\0';
            flags = 0;
            startBlock = 0;
            blockCount = 0;
        }
    };


    /**
     * Index table at the top of the filesystem.
     *
     */
    struct IndexTable {
        // if a file is deleted: the name is set to \0 and other fields should be 0 but are not guaranteed
        File files[BOSFS_FILE_MAXAMOUNT];
    };

    struct FileSystem {
        char fsName[BOSFS_FILESYSTEM_NAME_MAXLENGTH]; // 256 bytes
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

    inline bool clearFlag(File &file, const FileFlags flags) {
        //example: clearFlag(file, 0b00000001) -> clears the flag 0b00000001 for the file
        return file.flags &= ~flags;
    }

    inline bool checkIfFree(const File &file) {
        return file.name[0] == '\0';
    }


    // functions


    unsigned int countFiles(const IndexTable &indexTable);

    //implemented depending on the access solution
    Block loadBlock(const FileSystem &fs, Address address);

    //implemented depending on the access solution
    void saveBlock(const FileSystem &fs, const Block &block);

    //implemented depending on the access solution
    /**
     * Initializes the filesystem.
     * @param fsName name of the filesystem
     * @param blocks amount of blocks to allocate if the filesystem is created
     * @return pointer to the filesystem
     */
    [[maybe_unused]] FileSystem *startFileSystem(const char *fsName, unsigned long blocks = 1);


}

#endif //BOSFS_FILESYSTEM_H
