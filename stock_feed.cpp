#include "stock_feed.h"

stock_message::stock_message(double value, double delta, std::string &timestamp) : value(value), delta(delta), timestamp(timestamp) {}

stock_feed::stock_feed(std::string &ticker_name, int port) : ticker_name(ticker_name)
{
    // Initialize Socket to localhost and given port
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);
    bind(this->server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
}

std::string stock_message::to_string()
{
    std::stringstream message_stream;
    message_stream << this->timestamp << ":  New Value: " << this->value << " Delta: " << this->delta << "\n";
    return message_stream.str();
}
void stock_feed::start_data_simulation()
{
    // Set Variables for Randomization
    std::random_device rd;
    std::mt19937 gen(rd());
    std::lognormal_distribution<double> distribution(0.0, 0.01);
    std::lognormal_distribution<double> time_distribution(0.0, 1.0);

    // Create an initial Stock Value between 100 and 200
    this->cur_value = rand() % 100 + 100;

    while (true)
    {
        // Generate an update interval and amount according to a logartihmic normal distribution
        double update_interval = time_distribution(gen);
        double update_amount = distribution(gen);
        double new_amount = this->cur_value * update_amount;
        double delta = new_amount - this->cur_value;
        this->cur_value = new_amount;

        auto time = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(time);
        std::string timestamp = std::ctime(&end_time);
        stock_message message{new_amount, delta, timestamp};
        std::string message_str = message.to_string();

        std::vector<std::thread> thread_pool;
        for (auto socket_id : this->socket_pool)
        {
            std::thread t = std::thread(&stock_feed::send_message, this, socket_id, std::ref(message_str));

            thread_pool.push_back(std::move(t));
        }
        for (auto &thread : thread_pool)
        {
            thread.join();
        }
        for (int invalid_socket_id : invalid_sockets)
        {
            socket_pool.erase(std::remove(socket_pool.begin(), socket_pool.end(), invalid_socket_id), socket_pool.end());
        }
        invalid_sockets = std::vector<int>();
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(update_interval * 1000)));
    }
}

void stock_feed::send_message(int socket_id, std::string &message)
{

    int res = send(socket_id, message.c_str(), message.size(), 0);
    if (res == -1)
    {
        // If send() fails, close the socket and remove it out of the socket_pool
        close(socket_id);
        this->invalid_sockets.push_back(socket_id);
    }
}

void stock_feed::accept_connections()
{
    // Listen for maximum 10 Connections
    listen(this->server_socket, 10);

    // Start Data Simulation Thread
    std::thread data_simulation(&stock_feed::start_data_simulation, this);
    while (true)
    {
        // Accept now Connections and add them in the Socket Pool
        sockaddr_in client_address;
        socklen_t client_address_length = sizeof(client_address);
        int client_socket = accept(this->server_socket, (struct sockaddr *)&client_address, &client_address_length);
        std::cout << "Connection accepted from " << inet_ntoa(client_address.sin_addr) << std::endl;
        this->pool_mutex.lock();
        this->socket_pool.push_back(client_socket);
        this->pool_mutex.unlock();
    }
}

int main()
{
    // Ignore SIGPIPE in order for send() not to crash the Program when a Socket is closed on the Client side.
    signal(SIGPIPE, SIG_IGN);

    std::string ticker_name = "BMW";
    int port = 12345;
    std::cout << "To connect to the Stock_feed server, run ||| nc localhost " << port << " ||| on another Terminal Window." << std::endl;

    stock_feed server(ticker_name, port);
    server.accept_connections();

    return 0;
}