#include <iostream>
#include <cstring>
#include <string>
#include <openssl/bn.h>
#define NBITS 128
using namespace std;

void printBN(string msg, BIGNUM *a)
{
    char message[msg.size() + 1];
    strcpy(message, msg.c_str());
    char *num_str = BN_bn2hex(a);

    cout << msg << " " << num_str << endl;
    OPENSSL_free(num_str);
}

int main()
{
    // init
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *n = BN_new();
    BIGNUM *d = BN_new();
    BIGNUM *M1 = BN_new();
    BIGNUM *M2 = BN_new();
    BIGNUM *C1 = BN_new();
    BIGNUM *C2 = BN_new();

    // set value
    BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
    BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");

    // hex encode for "I owe you $2000"
    BN_hex2bn(&M1, "49206f776520796f75202432303030");

    // hex encode for "I owe you $3000"
    BN_hex2bn(&M2, "49206f776520796f75202433303030");

    // encrypt M: M^d mod n
    BN_mod_exp(C1, M1, d, n, ctx);
    BN_mod_exp(C2, M2, d, n, ctx);
    printBN("M1 Signature Output:", C1);
    printBN("M2 Signature Output:", C2);

    // clear sensitive data
    BN_clear_free(n);
    BN_clear_free(d);
    BN_clear_free(M1);
    BN_clear_free(M2);
    BN_clear_free(C1);
    BN_clear_free(C2);

    return 0;
}