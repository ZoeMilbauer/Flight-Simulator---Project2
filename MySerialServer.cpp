#include "MySerialServer.h"

MySerialServer::MySerialServer() {
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
}

void waitForClientThread(int & sockfd, ClientHandler* c) {
    int clilen, newsockfd;
    string input = "";
    char temp[1024];
    char output[1024];
    char buffer[256];
    struct sockaddr_in cli_addr;
    int n;


    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    /* Accept actual connection from the client */
    while (true) {

        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);

        if (newsockfd < 0) {
            if (errno == EWOULDBLOCK) {
                cout << "timeout!" << endl;
            } else {
                perror("ERROR on accept");
            }
            return;
        }

        /* If connection is established then start communicating */
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        // read all lines of matrix until end
        while (strcmp(buffer, "end") == 0) {
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            input += buffer;
            // sign for end of line
            input += "*,";
            bzero(buffer,256);
            n = read( newsockfd,buffer,255 );
        }

        strcpy(temp, input.c_str());
        c->handleClient(temp, output);
        n = write(newsockfd,output,255);
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
        close(newsockfd);
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
    }

}

void MySerialServer::open(int port, ClientHandler* c) {
    int portno;
    struct sockaddr_in serv_addr;

    if (this->sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    thread t(waitForClientThread, ref(this->sockfd), c);
    t.join();
}

void MySerialServer::stop() {
    close(this->sockfd);
}