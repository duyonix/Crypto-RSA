#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a)
{
    char *number_str_a = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str_a);
    OPENSSL_free(number_str_a);
}

std::string string_to_hex(const std::string &in)
{
    // https://stackoverflow.com/a/16125797
    std::stringstream ss;

    ss << std::hex << std::setfill('0');
    for (size_t i = 0; in.length() > i; ++i)
    {
        ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
    }

    return ss.str();
}

int main()
{
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *n = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *M = BN_new();
    BIGNUM *mr = BN_new();
    BIGNUM *S = BN_new();

    BN_hex2bn(&n, "AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115");
    BN_dec2bn(&e, "65537");
    BN_hex2bn(&M, string_to_hex("Launch a missile.").c_str());
    BN_hex2bn(&S, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F");

    // tinh mr = s^e mod n
    BN_mod_exp(mr, S, e, n, ctx);

    // Kiem tra mr thuoc Mr
    if (BN_cmp(mr, M) == 0)
    {
        std::cout << "Chu ky hop le \n";
    }
    else
    {
        std::cout << "Chu ky khong hop le \n";
    }

    BN_clear_free(n);
    BN_clear_free(e);
    BN_clear_free(M);
    BN_clear_free(mr);
    BN_clear_free(S);

    return 0;
}