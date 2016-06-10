/*
 * Copyright 2005-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <openssl/whrlpool.h>
#include <openssl/crypto.h>

#if defined(OPENSSL_NO_WHIRLPOOL)
int main(int argc, char *argv[])
{
    printf("No Whirlpool support\n");
    return (0);
}
#else

/* ISO/IEC 10118-3 test vector set */
static const unsigned char iso_test_1[WHIRLPOOL_DIGEST_LENGTH] = {
    0x19, 0xFA, 0x61, 0xD7, 0x55, 0x22, 0xA4, 0x66,
    0x9B, 0x44, 0xE3, 0x9C, 0x1D, 0x2E, 0x17, 0x26,
    0xC5, 0x30, 0x23, 0x21, 0x30, 0xD4, 0x07, 0xF8,
    0x9A, 0xFE, 0xE0, 0x96, 0x49, 0x97, 0xF7, 0xA7,
    0x3E, 0x83, 0xBE, 0x69, 0x8B, 0x28, 0x8F, 0xEB,
    0xCF, 0x88, 0xE3, 0xE0, 0x3C, 0x4F, 0x07, 0x57,
    0xEA, 0x89, 0x64, 0xE5, 0x9B, 0x63, 0xD9, 0x37,
    0x08, 0xB1, 0x38, 0xCC, 0x42, 0xA6, 0x6E, 0xB3
};

static const unsigned char iso_test_2[WHIRLPOOL_DIGEST_LENGTH] = {
    0x8A, 0xCA, 0x26, 0x02, 0x79, 0x2A, 0xEC, 0x6F,
    0x11, 0xA6, 0x72, 0x06, 0x53, 0x1F, 0xB7, 0xD7,
    0xF0, 0xDF, 0xF5, 0x94, 0x13, 0x14, 0x5E, 0x69,
    0x73, 0xC4, 0x50, 0x01, 0xD0, 0x08, 0x7B, 0x42,
    0xD1, 0x1B, 0xC6, 0x45, 0x41, 0x3A, 0xEF, 0xF6,
    0x3A, 0x42, 0x39, 0x1A, 0x39, 0x14, 0x5A, 0x59,
    0x1A, 0x92, 0x20, 0x0D, 0x56, 0x01, 0x95, 0xE5,
    0x3B, 0x47, 0x85, 0x84, 0xFD, 0xAE, 0x23, 0x1A
};

static const unsigned char iso_test_3[WHIRLPOOL_DIGEST_LENGTH] = {
    0x4E, 0x24, 0x48, 0xA4, 0xC6, 0xF4, 0x86, 0xBB,
    0x16, 0xB6, 0x56, 0x2C, 0x73, 0xB4, 0x02, 0x0B,
    0xF3, 0x04, 0x3E, 0x3A, 0x73, 0x1B, 0xCE, 0x72,
    0x1A, 0xE1, 0xB3, 0x03, 0xD9, 0x7E, 0x6D, 0x4C,
    0x71, 0x81, 0xEE, 0xBD, 0xB6, 0xC5, 0x7E, 0x27,
    0x7D, 0x0E, 0x34, 0x95, 0x71, 0x14, 0xCB, 0xD6,
    0xC7, 0x97, 0xFC, 0x9D, 0x95, 0xD8, 0xB5, 0x82,
    0xD2, 0x25, 0x29, 0x20, 0x76, 0xD4, 0xEE, 0xF5
};

static const unsigned char iso_test_4[WHIRLPOOL_DIGEST_LENGTH] = {
    0x37, 0x8C, 0x84, 0xA4, 0x12, 0x6E, 0x2D, 0xC6,
    0xE5, 0x6D, 0xCC, 0x74, 0x58, 0x37, 0x7A, 0xAC,
    0x83, 0x8D, 0x00, 0x03, 0x22, 0x30, 0xF5, 0x3C,
    0xE1, 0xF5, 0x70, 0x0C, 0x0F, 0xFB, 0x4D, 0x3B,
    0x84, 0x21, 0x55, 0x76, 0x59, 0xEF, 0x55, 0xC1,
    0x06, 0xB4, 0xB5, 0x2A, 0xC5, 0xA4, 0xAA, 0xA6,
    0x92, 0xED, 0x92, 0x00, 0x52, 0x83, 0x8F, 0x33,
    0x62, 0xE8, 0x6D, 0xBD, 0x37, 0xA8, 0x90, 0x3E
};

