#include "prog_opts_util.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace boost::program_options;

variables_map Parse_command_line(int argc, char *argv[])
{
    options_description desc("udp_send_recv");

    string filename;
    desc.add_options()
        ("help,h", "produce help message")
        ("config_file,f", value<string>(&filename)->default_value(""), "config file")
        ("server_addr", value<string>()->default_value("127.0.0.1"), "server addr that client to connect")
        ("server_port", value<int>()->default_value(9999), "server port that client to connect")
        ("local_addr", value<string>()->default_value(""), "local addr that client bind")
        ("local_port", value<int>()->default_value(0), "local port that client bind")
        ("send_data", value<string>()->default_value("hello world"), "send data")
        ("packets_per_request", value<int>()->default_value(1), "send packet number per request")
        ("sleep_per_loop", value<int>()->default_value(1000), "sleep ms per send loop")
        ;

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (!filename.empty()) {
        ifstream ifs(filename);
        store(parse_config_file(ifs, desc, true), vm);
    }

    if (vm.count("help")) {
        cout << desc << endl;
        exit(1);
    }

    return vm;
}

void Print_variables_map(const boost::program_options::variables_map &vm)
{
    cout << "config_file: " << vm["config_file"].as<string>() << "\n";
    cout << "server_addr: " << vm["server_addr"].as<string>() << "\n";
    cout << "server_port: " << vm["server_port"].as<int>() << "\n";
    cout << "local_addr: " << vm["local_addr"].as<string>() << "\n";
    cout << "local_port: " << vm["local_port"].as<int>() << "\n";
    cout << "send_data: " << vm["send_data"].as<string>() << "\n";
    cout << "packets_per_request: " << vm["packets_per_request"].as<int>() << "\n";
    cout << "sleep_per_loop: " << vm["sleep_per_loop"].as<int>() << "ms\n";
}

