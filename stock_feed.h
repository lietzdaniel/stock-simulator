#ifndef STOCK_FEED_H
#define STOCK_FEED_H

#include "string"
#include "vector"
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
#include "mutex"
#include "ctime"
#include "sstream"
class stock_message
{

    double value;
    double delta;
    std::string timestamp;

public:
    stock_message(double value, double delta, std::string &timestamp);
    std::string to_string();
};

class stock_feed
{
    double cur_value;
    std::string ticker_name;
    std::mutex pool_mutex;
    std::vector<int> invalid_sockets;

public:
    stock_feed(std::string &ticker_name, int port);
    std::vector<int> socket_pool;
    int server_socket;

    void create_socket(int port);
    void accept_connections();
    void start_data_simulation();
    void send_message(int socket_id, std::string &stock_message);
};

#endif