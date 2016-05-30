/*
 * Copyright 2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include "bio_lcl.h"

BIO_METHOD *BIO_meth_new(int type, const char *name)
{
    BIO_METHOD *biom = OPENSSL_zalloc(sizeof(BIO_METHOD));

    if (biom != NULL) {
        biom->type = type;
        biom->name = name;
    }
    return biom;
}

void BIO_meth_free(BIO_METHOD *biom)
{
    OPENSSL_free(biom);
}

int (*BIO_meth_get_write(BIO_METHOD *biom)) (BIO *, const char *, int)
{
    return biom->bwrite;
}

int BIO_meth_set_write(BIO_METHOD *biom,
                       int (*bwrite) (BIO *, const char *, int))
{
    biom->bwrite = bwrite;
    return 1;
}

int (*BIO_meth_get_read(BIO_METHOD *biom)) (BIO *, char *, int)
{
    return biom->bread;
}

int BIO_meth_set_read(BIO_METHOD *biom,
                      int (*bread) (BIO *, char *, int))
{
    biom->bread = bread;
    return 1;
}

int (*BIO_meth_get_puts(BIO_METHOD *biom)) (BIO *, const char *)
{
    return biom->bputs;
}

int BIO_meth_set_puts(BIO_METHOD *biom,
                      int (*bputs) (BIO *, const char *))
{
    biom->bputs = bputs;
    return 1;
}

int (*BIO_meth_get_gets(BIO_METHOD *biom)) (BIO *, char *, int)
{
    return biom->bgets;
}

int BIO_meth_set_gets(BIO_METHOD *biom,
                      int (*bgets) (BIO *, char *, int))
{
    biom->bgets = bgets;
    return 1;
}

long (*BIO_meth_get_ctrl(BIO_METHOD *biom)) (BIO *, int, long, void *)
{
    return biom->ctrl;
}

int BIO_meth_set_ctrl(BIO_METHOD *biom,
                      long (*ctrl) (BIO *, int, long, void *))
{
    biom->ctrl = ctrl;
    return 1;
}

int (*BIO_meth_get_create(BIO_METHOD *biom)) (BIO *)
{
    return biom->create;
}

int BIO_meth_set_create(BIO_METHOD *biom, int (*create) (BIO *))
{
    biom->create = create;
    return 1;
}

int (*BIO_meth_get_destroy(BIO_METHOD *biom)) (BIO *)
{
    return biom->destroy;
}

int BIO_meth_set_destroy(BIO_METHOD *biom, int (*destroy) (BIO *))
{
    biom->destroy = destroy;
    return 1;
}

long (*BIO_meth_get_callback_ctrl(BIO_METHOD *biom)) (BIO *, int, bio_info_cb *)
{
    return biom->callback_ctrl;
}

int BIO_meth_set_callback_ctrl(BIO_METHOD *biom,
                               long (*callback_ctrl) (BIO *, int,
                                                      bio_info_cb *))
{
    biom->callback_ctrl = callback_ctrl;
    return 1;
}
