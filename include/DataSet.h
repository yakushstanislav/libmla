/*
   Copyright (c) 2014 Stanislav Yakush (st.yakush@yandex.ru)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#ifndef __MLA_DATASET_H__
#define __MLA_DATASET_H__

namespace MLA {

template<typename T>
class DataSet
{
public:
    inline void insert(const T& data)
    {
        _dataset.push_back(data);
    }

    inline T& get(const std::size_t index)
    {
        assert(index < _dataset.size());

        return _dataset[index];
    }

    inline T& operator[](const std::size_t index)
    {
        return get(index);
    }

    inline std::size_t size() const
    {
        return _dataset.size();
    }

    inline void clear()
    {
        _dataset.clear();
    }

private:
    std::vector<T> _dataset;
};

};

#endif
