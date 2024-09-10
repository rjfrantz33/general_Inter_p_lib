/// @file
/// @copyright (c) Jean Frantz René

#include <gtest/gtest.h>
#include "image.h"
#include <vector>

// Test fixture for Image
class ImageTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

// Parameterized test fixture for Image
class ImageParameterizedTest : public ::testing::TestWithParam<std::tuple<std::size_t, std::size_t, std::size_t>>
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

// Test default constructor
TEST_F(ImageTest, DefaultConstructor)
{
    Image<int> image;
    EXPECT_EQ(image.width(), 0U);
    EXPECT_EQ(image.height(), 0U);
    EXPECT_EQ(image.num_channels(), 0U);
    EXPECT_EQ(image.size(), 0U);
}

// Test constructor with default data
TEST_P(ImageParameterizedTest, ConstructorWithDefaultData)
{
    auto [width, height, num_channels] = GetParam();
    Image<int> image(width, height, num_channels);
    EXPECT_EQ(image.width(), width);
    EXPECT_EQ(image.height(), height);
    EXPECT_EQ(image.num_channels(), num_channels);
    EXPECT_EQ(image.size(), width * height);
}

// Test constructor with custom data
TEST_P(ImageParameterizedTest, ConstructorWithCustomData)
{
    auto [width, height, num_channels] = GetParam();
    std::vector<int> data(width * height * num_channels, 255);
    Image<int> image(data, width, height, num_channels);
    EXPECT_EQ(image.width(), width);
    EXPECT_EQ(image.height(), height);
    EXPECT_EQ(image.num_channels(), num_channels);
    EXPECT_EQ(image.size(), width * height);
    EXPECT_EQ(image.readData().size(), data.size());
    EXPECT_EQ(image.readData()[0], 255);
}

// Test readData method
TEST_P(ImageParameterizedTest, ReadData)
{
    auto [width, height, num_channels] = GetParam();
    std::vector<int> data(width * height * num_channels, 255);
    Image<int> image(data, width, height, num_channels);
    auto span = image.readData();
    EXPECT_EQ(span.size(), data.size());
    EXPECT_EQ(span[0], 255);
}

// Test pixelValue method
TEST_P(ImageParameterizedTest, PixelValue)
{
    auto [width, height, num_channels] = GetParam();
    Image<int> image(width, height, num_channels);
    image.pixelValue(0, 0, 0) = 128;
    EXPECT_EQ(image.pixelValue(0, 0, 0), 128);
}

// Test equality operator
TEST_P(ImageParameterizedTest, EqualityOperator)
{
    auto [width, height, num_channels] = GetParam();
    std::vector<int> data1(width * height * num_channels, 255);
    Image<int> image1(data1, width, height, num_channels);

    std::vector<int> data2(width * height * num_channels, 255);
    Image<int> image2(data2, width, height, num_channels);

    EXPECT_TRUE(image1 == image2);

    data2[0] = 128;
    Image<int> image3(data2, width, height, num_channels);
    EXPECT_FALSE(image1 == image3);
}

// Instantiate the parameterized tests with different sets of parameters
INSTANTIATE_TEST_SUITE_P(
    ImageTests,
    ImageParameterizedTest,
    ::testing::Values(
        std::make_tuple(100, 100, 1),
        std::make_tuple(100, 100, 3),
        std::make_tuple(200, 200, 1),
        std::make_tuple(200, 200, 3)
    )
);
