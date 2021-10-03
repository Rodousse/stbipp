#pragma once

#include <array>
#include <limits>
#include <type_traits>

namespace
{
template<class DataType, class ODataType>
struct is_integer_to_integer_cast
{
    static const bool value = (std::is_integral<ODataType>::value && std::is_integral<DataType>::value) &&
                              !std::is_same<DataType, ODataType>::value;
};

template<class DataType, class ODataType>
struct is_float_to_integer_cast
{
    static const bool value = (std::is_floating_point<DataType>::value && std::is_integral<ODataType>::value) &&
                              !std::is_same<DataType, ODataType>::value;
};

template<class DataType, class ODataType>
struct is_integer_to_float_cast
{
    static const bool value = (std::is_integral<DataType>::value && std::is_floating_point<ODataType>::value) &&
                              !std::is_same<DataType, ODataType>::value;
};

template<class DataType>
struct is_data_type_compatible
{
    static const bool value = std::is_integral<DataType>::value || std::is_floating_point<DataType>::value;
};
} // namespace

namespace stbipp
{
/**
 * @brief Color class works like a classic mathematical vector with basic arithmetic operations
 *
 * @tparam DataType Type used to store individual elements
 * @tparam channels Number of channels for the color
 */
template<class DataType, unsigned int channels>
class Color
{
    static_assert(is_data_type_compatible<DataType>::value, "Data type must be an integer or floating point type");
    static_assert(channels, "Color must have at least one channel");

  private:
    std::array<DataType, channels> m_data{};

  public:
    using data_type = DataType;
    using iterator = typename decltype(m_data)::iterator;
    using const_iterator = typename decltype(m_data)::const_iterator;
    using reverse_iterator = typename decltype(m_data)::reverse_iterator;
    using const_reverse_iterator = typename decltype(m_data)::const_reverse_iterator;

    /**
     * @brief Color default constructor
     */
    Color() noexcept;

    /**
     * @brief Color constructor
     * @param[in] value Fill the color with specified value
     */
    explicit Color(DataType value);

    /**
     * @brief Color constructor
     * @param[in] r Red channel value
     * @param[in] g Green channel value
     */
    explicit Color(DataType r, DataType g);

    /**
     * @brief Color constructor
     * @param[in] r Red channel value
     * @param[in] g Green channel value
     * @param[in] b Blue channel value
     */
    explicit Color(DataType r, DataType g, DataType b);

    /**
     * @brief Color constructor
     * @param[in] r Red channel value
     * @param[in] g Green channel value
     * @param[in] b Blue channel value
     * @param[in] a Alpha channel value
     */
    explicit Color(DataType r, DataType g, DataType b, DataType a);

    /**
     * @brief Color copy constructor
     *
     * @param[in] other Color to copy
     */
    Color(const Color& other);

    /**
     * @brief Color move constructor
     *
     * @param other Color to move
     */
    Color(Color&& other);

    /**
     * @brief Color copy operator
     *
     * @param other Color to copy
     *
     * @return Reference to the color
     */
    Color& operator=(const Color& other);

    /**
     * @brief Color move operator
     *
     * @param other Color to move
     *
     * @return Reference to the color
     */
    Color& operator=(Color&& other);

    /**
     * @brief Returns an iterator pointing to the first color channel
     * @return LegacyRandomAccessIterator poiting to (*this)[0]
     */
    iterator begin() noexcept;

    /**
     * @brief Returns a const iterator pointing to the first color channel
     * @return Constant LegacyRandomAccessIterator poiting to (*this)[0]
     */
    const_iterator begin() const noexcept;

    /**
     * @brief Returns a const iterator pointing to the first color channel
     * @return Constant LegacyRandomAccessIterator poiting to (*this)[0]
     */
    const_iterator cbegin() const noexcept;

    /**
     * @brief Returns a reverse iterator pointing to the last color channel
     * @return std::reverse_iterator<iterator> poiting to (*this)[size()-1]
     */
    reverse_iterator rbegin() noexcept;

    /**
     * @brief Returns a constant reverse iterator pointing to the last color channel
     * @return std::reverse_iterator<const_iterator> poiting to (*this)[size()-1]
     */
    const_reverse_iterator rbegin() const noexcept;

    /**
     * @brief Returns a constant reverse iterator pointing to the last color channel
     * @return std::reverse_iterator<const_iterator> poiting to (*this)[size()-1]
     */
    const_reverse_iterator crbegin() const noexcept;

    /**
     * @brief Returns an iterator to the element following the last color channel
     * @return LegacyRandomAccessIterator
     */
    iterator end() noexcept;

    /**
     * @brief Returns a constant iterator to the element following the last color channel
     * @return Constant LegacyRandomAccessIterator
     */
    const_iterator end() const noexcept;

    /**
     * @brief Returns a constant iterator to the element following the last color channel
     * @return Constant LegacyRandomAccessIterator
     */
    const_iterator cend() const noexcept;

