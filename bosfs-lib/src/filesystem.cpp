//
// Created by Tureb on 20.01.2025.
//

#include "filesystem.h"
#include "bosfs_exceptions.h"


unsigned int bosfs::countFiles(const bosfs::IndexTable &indexTable) {
    unsigned int count = 0;
    for (const auto &file: indexTable.files) {
        if (!checkIfFree(file)) {
            count++;
        }
    }
    return count;
}


constexpr unsigned long long calculateMaxFileSize() {
    return (uint64_t) BOSFS_FILE_MAXBLOCKS * BOSFS_BLOCK_SIZE;
}

/*
 * BOSFS Insertion Strategy:
 *
 * Files are stored in blocks of 64 bytes.
 * BOSFS prefers to store files in the available space from the back to the front.
 * Biggest files are stored first (in the back).
 * This will be enforced by calling defragment().
 * If a file is too large to be stored in the available space, a BosfsOutOfSpaceException will be thrown.
 */

void bosfs::storeNewFile(bosfs::FileSystem &fs,
                         const char *name,
                         const char *data,
                         unsigned int length) {

    if ((uint64_t) length > calculateMaxFileSize()) {
        throw BosfsFileTooLargeException();
    }

    //calculate needed blocks

    unsigned long long blocks = (length / BOSFS_BLOCK_SIZE) + 1;


}

bosfs::Address bosfs::findFreeBlocks(bosfs::FileSystem &fs, unsigned int blocks) {
    //from the back to the front

    IndexTable it = fs.indexTable;

    File *files = it.files;

    unsigned long long curr_freeBlocks = 0; //current free blocks

    //iterate through the files
    BlockMap blockMap = getBlockMap(fs);

    //iterate over blockmap to find free blocks

    for (BlockMapPart currentPart = fs.blocks / 64; currentPart >= 0; currentPart--) {
        BlockMapPart part = blockMap[currentPart];
        for (int i = 0; i < 64; i++) {
            if ((part & (1 << i)) == 0) {
                curr_freeBlocks++;
                if (curr_freeBlocks == blocks) {
                    return currentPart * 64 + i;
                }
            } else {
                curr_freeBlocks = 0;
            }
        }
    }


    delete[] blockMap;


}

uint64_t bosfs::populateBlockMap(bosfs::FileSystem &fs, bosfs::BlockMap &blockMap) {
    //if a block is not free, set the corresponding bit in the block map
    IndexTable it = fs.indexTable;

    File *files = it.files;
    uint64_t taken = 0;
    for (int i = 0; i < BOSFS_FILE_MAXAMOUNT; i++) {
        File &file = files[i];

        Address blockNumber = file.startBlock;
        unsigned long blockCount = file.blockCount;

        for (Address j = blockNumber; j < blockCount; j++) {
            blockMap[blockNumber / 64] |= 1 << (blockNumber % 64);
            blockNumber++;
            taken++;
        }
    }

    //set the rest of the bits to 0
    for (uint64_t i = taken; i < BOSFS_FILE_MAXBLOCKS; i++) {
        blockMap[i / 64] &= ~(1 << (i % 64));
    }

    //ensure to fill block bits in the last block map part with 1 (occupied) when the last block is not a multiple of 64
    if (fs.blocks % 64 != 0) {
        for (Address i = fs.blocks % 64; i < 64; i++) {
            blockMap[fs.blocks / 64] |= 1 << i;
        }
    }

    return taken;
}

[[nodiscard]] bosfs::BlockMap bosfs::getBlockMap(bosfs::FileSystem &fs) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"
    auto blockMap = new BlockMapPart[fs.blocks / 64]; //memory leak !!!
#pragma clang diagnostic pop
    populateBlockMap(fs, blockMap);
    return blockMap;
}




