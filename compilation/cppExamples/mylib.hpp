#pragma once
#include <cstddef>
#include <openssl/evp.h>   // REQUIRED so EVP_MD_CTX is visible

EVP_MD_CTX* get_ctx();
void hash_data(const unsigned char* data, size_t len, unsigned char* out);
