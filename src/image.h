
/// @file
/// @copyright (c) Jean Frantz René
/// Interface of the Image class.

#ifndef GENERAL_INTER_P_LIB_SRC_IMAGE_H
#define GENERAL_INTER_P_LIB_SRC_IMAGE_H

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <cstddef>
#include <cstdint>
#include <iostream>

#include <vector>
#include <span>
#include <cassert>

/// @brief The Image class template in image.h is designed to represent an image with customizable data types.
/// It provides constructors for creating an image with default and custom data,
/// and various member functions to access image properties and data.
///
/// @tparam T template to allow different data types for the image pixels.
/// @param width Width of the image.
/// @param height Height of the image.
/// @param num_channels Number of channels in the image (e.g., RGB has 3 channels).
/// @param data Vector to hold the image data in a contiguous block.
///
/// @pre num_channels > 0.
/// @pre idx < data_.size().
/// @pre width >= 0
/// @pre height >= 0
///
template <typename T>
class Image final
{
public:
    /// Default constructor
    Image() : width_(0), height_(0), num_channels_(0), data_() {}

    /// Construct an image object with default data.
    Image(std::size_t width, std::size_t height, std::size_t num_channels = 1)
        : width_(width), height_(height), num_channels_(num_channels), data_(width_ * height_ * num_channels_)
    {
        /// To ensure that the image object is always constructed with a valid number of channels.
        assert(num_channels > 0U && "Number of channels must be greater than 0");
        assert(width > 0U && "Width must be greater than or equal to 0");
        assert(height > 0U && "Height must be greater than or equal to 0");
    }

    /// Constructs which allows the initialization of image object with custom data.
    Image(std::vector<T> const &data, std::size_t width, std::size_t height, std::size_t num_channels = 1)
        : width_(width), height_(height), num_channels_(num_channels), data_(data)
    {
    }

    /// @brief Get the size of the image.
    /// @return The size of the image.
    std::size_t size() const { return width_ * height_; }

    /// @brief Get the width of the image.
    /// @return The width of the image.
    std::size_t width() const { return width_; }

    /// @brief Get the height of the image.
    /// @return The height of the image.
    std::size_t height() const { return height_; }

    /// @brief Get the number of channels in the image.
    /// @return The number of channels in the image.
    std::size_t num_channels() const { return num_channels_; }

    /// @brief Function to read the image data.
    /// @return A span to the image data.
    std::span<const T> readData() const { return std::span<const T>(data_); }

    /// @brief Setter and getter pixel value at a given position in the image.
    /// Converts a 3D pixel into 1D index.
    /// @param pixel_position_along_width The horizontal position of the pixel.
    /// @param pixel_position_along_heighthorizontal The vertical position of the pixel.
    /// @param channel channel of the pixel (e.g., 0 for red, 1 for green, 2 for blue in an RGB image).
    /// The Channel data is to be set by the user.
    ///
    /// @return The pixel value at the given position.
    ///
    T &pixelValue(std::size_t const pixel_position_along_width, std::size_t const pixel_position_along_height, std::size_t const channel)
    {
        auto const idx = channel * (height_ * width_) + (pixel_position_along_height * width_ + pixel_position_along_width);
        assert(idx < data_.size() && "Index out of bounds");
        return data_[idx];
    }

    const T &pixelValue(std::size_t const pixel_position_along_width, std::size_t const pixel_position_along_height, std::size_t const channel) const
    {
        auto const idx = channel * (height_ * width_) + (pixel_position_along_height * width_ + pixel_position_along_width);
        assert(idx < data_.size() && "Index out of bounds");
        return data_[idx];
    }

    /// @brief Equality operator for comparing two Image objects.
    bool operator==(const Image<T> &other) const
    {
        return width_ == other.width_ &&
               height_ == other.height_ &&
               data_ == other.data_;
    }

private:
    std::size_t width_;
    std::size_t height_;
    std::size_t num_channels_;
    std::vector<T> data_;
};
#endif // GENERAL_INTER_P_LIB_SRC_IMAGE_H

