// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <string>

using namespace std;
class Server{
    private :
        int port;
        int server_fd, new_socket, valread; 
        struct sockaddr_in address; 
        int opt = 1; 
        int addrlen = sizeof(address); 
        char buffer[1024] = {0}; 


    
    public :
        void setup(int port){
            port = port;
         
            if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
                perror("socket creation failed"); 
                exit(EXIT_FAILURE); 
            } 
        
            if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                        &opt, sizeof(opt))) { 
                perror("socket attaching failed"); 
                exit(EXIT_FAILURE); 
            } 
            
            address.sin_family = AF_INET; 
            address.sin_addr.s_addr = INADDR_ANY; 
            address.sin_port = htons( port ); 
           
            if (bind(server_fd, (struct sockaddr *)&address, 
                                        sizeof(address))<0){ 
                perror("bind failed"); 
                exit(EXIT_FAILURE); 
            } 
            if (listen(server_fd, 3) < 0) { 
                perror("listen"); 
                exit(EXIT_FAILURE); 
            } 

        }

        char* listen_request(char * send_buffer){
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                            (socklen_t*)&addrlen))<0) { 
                perror("accept"); 
                exit(EXIT_FAILURE); 
            } 
            valread = read( new_socket , buffer, 1024); 
            send(new_socket , send_buffer , strlen(send_buffer) , 0 ); 
            printf("Server : Sent \n"); 
            return buffer;
        }
};

