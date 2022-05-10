#include <iostream>
#include <fstream>
#include <openssl/bn.h>
using namespace std;

void printBN(BIGNUM *a)
{
    char *number_str_a = BN_bn2hex(a);
    cout << number_str_a << endl;
    OPENSSL_free(number_str_a);
}

bool isNum(char c)
{
    return c >= '0' && c <= '9';
}

int getFirstNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        // gap ki tu so, thi lay tiep cac ki tu so tiep theo cho den khi gap ki tu khong phai so, ghep nhung ki tu do thanh 1 int
        if (isNum(s[i]))
        {
            int num = s[i] - '0';
            int j = i + 1;
            while (isNum(s[j]))
            {
                num = num * 10 + (s[j] - '0');
                j++;
            }
            return num;
        }
    }
    return -1;
}

int main()
{
    // get n
    fstream f("modulus.txt", ios::in);

    string s;
    f >> s;
    s = s.substr(8); // bo "Modulus="

    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *n = BN_new();
    BN_hex2bn(&n, s.c_str());

    f.close();

    // get e
    f = fstream("CA_AllFields.txt", ios::in);
    int e;

    while (getline(f, s))
    {
        // tim thay dong co chu "Exponent" thi lay so dau tien trong dong do
        if (s.find("Exponent") != std::string::npos)
        {
            e = getFirstNumber(s);
            break;
        }
    }

    f.close();

    cout << "n = ";
    printBN(n);

    cout << "\ne = " << e << endl;

    f.open("publicKey.txt", ios::out);
    f << BN_bn2hex(n) << " " << e;
    f.close();
}