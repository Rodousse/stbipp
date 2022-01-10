
#include <cstring>
namespace stbipp
{
template<class DataType, unsigned int channels>
Color<DataType, channels>::Color() noexcept: Color<DataType, channels>(static_cast<DataType>(0.0))
{
}

template<class DataType, unsigned int channels>
Color<DataType, channels>::Color(DataType value)
{
    std::fill(m_data.begin(), m_data.end(), value);
}

template<class DataType, unsigned int channels>
Color<DataType, channels>::Color(DataType r, DataType g): m_data({r, g})
{
    static_assert(channels > 1, "Can't set value beyond size of color (number of channels < 2)");
}

template<class DataType, unsigned int channels>
Color<DataType, channels>::Color(DataType r, DataType g, DataType b): m_data({r, g, b})
{
    static_assert(channels > 2, "Can't set value beyond size of color (number of channels < 3)");
}

template<class DataType, unsigned int channels>
Color<DataType, channels>::Color(DataType r, DataType g, DataType b, DataType a): m_data({r, g, b, a})
{
    static_assert(channels > 3, "Can't set value beyond size of color (number of channels < 4)");
}

template<class DataType, unsigned int channels>
Color<DataType, channels>::Color(const DataType* data)
{
    memcpy(m_data.data(), data, channels * sizeof(DataType));
}

template<class DataType, unsigned int channels>
Color<DataType, channels>::Color(const Color<DataType, channels>& other): m_data(other.m_data)
{
}

template<class DataType, unsigned int channels>
Color<DataType, channels>::Color(Color<DataType, channels>&& other): m_data(std::move(other.m_data))
{
}

template<class DataType, unsigned int channels>
Color<DataType, channels>& Color<DataType, channels>::operator=(const Color<DataType, channels>& other)
{
    std::copy(other.m_data.cbegin(), other.m_data.cend(), m_data.begin());
    return *this;
}

template<class DataType, unsigned int channels>
Color<DataType, channels>& Color<DataType, channels>::operator=(Color<DataType, channels>&& other)
{
    std::swap(other.m_data, m_data);
    return *this;
}

template<class DataType, unsigned int channels>
typename Color<DataType, channels>::iterator Color<DataType, channels>::begin() noexcept
{
    return m_data.begin();
}

template<class DataType, unsigned int channels>
typename Color<DataType, channels>::const_iterator Color<DataType, channels>::begin() const noexcept
{
    return m_data.cbegin();
}

template<class DataType, unsigned int channels>
typename Color<DataType, channels>::const_iterator Color<DataType, channels>::cbegin() const noexcept
{
    return m_data.cbegin();
}

template<class DataType, unsigned int channels>
typename Color<DataType, channels>::reverse_iterator Color<DataType, channels>::rbegin() noexcept
{
    return m_data.rbegin();
}

template<class DataType, unsigned int channels>
typename Color<DataType, channels>::const_reverse_iterator Color<DataType, channels>::rbegin() const noexcept
{
    return m_data.crbegin();
}

template<class DataType, unsigned int channels>
typename Color<DataType, channels>::const_reverse_iterator Color<DataType, channels>::crbegin() const noexcept
{
    return m_data.crbegin();
}

template<class DataType, unsigned int channels>
typename Color<DataType, channels>::iterator Color<DataType, channels>::end() noexcept
{
    return m_data.end();
}

template<class DataType, unsigned int channels>
typename Color<DataType, channels>::const_iterator Color<DataType, channels>::end() const noexcept
{
    return m_data.cend();
}

template<class DataType, unsigned int channels>
typename Color<DataType, channels>::const_iterator Color<DataType, channels>::cend() const noexcept
{
    return m_data.cend();
}

template<class DataType, unsigned int channels>
typename Color<DataType, channels>::reverse_iterator Color<DataType, channels>::rend() noexcept
{
    return m_data.rend();
}

template<class DataType, unsigned int channels>
typename Color<DataType, channels>::const_reverse_iterator Color<DataType, channels>::rend() const noexcept
{
    return m_data.crend();
}

template<class DataType, unsigned int channels>
typename Color<DataType, channels>::const_reverse_iterator Color<DataType, channels>::crend() const noexcept
{
    return m_data.crend();
}

template<class DataType, unsigned int channels>
DataType Color<DataType, channels>::r() const
{
    return m_data[0];
}

template<class DataType, unsigned int channels>
DataType& Color<DataType, channels>::r()
{
    return m_data[0];
}

template<class DataType, unsigned int channels>
DataType Color<DataType, channels>::g() const
{
    static_assert(channels > 1, "Can't access the element at the second index (green) of a color with 1 channel");
    return m_data[1];
}

template<class DataType, unsigned int channels>
DataType& Color<DataType, channels>::g()
{
    static_assert(channels > 1, "Can't access the element at the second index (green) of a color with 1 channel");
    return m_data[1];
}

template<class DataType, unsigned int channels>
DataType Color<DataType, channels>::b() const
{
    static_assert(channels > 2, "Can't access the element at the third index (blue) of a color with 1 or 2 channels");
    return m_data[2];
}

template<class DataType, unsigned int channels>
DataType& Color<DataType, channels>::b()
{
    static_assert(channels > 2, "Can't access the element at the third index (blue) of a color with 1 or 2 channels");
    return m_data[2];
}

template<class DataType, unsigned int channels>
DataType Color<DataType, channels>::a() const
{
    static_assert(channels > 3,
                  "Can't access the element at the fourth index (alpha) of a color with 1, 2 or 3 channels");
    return m_data[3];
}

template<class DataType, unsigned int channels>
DataType& Color<DataType, channels>::a()
{
    static_assert(channels > 3,
                  "Can't access the element at the fourth index (alpha) of a color with 1, 2 or 3 channels");
    return m_data[3];
}

template<class DataType, unsigned int channels>
constexpr unsigned int Color<DataType, channels>::size() const noexcept
{
    return channels;
}

template<class DataType, unsigned int channels>
const DataType* Color<DataType, channels>::data() const
{
    return m_data.data();
}

template<class DataType, unsigned int channels>
DataType* Color<DataType, channels>::data()
{
    return m_data.data();
}

template<class DataType, unsigned int channels>
DataType Color<DataType, channels>::operator[](int index) const
{
    return m_data[index];
}

template<class DataType, unsigned int channels>
DataType& Color<DataType, channels>::operator[](int index)
{
    return m_data[index];
}

template<class DataType, unsigned int channels>
template<class ODataType, unsigned int oDataSize>
void Color<DataType, channels>::copy(const Color<ODataType, oDataSize>& other,
                                     typename std::enable_if<std::is_same<DataType, ODataType>::value>::type*)
{
    std::size_t minSize = std::min(oDataSize, channels);
    for(std::size_t index = 0; index < minSize; ++index)
    {
        m_data[index] = other[static_cast<int>(index)];
    }
    for(std::size_t index = minSize; index < channels; ++index)
    {
        m_data[index] = 0.0;
    }
}

template<class DataType, unsigned int channels>
template<class ODataType, unsigned int oDataSize>
void Color<DataType, channels>::copy(
  const Color<ODataType, oDataSize>& other,
  typename std::enable_if<is_float_to_integer_cast<DataType, ODataType>::value>::type*)
{
    std::size_t minSize = std::min(oDataSize, channels);
    for(std::size_t index = 0; index < minSize; ++index)
    {
        m_data[index] = static_cast<DataType>(other[static_cast<int>(index)]) / std::numeric_limits<ODataType>::max();
    }
    for(std::size_t index = minSize; index < channels; ++index)
    {
        m_data[index] = 0.0;
    }
}

template<class DataType, unsigned int channels>
template<class ODataType, unsigned int oDataSize>
void Color<DataType, channels>::copy(
  const Color<ODataType, oDataSize>& other,
  typename std::enable_if<is_integer_to_float_cast<DataType, ODataType>::value>::type*)
{
    std::size_t minSize = std::min(oDataSize, channels);
    for(std::size_t index = 0; index < minSize; ++index)
    {
        m_data[index] = static_cast<DataType>(std::numeric_limits<DataType>::max() * other[static_cast<int>(index)]);
    }
    for(std::size_t index = minSize; index < channels; ++index)
    {
        m_data[index] = static_cast<DataType>(0.0);
    }
}

template<class DataType, unsigned int channels>
template<class ODataType, unsigned int oDataSize>
void Color<DataType, channels>::copy(
  const Color<ODataType, oDataSize>& other,
  typename std::enable_if<is_integer_to_integer_cast<DataType, ODataType>::value>::type*)
{
    std::size_t minSize = std::min(oDataSize, channels);
    for(std::size_t index = 0; index < minSize; ++index)
    {
        m_data[index] =
          static_cast<DataType>((static_cast<double>(other[index]) * std::numeric_limits<DataType>::max()) /
                                std::numeric_limits<ODataType>::max());
    }
    for(std::size_t index = minSize; index < channels; ++index)
    {
        m_data[index] = 0.0;
    }
}

template<class DataType, unsigned int channels>
template<class ODataType,
         unsigned int oDataSize,
         typename std::enable_if<!(std::is_same<ODataType, DataType>::value && oDataSize == channels), bool>::type>
Color<DataType, channels>& Color<DataType, channels>::operator=(const Color<ODataType, oDataSize>& other)
{
    copy(other);
    return *this;
}

template<class DataType, unsigned int channels>
template<class ODataType,
         unsigned int oDataSize,
         typename std::enable_if<!(std::is_same<ODataType, DataType>::value && oDataSize == channels), bool>::type>
Color<DataType, channels>::Color(const Color<ODataType, oDataSize>& other)
{
    copy(other);
}

template<class DataType, unsigned int channels>
template<class ODataType, unsigned int oDataSize>
Color<DataType, channels>& Color<DataType, channels>::operator+=(const Color<ODataType, oDataSize>& other)
{
    static_assert(oDataSize == channels && std::is_same<DataType, ODataType>::value,
                  "Both colors must be of the same size and type");
    for(auto comp = 0; comp < channels; ++comp)
    {
        m_data[comp] += other[comp];
    }
    return *this;
}

template<class DataType, unsigned int channels>
template<class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, Color<DataType, channels>>::type&
Color<DataType, channels>::operator+=(Real val)
{
    for(auto& channel: m_data)
    {
        channel += static_cast<DataType>(val);
    }
    return *this;
}

template<class DataType, unsigned int channels>
template<class ODataType, unsigned int oDataSize>
Color<DataType, channels> Color<DataType, channels>::operator+(const Color<ODataType, oDataSize>& other) const
{
    static_assert(oDataSize == channels && std::is_same<DataType, ODataType>::value,
                  "Both colors must be of the same size and type");
    Color temp{*this};
    return temp += other;
}

template<class DataType, unsigned int channels>
template<class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, Color<DataType, channels>>::type
Color<DataType, channels>::operator+(Real val) const
{
    Color temp{*this};
    return temp += val;
}

template<class DataType, unsigned int channels>
template<class ODataType, unsigned int oDataSize>
Color<DataType, channels>& Color<DataType, channels>::operator-=(const Color<ODataType, oDataSize>& other)
{
    static_assert(oDataSize == channels && std::is_same<DataType, ODataType>::value,
                  "Both colors must be of the same size and type");
    for(auto comp = 0; comp < channels; ++comp)
    {
        m_data[comp] -= other[comp];
    }
    return *this;
}

template<class DataType, unsigned int channels>
template<class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, Color<DataType, channels>>::type&
Color<DataType, channels>::operator-=(Real val)
{
    for(auto& channel: m_data)
    {
        channel -= static_cast<DataType>(val);
    }
    return *this;
}

template<class DataType, unsigned int channels>
template<class ODataType, unsigned int oDataSize>
Color<DataType, channels> Color<DataType, channels>::operator-(const Color<ODataType, oDataSize>& other) const
{
    static_assert(oDataSize == channels && std::is_same<DataType, ODataType>::value,
                  "Both colors must be of the same size and type");
    Color temp{*this};
    return temp -= other;
}

template<class DataType, unsigned int channels>
template<class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, Color<DataType, channels>>::type
Color<DataType, channels>::operator-(Real val) const
{
    Color temp{*this};
    return temp -= val;
}

template<class DataType, unsigned int channels>
Color<DataType, channels> Color<DataType, channels>::operator-() const
{
    Color temp{0.0f};
    return temp -= *this;
}

template<class DataType, unsigned int channels>
template<class ODataType, unsigned int oDataSize>
Color<DataType, channels>& Color<DataType, channels>::operator*=(const Color<ODataType, oDataSize>& other)
{
    static_assert(oDataSize == channels && std::is_same<DataType, ODataType>::value,
                  "Both colors must be of the same size and type");
    for(auto comp = 0; comp < channels; ++comp)
    {
        m_data[comp] *= other[comp];
    }
    return *this;
}
template<class DataType, unsigned int channels>
template<class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, Color<DataType, channels>>::type&
Color<DataType, channels>::operator*=(Real val)
{
    for(auto& channel: m_data)
    {
        channel *= val;
    }
    return *this;
}

template<class DataType, unsigned int channels>
template<class ODataType, unsigned int oDataSize>
Color<DataType, channels> Color<DataType, channels>::operator*(const Color<ODataType, oDataSize>& other) const
{
    static_assert(oDataSize == channels && std::is_same<DataType, ODataType>::value,
                  "Both colors must be of the same size and type");
    Color temp{*this};
    return temp *= other;
}

template<class DataType, unsigned int channels>
template<class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, Color<DataType, channels>>::type
  Color<DataType, channels>::operator*(Real val) const
{
    Color temp{*this};
    return temp *= val;
}

template<class DataType, unsigned int channels>
template<class ODataType, unsigned int oDataSize>
Color<DataType, channels>& Color<DataType, channels>::operator/=(const Color<ODataType, oDataSize>& other)
{
    static_assert(oDataSize == channels && std::is_same<DataType, ODataType>::value,
                  "Both colors must be of the same size and type");
    for(auto comp = 0; comp < channels; ++comp)
    {
        m_data[comp] /= other[comp];
    }
    return *this;
}

template<class DataType, unsigned int channels>
template<class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, Color<DataType, channels>>::type&
Color<DataType, channels>::operator/=(Real val)
{
    for(auto& channel: m_data)
    {
        channel /= val;
    }
    return *this;
}

template<class DataType, unsigned int channels>
template<class ODataType, unsigned int oDataSize>
Color<DataType, channels> Color<DataType, channels>::operator/(const Color<ODataType, oDataSize>& other) const
{
    static_assert(oDataSize == channels && std::is_same<DataType, ODataType>::value,
                  "Both colors must be of the same size and type");
    Color temp{*this};
    return temp /= other;
}

template<class DataType, unsigned int channels>
template<class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, Color<DataType, channels>>::type
Color<DataType, channels>::operator/(Real val) const
{
    Color temp{*this};
    return temp /= val;
}
} // namespace stbipp

template<class DataType, unsigned int channels, class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, stbipp::Color<DataType, channels>>::type operator+(
  Real val, const stbipp::Color<DataType, channels>& col)
{
    return col + val;
}

template<class DataType, unsigned int channels, class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, stbipp::Color<DataType, channels>>::type operator-(
  Real val, const stbipp::Color<DataType, channels>& col)
{
    stbipp::Color<DataType, channels> retCol{val};
    return retCol - col;
}

template<class DataType, unsigned int channels, class Real>
typename std::enable_if<is_data_type_compatible<Real>::value, stbipp::Color<DataType, channels>>::type operator*(
  Real val, const stbipp::Color<DataType, channels>& col)
{
    return col * val;
}
