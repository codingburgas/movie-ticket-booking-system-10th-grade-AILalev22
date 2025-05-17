#pragma once

// default value for point x and y
#define DEFAULT_POINT 1000
namespace Matrix
{
    class Sparse
    {
        //element in the matrix
        struct Element
        {
            int x;
            int y;
            std::string val;
        };
        // matrix arr
        Element* data;
        // total rows
        int row;
        // total columns
        int column;
        // matrix default value
        std::string mvalue;

        //elements total size
        int size;
        // used elements count
        int count;
    public:
        Sparse(int sizeCol, int sizeRow, std::string mvalue);
        Sparse() : Sparse(5, 5,"x")
        {
        }
        ~Sparse();         
        // get a value from the matrix
        const std::string& Get(int x, int y);
        // get a point with coordinates based on val
        POINT Get(const std::string& val);
        // set a value in the matrix
        bool Set(int x, int y, const std::string& val);
        // get row size
        const int Rows() const { return row; }
        // get column size
        const int Columns() const { return column; }
        // print the matrix
        void Print();
    };
}