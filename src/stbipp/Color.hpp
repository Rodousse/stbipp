#pragma once

#include "stbipp/TypeTraits.hpp"

#include <array>

namespace stbipp {


template<class DataType, int nbComponents, typename = typename std::enable_if<is_color_format_supported<DataType, nbComponents>>::type>
class Color
{
public:

    Color() = default;

    template<typename = typename std::enable_if<(nbComponents > 0)>::type > Color(DataType r):
        m_data({r})
    {}
    template<typename = typename std::enable_if<(nbComponents > 1)>::type > Color(DataType r,
            DataType g):
        m_data({r, g})
    {}
    template<typename = typename std::enable_if<(nbComponents > 2)>::type > Color(DataType r,
            DataType g,
            DataType b):
        m_data({r, g, b})
    {}
    template<typename = typename std::enable_if<(nbComponents > 3)>::type > Color(DataType r,
            DataType g,
            DataType b, DataType a):
        m_data({r, g, b, a})
    {}


    template<typename = typename std::enable_if<(nbComponents > 0)>::type >
    DataType r()const
    {
        return m_data[0];
    }

    template<typename = typename std::enable_if<(nbComponents > 0) >::type >
    DataType & r()
    {
        return m_data[0];
    }

    template<typename = typename std::enable_if<(nbComponents > 1)>::type >
    DataType g()const
    {
        return m_data[1];
    }
    template<typename = typename std::enable_if<(nbComponents > 1)>::type >
    DataType & g()
    {
        return m_data[1];
    }

    template<typename = typename std::enable_if<(nbComponents > 2)>::type >
    DataType b()const
    {
        return m_data[2];
    }

    template<typename = typename std::enable_if<(nbComponents > 2)>::type >
    DataType & b()
    {
        return m_data[2];
    }

    template<typename = typename std::enable_if<(nbComponents > 3)>::type >
    DataType a()const
    {
        return m_data[3];
    }

    template<typename = typename std::enable_if<(nbComponents > 3)>::type >
    DataType & a()
    {
        return m_data[3];
    }

    int size()const
    {
        return nbComponents;
    }

    DataType* data()
    {
        return m_data.data();
    }

    DataType operator[](int index)const
    {
        return m_data[index];
    }

    DataType& operator[](int index)
    {
        return m_data[index];
    }

private:
    template<typename ODataType, int oDataSize>
    void copy(const Color<DataType, oDataSize>& other,
              typename std::enable_if <std::is_same<DataType, ODataType>::value>::type* = nullptr)
    {
        std::size_t minSize = std::min(oDataSize, nbComponents);
        std::copy_n(other.m_data.begin(), minSize, m_data.begin());
        for(std::size_t index = minSize; index < nbComponents; ++index)
        {
            m_data[index] = 0.0;
        }
        return *this;
    }

    template < class ODataType, int oDataSize>
    void copy(const Color<ODataType, oDataSize>& other,
              typename std::enable_if < std::is_same<DataType, float>::value
              && !std::is_same<ODataType, float>::value
              && !std::is_same<DataType, ODataType>::value >::type* = nullptr)
    {
        std::size_t minSize = std::min(oDataSize, nbComponents);
        for(std::size_t index = 0; index < minSize; ++index)
        {
            m_data[index] =  static_cast<float>(other[index]) / std::numeric_limits<ODataType>::max();
        }
        for(std::size_t index = minSize; index < nbComponents; ++index)
        {
            m_data[index] = 0.0;
        }
    }


    template < class ODataType, int oDataSize>
    void copy(const Color<ODataType, oDataSize>& other,
              typename std::enable_if < std::is_same<ODataType, float>::value
              && !std::is_same<DataType, float>::value
              && !std::is_same<DataType, ODataType>::value >::type* = nullptr)
    {
        std::size_t minSize = std::min(oDataSize, nbComponents);
        for(std::size_t index = 0; index < minSize; ++index)
        {
            m_data[index] = static_cast<DataType>(std::numeric_limits<DataType>::max() * other[index]);
        }
        for(std::size_t index = minSize; index < nbComponents; ++index)
        {
            m_data[index] = 0.0;
        }
    }

    template < class ODataType, int oDataSize>
    void copy(const Color<ODataType, oDataSize>& other,
              typename std::enable_if < !(std::is_same<ODataType, float>::value
                                          || std::is_same<DataType, float>::value)
              && !std::is_same<DataType, ODataType>::value >::type* = nullptr)
    {
        std::size_t minSize = std::min(oDataSize, nbComponents);
        for(std::size_t index = 0; index < minSize; ++index)
        {
            m_data[index] = static_cast<DataType>((static_cast<float>(other[index]) /
                                                   std::numeric_limits<ODataType>::max()) * std::numeric_limits<DataType>::max());
        }
        for(std::size_t index = minSize; index < nbComponents; ++index)
        {
            m_data[index] = 0.0;
        }
    }

public:

    template <class ODataType, int oDataSize>
    Color& operator=(const Color<ODataType, oDataSize>& other)
    {
        copy(other);
        return *this;
    }

    template <int oDataSize> Color(const Color<DataType, oDataSize>& other)
    {
        copy<DataType, oDataSize>(other);
    }

    template <class ODataType, int oDataSize> Color(const Color<ODataType, oDataSize>& other)
    {
        copy<ODataType, oDataSize>(other);
    }



private:
    std::array<DataType, nbComponents> m_data;
};

using Colorf =  Color<float, 1>;
using Color2f = Color<float, 2>;
using Color3f = Color<float, 3>;
using Color4f = Color<float, 4>;

using Coloruc =  Color<unsigned char, 1>;
using Color2uc = Color<unsigned char, 2>;
using Color3uc = Color<unsigned char, 3>;
using Color4uc = Color<unsigned char, 4>;


using Colorus =  Color<unsigned short, 1>;
using Color2us = Color<unsigned short, 2>;
using Color3us = Color<unsigned short, 3>;
using Color4us = Color<unsigned short, 4>;

}
