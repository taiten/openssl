/*
 * Copyright 2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL licenses, (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * https://www.openssl.org/source/license.html
 * or in the file LICENSE in the source distribution.
 */

/*
 * Fuzz ASN.1 parsing for various data structures. Specify which on the
 * command line:
 *
 * asn1 <data structure>
 */

#include <stdio.h>
#include <string.h>
#include <openssl/asn1.h>
#include <openssl/asn1t.h>
#include <openssl/ec.h>
#include <openssl/ocsp.h>
#include <openssl/pkcs12.h>
#include <openssl/ts.h>
#include <openssl/x509v3.h>
#include "fuzzer.h"

static ASN1_ITEM_EXP *item_type[] = {
    ASN1_ITEM_ref(ASN1_SEQUENCE),
    ASN1_ITEM_ref(AUTHORITY_INFO_ACCESS),
    ASN1_ITEM_ref(BIGNUM),
    ASN1_ITEM_ref(ECPARAMETERS),
    ASN1_ITEM_ref(ECPKPARAMETERS),
    ASN1_ITEM_ref(GENERAL_NAME),
    ASN1_ITEM_ref(GENERAL_SUBTREE),
    ASN1_ITEM_ref(NAME_CONSTRAINTS),
    ASN1_ITEM_ref(OCSP_BASICRESP),
    ASN1_ITEM_ref(OCSP_RESPONSE),
    ASN1_ITEM_ref(PKCS12),
    ASN1_ITEM_ref(PKCS12_AUTHSAFES),
    ASN1_ITEM_ref(PKCS12_SAFEBAGS),
    ASN1_ITEM_ref(PKCS7),
    ASN1_ITEM_ref(PKCS7_ATTR_SIGN),
    ASN1_ITEM_ref(PKCS7_ATTR_VERIFY),
    ASN1_ITEM_ref(PKCS7_DIGEST),
    ASN1_ITEM_ref(PKCS7_ENC_CONTENT),
    ASN1_ITEM_ref(PKCS7_ENCRYPT),
    ASN1_ITEM_ref(PKCS7_ENVELOPE),
    ASN1_ITEM_ref(PKCS7_RECIP_INFO),
    ASN1_ITEM_ref(PKCS7_SIGN_ENVELOPE),
    ASN1_ITEM_ref(PKCS7_SIGNED),
    ASN1_ITEM_ref(PKCS7_SIGNER_INFO),
    ASN1_ITEM_ref(POLICY_CONSTRAINTS),
    ASN1_ITEM_ref(POLICY_MAPPINGS),
    ASN1_ITEM_ref(SXNET),
    /*ASN1_ITEM_ref(TS_RESP),  want to do this, but type is hidden, however d2i exists... */
    ASN1_ITEM_ref(X509),
    ASN1_ITEM_ref(X509_CRL),
    NULL
};

int FuzzerInitialize(int *argc, char ***argv) {
    return 1;
}

int FuzzerTestOneInput(const uint8_t *buf, size_t len) {
    int n;

    for (n = 0; item_type[n] != NULL; ++n) {
        const uint8_t *b = buf;
        const ASN1_ITEM *i = ASN1_ITEM_ptr(item_type[n]);
        ASN1_VALUE *o = ASN1_item_d2i(NULL, &b, len, i);
        ASN1_item_free(o, i);
    }
    return 0;
}
