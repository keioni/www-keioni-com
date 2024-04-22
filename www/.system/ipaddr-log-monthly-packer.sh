#!/usr/local/bin/bash

target_month=`date -v-1m "+%Y%m"`

cd $LOG_DIR
mkdir -p $target_month

mv ${target_month}*.log $target_month

tar zcf ${target_month}.tar.gz $target_month

rm -rf $target_month
