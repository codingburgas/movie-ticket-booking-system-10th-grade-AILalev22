#pragma once

// default value for point x and y
#define DEFAULT_POINT -1
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
        // matrix default value
        std::string mvalue;

        //elements total size
        int size;
        // used elements count
        int count;

        int rowSize;
        int colSize;
        // print the matrix
        void Print(int size1, int size2) const;
    public:
        Sparse(int sizeCol, int sizeRow, std::string mvalue);
        Sparse() : Sparse(5, 5,"x")
        {
        }
        ~Sparse();         
        // get a value from the matrix
        const std::string& Get(int x, int y) const;
        // get a point with coordinates based on val
        POINT Get(const std::string& val) const;
        // set a value in the matrix
        bool Set(int x, int y, const std::string& val);
        // print matrix row by row
        void PrintRows()
        {
            Print(rowSize, colSize);
        }
        // print matrix column by column
        void PrintCols()
        {
            Print(colSize, rowSize);
        }
    };
}