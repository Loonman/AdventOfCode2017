#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

#include <memory>
#include <mutex>
#include <cstdlib>

template <class T>
class RingBuffer {
public:
    RingBuffer(size_t size) :
        _buf(std::unique_ptr<T[]>(new T[size + 1])),
        _size(size + 1)
    {
        //empty constructor
    }

    void put(T item)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _buf[_head] = item;
        _head = (_head + 1) % _size;
        if(_head == _tail)
        {
            _tail = (_tail + 1) % _size;
        }
    }

    T get(void)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if(empty())
        {
            return T();
        }
    
        T val = _buf[_tail];
        _tail = (_tail +1) % _size;
        return val;
    }
    
    //Non-destructive unsafe read, only works on full array
    T read(int index)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if(full())
        {
            T val = _buf[(_tail + index) % _size];
            return val;
        }
        return T();
    }

    void reset(void)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _head = _tail;
    }
    
    bool empty(void)
    {
        return _head == _tail;
    }
    
    bool full(void)
    {
        return ((_head + 1) % _size) == _tail;
    }
    
    size_t size(void) 
    {
        return _size - 1;
    }

private:
    std::mutex _mutex;
    std::unique_ptr<T[]> _buf;
    size_t _head = 0;
    size_t _tail = 0;
    size_t _size;
};
#endif