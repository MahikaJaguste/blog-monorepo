#include "mylib.hpp"
#include <openssl/sha.h>

void hash_data(const unsigned char* data, size_t len, unsigned char* out) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, data, len);
    SHA256_Final(out, &ctx);
}
