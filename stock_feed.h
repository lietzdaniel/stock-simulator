#ifndef STOCK_FEED_H
#define STOCK_FEED_H

#include <string>
#include <vector>
#include "iostream"
#include "string"
#include "cstring"
#include "unistd.h"
#include "netinet/in.h"
#include "random"
#include "chrono"
#include "thread"
#include "arpa/inet.h"
#include "csignal"

class stock_feed
{
    double cur_value;
    std::string ticker_name;

public:
    std::vector<int> socket_pool;
    int server_socket;
    stock_feed(std::string &ticker_name, int port);
    void create_socket(int port);
    void accept_connections();
    void start_data_simulation();
};

#endif