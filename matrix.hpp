/*
  This piece implements matrix objects with some methods to manipulate them, and some 
  operations and functions. I would define the "null matrix" such as one that have a 
  dimension(or both) equaly to 0. This one would be returned in case of error.
  The class matrix is implemented in matrix.cpp, but Matrix_2sq, Matrix_4sq and
  Matrix_8sq are not yet.
*/

#ifndef mod_matrix
#define mod_matrix

class Matrix{
private:
    float * _data_;
    unsigned _rows_;
    unsigned _columns_;
public:
    Matrix(); // null matrix
    Matrix(unsigned, unsigned, float * &); // put elems == nullptr
    Matrix(unsigned, unsigned, float * &&); // not what's above
    Matrix(const Matrix &);
    Matrix(Matrix &&);
    ~Matrix();
    Matrix operator=(const Matrix &);
    Matrix operator=(Matrix &&);
    
    unsigned rows() const;
    unsigned cols() const;

    void mult_row(unsigned, float);
    void mult_column(unsigned, float);
    void change_columns(unsigned, unsigned);
    void change_rows(unsigned, unsigned);

    bool is_estocastic() const;
    bool is_square() const;
    bool is_vector() const;
    
    float operator()(unsigned, unsigned) const; // operator[]
    Matrix operator*(float) const;
    Matrix operator*(const Matrix &) const;
    Matrix operator+(const Matrix &) const;
    //Matrix operator+(Matrix &&); // i can use the same r-value matrix to return

    // this two will be nearly the same
    Matrix invert();
    float determinant(); 
    
    Matrix traspose();
    Matrix matrix_attached(unsigned, unsigned);
};

Matrix identity(unsigned);

Matrix mfo(unsigned, unsigned, float); //matrix of dimentions (row x col) where each element are elem.

/*
    Square matrices that have fixed dimensions of 2, 4 or 8. It implements
    the operations more effitiently, using c++ instrinsics and making them 
    more specific to the dimension considered.
*/
class Matrix_Nsq{
public:
    Matrix_Nsq(unsigned N, float * & elems); // put elems == nullptr
    Matrix_Nsq(unsigned N, float * && elems); // not what's above
    Matrix_Nsq(const Matrix_Nsq &);
    Matrix_Nsq(Matrix_Nsq &&);
    virtual ~Matrix_Nsq(){};
    Matrix_Nsq operator=(const Matrix_Nsq &);
    Matrix_Nsq operator=(Matrix_Nsq &&);

    unsigned get_dim();

    void mult_row(unsigned row, float a);
    void mult_column(unsigned column, float a);
    void change_columns(unsigned col1, unsigned col2);
    void change_rows(unsigned row1, unsigned row2);

    bool is_estocastic();
    
    Matrix_Nsq operator()(unsigned, unsigned); // operator[]
    Matrix_Nsq operator*(float num);
    Matrix_Nsq operator*(const Matrix_Nsq & A);
    Matrix_Nsq operator+(const Matrix_Nsq & A);
    Matrix_Nsq operator+(Matrix_Nsq && A); // i can use the same r-value Matrix_Nsq to return

    // this two will be nearly the same
    Matrix_Nsq determinant();
    Matrix_Nsq escalate();

    Matrix_Nsq traspose();
    Matrix_Nsq matrix_attached(unsigned elimine_row, unsigned elimine_column);

};

class Matrix_2sq : public Matrix_Nsq{};
class Matrix_4sq : public Matrix_Nsq{};
class Matrix_8sq : public Matrix_Nsq{};

#endif
