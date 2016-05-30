/*
 * Copyright 2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_SSL_TEST_CTX_H
#define HEADER_SSL_TEST_CTX_H

#include <openssl/conf.h>
#include <openssl/ssl.h>

typedef enum {
    SSL_TEST_SUCCESS = 0,  /* Default */
    SSL_TEST_SERVER_FAIL,
    SSL_TEST_CLIENT_FAIL,
    SSL_TEST_INTERNAL_ERROR
} ssl_test_result_t;

typedef enum {
    SSL_TEST_VERIFY_NONE = 0, /* Default */
    SSL_TEST_VERIFY_ACCEPT_ALL,
    SSL_TEST_VERIFY_REJECT_ALL
} ssl_verify_callback_t;

typedef struct ssl_test_ctx {
    /* Test expectations. */
    /* Defaults to SUCCESS. */
    ssl_test_result_t expected_result;
    /* Alerts. 0 if no expectation. */
    /* See ssl.h for alert codes. */
    /* Alert sent by the client / received by the server. */
    int client_alert;
    /* Alert sent by the server / received by the client. */
    int server_alert;
    /* Negotiated protocol version. 0 if no expectation. */
    /* See ssl.h for protocol versions. */
    int protocol;
    /* One of a number of predefined custom callbacks. */
    ssl_verify_callback_t client_verify_callback;
} SSL_TEST_CTX;

const char *ssl_test_result_name(ssl_test_result_t result);
const char *ssl_alert_name(int alert);
const char *ssl_protocol_name(int protocol);
const char *ssl_verify_callback_name(ssl_verify_callback_t verify_callback);

/*
 * Load the test case context from |conf|.
 * See test/README.ssl_test for details on the conf file format.
 */
SSL_TEST_CTX *SSL_TEST_CTX_create(const CONF *conf, const char *test_section);

SSL_TEST_CTX *SSL_TEST_CTX_new(void);

void SSL_TEST_CTX_free(SSL_TEST_CTX *ctx);

#endif  /* HEADER_SSL_TEST_CTX_H */
