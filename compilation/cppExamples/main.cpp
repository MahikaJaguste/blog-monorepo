#include <iostream>
#include <iomanip>
#include <sstream>
#include "mylib.hpp"
#include "mylibalso.hpp"

int main() {
    unsigned char hash[32];
    // Using mylib to hash data
    hash_data(reinterpret_cast<const unsigned char*>("Hello, World!"), 13, hash);

    // Convert the hash to a hex string for display
    std::stringstream ss;
    for (int i = 0; i < 32; i++) {
        ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(hash[i]);
    }
    std::cout << "SHA256 Hash: " << ss.str() << "\n";

    return 0;
}
