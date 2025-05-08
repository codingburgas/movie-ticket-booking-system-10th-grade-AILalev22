#include "pch.h"
#include "matrix.h"

namespace Matrix
{
    Sparse::Sparse(int sizeCol, int sizeRow, char mvalue) : column(sizeCol),row(sizeRow)
    {
        size = row * column;
        data = new Element[size];

        this->mvalue = mvalue;
        
        for (int i = 0; i < size; i++)
        {
            data[i].x = data[i].y = -1;
            data[i].val = mvalue;
        }       
    }
    Sparse::~Sparse()
    {
        if (data)
        {
            delete[] data;
            data = nullptr;
        }
    }
    char Sparse::Get(int x, int y)
    {
        if (!(x >= 0 && x < row && y >= 0 && y < column)) return mvalue; // if x,y are outside the matrix

        for (int i = 0; i < size; i++)
            if (data[i].x == x && data[i].y == y)
                return data[i].val;
        return mvalue; // if element isn't found
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
}