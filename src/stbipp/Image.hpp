#pragma once

#include "stbipp/Color.hpp"
#include "stbipp/ImageFormat.hpp"
#include "stbipp/StbippSymbols.h"

#include <memory>
#include <vector>

namespace stbipp
{
/**
 * @brief The Image class is a 2D pixel matrix
 * A pixel with 4 float channels
 */
class STBIPP_API Image
{
  public:
    using Color = Color4f;

    /**
     * @brief Default image constructor
     */
    explicit Image() = default;

    /**
     * @brief Image contructor, resize the image with the given dimensions
     * @param[in] width The image width
     * @param[in] height The image height
     */
    Image(int width, int height);

    /**
     * @brief Image contructor, filling the content with the given color
     * @param[in] width The image width
     * @param[in] height The image height
     * @param[in] color The image will be filled with this color
     */
    Image(int width, int height, const Color& color);

    /**
     * @brief Image constructor
     * @param[in] data The data that will populate the pixel matrix
     * @param[in] width Image width
     * @param[in] height Image height
     * @param[in] pixelFormat The data pixel format
     * (must be set depending on the data argument
     * e.g : RGBA8 this means that data is pointing to an unsigned char array of dimension :
     * width * height * formatChannelCount(pixelFormat))
     */
    Image(const void* data, int width, int height, ImageFormat pixelFormat);

    /**
     * @brief Image copy constructor
     * @param[in] other The image to copy
     */
    Image(const Image& other);

    /**
     * @brief Image move constructor
     * @param[in] other The image moved
     */
    Image(Image&& other);

    /**
     * @brief Image destructor
     */
    ~Image() = default;

    /**
     * @brief Access the data of the first element
     * @return Pointer to the color matrix data
     */
    const Color* data() const;

    /**
     * @brief Access the data of the first element
     * @return Pointer to the color matrix data
     */
    Color* data();

    /**
     * @brief Fill the image with the given color
     * @param[in] color The image will be filled with this color
     */
    void fill(const Color& color);

    /**
     * @brief Resize the image with the given dimensions
     * @param[in] width The new image width
     * @param[in] height The new image height
     */
    void resize(int width, int height);

    /**
     * @brief Cast data to another color type
     * @tparam ColorType The new color type (e.g : Color3uc, Colorus,...)
     * @return The pixel matrix casted
     */
    template<class ColorType>
    std::vector<ColorType> castData() const
    {
        std::size_t size = m_width * m_height;
        std::vector<ColorType> castedValue(size);
        for(std::size_t index = 0; index < size; ++index)
        {
            castedValue[index] = m_data[index];
        }
        return castedValue;
    }

    /**
     * @brief Image height getter
     * @return The image height
     */
    int height() const;

    /**
     * @brief Image width getter
     * @return The image width
     */
    int width() const;

    /**
     * @brief Accessor to the color at the specified coordinate
     * @param[in] column The x coordinate
     * @param[in] row The y coordinate
     * @return The color at the given coordinate
     */
    const Color& operator()(int column, int row) const;

    /**
     * @brief Accessor to the color at the specified coordinate
     * @param[in] column The x coordinate
     * @param[in] row The y coordinate
     * @return The color at the given coordinate
     */
    Color& operator()(int column, int row);

    /**
     * @brief Copy operator
     * @param[in] other The image to copy
     * @return A reference to the image
     */
    Image& operator=(const Image& other);

    /**
     * @brief Move operator
     * @param[in] other The image to move
     * @return A reference to the image
     */
    Image& operator=(Image&& other) = default;

  private:
    /**
     * @brief Copy the data of the other image into this
     * @param[in] other The image to copy
     */
    void copyData(const Image& other);

    /**
     * @brief Copy the data at the given location
     * @param[in] data Pointer to the data
     * @param[in] width Image width
     * @param[in] height Image height
     * @param[in] pixelFormat The pixel format describing the data format
     */
    void copyData(const unsigned char* data, int width, int height, ImageFormat pixelFormat);

    /**
     * @brief Copy the data at the given location
     * @param[in] data Pointer to the data
     * @param[in] width Image width
     * @param[in] height Image height
     * @param[in] pixelFormat The pixel format describing the data format
     */
    void copyData(const unsigned short* data, int width, int height, ImageFormat pixelFormat);

    /**
     * @brief Copy the data at the given location
     * @param[in] data Pointer to the data
     * @param[in] width Image width
     * @param[in] height Image height
     * @param[in] pixelFormat The pixel format describing the data format
     */
    void copyData(const float* data, int width, int height, ImageFormat pixelFormat);

    /**
     * @brief Resize the pixel matrix
     * @param[in] width New image width
     * @param[in] height New image height
     */
    void resizeData(int width, int height);

    std::vector<Color> m_data;
    int m_width{0};
    int m_height{0};

  public:
    using iterator = typename decltype(m_data)::iterator;
    using const_iterator = typename decltype(m_data)::const_iterator;
    using reverse_iterator = typename decltype(m_data)::reverse_iterator;
    using const_reverse_iterator = typename decltype(m_data)::const_reverse_iterator;
    /**
     * @brief Returns a row wise iterator
     * @return LegacyRandomAccessIterator
     */
    iterator begin() noexcept;

    /**
     * @brief Returns a row wise iterator
     * @return Constant LegacyRandomAccessIterator
     */
    const_iterator begin() const noexcept;

    /**
     * @brief Returns a row wise iterator
     * @return Constant LegacyRandomAccessIterator
     */
    const_iterator cbegin() const noexcept;

    /**
     * @brief Returns a reverse row wise iterator
     * @return std::reverse_iterator<iterator>
     */
    reverse_iterator rbegin() noexcept;

    /**
     * @brief Returns a constant reverse row wise iterator
     * @return std::reverse_iterator<const_iterator>
     */
    const_reverse_iterator rbegin() const noexcept;

    /**
     * @brief Returns a constant reverse row wise
     * @return std::reverse_iterator<const_iterator>
     */
    const_reverse_iterator crbegin() const noexcept;

    /**
     * @brief Returns a reverse row wise iterator
     * @return LegacyRandomAccessIterator
     */
    iterator end() noexcept;

    /**
     * @brief Returns a constant row wise iterator
     * @return Constant LegacyRandomAccessIterator
     */
    const_iterator end() const noexcept;

    /**
     * @brief Returns a constant row wise iterator
     * @return Constant LegacyRandomAccessIterator
     */
    const_iterator cend() const noexcept;

    /**
     * @brief Returns a reverse row wise iterator
     * @return std::reverse_iterator<iterator>
     */
    reverse_iterator rend() noexcept;

    /**
     * @brief Returns a constant reverse row wise iterator
     * @return std::reverse_iterator<const_iterator>
     */
    const_reverse_iterator rend() const noexcept;

    /**
     * @brief Returns a constant reverse row wise iterator
     * @return std::reverse_iterator<const_iterator>
     */
    const_reverse_iterator crend() const noexcept;
};

} // namespace stbipp
