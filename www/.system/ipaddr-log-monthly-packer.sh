#!/usr/local/bin/bash

target_month=`date -v-1m "+%Y%m"`

cd $LOG_DIR
cat ${target_month}*.log > aggregate_${target_month}.log
# rm ${target_month}*.log

mv aggregate_${target_month}.log ${target_month}.log
