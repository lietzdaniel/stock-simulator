#include "tqueue.h"


template<typename T>
tqueue<T>::tqueue(): internal_queue(), queue_write_mutex() {}

template<typename T>
T& tqueue<T>::front(){
    return this->internal_queue.front();
}

template<typename T>
const T& tqueue<T>::front() const{
    return this->internal_queue.front();
}

template<typename T>
T& tqueue<T>::back(){
    return this->internal_queue.back();
}

template<typename T>
const T& tqueue<T>::back() const{
    return this->internal_queue.back();
}

template<typename T>
bool tqueue<T>::empty() const{
    return this->internal_queue.empty();
}

template<typename T>
size_t tqueue<T>::size() const{
    return this->internal_queue.size();
}

template<typename T>
void tqueue<T>::push( T&& value ){
    this->queue_write_mutex.lock();
    this->internal_queue.push(value);
    this->queue_write_mutex.unlock();
}

template<typename T>
void tqueue<T>::push_range( T&& rg ){
    this->queue_write_mutex.lock();
    this->internal_queue.push_range(rg);
    this->queue_write_mutex.unlock();
}

template<typename T>
decltype(auto) tqueue<T>::emplace( T&& t ){
    this->queue_write_mutex.lock();
    decltype(auto) result = this->internal_queue.emplace(t);
    this->queue_write_mutex.unlock();
    return result;
}

template<typename T>
void tqueue<T>::pop(){
    this->queue_write_mutex.lock();
    this->internal_queue.pop();
    this->queue_write_mutex.unlock();
}

template<typename T>
void tqueue<T>::swap( tqueue& other ){
    this->queue_write_mutex.lock();
    this->internal_queue.swap();
    this->queue_write_mutex.unlock();
}

template<typename T>
tqueue<T>& tqueue<T>::operator=( const tqueue<T>& other ){
    this->queue_write_mutex.lock();
    this->internal_queue = other;
    this->queue_write_mutex.unlock();
}