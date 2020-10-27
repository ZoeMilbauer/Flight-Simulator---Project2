#include "MyParallelServer.h"
#include <vector>
#include "MyClientHandler.h"

MyParallelServer::MyParallelServer() {
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
}

void hendleClient(int newsockfd, ClientHandler* c) {
    char output[1024];
    char input[1024];
    char buffer[1024];
    string allData;
    int n;
    /* If connection is established then start communicating */
    bzero(buffer,1024);
    n = read(newsockfd,buffer,1023);
    allData = (string)buffer;
    // read all lines of matrix until end
    while (allData.find("end") == allData.npos) {
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        //strcat(input, buffer);
        // sign for end of line
        bzero(buffer,1024);
        n = read(newsockfd,buffer,1023 );
        allData += (string)buffer;
    }

    // remove spaces from data string
    string::iterator end_pos = remove(allData.begin(), allData.end(), ' ');
    allData.erase(end_pos, allData.end());
    char* temp = new char[allData.size()];
    strcpy(temp, allData.c_str());
    char* token = strtok(temp, "\n");
    // token != NULL
    while (strcmp(token, "end")) {
        strcat(input, token);
        strcat(input, "*,");
        token = (strtok(NULL, "\n"));
    }

    c->handleClient(input, output);
    n = write(newsockfd,output,1023);
    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

}


void waitForClient(int & sockfd, ClientHandler* c) {
    int clilen, newsockfd;
    struct sockaddr_in cli_addr;
    vector<thread> threads;
    ClientHandler* ch;

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    /* Accept actual connection from the client */
    while ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen)) >= 0 ) {
        ch = c->clone();
        threads.push_back(thread(hendleClient, newsockfd, ch));
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
    }
    if (newsockfd < 0) {
        if (errno == EWOULDBLOCK) {
            cout << "timeout!" << endl;
        }
        else {
            perror("ERROR on accept");
        }
    }
    for(vector<thread>::iterator it = threads.begin(); it != threads.end(); it++) {
        (*it).join();
    }
}


void MyParallelServer::open(int port, ClientHandler* c) {
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

    thread t(waitForClient, ref(this->sockfd), c);
    t.join();
}


void MyParallelServer::stop() {
    close(this->sockfd);
}