    /**
     * @brief Returns a reverse iterator to the element preceding the first color channel
     * @return std::reverse_iterator<iterator>
     */
    reverse_iterator rend() noexcept;

    /**
     * @brief Returns a constant reverse iterator to the element preceding the first color channel
     * @return std::reverse_iterator<const_iterator>
     */
    const_reverse_iterator rend() const noexcept;

    /**
     * @brief Returns a constant reverse iterator to the element preceding the first color channel
     * @return std::reverse_iterator<const_iterator>
     */
    const_reverse_iterator crend() const noexcept;

    /**
     * @brief Access the red channel data
     * @return Red channel value
     */
    DataType r() const;

    /**
     * @brief Access the red channel data
     * @return Red channel value
     */
    DataType& r();

    /**
     * @brief Access the green channel data
     * @return Green channel value
     */
    DataType g() const;

    /**
     * @brief Access the green channel data
     * @return Green channel value
     */
    DataType& g();

    /**
     * @brief Access the blue channel data
     * @return Blue channel value
     */
    DataType b() const;

    /**
     * @brief Access the blue channel data
     * @return Blue channel value
     */
    DataType& b();

    /**
     * @brief Access the alpha channel data
     * @return Alpha channel value
     */
    DataType a() const;

    /**
     * @brief Access the alpha channel data
     * @return Alpha channel value
     */
    DataType& a();

    /**
     * @brief Retrieve the number of channels
     * @return Channels count
     */
    constexpr unsigned int size() const noexcept;

    /**
     * @brief Access the data of the first element
     * @return A pointer to the first color element
     */
    const DataType* data() const;

    /**
     * @brief Access the data of the first element
     * @return A pointer to the first color element
     */
    DataType* data();

    /**
     * @brief Access the data the given index
     * @return The value at the given index
     */
    DataType operator[](int index) const;

    /**
     * @brief Access the data the given index
     * @return The value at the given index
     */
    DataType& operator[](int index);

  private:
    /**
     * @brief Copy data of another color into this, with other uses the same data type as this but with possibly a
     * different length
     * @param[in] other Color to copy
     */
    template<typename ODataType, unsigned int oDataSize>
    void copy(const Color<ODataType, oDataSize>& other,
              typename std::enable_if<std::is_same<DataType, ODataType>::value>::type* = nullptr);

    /**
     * @brief Copy data of another color into this, with other using an integer type and this a floating type
     * @param[in] other Color to copy
     */
    template<class ODataType, unsigned int oDataSize>
    void copy(const Color<ODataType, oDataSize>& other,
              typename std::enable_if<is_float_to_integer_cast<DataType, ODataType>::value>::type* = nullptr);

    /**
     * @brief Copy data of another color into this, with other using a floating type and this an integer type
     * @param[in] other Color to copy
     */
    template<class ODataType, unsigned int oDataSize>
    void copy(const Color<ODataType, oDataSize>& other,
              typename std::enable_if<is_integer_to_float_cast<DataType, ODataType>::value>::type* = nullptr);

    /**
     * @brief Copy data of another color into this, with this and other using different integer types
     * @param[in] other Color to copy
     */
    template<class ODataType, unsigned int oDataSize>
    void copy(const Color<ODataType, oDataSize>& other,
              typename std::enable_if<is_integer_to_integer_cast<DataType, ODataType>::value>::type* = nullptr);

  public:
    /**
     * @brief Assignment operator
     * @param[in] other The color to copy
     * @return A reference to this
     */
    template<
      class ODataType,
      unsigned int oDataSize,
      typename std::enable_if<!(std::is_same<ODataType, DataType>::value && oDataSize == channels), bool>::type = true>
    Color& operator=(const Color<ODataType, oDataSize>& other);

    /**
     * @brief Color copy constructor
     *
     * @param other Color to copy
     */
    template<
      class ODataType,
      unsigned int oDataSize,
      typename std::enable_if<!(std::is_same<ODataType, DataType>::value && oDataSize == channels), bool>::type = true>
    Color(const Color<ODataType, oDataSize>& other);

    /**
     * @brief Add the content of other to this
     * @param[in] other The color to add
     * @return A reference to this
     */
    template<class ODataType, unsigned int oDataSize>
    Color& operator+=(const Color<ODataType, oDataSize>& other);

    /**
     * @brief Add the content of val to all channels of this
     *
     * @tparam Real val type
     * @param[in] val Value to be added
     *
     * @return A reference to this
     */
    template<class Real>
    typename std::enable_if<is_data_type_compatible<Real>::value, Color>::type& operator+=(Real val);

    /**
     * @brief Add the content of other to this in a new object
     * @param[in] other The color to add
     * @return The addition of this and other
     */
    template<class ODataType, unsigned int oDataSize>
    Color operator+(const Color<ODataType, oDataSize>& other) const;

