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
            char val;
        };
        // matrix arr
        Element* data;
        // total rows
        int row;
        // total columns
        int column;
        // matrix default value
        char mvalue;

        //elements count
        int size;
    public:
        Sparse(int size_column, int size_row, char mval);
        Sparse() : Sparse(5, 5,'x')
        {
        }
        ~Sparse()
        {
            Release();
        }
        // release matrix arr
        void Release();       
        // get a value from the matrix
        char Get(int x, int y);
        // set a value in the matrix
        bool Set(int x, int y, char val);
        // get row size
        const int Rows() const { return row; }
        // get column size
        const int Columns() const { return column; }
        // print the matrix
        void Print();
    };
}