

#ifndef GENERAL_INTER_P_LIB_SRC_SHARED_MEMORY_H
#define GENERAL_INTER_P_LIB_SRC_SHARED_MEMORY_H

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <string>
#include <vector>
#include <cstddef>

/// @brief The SharedMemory class template is designed to facilitate the sharing of data
/// between processes using shared memory.
/// It leverages the Boost.Interprocess library to manage synchronization and shared memory operations.
///
/// @tparam T template to allow different data types for the shared data.
///
template <typename T>
class SharedMemory
{
public:
    /// @brief Enum to represent the status of a write operation.
    ///
    enum class WriteStatus
    {
        Success, ///< Indicates a successful write operation.
        Failure  ///< Indicates a failed write operation.
    };

    /// @brief Constructor to create or open shared memory.
    /// @param name The name of the shared memory object.
    /// @param data_size The size of the data to be stored in shared memory.
    ///
    SharedMemory(const std::string &name, std::size_t data_size);

    /// @brief Destructor to clean up shared memory.
    ///
    ~SharedMemory();

    /// @brief Write data to shared memory.
    /// @param data The data to be written to shared memory.
    /// @return WriteStatus indicating success or failure of the write operation.
    ///
    WriteStatus write(const T &data);

    /// @brief Read data from shared memory.
    /// @return The data read from shared memory.
    /// @throws std::runtime_error if shared_data_ is nullptr.
    ///
    T read() const;

    /// @brief Set shared_data_ to nullptr for testing purposes.
    ///
    void setSharedDataNullptr()
    {
        shared_data_ = nullptr;
    }

private:
    /// @brief Structure to hold shared data.
    ///
    struct SharedData
    {
        SharedData() : new_data(false) {}                     ///< Default constructor
        T data;                                               ///< The actual data stored in shared memory.
        bool new_data;                                        ///< Flag to indicate if new data is available.
        boost::interprocess::interprocess_mutex mutex;        ///< Mutex for synchronizing access.
        boost::interprocess::interprocess_condition cond_var; ///< Condition variable for synchronization
    };

    std::string name_;                              ///< Name of the shared memory object.
    boost::interprocess::shared_memory_object shm_; ///< Shared memory object.
    boost::interprocess::mapped_region region_;     ///< Mapped region of the shared memory.
    SharedData *shared_data_;                       ///< Pointer to the shared data.
};

#endif // GENERAL_INTER_P_LIB_SRC_SHARED_MEMORY_H

