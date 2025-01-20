//
// Created by Tureb on 20.01.2025.
//

#ifndef BOSFS_BOSFS_EXCEPTIONS_H
#define BOSFS_BOSFS_EXCEPTIONS_H

#include <exception>

class BosfsException : public std::exception {
public:
    const char *message;
    explicit BosfsException(const char *message) : message(message) {}

    const char *what() const noexcept override {
        return message;
    }
};

class BosfsFileSystemException : public BosfsException {
public:
    explicit BosfsFileSystemException(const char *message) : BosfsException(message) {}
};

#endif //BOSFS_BOSFS_EXCEPTIONS_H
