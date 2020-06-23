#pragma once

#include "stbipp/TypeTraits.hpp"

#include <array>

#include <limits>
#include <type_traits>

namespace stbipp {


template<class DataType, unsigned int nbComponents>
class Color
{
    static_assert ((std::is_same<DataType, unsigned short>::value
                    || std::is_same<DataType, unsigned char>::value
                    || std::is_same<DataType, float>::value)
                    && (nbComponents > 0)
                    && (nbComponents < 5) ,
                    "Color template argument expect : float, unsigned short or unsigned char "
                    "\n Color template argument expect number of components < 5");

public:

    Color()
    {
        std::fill(m_data.begin(), m_data.end(), DataType(0));
    };

    template<int I = nbComponents, typename std::enable_if<!(I > 0)>::type* = nullptr>
    Color(DataType r) = delete;
    template<int I = nbComponents, typename std::enable_if<(I > 0)>::type* = nullptr> Color(DataType r):
        m_data({r})
    {}

    template<int I = nbComponents, typename std::enable_if<!(I > 1)>::type* = nullptr> Color(DataType r,
            DataType g) = delete;
    template<int I = nbComponents, typename std::enable_if<(I > 1)>::type* = nullptr> Color(DataType r,
            DataType g):
        m_data({r, g})
    {}

    template<int I = nbComponents, typename std::enable_if<!(I > 2)>::type* = nullptr> Color(DataType r,
            DataType g,
            DataType b) = delete;
    template<int I = nbComponents, typename std::enable_if<(I > 2)>::type* = nullptr> Color(DataType r,
            DataType g,
            DataType b):
        m_data({r, g, b})
    {}

    template<int I = nbComponents, typename std::enable_if<!(I > 3)>::type* = nullptr> Color(DataType r,
            DataType g,
            DataType b, DataType a) = delete;
    template<int I = nbComponents, typename std::enable_if<(I > 3)>::type* = nullptr> Color(DataType r,
            DataType g,
            DataType b, DataType a):
        m_data({r, g, b, a})
    {}


    template<int I = nbComponents, typename std::enable_if<!(I > 0)>::type* = nullptr>
    DataType r()const = delete;
    template<int I = nbComponents, typename std::enable_if<(I > 0)>::type* = nullptr>
    DataType r()const
    {
        return m_data[0];
    }

    template<int I = nbComponents, typename std::enable_if<!(I > 0)>::type* = nullptr>
    DataType & r() = delete;
    template<int I = nbComponents, typename std::enable_if<(I > 0)>::type* = nullptr>
    DataType & r()
    {
        return m_data[0];
    }

    template<int I = nbComponents, typename std::enable_if<!(I > 1)>::type* = nullptr>
    DataType g()const = delete;
    template<int I = nbComponents, typename std::enable_if<(I > 1)>::type* = nullptr>
    DataType g()const
    {
        return m_data[1];
    }

    template<int I = nbComponents, typename std::enable_if<!(I > 1)>::type* = nullptr>
    DataType & g() = delete;
    template<int I = nbComponents, typename std::enable_if<(I > 1)>::type* = nullptr>
    DataType & g()
    {
        return m_data[1];
    }

    template<int I = nbComponents, typename std::enable_if<!(I > 2)>::type* = nullptr>
    DataType b()const = delete;
    template<int I = nbComponents, typename std::enable_if<(I > 2)>::type* = nullptr>
    DataType b()const
    {
        return m_data[2];
    }

    template<int I = nbComponents, typename std::enable_if<!(I > 2)>::type* = nullptr>
    DataType & b() = delete;
    template<int I = nbComponents, typename std::enable_if<(I > 2)>::type* = nullptr>
    DataType & b()
    {
        return m_data[2];
    }

    template<int I = nbComponents, typename std::enable_if<!(I > 3)>::type* = nullptr>
    DataType a()const = delete;

    template<int I = nbComponents, typename std::enable_if<(I > 3)>::type* = nullptr>
    DataType a()const
    {
        return m_data[3];
    }

    template<int I = nbComponents, typename std::enable_if<!(I > 3)>::type* = nullptr>
    DataType & a() = delete;
    template<int I = nbComponents, typename std::enable_if<(I > 3)>::type* = nullptr>
    DataType & a()
    {
        return m_data[3];
    }

    unsigned int size()const
    {
        return nbComponents;
    }

    const DataType* data()const
    {
        return m_data.data();
    }

    DataType* data()
    {
        return m_data.data();
    }

    DataType operator[](unsigned int index)const
    {
        return m_data[index];
    }

    DataType& operator[](unsigned int index)
    {
        return m_data[index];
    }

private:
    template<typename ODataType, unsigned int oDataSize>
    void copy(const Color<ODataType, oDataSize>& other,
              typename std::enable_if <std::is_same<DataType, ODataType>::value>::type* = nullptr)
    {
        std::size_t minSize = std::min(oDataSize, nbComponents);
        for(std::size_t index = 0; index < minSize; ++index)
        {
            m_data[index] =  other[index];
        }
        for(std::size_t index = minSize; index < nbComponents; ++index)
        {
            m_data[index] = 0.0;
        }
    }

    template < class ODataType, unsigned int oDataSize>
    void copy(const Color<ODataType, oDataSize>& other,
              typename std::enable_if < std::is_floating_point<DataType>::value
              && !std::is_floating_point<ODataType>::value
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


    template < class ODataType, unsigned int oDataSize>
    void copy(const Color<ODataType, oDataSize>& other,
              typename std::enable_if < std::is_floating_point<ODataType>::value
              && !std::is_floating_point<DataType>::value
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

    template < class ODataType, unsigned int oDataSize>
    void copy(const Color<ODataType, oDataSize>& other,
              typename std::enable_if < !(std::is_floating_point<ODataType>::value
                                          || std::is_floating_point<DataType>::value)
              && !std::is_same<DataType, ODataType>::value >::type* = nullptr)
    {
        std::size_t minSize = std::min(oDataSize, nbComponents);
        for(std::size_t index = 0; index < minSize; ++index)
        {
            m_data[index] = static_cast<DataType>((static_cast<float>(other[index]) *
                                                   std::numeric_limits<DataType>::max()) /
                                                  std::numeric_limits<ODataType>::max());
        }
        for(std::size_t index = minSize; index < nbComponents; ++index)
        {
            m_data[index] = 0.0;
        }
    }

public:

    template <class ODataType, unsigned int oDataSize>
    Color& operator=(const Color<ODataType, oDataSize>& other)
    {
        copy(other);
        return *this;
    }

    template <unsigned int oDataSize> Color(const Color<DataType, oDataSize>& other)
    {
        copy<DataType, oDataSize>(other);
    }

    template <class ODataType, unsigned int oDataSize> Color(const Color<ODataType, oDataSize>& other)
    {
        copy<ODataType, oDataSize>(other);
    }



private:
    std::array<DataType, nbComponents> m_data{};
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
