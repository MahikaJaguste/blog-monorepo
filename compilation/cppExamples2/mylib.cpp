// #include "mylib.hpp"
// #include <openssl/sha.h>

// void hash_data(const unsigned char* data, size_t len, unsigned char* out) {
//     SHA256_CTX ctx;
//     SHA256_Init(&ctx);
//     SHA256_Update(&ctx, data, len);
//     SHA256_Final(out, &ctx);
// }

#include "mylib.hpp"
#include <openssl/evp.h>


static EVP_MD_CTX* global_ctx = nullptr;

EVP_MD_CTX* get_ctx() {
    return global_ctx;
}

void hash_data(const unsigned char* data, size_t len, unsigned char* out) {
    global_ctx = EVP_MD_CTX_new();   // allocated using OpenSSL 1.1.1
    EVP_DigestInit_ex(global_ctx, EVP_sha256(), nullptr);
    EVP_DigestUpdate(global_ctx, data, len);
    EVP_DigestFinal_ex(global_ctx, out, nullptr);
}