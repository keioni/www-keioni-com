#!/bin/bash -eux

server=keioni.com
tarfile=/tmp/$server.tar.gz

cat www/img/connected/via_ipv4.png | bin/binary-to-array/binary-to-array ipv4_img > bin/ipaddr-logger/ipv4_img_array.h
cat www/img/connected/via_ipv6.png | bin/binary-to-array/binary-to-array ipv6_img > bin/ipaddr-logger/ipv6_img_array.h

cp -pr bin/ipaddr-logger www/cgi-bin/src

tar zcvf $tarfile \
    --no-mac-metadata \
    --exclude .DS_Store \
    --exclude '*.pdf' \
    --exclude '*.log' \
    --exclude '.git*' \
    --exclude '.o' \
    -C www .

scp $tarfile bin/server-side-deploy.sh keioni.com:
ssh keioni.com "./server-side-deploy.sh"
rm $tarfile
