#include <iostream>
#include <sstream>
#include "src/asciic.h"

int main(int argc, char** argv) {
    std::string gradient = " .:!/r(l1Z4H9W8$@";

    // " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"
    // " .:!/r(l1Z4H9W8$@"
    // " .:-=+*#%@"

    Image ascii("D:\\Galery\\Images\\Saved\\Sea-of-thieves-logo.jpg");//argv[0]);
    ascii.generateAsciiImg(gradient, 50, 150, 70, false);//std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), false);
    ascii.write_to_terminal();

    return 0;
}