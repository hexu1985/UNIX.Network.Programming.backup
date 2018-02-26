#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/IPAddress.h"
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " <host> <port>" << std::endl;
        return -1;
    }

    std::string host = argv[1];
    int port = atoi(argv[2]);
    Poco::Net::SocketAddress serverAddress(host, port);
    Poco::Net::DatagramSocket datagramSocket;
    datagramSocket.connect(serverAddress);

    char buffer[2048];
    std::string data;
    
    while (std::getline(std::cin, data))
    {
        datagramSocket.sendBytes(data.c_str(), data.size());
        int n = datagramSocket.receiveBytes(buffer, sizeof(buffer) - 1);
        buffer[n] = '\0';
        std::cout << "Received: " << buffer << std::endl;
    }

    return 0;
}
