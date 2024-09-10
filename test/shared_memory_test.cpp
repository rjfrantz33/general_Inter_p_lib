/// @file
/// @brief Unit tests for the SharedMemory class.
/// @copyright (c) Jean Frantz René

#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <boost/interprocess/shared_memory_object.hpp>
#include "image.h"
#include "shared_memory.h"

// Test fixture for SharedMemory
class SharedMemoryTest : public ::testing::Test
{
protected:
    /// @brief Set up the test environment.
    /// This method is called before each test is run.
    ///
    void SetUp() override
    {
    }

    /// @brief Tear down the test environment.
    /// This method is called after each test is run.
    /// It removes the shared memory object used in the tests.
    ///
    void TearDown() override
    {
        boost::interprocess::shared_memory_object::remove("SharedMemoryTest");
    }

    /// @brief Perform a shared memory test.
    /// This method writes data to shared memory and then reads it back to verify the operation.
    /// @tparam T The type of data to be written and read.
    /// @param data The data to be written to shared memory.
    ///
    template <typename T>
    void performSharedMemoryTest(const T &data)
    {
        // Create a SharedMemory object with the specified data type and size.
        SharedMemory<T> sharedMemory("SharedMemoryTest", sizeof(T));

        // Write data to shared memory and check if the operation was successful.
        const auto status = sharedMemory.write(data);
        EXPECT_EQ(status, SharedMemory<T>::WriteStatus::Success);

        // Read data from shared memory and verify it matches the written data.
        const auto value = sharedMemory.read();
        EXPECT_EQ(value, data);
    }

    /// @brief Perform a concurrent access test on shared memory.
    /// This method tests concurrent read and write operations on shared memory.
    /// @tparam T The type of data to be written and read.
    /// @param data The data to be written to shared memory.
    ///
    template <typename T>
    void performConcurrentAccessTest(const T &data)
    {
        // Create a SharedMemory object with the specified data type and size.
        SharedMemory<T> sharedMemory("SharedMemoryTest", sizeof(T));

        // Create a writer thread that writes data to shared memory after a delay.
        std::thread writer_thread([&sharedMemory, &data]()
                                  {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            sharedMemory.write(data); });

        // Create a reader thread that reads data from shared memory.
        std::thread reader_thread([&sharedMemory, &data]()
                                  {
            const auto value = sharedMemory.read();
            EXPECT_EQ(value, data); });

        // Wait for both threads to complete.
        writer_thread.join();
        reader_thread.join();
    }
};

// The data to be written to shared memory is of type std::vector<float>.

// Write to shared memory test
TEST_F(SharedMemoryTest, WriteVectorFloatToSharedMemory)
{
    std::vector<float> data(1000, 42.0F);
    performSharedMemoryTest(data);
}

// Read from shared memory Test
TEST_F(SharedMemoryTest, ReadVectorFloatFromSharedMemory)
{
    std::vector<float> data(1000, 42.0F);
    performSharedMemoryTest(data);
}

// Concurrent access to shared memory Test
TEST_F(SharedMemoryTest, ConcurrentAccessVectorFloat)
{
    std::vector<float> data(1000, 42.0F); // Vector with 1000 elements, each initialized to 42.0f
    performConcurrentAccessTest(data);
}

// The data to be written to shared memory is of type Image<std::size_t>.

// Write image to shared memory test
TEST_F(SharedMemoryTest, WriteImageToSharedMemory)
{
    Image<std::size_t> image(100U, 100U);                                                               // 100x100 image
    std::vector<std::size_t> data(image.size() * image.num_channels(), static_cast<std::size_t>(255U)); // Fill with white color
    image = Image<std::size_t>(data, 100U, 100U);

    performSharedMemoryTest(image);
}

// Read image from shared memory test
TEST_F(SharedMemoryTest, ReadImageFromSharedMemory)
{
    Image<std::size_t> image(100U, 100U);
    std::vector<std::size_t> data(image.size() * image.num_channels(), static_cast<std::size_t>(255U));
    image = Image<std::size_t>(data, 100U, 100U);

    performSharedMemoryTest(image);
}

// Concurrent access to shared memory Test
TEST_F(SharedMemoryTest, ConcurrentAccess)
{
    Image<std::size_t> image(100U, 100U);
    std::vector<std::size_t> data(image.size() * image.num_channels(), static_cast<std::size_t>(255U));
    image = Image<std::size_t>(data, 100U, 100U);

    performConcurrentAccessTest(image);
}

// Fail to write due to nullptr shared_data_ with Image<std::size_t>.
TEST_F(SharedMemoryTest, WriteFailureDueToNullptr)
{
    SharedMemory<Image<std::size_t>> sharedMemory("SharedMemoryTest", sizeof(Image<std::size_t>));

    // Set shared_data_ to nullptr
    sharedMemory.setSharedDataNullptr();

    Image<std::size_t> image(100U, 100U);
    std::vector<std::size_t> data(image.size() * image.num_channels(), static_cast<std::size_t>(255U));
    image = Image<std::size_t>(data, 100U, 100U);

    const auto status = sharedMemory.write(image);
    EXPECT_EQ(status, SharedMemory<Image<std::size_t>>::WriteStatus::Failure);
}

// Fail to read due to nullptr shared_data_ with Image<std::size_t>.
TEST_F(SharedMemoryTest, ReadFailureDueToNullptr)
{
    SharedMemory<Image<std::size_t>> sharedMemory("SharedMemoryTest", sizeof(Image<std::size_t>));

    // Set shared_data_ to nullptr
    sharedMemory.setSharedDataNullptr();

    EXPECT_THROW(sharedMemory.read(), std::runtime_error);
}
