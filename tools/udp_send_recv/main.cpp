#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>
#include <stdint.h>
#include "prog_opts_util.h"

extern "C" {
#include "wrapsock.h"
#include "wraplib.h"
#include "sock_ntop.h"
}

using namespace std;
using namespace std::chrono;
using boost::program_options::variables_map;

void recv_routine(int sockfd);
void send_routine(int sockfd, variables_map vm);

int main(int argc, char *argv[])
{
    auto vm = Parse_command_line(argc, argv);

    cout << "program_options: \n";
    Print_variables_map(vm);
    cout << "\n\n" << endl;

    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    auto local_addr = vm["local_addr"].as<string>();
    auto local_port = vm["local_port"].as<int>();

    struct sockaddr_in self_addr;
    self_addr.sin_family = AF_INET;
    if (local_addr.empty()) {
        self_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        Inet_pton(AF_INET, local_addr.c_str(), &self_addr.sin_addr);
    }
    self_addr.sin_port = htons((uint16_t) local_port);

    Bind(sockfd, (struct sockaddr *) &self_addr, sizeof(self_addr));

    std::thread recv_thread(&recv_routine, sockfd);
    recv_thread.detach();

    send_routine(sockfd, vm);

    return 0;
}

void send_routine(int sockfd, variables_map vm)
{
    auto server_addr = vm["server_addr"].as<string>();
    auto server_port = vm["server_port"].as<int>();
    auto send_data = vm["send_data"].as<string>();
    auto packets_per_request = vm["packets_per_request"].as<int>();
    auto sleep_per_loop = vm["sleep_per_loop"].as<int>();

    struct sockaddr_in peer_addr;
    memset(&peer_addr, 0, sizeof(peer_addr));
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons((uint16_t) server_port);
    Inet_pton(AF_INET, server_addr.c_str(), &peer_addr.sin_addr);

    for ( ; ; ) {
        for (int j = 0; j < packets_per_request; j++) {
            if (sendto(sockfd, send_data.c_str(), send_data.size(), 0, (struct sockaddr *) &peer_addr, sizeof (peer_addr)) < 0) {
                cout << "sendto error" << endl;
            } else {
                cout << "send \"" << send_data << "\" to " << server_addr << ":" << server_port << endl;
            }
        }

        if (sleep_per_loop > 0) {
            this_thread::sleep_for(milliseconds(sleep_per_loop));
        } else {
            this_thread::sleep_for(seconds(1));
        }
    }
}

void recv_routine(int sockfd)
{
    const int BUF_SIZE = 8192;
    char      buff[BUF_SIZE];
    struct sockaddr_in peer_addr;
    socklen_t len;
    int n;

	for ( ; ; ) {
        len = sizeof(sockaddr_storage); 
        if ((n = recvfrom(sockfd, buff, BUF_SIZE, 0, (struct sockaddr *) &peer_addr, &len)) < 0) {
            cout << "recvfrom error" << endl;
            continue;
        }
        cout << "recv \"" << string(buff, n) << "\" from " << Sock_ntop((struct sockaddr *) &peer_addr, len) << endl;
    }
}