    /**
     * @brief Add the content of val to all channels content of this in a new object
     *
     * @tparam Real val type
     * @param[in] val Value to be added
     *
     * @return The addition of this and val
     */
    template<class Real>
    typename std::enable_if<is_data_type_compatible<Real>::value, Color>::type operator+(Real val) const;

    /**
     * @brief Substract the content of this by other
     * @param[in] other The color to substract
     * @return A reference to this
     */
    template<class ODataType, unsigned int oDataSize>
    Color& operator-=(const Color<ODataType, oDataSize>& other);

    /**
     * @brief Substract the content of val to all channels content of this
     *
     * @tparam Real val type
     * @param[in] val Value to be substracted
     *
     * @return A reference to this
     */
    template<class Real>
    typename std::enable_if<is_data_type_compatible<Real>::value, Color>::type& operator-=(Real val);

    /**
     * @brief Substract the content of this by other in a new object
     * @param[in] other The color to substract
     * @return The substraction of this by other
     */
    template<class ODataType, unsigned int oDataSize>
    Color operator-(const Color<ODataType, oDataSize>& other) const;

    /**
     * @brief Substract the content of val to all channels of this in a new object
     *
     * @tparam Real val type
     * @param[in] val Value to be substracted
     *
     * @return The substraction of this and val
     */
    template<class Real>
    typename std::enable_if<is_data_type_compatible<Real>::value, Color>::type operator-(Real val) const;

    /**
     * @brief Negate the content of this
     * @return The negative version of this
     */
    Color operator-() const;

    /**
     * @brief Multiply the content of other by this
     * @param[in] other The color to multiply by
     * @return A reference to this
     */
    template<class ODataType, unsigned int oDataSize>
    Color& operator*=(const Color<ODataType, oDataSize>& other);

    /**
     * @brief Multiply the content of val by all channels value
     *
     * @tparam Real val type
     * @param[in] val Value to multiply
     *
     * @return A reference to this
     */
    template<class Real>
    typename std::enable_if<is_data_type_compatible<Real>::value, Color>::type& operator*=(Real val);

    /**
     * @brief Multiply the content of this by other in a new object
     * @param[in] other The color to multiply
     * @return The multiplication of this by other
     */
    template<class ODataType, unsigned int oDataSize>
    Color operator*(const Color<ODataType, oDataSize>& other) const;

    /**
     * @brief Multiply the content of val by all channels value in a new object
     *
     * @tparam Real val type
     * @param[in] val Value to multiply
     *
     * @return The multiplication of this and val
     */
    template<class Real>
    typename std::enable_if<is_data_type_compatible<Real>::value, Color>::type operator*(Real val) const;

    /**
     * @brief Divide the content of this by other
     * @param[in] other The color to divide
     * @return A reference to this
     */
    template<class ODataType, unsigned int oDataSize>
    Color& operator/=(const Color<ODataType, oDataSize>& other);

    /**
     * @brief Divide the content of all channels by val
     *
     * @tparam Real val type
     * @param[in] val Value to divide by
     *
     * @return A reference to this
     */
    template<class Real>
    typename std::enable_if<is_data_type_compatible<Real>::value, Color>::type& operator/=(Real val);

    /**
     * @brief Divide the content of this by other in a new object
     * @param[in] other The color to divide
     * @return The division of this by other
     */
    template<class ODataType, unsigned int oDataSize>
    Color operator/(const Color<ODataType, oDataSize>& other) const;

    /**
     * @brief Divide the content of all channels by val in a new object
     *
     * @tparam Real val type
     * @param[in] val Value to divide by
     *
     * @return The division of this and val
     */
    template<class Real>
    typename std::enable_if<is_data_type_compatible<Real>::value, Color>::type operator/(Real val) const;
};
} // namespace stbipp

template<class DataType, unsigned int channels, class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, stbipp::Color<DataType, channels>>::type operator+(
  Real val, const stbipp::Color<DataType, channels>& col);

template<class DataType, unsigned int channels, class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, stbipp::Color<DataType, channels>>::type operator-(
  Real val, const stbipp::Color<DataType, channels>& col);

template<class DataType, unsigned int channels, class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, stbipp::Color<DataType, channels>>::type operator*(
  Real val, const stbipp::Color<DataType, channels>& col);

#include "stbipp/Color.inl"

namespace stbipp
{
using Colorf = Color<float, 1>;
using Color2f = Color<float, 2>;
using Color3f = Color<float, 3>;
using Color4f = Color<float, 4>;

using Coloruc = Color<unsigned char, 1>;
using Color2uc = Color<unsigned char, 2>;
using Color3uc = Color<unsigned char, 3>;
using Color4uc = Color<unsigned char, 4>;

using Colorus = Color<unsigned short, 1>;
using Color2us = Color<unsigned short, 2>;
using Color3us = Color<unsigned short, 3>;
using Color4us = Color<unsigned short, 4>;
} // namespace stbipp
