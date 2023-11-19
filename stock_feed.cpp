#include "stock_feed.h"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <random>
#include <chrono>
#include <thread>
#include <arpa/inet.h>
stock_feed::stock_feed(std::string &ticker_name, int port) : ticker_name(ticker_name)
{
    // Initialize Socket
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);
    bind( this->server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
}

void stock_feed::start_data_simulation()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::lognormal_distribution<double> distribution(0.0, 0.01);
    std::lognormal_distribution<double> time_distribution(0.0, 1.0);
    this->cur_value = rand()%100+100;
    while (true){
        double update_interval = time_distribution(gen);
        double update_amount = distribution(gen);
        double new_amount = this->cur_value * update_amount;
        double delta = new_amount - this->cur_value;
        this->cur_value = new_amount;
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(update_interval * 1000)));
          std::string stockInfo = "Stock update: " + ticker_name + " price: " + std::to_string(new_amount) + "\n";
        for(auto &socket: this->socket_pool){
            send(socket, stockInfo.c_str(), stockInfo.size(), 0);
        }
       
    }
}
void stock_feed::accept_connections()
{
    // Listen for Connections
    listen(this->server_socket, 10);

    std::thread data_simulation(&stock_feed::start_data_simulation,this); 
    while (true)
    {
        sockaddr_in clientAddress;
        socklen_t clientAdressLength = sizeof(clientAddress);
        int client_socket = accept(this->server_socket, (struct sockaddr *)&clientAddress, &clientAdressLength);
        std::cout << "Connection accepted from " << inet_ntoa(clientAddress.sin_addr) << std::endl;
        this->socket_pool.push_back(client_socket);
    }
}

int main() {
    std::string ticker_name = "BMW";
    int port = 12345;

    stock_feed server(ticker_name, port);
    server.accept_connections();

    return 0;
}