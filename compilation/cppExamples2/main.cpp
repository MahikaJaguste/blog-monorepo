// #include <iostream>
// #include <iomanip>
// #include <sstream>
// #include "mylib.hpp"

// // include OpenSSL 3.x headers
// #include <openssl/sha.h>

// int main() {
//     unsigned char hash[32];
//     hash_data(reinterpret_cast<const unsigned char*>("Hello, World!"), 13, hash);

//     std::stringstream ss;
//     for (int i = 0; i < 32; i++) {
//         ss << std::hex << std::setfill('0') << std::setw(2)
//            << static_cast<int>(hash[i]);
//     }
//     std::cout << "SHA256 hash (from mylib 1.x): " << ss.str() << "\n";

//     // Now call OpenSSL 3.x directly → collision
//     unsigned char hash2[32];
//     SHA256(reinterpret_cast<const unsigned char*>("Hello, World!"), 13, hash2);

//     std::stringstream ss2;
//     for (int i = 0; i < 32; i++) {
//         ss2 << std::hex << std::setfill('0') << std::setw(2)
//             << static_cast<int>(hash2[i]);
//     }
//     std::cout << "SHA256 hash (from OpenSSL 3.x): " << ss2.str() << "\n";
// }
#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/evp.h>     // OpenSSL 3.x headers
#include "mylib.hpp"

int main() {
    unsigned char hash[32];
    hash_data(reinterpret_cast<const unsigned char*>("Hello, World!"), 13, hash);

    std::stringstream ss;
    for (int i = 0; i < 32; i++) {
        ss << std::hex << std::setfill('0') << std::setw(2)
           << static_cast<int>(hash[i]);
    }
    std::cout << "SHA256 hash: " << ss.str() << "\n";

    // Get ctx allocated by OpenSSL 1.1.1
    EVP_MD_CTX* ctx = get_ctx();

    // FREE using OpenSSL 3.x → guaranteed crash
    EVP_MD_CTX_free(ctx);

    return 0;
}
