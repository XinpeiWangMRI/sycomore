#include "Grid.h"

#include <algorithm>
#include <numeric>
#include <vector>

#include "sycomore/IndexGenerator.h"
#include "sycomore/sycomore.h"

namespace sycomore
{

template<typename T>
Grid<T>
::Grid()
: Grid(Index(), Shape())
{
    // Nothing else.
}

template<typename T>
Grid<T>
::Grid(Index const & origin, Shape const & shape)
: _origin(origin), _shape(shape), _stride(_compute_stride(shape))
{
    if(!this->_stride.empty())
    {
        this->_data.resize(this->_stride[this->_stride.size()-1]);
    }
}

template<typename T>
Grid<T>
::Grid(Index const & origin, Shape const & shape, value_type const & value)
: Grid(origin, shape)
{
    std::fill(this->_data.begin(), this->_data.end(), value);
}

template<typename T>
typename Grid<T>::value_type const *
Grid<T>
::data() const
{
    return this->_data.data();
}

template<typename T>
typename Grid<T>::value_type *
Grid<T>
::data()
{
    return this->_data.data();
}

template<typename T>
typename Grid<T>::value_type &
Grid<T>
::operator[](Index const & index)
{
    auto const position = dot(index-this->_origin, this->_stride);
    return this->_data[position];
}

template<typename T>
typename Grid<T>::value_type const &
Grid<T>
::operator[](Index const & index) const
{
    auto const position = dot(index-this->_origin, this->_stride);
    return this->_data[position];
}

template<typename T>
size_t
Grid<T>
::dimension() const
{
    return this->_shape.size();
}

template<typename T>
Index const &
Grid<T>
::origin() const
{
    return this->_origin;
}

template<typename T>
Shape const &
Grid<T>
::shape() const
{
    return this->_shape;
}

template<typename T>
Stride const &
Grid<T>
::stride() const
{
    return this->_stride;
}

template<typename T>
void
Grid<T>
::reshape(Index const & origin, Shape const & shape)
{
    if(shape.size() != this->dimension())
    {
        throw std::runtime_error("Reshaping must preserve dimension");
    }

    Grid new_grid(origin, shape);
    this->_reshape(new_grid);
}

template<typename T>
void
Grid<T>
::reshape(Index const & origin, Shape const & shape, value_type const & value)
{
    if(shape.size() != this->dimension())
    {
        throw std::runtime_error("Reshaping must preserve dimension");
    }

    Grid new_grid(origin, shape, value);
    this->_reshape(new_grid);
}

template<typename T>
typename Grid<T>::iterator
Grid<T>
::begin()
{
    return this->_data.begin();
}

template<typename T>
typename Grid<T>::const_iterator
Grid<T>
::begin() const
{
    return this->_data.begin();
}

template<typename T>
typename Grid<T>::const_iterator
Grid<T>
::cbegin() const
{
    return this->_data.cbegin();
}

template<typename T>
typename Grid<T>::iterator
Grid<T>
::end()
{
    return this->_data.end();
}

template<typename T>
typename Grid<T>::const_iterator
Grid<T>
::end() const
{
    return this->_data.end();
}

template<typename T>
typename Grid<T>::const_iterator
Grid<T>
::cend() const
{
    return this->_data.cend();
}

template<typename T>
Stride
Grid<T>
::_compute_stride(Shape const & shape)
{
    if(shape.size() == 0)
    {
        return Stride();
    }

    Stride stride(shape.size()+1);
    stride[0] = 1;
    for(unsigned int i=0; i< shape.size(); ++i)
    {
        stride[i+1] = shape[i]*stride[i];
    }

    return stride;
}

template<typename T>
void
Grid<T>
::_reshape(Grid & new_grid)
{
    Index const max_origin = maximum(this->_origin, new_grid.origin());

    auto const old_last = IndexGenerator(this->origin(), this->shape()).last();
    auto const new_last = IndexGenerator(
        new_grid.origin(), new_grid.shape()).last();
    Index min_last = minimum(old_last, new_last);

    // Check whether the two grids are disjoint (on at least one axis,
    // max_origin >= min_last)
    auto mismatch = std::mismatch(
        max_origin.begin(), max_origin.end(), min_last.begin(),
        std::less<int>());
    if(mismatch.first == max_origin.end())
    {
        Shape min_shape(min_last.size());
        std::transform(
            min_last.begin(), min_last.end(),
            max_origin.begin(), min_shape.begin(),
            std::minus<int>());

        // NOTE: we could memcopy line-by-line
        for(auto && index: IndexGenerator(max_origin, min_shape))
        {
            new_grid[index] = (*this)[index];
        }
    }
    // Otherwise the two grids are disjoint, nothing to copy.

    this->_origin = std::move(new_grid._origin);
    this->_shape = std::move(new_grid._shape);
    this->_stride = std::move(new_grid._stride);
    this->_data = std::move(new_grid._data);
}

}