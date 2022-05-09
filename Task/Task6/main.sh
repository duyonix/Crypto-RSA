echo 'a' | openssl s_client -connect hcmus.edu.vn:443 -showcerts > downloaded.txt # echo 'a' de tranh bi block (phai enter)

echo -e "\n\n2 certificate duoc down ve:\n\n"

g++ extractCertificate.cpp
./a.out

openssl x509 -in c1.pem -noout -modulus > modulus.txt
openssl x509 -in c1.pem -text -noout > CA_AllFields.txt
g++ extractPublicKey.cpp -lcrypto
./a.out

openssl x509 -in c0.pem -text -noout > Server_AllFields.txt
g++ extractSignature.cpp -lcrypto
./a.out
cat signatureWithSpacesAndColons | tr -d '[:space:]:' > signature
echo -e '\nSignature: '$(cat signature)'\n'

openssl asn1parse -i -in c0.pem -strparse 4 -out c0_body.bin -noout
sha256sum c0_body.bin > c0_body_sha256.txt

g++ verifyCert.cpp -lcrypto
./a.out
