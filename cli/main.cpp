#include "iostream"

#include "filesystem.h"
#include "development.h"
#include "iostream"

int main(int argc, char **argv) {
    //TODO good cli implementation

    if(argc == 1) {
        bosfs::printWelcomeMessage();
    } else if (argc == 3) {
        const char *name = argv[1];
        unsigned long blocks = std::stoul(argv[2]);
        bosfs::startFileSystem(name, blocks);

        std::cout << "Filesystem created" << std::endl;

    } else {
        std::cout << "demo usage: bosfs <name>" << std::endl;
    }

    return 0;
}