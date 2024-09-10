#include "shared_memory.h"
#include "image.h"
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>

/// Constructor to create or open shared memory.
template <typename T>
SharedMemory<T>::SharedMemory(const std::string &name, std::size_t data_size)
    : name_(name),
      shm_(boost::interprocess::open_or_create, name.c_str(), boost::interprocess::read_write),
      region_()
{
    shm_.truncate(sizeof(SharedData) + data_size * sizeof(T));
    region_ = boost::interprocess::mapped_region(shm_, boost::interprocess::read_write);
    void *addr = region_.get_address();
    shared_data_ = new (addr) SharedData();
}

/// Destructor
template <typename T>
SharedMemory<T>::~SharedMemory()
{
    if (shared_data_)
    {
        // Explicitly call the destructor of SharedData
        shared_data_->~SharedData();

        boost::interprocess::shared_memory_object::remove(name_.c_str());
    }
}

/// Write data to shared memory
template <typename T>
typename SharedMemory<T>::WriteStatus SharedMemory<T>::write(const T &data)
{
    if (!shared_data_)
    {
        return WriteStatus::Failure; // Indicate failure if shared_data_ is nullptr
    }

    boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(shared_data_->mutex);
    if (shared_data_)
    {
        shared_data_->data = data;
        shared_data_->new_data = true;
        shared_data_->cond_var.notify_all();
        return WriteStatus::Success; // Indicate success
    }
    return WriteStatus::Failure; // Indicate failure
}

/// Read data from shared memory
template <typename T>
T SharedMemory<T>::read() const
{
    if (!shared_data_)
    {
        throw std::runtime_error("Shared data is nullptr");
    }

    boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(shared_data_->mutex);
    while (!shared_data_->new_data)
    {
        shared_data_->cond_var.wait(lock);
    }
    shared_data_->new_data = false;
    return shared_data_->data;
}

// Explicit template instantiation
template class SharedMemory<int>;
template class SharedMemory<float>;
template class SharedMemory<Image<std::size_t>>;
template class SharedMemory<std::vector<float>>;
