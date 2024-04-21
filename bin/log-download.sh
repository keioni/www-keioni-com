#!/bin/bash -eux

server=keioni.com
timestamp=`date "+%Y%m%d"`

tarfile=log-${server}-${timestamp}.tar.gz

ssh keioni.com "tar zcvf tmp/access-log/$tarfile -C www/$server/.system log"
scp keioni.com:tmp/access-log/$tarfile tmp

mkdir -p tmp/log/${server}-${timestamp}
tar zxvf tmp/$tarfile -C tmp/log/${server}-${timestamp}
