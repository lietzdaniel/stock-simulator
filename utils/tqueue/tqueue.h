#include <queue>
#include <mutex>


template<typename T>
class tqueue {
    std::queue<T> internal_queue;
    std::mutex queue_write_mutex;

    public: 

    tqueue() : internal_queue(), queue_write_mutex() {}


    T& front(){
        return this->internal_queue.front();
    }    


    const T& front() const{
        return this->internal_queue.front();
    }


    T& back(){
        return this->internal_queue.back();
    }


    const T& back() const{
        return this->internal_queue.back();
    }


    bool empty() const{
        return this->internal_queue.empty();
    }


    size_t size() const{
        return this->internal_queue.size();
    }


    void push( T&& value ){
        this->queue_write_mutex.lock();
        this->internal_queue.push(value);
        this->queue_write_mutex.unlock();
    }


    void push_range( T&& rg ){
        this->queue_write_mutex.lock();
        this->internal_queue.push_range(rg);
        this->queue_write_mutex.unlock();
    }


    decltype(auto) emplace( T&& t ){
        this->queue_write_mutex.lock();
        decltype(auto) result = this->internal_queue.emplace(t);
        this->queue_write_mutex.unlock();
        return result;
    }


    void pop(){
        this->queue_write_mutex.lock();
        this->internal_queue.pop();
        this->queue_write_mutex.unlock();
    }


    void swap( tqueue& other ){
        this->queue_write_mutex.lock();
        this->internal_queue.swap();
        this->queue_write_mutex.unlock();
    }


    tqueue<T>& operator=( const tqueue<T>& other){
        this->queue_write_mutex.lock();
        this->internal_queue = other;
        this->queue_write_mutex.unlock();
    }
    
};



