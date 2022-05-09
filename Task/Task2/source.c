#include <stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a)
{
    char *num_str = BN_bn2hex(a);
    printf("%s %s\n", msg, num_str);
    OPENSSL_free(num_str);
}

int main()
{
    // init
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *n = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *M = BN_new();
    BIGNUM *C = BN_new();

    // set value
    BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
    BN_dec2bn(&e, "65537");

    // hex encode for " A top secret!"
    BN_hex2bn(&M, "4120746f702073656372657421");

    // encrypt M: M^e mod n
    BN_mod_exp(C, M, e, n, ctx);
    printBN("Encryption Output:", C);

    // clear sensitive data
    BN_clear_free(n);
    BN_clear_free(e);
    BN_clear_free(M);
    BN_clear_free(C);

    return 0;
}