#!/usr/local/bin/bash

file_timestamp=`date -v-1d "+%Y%m%d"`
border_timestamp=`date -v-1d "+%Y-%m-%d"`

yesterday_log=$LOG_DIR/${file_timestamp}.log
touch $yesterday_log


# ######################################################################
# 全部の log

all_log_file=$LOG_DIR/all-access.log

echo "==================== $border_timestamp ====================" >> $all_log_file
cat $yesterday_log >> $all_log_file


# ######################################################################
# 自分自身(おにまる)のアクセスを除いた log

valuable_log_file=$LOG_DIR/valuable-access.log

echo "==================== $border_timestamp ====================" >> $valuable_log_file
cat $yesterday_log | grep -v $MY_IP6ADDR_PREFIX >> $valuable_log_file
