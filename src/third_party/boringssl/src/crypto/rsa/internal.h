﻿/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.] */

#ifndef OPENSSL_HEADER_RSA_INTERNAL_H
#define OPENSSL_HEADER_RSA_INTERNAL_H

#include <openssl/base.h>


#if defined(__cplusplus)
extern "C" {
#endif


/* Default implementations of RSA operations. */

extern const RSA_METHOD RSA_default_method;

size_t rsa_default_size(const RSA *rsa);
int rsa_default_encrypt(RSA *rsa, size_t *out_len, uint8_t *out, size_t max_out,
                        const uint8_t *in, size_t in_len, int padding);
int rsa_default_sign_raw(RSA *rsa, size_t *out_len, uint8_t *out,
                         size_t max_out, const uint8_t *in, size_t in_len,
                         int padding);
int rsa_default_decrypt(RSA *rsa, size_t *out_len, uint8_t *out, size_t max_out,
                        const uint8_t *in, size_t in_len, int padding);
int rsa_default_verify_raw(RSA *rsa, size_t *out_len, uint8_t *out,
                           size_t max_out, const uint8_t *in, size_t in_len,
                           int padding);
int rsa_default_private_transform(RSA *rsa, uint8_t *out, const uint8_t *in,
                                  size_t len);
int rsa_default_multi_prime_keygen(RSA *rsa, int bits, int num_primes,
                                   BIGNUM *e_value, BN_GENCB *cb);
int rsa_default_keygen(RSA *rsa, int bits, BIGNUM *e_value, BN_GENCB *cb);


#define RSA_PKCS1_PADDING_SIZE 11


/* BN_BLINDING flags */
#define BN_BLINDING_NO_UPDATE 0x00000001
#define BN_BLINDING_NO_RECREATE 0x00000002

BN_BLINDING *BN_BLINDING_new(const BIGNUM *A, const BIGNUM *Ai, BIGNUM *mod);
void BN_BLINDING_free(BN_BLINDING *b);
int BN_BLINDING_update(BN_BLINDING *b, BN_CTX *ctx);
int BN_BLINDING_convert(BIGNUM *n, BN_BLINDING *b, BN_CTX *ctx);
int BN_BLINDING_invert(BIGNUM *n, BN_BLINDING *b, BN_CTX *ctx);
int BN_BLINDING_convert_ex(BIGNUM *n, BIGNUM *r, BN_BLINDING *b, BN_CTX *);
int BN_BLINDING_invert_ex(BIGNUM *n, const BIGNUM *r, BN_BLINDING *b, BN_CTX *);
unsigned long BN_BLINDING_get_flags(const BN_BLINDING *);
void BN_BLINDING_set_flags(BN_BLINDING *, unsigned long);
BN_BLINDING *BN_BLINDING_create_param(
    BN_BLINDING *b, const BIGNUM *e, BIGNUM *m, BN_CTX *ctx,
    int (*bn_mod_exp)(BIGNUM *r, const BIGNUM *a, const BIGNUM *p,
                      const BIGNUM *m, BN_CTX *ctx, const BN_MONT_CTX *mont),
    const BN_MONT_CTX *mont);
BN_BLINDING *rsa_setup_blinding(RSA *rsa, BN_CTX *in_ctx);


int RSA_padding_add_PKCS1_type_1(uint8_t *to, unsigned to_len,
                                 const uint8_t *from, unsigned from_len);
int RSA_padding_check_PKCS1_type_1(uint8_t *to, unsigned to_len,
                                   const uint8_t *from, unsigned from_len);
int RSA_padding_add_PKCS1_type_2(uint8_t *to, unsigned to_len,
                                 const uint8_t *from, unsigned from_len);
int RSA_padding_check_PKCS1_type_2(uint8_t *to, unsigned to_len,
                                   const uint8_t *from, unsigned from_len);
int RSA_padding_add_PKCS1_OAEP_mgf1(uint8_t *to, unsigned to_len,
                                    const uint8_t *from, unsigned from_len,
                                    const uint8_t *param, unsigned plen,
                                    const EVP_MD *md, const EVP_MD *mgf1md);
int RSA_padding_check_PKCS1_OAEP_mgf1(uint8_t *to, unsigned to_len,
                                      const uint8_t *from, unsigned from_len,
                                      const uint8_t *param, unsigned plen,
                                      const EVP_MD *md, const EVP_MD *mgf1md);
int RSA_padding_add_none(uint8_t *to, unsigned to_len, const uint8_t *from,
                         unsigned from_len);

/* RSA_private_transform calls either the method-specific |private_transform|
 * function (if given) or the generic one. See the comment for
 * |private_transform| in |rsa_meth_st|. */
int RSA_private_transform(RSA *rsa, uint8_t *out, const uint8_t *in,
                          size_t len);


/* RSA_additional_prime contains information about the third, forth etc prime
 * in a multi-prime RSA key. */
typedef struct RSA_additional_prime_st {
  BIGNUM *prime;
  /* exp is d^{prime-1} mod prime */
  BIGNUM *exp;
  /* coeff is such that r×coeff ≡ 1 mod prime. */
  BIGNUM *coeff;

  /* Values below here are not in the ASN.1 serialisation. */

  /* r is the product of all primes (including p and q) prior to this one. */
  BIGNUM *r;
  /* mont is a |BN_MONT_CTX| modulo |prime|. */
  BN_MONT_CTX *mont;
} RSA_additional_prime;

void RSA_additional_prime_free(RSA_additional_prime *ap);


#if defined(__cplusplus)
} /* extern C */
#endif

#endif /* OPENSSL_HEADER_RSA_INTERNAL_H */
