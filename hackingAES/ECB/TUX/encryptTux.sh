head -n 3 Tux.ppm > Tux.header
tail -n +4 Tux.ppm > Tux.body
openssl enc -aes-128-ecb -nosalt -pass pass:"1234" -in Tux.body -out Tux.body.ecb
cat Tux.header Tux.body.ecb > Tux.ecb.ppm