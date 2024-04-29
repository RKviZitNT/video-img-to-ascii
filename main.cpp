#include <iostream>
#include <sstream>
#include"src/imgasciic.h"

int main(int argc, char** argv) {
    std::string gradient = " .:!/r(l1Z4H9W8$@";

    // " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"
    // " .:!/r(l1Z4H9W8$@"
    // " .:-=+*#%@"

    Image image(argv[1]);
    image.generateAsciiImg(std::stoi(argv[2]), gradient, false);
    image.write_to_terminal();

    return 0;
}