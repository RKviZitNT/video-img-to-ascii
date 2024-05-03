#include <iostream>
#include <sstream>
#include "src/asciic.h"

int main(int argc, char** argv) {
    std::string gradient = " .:!/r(l1Z4H9W8$@";

    // " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"
    // " .:!/r(l1Z4H9W8$@"
    // " .:-=+*#%@"

    Ascii ascii(argv[1]);
    ascii.generateAscii(gradient, std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), false);

    return 0;
}