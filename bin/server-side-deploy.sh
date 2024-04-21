#!/usr/local/bin/bash -eux

server=keioni.com
tarfile=./$server.tar.gz

tar zxvf $tarfile -C www/$server

cp -p www/$server/img/favicon/favicon-prod.png www/$server/favicon.ico
make -C www/$server/cgi-bin/src

rm $tarfile $0
