#include "stock_feed.h"

stock_feed::stock_feed(std::string &ticker_name, int port) : ticker_name(ticker_name)
{
    // Initialize Socket to localhost and given port
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);
    bind( this->server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
}

void stock_feed::start_data_simulation()
{
    // Set Variables for Randomization
    std::random_device rd;
    std::mt19937 gen(rd());
    std::lognormal_distribution<double> distribution(0.0, 0.01);
    std::lognormal_distribution<double> time_distribution(0.0, 1.0);

    // Create an initial Stock Value between 100 and 200
    this->cur_value = rand()%100+100;

    while (true){
        // Generate an update interval and amount according to a logartihmic normal distribution
        double update_interval = time_distribution(gen);
        double update_amount = distribution(gen);
        double new_amount = this->cur_value * update_amount;
        double delta = new_amount - this->cur_value;
        this->cur_value = new_amount;

        std::this_thread::sleep_for(std::chrono::milliseconds((int)(update_interval * 1000)));
        std::string stock_info = "Stock update: " + ticker_name + " price: " + std::to_string(new_amount) + "\n";
        
        for (auto it = this->socket_pool.begin(); it != this->socket_pool.end();){
            int socket = *it;
            int res = send(socket, stock_info.c_str(), stock_info.size(), 0);
            if(res == -1){
                // If send() fails, close the socket and remove it out of the socket_pool
                close(socket);
                it = this->socket_pool.erase(it);
            } else {
                ++it;
            }
        }
       
    }
}
void stock_feed::accept_connections()
{
    // Listen for maximum 10 Connections
    listen(this->server_socket, 10);

    // Start Data Simulation Thread
    std::thread data_simulation(&stock_feed::start_data_simulation,this); 
    while (true)
    {
        // Accept now Connections and add them in the Socket Pool 
        sockaddr_in client_address;
        socklen_t client_address_length = sizeof(client_address);
        int client_socket = accept(this->server_socket, (struct sockaddr *)&client_address, &client_address_length);
        std::cout << "Connection accepted from " << inet_ntoa(client_address.sin_addr) << std::endl;
        this->socket_pool.push_back(client_socket);
    }
}

int main() {
    // Ignore SIGPIPE in order for send() not to crash the Program when a Socket is closed on the Client side.
    signal(SIGPIPE, SIG_IGN);


    std::string ticker_name = "BMW";
    int port = 12345;
    std::cout << "To connect to the Stock_feed server, run ||| nc localhost " << port << " ||| on another Terminal Window." << std::endl;

    stock_feed server(ticker_name, port);
    server.accept_connections();

    return 0;
}