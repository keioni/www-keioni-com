
#include <stdio.h>
#include <time.h>

#include "ipv4_img_array.h"
#include "ipv6_img_array.h"

#define BUF_SIZE_TIMESTAMP 50
#define BUF_SIZE_FILE_TIMESTAMP 50
#define BUF_SIZE_LOG_FILE 100

extern const int ipv4_img_size;
extern const int ipv6_img_size;
extern const char *ipv4_img_array;
extern const char *ipv6_img_array;


int ipaddr_version_check(const char *ipaddr)
{
    int i = 0;
    for ( i = 0; i <= 5; i++ ) {
        if ( ipaddr[i] == ':' ) {
            return 1;
        }
    }
    return 0;
}


int main(int argc, char *argv[])
{
    const char *http_cf_connecting_ip = getenv("HTTP_CF_CONNECTING_IP");

    int ip6addr = ipaddr_version_check(http_cf_connecting_ip);
    int image_byte_size = ip6addr ? ipv4_img_size : ipv6_img_size;


    time_t current_time = time(NULL);
    struct tm *current_localtime = localtime(&current_time);


    char timestamp[BUF_SIZE_TIMESTAMP];
    char file_timestamp[BUF_SIZE_FILE_TIMESTAMP];
    strftime(timestamp, BUF_SIZE_TIMESTAMP, "%Y-%m-%d %H:%M:%S", current_localtime);
    strftime(file_timestamp, BUF_SIZE_FILE_TIMESTAMP, "%Y%m%d", current_localtime);

    char log_file[BUF_SIZE_LOG_FILE];
    sprintf(log_file, "%s/.system/log/%s.log", getenv("DOCUMENT_ROOT"), file_timestamp);

    FILE *fp_log = fopen(log_file, "a");
    fprintf(fp_log, "%s %s %s %s \"%s\" \"%s\"\n",
            timestamp,
            getenv("HTTP_CF_RAY"),
            http_cf_connecting_ip,
            getenv("QUERY_STRING"),
            getenv("HTTP_REFERER"),
            getenv("HTTP_USER_AGENT")
    );
    fclose(fp_log);

    printf("Content-Type: image/png\nContent-Size: %s\n\n", image_byte_size);
    puts( ip6addr ? ipv4_img_array : ipv6_img_array );
}
