#pragma once

namespace Matrix
{
    class Sparse
    {
        //element in the matrix
        struct Element
        {
            int x;
            int y;
            int val;
        };
        // matrix arr
        Element* data;
        // total rows
        int row;
        // total columns
        int column;
        // default value in matrix
        int def_value;

        // row * column
        int size;
        // check and grow if arr is too small
       /* bool Grow();
        bool Realloc(int len);*/
    public:
        Sparse(int size_column, int size_row, int def_value = 0);
        Sparse() : Sparse(5, 5)
        {
        }
        ~Sparse()
        {
            Release();
        }
        // release matrix arr
        void Release()
        {
            if (data)
            {
                delete[] data;
                data = nullptr;
            }
        }
        // get a value from the matrix
        int Get(int x, int y);
        // set a value in the matrix
        bool Set(int x, int y, int val);
        // get row size
        const int Rows() const { return row; }
        // get column size
        const int Columns() const { return column; }
        // print the matrix
        void Print();
    };
}