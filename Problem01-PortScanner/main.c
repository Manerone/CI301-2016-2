#include "stdio.h"
#include <netinet/in.h>
#include "sys/socket.h"
#include <arpa/inet.h>
#include <unistd.h>
#include "data.c"

void scan(char* ip, int port){
    int sock;
    struct sockaddr_in sa;
    int connection;
    char buffer[4096];
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(ip);
    sa.sin_port = htons(port);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
      fprintf(stderr, "Cannot create socket");
      return;
     }
     connection = connect(sock, (struct sockaddr*)&sa, sizeof(sa));
     if (connection >= 0) {
         memset(buffer, 0, sizeof(buffer));
         strcpy(buffer, "ls\r\n");
         connection = write(sock, buffer, strlen(buffer));
         if(connection < 0) return;
         bzero(buffer, 4096);
         connection = read(sock, buffer, 4096);
         if(connection < 0) return;
         printf("%s\t%d\t%s\n", ip, port, buffer);
     }
     close(sock);
}

int main(int argc, char *argv[]) {
        Data* data = get_data(argc, argv);


        String* final_part_of_ip;
        char* ip;


        for (uint current_ip = data->ip_start; current_ip <= data->ip_end; ++current_ip) {
            final_part_of_ip = String_int_to_string(current_ip);
            ip = String_concat(data->base_ip, final_part_of_ip);
            for (uint port = data->port_start; port <= data->port_end; ++port)
                scan(ip, port);
        }
        return 0;
}
