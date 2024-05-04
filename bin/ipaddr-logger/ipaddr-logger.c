#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ipv4_img_array.h"
#include "ipv6_img_array.h"

#define BUF_SIZE_TIMESTAMP 50
#define BUF_SIZE_FILE_TIMESTAMP 50
#define BUF_SIZE_LOG_FILE 100


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
    if ( ip6addr ) {
        printf("Content-Type: image/png\nContent-Length: %lu\n\n", ipv6_img_size);
        fwrite(ipv6_img_array, 1, ipv6_img_size, stdout);
    } else {
        printf("Content-Type: image/png\nContent-Length: %lu\n\n", ipv4_img_size);
        fwrite(ipv4_img_array, 1, ipv4_img_size, stdout);
    }

    time_t current_time = time(NULL);
    struct tm *current_localtime = localtime(&current_time);

    char timestamp[BUF_SIZE_TIMESTAMP];
    char file_timestamp[BUF_SIZE_FILE_TIMESTAMP];
    strftime(timestamp, BUF_SIZE_TIMESTAMP, "%Y-%m-%d %H:%M:%S", current_localtime);
    strftime(file_timestamp, BUF_SIZE_FILE_TIMESTAMP, "%Y%m%d", current_localtime);

    const char *document_root = getenv("DOCUMENT_ROOT");
    int document_root_len = strlen(document_root);
    char log_file[BUF_SIZE_LOG_FILE + document_root_len + 1];
    sprintf(log_file, "%s/.system/log/%s.log", document_root, file_timestamp);

    FILE *fp_log = NULL;
    if (( fp_log = fopen(log_file, "a+") ) == NULL) {
        fprintf(stderr, "Error: Failed to open log file.\nFile: %s\n", log_file);
        return 1;
    }

    fprintf(fp_log, "%s %s %s %s \"%s\" \"%s\"\n",
            timestamp,
            getenv("HTTP_CF_RAY"),
            http_cf_connecting_ip,
            getenv("QUERY_STRING"),
            getenv("HTTP_REFERER"),
            getenv("HTTP_USER_AGENT")
    );
    fclose(fp_log);
}
