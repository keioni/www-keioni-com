ipaddr-logger: ipaddr-logger.o image-binary-object.o
	gcc -O3 ipaddr-logger.o image-binary-object.o -o ipaddr-logger
	strip ipaddr-logger
	cp ipaddr-logger ../ipaddr-logger.cgi

ipaddr-logger.o: ipaddr-logger.c
	gcc -c -O3 ipaddr-logger.c -o ipaddr-logger.c
