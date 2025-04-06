#include "pch.h"
#include "matrix.h"

namespace Matrix
{
    Sparse::Sparse(int row, int column, int size, int def_value) : size(size), column(column),row(row), c_data(0)
    {
        if (size > row * column) size = row * column; // readjust capacity if exceeding

        data = new Element[size];
        for (int i = 0; i < size; i++)
        {
            data[i].x = data[i].y = def_value;
            data[i].val = def_value;
        }
        this->def_value = def_value;
    }
    //bool Sparse::Grow()
    //{
    //    const int max_size = row * column;
    //    int add_size = c_data;
    //    if (c_data + add_size >= max_size)
    //    {
    //         add_size = max_size - c_data;
    //         if (add_size <= 0)
    //             return false;
    //    }
    //    return Realloc(c_data + add_size);
    //}
    //bool Sparse::Realloc(int len)
    //{
    //    Element* new_data = new Element[len];
    //    if (data)
    //    {
    //        for (int i = 0; i < c_data; i++)
    //        {
    //            new_data[i] = data[i];
    //        }
    //        delete[] data;
    //        data = new_data;
    //        size = len;

    //        return true;
    //    }
    //    return false;
    //}

    int Sparse::Get(int x, int y)
    {
        if (!(x >= 0 && x < row && y >= 0 && y < column)) return def_value; // if x,y are outside the matrix

        for (int i = 0; i < c_data; i++)
            if (data[i].x == x && data[i].y == y)
                return data[i].val;
        return def_value; // if element isn't found
    }
    bool Sparse::Set(int x, int y, int val)
    {
        if (!(x >= 0 && x < row && y >= 0 && y < column)) return false; // if x,y are outside the matrix
        for (int i = 0; i < c_data; i++)
        {
            if (data[i].x == x && data[i].y == y)
            {
                data[i].val = val; // if data is found at x,y set new val
                return true;
            }
        }
        return false;
    }
    void Sparse::Print()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                std::cout << Get(i,j) << ' '; // print the whole matrix
            }
            std::cout << "\n";
        }
    }
}