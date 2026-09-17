#include <iostream>
#include <iomanip>
#include <sstream>
#include "mylib.hpp"

int main() {
    unsigned char hash[32];
    hash_data(reinterpret_cast<const unsigned char*>("Hello, World!"), 13, hash);

    std::stringstream ss;
    for (int i = 0; i < 32; i++) {
        ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(hash[i]);
    }
    std::cout << "SHA256 hash: " << ss.str() << "\n";
}
