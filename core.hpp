/**
 * core.hpp
*/

#ifndef __CORE_HPP__
#define __CORE_HPP__

#include <cstddef>



namespace cv {

class Range
{
public:
    Range();
    Range(int _start, int _end);
    int size() const;
    bool empty() const;
    static Range all();

    int start, end;
};


class Mat
{
public:
    //! default constructor
    Mat();

    // copy constructor
    Mat(const Mat& m);
    // 
    Mat(int rows, int clos, int type, void* data);

    // creates a matrix header for a part of the bigger matrix
    
    // ! destructor - calls release()
    ~Mat();

    // assignment operators
    Mat& operator = (const Mat& m);

    // returns a new matrix header for the specified row
    Mat row(int y) const;
    // returns a new matrix header for the specified column
    Mat clo(int x) const;
        //! ... for the specified row span
    Mat rowRange(int startrow, int endrow) const;
    Mat rowRange(const Range& r) const;
    //! ... for the specified column span
    Mat colRange(int startcol, int endcol) const;
    Mat colRange(const Range& r) const;

    //! creates alternative matrix header for the same data, with different
    // number of channels and/or different number of rows. see cvReshape.
    Mat reshape(int cn, int rows=0) const;
    Mat reshape(int cn, int newndims, const int* newsz) const;

    //! allocates new matrix data unless the matrix already has specified size and type.
    // previous data is unreferenced if needed.
    void create(int rows, int cols, int type);

    //! decreases reference counter;
    // deallocates the data when reference counter reaches 0.
    void release();

    //! extracts a rectangular sub-matrix
    // (this is a generalized form of row, rowRange etc.)
    Mat operator()( Range rowRange, Range colRange ) const;
    Mat operator()( const Range* ranges ) const;

    //! returns element type, similar to CV_MAT_TYPE(cvmat->type)
    int type() const;
    //! returns element type, similar to CV_MAT_DEPTH(cvmat->type)
    int depth() const;
    //! returns element type, similar to CV_MAT_CN(cvmat->type)
    int channels() const;

    /*! includes several bit-fields:
         - the magic signature
         - continuity flag
         - depth
         - number of channels
     */
    int flags;
    //! the matrix dimensionality, >= 2
    int dims;
    //! the number of rows and columns or (-1, -1) when the matrix has more than 2 dimensions
    int rows, cols;
    //! pointer to the data
    unsigned char* data;

    //! pointer to the reference counter;
    // when matrix points to user-allocated data, the pointer is NULL
    int* refcount;

    //! helper fields used in locateROI and adjustROI
    unsigned char* datastart;
    unsigned char* dataend;
    unsigned char* datalimit;    

    struct  MSize
    {
        MSize(int* _p);
        const int& operator[](int i) const;
        int& operator[](int i);
        operator const int*() const;
        bool operator == (const MSize& sz) const;
        bool operator != (const MSize& sz) const;

        int* p;
    };

    struct  MStep
    {
        MStep();
        MStep(size_t s);
        const size_t& operator[](int i) const;
        size_t& operator[](int i);
        operator size_t() const;
        MStep& operator = (size_t s);

        size_t* p;
        size_t buf[2];
    protected:
        MStep& operator = (const MStep&);
    };

    MSize size;
    MStep step;

protected:
    void initEmpty();
};



}

#endif // __CORE_HPP_
