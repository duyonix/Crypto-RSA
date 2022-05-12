#include <iostream>
#include <fstream>
#include <openssl/bn.h>
using namespace std;

void printBN(string msg, BIGNUM *a)
{
    char *number_str = BN_bn2hex(a);
    cout << msg << number_str << "\n\n";
    OPENSSL_free(number_str);
}

void getPublicKey(BIGNUM *&n, BIGNUM *&e)
{
    fstream f("publicKey.txt", ios::in);
    string temp;
    f >> temp;
    BN_hex2bn(&n, temp.c_str());
    f >> temp;
    BN_dec2bn(&e, temp.c_str());
    f.close();
}

void getSignature(BIGNUM *&S)
{
    fstream f("signature", ios::in);
    string temp;
    f >> temp;
    BN_hex2bn(&S, temp.c_str());
    f.close();
}

void getPaddedHashedMessage(BIGNUM *&M)
{
    fstream f("c0_body_sha256.txt", ios::in);
    string serverCertBodyHashed;
    f >> serverCertBodyHashed;
    f.close();

    string prefix = "0001";
    string A = "3031300D060960864801650304020105000420"; // SHA-256 DER Encoding, https://datatracker.ietf.org/doc/html/rfc3447, page 42
    int totalLength = 256;                               // vi kich thuoc cua n va signature deu la 256

    int padLength = totalLength - 1 - (A.length() + prefix.length() + serverCertBodyHashed.length()) / 2;
    string padString = "";
    for (int i = 0; i < padLength; i++)
        padString += "FF";

    string serverCertBodyPadded = prefix + padString + "00" + A + serverCertBodyHashed;
    BN_hex2bn(&M, serverCertBodyPadded.c_str());
}

int main()
{
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *n = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *M = BN_new();
    BIGNUM *mr = BN_new();
    BIGNUM *S = BN_new();

    getPublicKey(n, e);
    getSignature(S);

    getPaddedHashedMessage(M);
    printBN("Padded hashed server certificate body:\n", M);

    BN_mod_exp(mr, S, e, n, ctx);
    printBN("mr:\n", M);

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
}