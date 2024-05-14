# when asked about CN (common name), enter the API domain
# use "Google Trust Services" as CN for the root CA

touch certindex
echo 01 > certserial
echo 01 > crlnumber

openssl genrsa -des3 -out rootCA.key 4096
openssl req -x509 -new -nodes -key rootCA.key -sha256 -days 1024 -out rootCA.pem
openssl genrsa -out keyauth.win.key 2048
openssl req -new -key keyauth.win.key -out keyauth.win.csr
# openssl.cnf has to be configured correctly, needs to have clr
openssl ca -in keyauth.win.csr -out keyauth.win.crt -days 500 -extensions v3_ca
openssl ca -gencrl -keyfile rootCA.key -cert rootCA.pem -out rootCA.crl -crldays 30
openssl verify -CAfile rootCA.pem keyauth.win.crt
openssl x509 -outform der -in rootCA.pem -out rootCA.crt