#include <string>
#include <vector>

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
