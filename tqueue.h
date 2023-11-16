#include <queue>
#include <mutex>

template<typename T>
class tqueue {
    std::queue<T> internal_queue;
    std::mutex queue_write_mutex;
    
    void lock_mutex();
    void unlock_mutex();
    public:
        queue();
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        bool empty() const;
        size_t size() const;
        void push( T&& value );
        void push_range( R&& rg );
        decltype(auto) emplace( Args&&... args );
        void pop();
        void swap( tqueue& other )
        tqueue& operator=( const tqueue& other );
    


};