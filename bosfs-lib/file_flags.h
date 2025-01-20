//
// Created by Tureb on 20.01.2025.
//

#ifndef BOSFS_FILE_FLAGS_H
#define BOSFS_FILE_FLAGS_H

/**
 * This file contains macros to read and write file flags.
 *
 * Flags are stored in the index table of the filesystem alongside the file name and location.
 * The flags are stored in 2 bytes and can be read and written using the macros in this file.
 *
 * By defining BOSFS_FILE_FLAGS_EXTENDED, the amount of flags can be extended to 4 bytes.
 */

#define BOSFS_FLAG_READ 0b00000001 //allows reading the file (set by default)
#define BOSFS_FLAG_WRITE 0b00000010 //allows writing to the file (set by default)
#define BOSFS_FLAG_EXEC 0b00000100 //allows executing the file (set by default)
#define BOSFS_FLAG_HIDDEN 0b00001000 //hides the file from directory listings (to be implemented)
#define BOSFS_FLAG_SYSTEM 0b00010000 //marks the file as a system file (to be implemented)
#define BOSFS_FLAG_READONLY 0b00100000 //prevents writing to the file

#define BOSFS_FLAG_RESERVED_0 0b01000000 // reserved for future use
#define BOSFS_FLAG_RESERVED_1 0b10000000 // reserved for future use

#ifdef BOSFS_FILE_FLAGS_EXTENDED
#define BOSFS_FLAG_RESERVED_2 0b0000000100000000 // reserved for future use
#define BOSFS_FLAG_RESERVED_3 0b0000001000000000 // reserved for future use
#define BOSFS_FLAG_RESERVED_4 0b0000010000000000 // reserved for future use
#define BOSFS_FLAG_RESERVED_5 0b0000100000000000 // reserved for future use
#define BOSFS_FLAG_RESERVED_6 0b0001000000000000 // reserved for future use
#define BOSFS_FLAG_RESERVED_7 0b0010000000000000 // reserved for future use
#define BOSFS_FLAG_RESERVED_8 0b0100000000000000 // reserved for future use
#define BOSFS_FLAG_RESERVED_9 0b1000000000000000 // reserved for future use
#endif

#endif //BOSFS_FILE_FLAGS_H