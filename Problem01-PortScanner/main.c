#include "stdio.h"
#include <netinet/in.h>
#include "sys/socket.h"
#include <arpa/inet.h>
#include <unistd.h>
#include "data.c"

int main(int argc, char *argv[]) {
        Data* data = get_data(argc, argv);
        int sock;
        int connection;
        String* final_part_of_ip;
        char* ip;
        struct sockaddr_in sa;
        char buffer[4096];
        for (uint current_ip = data->ip_start; current_ip <= data->ip_end; ++current_ip) {
            final_part_of_ip = String_int_to_string(current_ip);
            ip = String_concat(data->base_ip, final_part_of_ip);
            memset(&sa, 0, sizeof(sa));
            sa.sin_family = AF_INET;
            sa.sin_addr.s_addr = inet_addr(ip);
            for (uint port = data->port_start; port <= data->port_end; ++port) {
                sa.sin_port = htons(port);
                sock = socket(AF_INET, SOCK_STREAM, 0);
                connection = connect(sock, (struct sockaddr*)&sa, sizeof(sa));
                if (connection >= 0) {
                    memset(buffer, 0, sizeof(buffer));
                    strcpy(buffer, "garbage\r\n");
                    connection = write(sock, buffer, strlen(buffer));
                    if(connection < 0) {
                        printf("[-]Error writing (Port closed maybe?!)\n");
                    }
                    bzero(buffer, 4096);
                    connection = read(sock, buffer, 4096);
                    if(connection < 0) {
                        printf("[-]Error reading (Port closed maybe?!)\n");
                    }
                    printf("%s\t%d\t%s\n", ip, port, buffer);
                }
                close(sock);
            }
        }
        return 0;
}