static const unsigned char iso_test_5[WHIRLPOOL_DIGEST_LENGTH] = {
    0xF1, 0xD7, 0x54, 0x66, 0x26, 0x36, 0xFF, 0xE9,
    0x2C, 0x82, 0xEB, 0xB9, 0x21, 0x2A, 0x48, 0x4A,
    0x8D, 0x38, 0x63, 0x1E, 0xAD, 0x42, 0x38, 0xF5,
    0x44, 0x2E, 0xE1, 0x3B, 0x80, 0x54, 0xE4, 0x1B,
    0x08, 0xBF, 0x2A, 0x92, 0x51, 0xC3, 0x0B, 0x6A,
    0x0B, 0x8A, 0xAE, 0x86, 0x17, 0x7A, 0xB4, 0xA6,
    0xF6, 0x8F, 0x67, 0x3E, 0x72, 0x07, 0x86, 0x5D,
    0x5D, 0x98, 0x19, 0xA3, 0xDB, 0xA4, 0xEB, 0x3B
};

static const unsigned char iso_test_6[WHIRLPOOL_DIGEST_LENGTH] = {
    0xDC, 0x37, 0xE0, 0x08, 0xCF, 0x9E, 0xE6, 0x9B,
    0xF1, 0x1F, 0x00, 0xED, 0x9A, 0xBA, 0x26, 0x90,
    0x1D, 0xD7, 0xC2, 0x8C, 0xDE, 0xC0, 0x66, 0xCC,
    0x6A, 0xF4, 0x2E, 0x40, 0xF8, 0x2F, 0x3A, 0x1E,
    0x08, 0xEB, 0xA2, 0x66, 0x29, 0x12, 0x9D, 0x8F,
    0xB7, 0xCB, 0x57, 0x21, 0x1B, 0x92, 0x81, 0xA6,
    0x55, 0x17, 0xCC, 0x87, 0x9D, 0x7B, 0x96, 0x21,
    0x42, 0xC6, 0x5F, 0x5A, 0x7A, 0xF0, 0x14, 0x67
};

static const unsigned char iso_test_7[WHIRLPOOL_DIGEST_LENGTH] = {
    0x46, 0x6E, 0xF1, 0x8B, 0xAB, 0xB0, 0x15, 0x4D,
    0x25, 0xB9, 0xD3, 0x8A, 0x64, 0x14, 0xF5, 0xC0,
    0x87, 0x84, 0x37, 0x2B, 0xCC, 0xB2, 0x04, 0xD6,
    0x54, 0x9C, 0x4A, 0xFA, 0xDB, 0x60, 0x14, 0x29,
    0x4D, 0x5B, 0xD8, 0xDF, 0x2A, 0x6C, 0x44, 0xE5,
    0x38, 0xCD, 0x04, 0x7B, 0x26, 0x81, 0xA5, 0x1A,
    0x2C, 0x60, 0x48, 0x1E, 0x88, 0xC5, 0xA2, 0x0B,
    0x2C, 0x2A, 0x80, 0xCF, 0x3A, 0x9A, 0x08, 0x3B
};

static const unsigned char iso_test_8[WHIRLPOOL_DIGEST_LENGTH] = {
    0x2A, 0x98, 0x7E, 0xA4, 0x0F, 0x91, 0x70, 0x61,
    0xF5, 0xD6, 0xF0, 0xA0, 0xE4, 0x64, 0x4F, 0x48,
    0x8A, 0x7A, 0x5A, 0x52, 0xDE, 0xEE, 0x65, 0x62,
    0x07, 0xC5, 0x62, 0xF9, 0x88, 0xE9, 0x5C, 0x69,
    0x16, 0xBD, 0xC8, 0x03, 0x1B, 0xC5, 0xBE, 0x1B,
    0x7B, 0x94, 0x76, 0x39, 0xFE, 0x05, 0x0B, 0x56,
    0x93, 0x9B, 0xAA, 0xA0, 0xAD, 0xFF, 0x9A, 0xE6,
    0x74, 0x5B, 0x7B, 0x18, 0x1C, 0x3B, 0xE3, 0xFD
};

static const unsigned char iso_test_9[WHIRLPOOL_DIGEST_LENGTH] = {
    0x0C, 0x99, 0x00, 0x5B, 0xEB, 0x57, 0xEF, 0xF5,
    0x0A, 0x7C, 0xF0, 0x05, 0x56, 0x0D, 0xDF, 0x5D,
    0x29, 0x05, 0x7F, 0xD8, 0x6B, 0x20, 0xBF, 0xD6,
    0x2D, 0xEC, 0xA0, 0xF1, 0xCC, 0xEA, 0x4A, 0xF5,
    0x1F, 0xC1, 0x54, 0x90, 0xED, 0xDC, 0x47, 0xAF,
    0x32, 0xBB, 0x2B, 0x66, 0xC3, 0x4F, 0xF9, 0xAD,
    0x8C, 0x60, 0x08, 0xAD, 0x67, 0x7F, 0x77, 0x12,
    0x69, 0x53, 0xB2, 0x26, 0xE4, 0xED, 0x8B, 0x01
};

