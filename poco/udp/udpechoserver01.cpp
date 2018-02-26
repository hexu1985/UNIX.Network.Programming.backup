#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/IPAddress.h"
#include <stdlib.h>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " <port>" << std::endl;
        return -1;
    }

    int port = atoi(argv[1]);

    Poco::Net::SocketAddress socketAddress(Poco::Net::IPAddress(), port);
    Poco::Net::DatagramSocket datagramSocket(socketAddress);

    char buffer[8192];

    while (true)
    {
        Poco::Net::SocketAddress sender;
        int n = datagramSocket.receiveFrom(buffer, sizeof(buffer) - 1, sender);
        buffer[n] = '\0';
        std::cout << sender.toString() << ": " << buffer << std::endl;
        datagramSocket.sendTo(buffer, n, sender);
    }

    return 0;
}
