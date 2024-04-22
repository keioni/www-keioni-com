# Web サーバ側のシステムファイル

Web サーバ側に置かなければならないが、一般ユーザには公開しないファイルを格納するディレクトリです。

この keioni.com はさくらインターネットのレンタルサーバを利用していているのですが、このディレクトリにあるスクリプトは `cron` で定期的に実行されています:

```
LOG_DIR=/home/example/www/keioni.com/.system/log
# NAME: Merge IP address log by day
27	1	*	*	0,1,2,3,4,5,6	/home/example/www/keioni.com/.system/ipaddr-log-daily-merger.sh
# NAME: Merge and pack IP address log by month
33	3	1	*	*	/home/example/www/keioni.com/.system/ipaddr-log-monthly-packer.sh
```

これらのスクリプトで、`via.png` 経由で取得したログをマージして、日ごとのログファイルを作成し、月ごとのログファイルを作成して圧縮しています。

`.htaccess` ファイルで、このディレクトリへの Web 経由でのアクセスはできないようにしています。
