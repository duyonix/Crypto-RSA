#include <iostream>
#include <fstream>
#include <openssl/ssl.h>
using namespace std;

string readUntilFoundCert(fstream &f)
{
    string cert = "";
    string s;
    while (getline(f, s))
    {
        if (s.find("BEGIN CERTIFICATE") != std::string::npos)
        {
            cert = s + '\n';
            while (getline(f, s))
            {
                cert += s + '\n';
                if (s.find("END CERTIFICATE") != std::string::npos)
                {
                    break;
                }
            }
            break;
        }
    }

    return cert;
}

int main()
{
    fstream f("downloaded.txt", ios::in);

    string cert1 = readUntilFoundCert(f);
    string cert2 = readUntilFoundCert(f);

    cout << cert1 << "\n\n"
         << cert2 << endl;

    f.close();

    f = fstream("c0.pem", ios::out);
    f << cert1;
    f = fstream("c1.pem", ios::out);
    f << cert2;
}