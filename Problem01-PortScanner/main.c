#include "stdio.h"
#include "my_string.c"

const char DOT = '.';

typedef struct data
{
	String* base_ip;
	uint ip_start;
	uint ip_end;
	uint port_start;
	uint port_end;
} Data;

void get_base_ip_and_ip_range(Data* data, char* ip){
	uint number_of_dots_in_a_base_ip = 3;
	uint dots_found = 0;
	uint index = 0;
	String* ip_start = String_new();
	String* ip_end = String_new();
	// Find the base ip, in 192.134.122.52
	// the base ip is 192.134.122.
	while(dots_found < number_of_dots_in_a_base_ip){
		if (ip[index] == DOT)
			dots_found++;
		String_add_element(data->base_ip, ip[index]);
		index++;
	}
	// Find the start ip range
	while(ip[index] != '-' && ip[index] != '\0'){
		String_add_element(ip_start, ip[index]);
		index++;
	}
	data->ip_start = String_to_int(ip_start);
	// Find the end ip range, if there is any
	if (ip[index] == '\0')
		data->ip_end = data->ip_start;
	else if (ip[index] == '-')
	{
		index++;
		while(ip[index] != '\0'){
			String_add_element(ip_end, ip[index]);
			index++;
		}
		data->ip_end = String_to_int(ip_end);
	}
}

Data* get_data(int argc, char *argv[]){
	Data* data = malloc(sizeof(Data));
	data->base_ip = String_new();
	get_base_ip_and_ip_range(data, argv[1]);
	printf("%s\n", data->base_ip->characters);
	printf("%d\n", data->ip_start);
	printf("%d\n", data->ip_end);
	return data;
}

int main(int argc, char *argv[]) {
		Data* data = get_data(argc, argv);
        return 0;
}
