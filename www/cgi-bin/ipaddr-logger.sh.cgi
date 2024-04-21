#!/usr/local/bin/bash

echo "Content-Type: image/png"
echo ""

timestamp=`date "+%Y-%m-%d %H:%M:%S"`
file_timestamp=`date "+%Y%m%d"`

echo "$timestamp $HTTP_CF_RAY $HTTP_CF_CONNECTING_IP $QUERY_STRING \"$HTTP_REFERER\" \"$HTTP_USER_AGENT\"" >> $DOCUMENT_ROOT/.system/log/${file_timestamp}.log

echo $HTTP_CF_CONNECTING_IP | grep : > /dev/null
if [ $? -eq 0 ]; then
    cat $DOCUMENT_ROOT/img/connected/via_ipv6.png
else
    cat $DOCUMENT_ROOT/img/connected/via.png
fi
