echo 'a' | openssl s_client -connect hcmus.edu.vn:443 -showcerts > downloaded.txt # echo 'a' de tranh bi block (phai enter)

# Lay 2 certificate dau tien trong downloaded.txt
echo -e "\n\n2 certificate dau tien trong noi dung duoc down ve:\n\n"
g++ -o run extractCertificates.cpp
./run

# Lay public key (n, e) tu certificate cua CA va ghi vao file publicKey.txt
openssl x509 -in c1.pem -noout -modulus > modulus.txt
openssl x509 -in c1.pem -text -noout > CA_AllFields.txt
g++ -o run extractPublicKey.cpp -lcrypto
./run

# Lay signature cua server tu certificate cua server
openssl x509 -in c0.pem -text -noout > Server_AllFields.txt
g++ -o run extractSignature.cpp -lcrypto
./run
cat signatureWithSpacesAndColons | tr -d '[:space:]:' > signature
echo -e '\nSignature: '$(cat signature)'\n'

# Certificate cua server duoc encoded bang ASN.1, parse no ra de lay phan body va hash body bang SHA-256
openssl asn1parse -i -in c0.pem -strparse 4 -out c0_body.bin -noout
sha256sum c0_body.bin > c0_body_sha256.txt

# Su dung public key, signature va body cua certificate cua server de kiem chung signature
g++ -o run verifyCert.cpp -lcrypto
./run
