#include <iostream>
#include <fstream>
using namespace std;

void goToTheSignature(fstream &f)
{
    // tim vi tri cuoi cung cua chuoi "Signature Algorithm"
    int pos = 0;
    string s;
    while (getline(f, s))
    {
        if (s.find("Signature Algorithm") != std::string::npos)
        {
            pos = f.tellg();
        }
    }

    f.clear();
    f.seekg(pos, ios::beg);
}

int main()
{
    fstream f("Server_AllFields.txt", ios::in);
    string signature = "";
    string s;

    goToTheSignature(f);

    while (getline(f, s))
    {
        if (s.find(":") == std::string::npos)
            break;
        signature += s + "\n";
    }

    f.close();

    f.open("signatureWithSpacesAndColons", ios::out);
    f << signature;
    f.close();
}