int main(int argc, char *argv[])
{
    unsigned char md[WHIRLPOOL_DIGEST_LENGTH];
    int i;
    WHIRLPOOL_CTX ctx;

# ifdef OPENSSL_IA32_SSE2
    /*
     * Alternative to this is to call OpenSSL_add_all_algorithms... The below
     * code is retained exclusively for debugging purposes.
     */
    {
        char *env;

        if ((env = getenv("OPENSSL_ia32cap")))
            OPENSSL_ia32cap = strtoul(env, NULL, 0);
    }
# endif

    fprintf(stdout, "Testing Whirlpool ");

    WHIRLPOOL("", 0, md);
    if (memcmp(md, iso_test_1, sizeof(iso_test_1))) {
        fflush(stdout);
        fprintf(stderr, "\nTEST 1 of 9 failed.\n");
        return 1;
    } else
        fprintf(stdout, ".");
    fflush(stdout);

    WHIRLPOOL("a", 1, md);
    if (memcmp(md, iso_test_2, sizeof(iso_test_2))) {
        fflush(stdout);
        fprintf(stderr, "\nTEST 2 of 9 failed.\n");
        return 1;
    } else
        fprintf(stdout, ".");
    fflush(stdout);

    WHIRLPOOL("abc", 3, md);
    if (memcmp(md, iso_test_3, sizeof(iso_test_3))) {
        fflush(stdout);
        fprintf(stderr, "\nTEST 3 of 9 failed.\n");
        return 1;
    } else
        fprintf(stdout, ".");
    fflush(stdout);

    WHIRLPOOL("message digest", 14, md);
    if (memcmp(md, iso_test_4, sizeof(iso_test_4))) {
        fflush(stdout);
        fprintf(stderr, "\nTEST 4 of 9 failed.\n");
        return 1;
    } else
        fprintf(stdout, ".");
    fflush(stdout);

    WHIRLPOOL("abcdefghijklmnopqrstuvwxyz", 26, md);
    if (memcmp(md, iso_test_5, sizeof(iso_test_5))) {
        fflush(stdout);
        fprintf(stderr, "\nTEST 5 of 9 failed.\n");
        return 1;
    } else
        fprintf(stdout, ".");
    fflush(stdout);

    WHIRLPOOL("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
              "abcdefghijklmnopqrstuvwxyz" "0123456789", 62, md);
    if (memcmp(md, iso_test_6, sizeof(iso_test_6))) {
        fflush(stdout);
        fprintf(stderr, "\nTEST 6 of 9 failed.\n");
        return 1;
    } else
        fprintf(stdout, ".");
    fflush(stdout);

    WHIRLPOOL("1234567890" "1234567890" "1234567890" "1234567890"
              "1234567890" "1234567890" "1234567890" "1234567890", 80, md);
    if (memcmp(md, iso_test_7, sizeof(iso_test_7))) {
        fflush(stdout);
        fprintf(stderr, "\nTEST 7 of 9 failed.\n");
        return 1;
    } else
        fprintf(stdout, ".");
    fflush(stdout);

    WHIRLPOOL("abcdbcdecdefdefgefghfghighijhijk", 32, md);
    if (memcmp(md, iso_test_8, sizeof(iso_test_8))) {
        fflush(stdout);
        fprintf(stderr, "\nTEST 8 of 9 failed.\n");
        return 1;
    } else
        fprintf(stdout, ".");
    fflush(stdout);

    WHIRLPOOL_Init(&ctx);
    for (i = 0; i < 1000000; i += 288)
        WHIRLPOOL_Update(&ctx, "aaaaaaaa" "aaaaaaaa" "aaaaaaaa" "aaaaaaaa"
                         "aaaaaaaa" "aaaaaaaa" "aaaaaaaa" "aaaaaaaa"
                         "aaaaaaaa" "aaaaaaaa" "aaaaaaaa" "aaaaaaaa"
                         "aaaaaaaa" "aaaaaaaa" "aaaaaaaa" "aaaaaaaa"
                         "aaaaaaaa" "aaaaaaaa" "aaaaaaaa" "aaaaaaaa"
                         "aaaaaaaa" "aaaaaaaa" "aaaaaaaa" "aaaaaaaa"
                         "aaaaaaaa" "aaaaaaaa" "aaaaaaaa" "aaaaaaaa"
                         "aaaaaaaa" "aaaaaaaa" "aaaaaaaa" "aaaaaaaa"
                         "aaaaaaaa" "aaaaaaaa" "aaaaaaaa" "aaaaaaaa",
                         (1000000 - i) < 288 ? 1000000 - i : 288);
    WHIRLPOOL_Final(md, &ctx);
    if (memcmp(md, iso_test_9, sizeof(iso_test_9))) {
        fflush(stdout);
        fprintf(stderr, "\nTEST 9 of 9 failed.\n");
        return 1;
    } else
        fprintf(stdout, ".");
    fflush(stdout);

    fprintf(stdout, " passed.\n");
    fflush(stdout);

    return 0;
}
#endif
