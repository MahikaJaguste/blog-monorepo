#include "mylib.hpp"
#include <openssl/sha.h>

int MYLIB_VERSION = 1000;

int get_mylib_version() {
    return MYLIB_VERSION;
}

void hash_data(const unsigned char* data, size_t len, unsigned char* out) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, data, len);
    SHA256_Final(out, &ctx);
}