#include "pch.h"
#include "matrix.h"

namespace Matrix
{
    Sparse::Sparse(int row, int column, char def_value) : column(column),row(row)
    {
        size = row * column;
        data = new Element[size];

        this->def_value = def_value;
        
        for (int i = 0; i < size; i++)
        {
            data[i].x = data[i].y = def_value;
            data[i].val = def_value;
        }       
    }
    char Sparse::Get(int x, int y)
    {
        if (!(x >= 0 && x < row && y >= 0 && y < column)) return def_value; // if x,y are outside the matrix

        for (int i = 0; i < size; i++)
            if (data[i].x == x && data[i].y == y)
                return data[i].val;
        return def_value; // if element isn't found
    }
    bool Sparse::Set(int x, int y, char val)
    {
        if (!(x >= 0 && x < row && y >= 0 && y < column)) return false; // if x,y are outside the matrix
        for (int i = 0; i < size; i++)
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
    void Sparse::Release()
    {
        if (data)
        {
            delete[] data;
            data = nullptr;
        }
    }
}