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
    
    /*
     * Return the quantity of rows in the matrix.
    */
    unsigned rows() const;

    /*
     * Return the quantity of columns in the matrix.
     */
    unsigned cols() const;

    /*
     * Multiply the row in the position specified by the float constant passed by parameter. If the
     * position is greater than the rows quantity, nothing will change.
     */
    void mult_row(unsigned, const float);

    /*
     * Multiply the column in the position specified by the float constant passed by paramenter. If
     * the position is greater than the columns quantity, nothing will change.
     */
    void mult_column(unsigned, const float);

    /*
     * Change the columns specified. If any of the columns specified overpass the columns quantity,
     * nothing will change.
     */
    void change_columns(unsigned, unsigned);

    /*
     * Change the rows specified. If any of the rows specified overpass the rows quantity, nothing
     * will change.
     */
    void change_rows(unsigned, unsigned);

    /*
     * Evaluate if the matrix is a stochastic one. Reminder: a matrix is Stochastic if all his rows
     * have all his elements between 0 and 1, and the addition of those(in the row) is equal to 1.
     */
    bool is_stochastic() const;

    /*
     * Evaluate if the matrix is a square matrix. Reminder: a matrix is a Square matrix if both
     * dimentions are equal.
     */
    bool is_square() const;

    /*
     * Evaluate if the matrix is a vector. Reminder: a vector is a matrix with one of his dimentions
     * are equal to 1.
     */
    bool is_vector() const;
    
    /*
     * Access operator: return the element in the position specified. If any of the parameters overpass 
     * the actual dimentions, 0 will be returned.
     */
    float operator()(unsigned, unsigned) const;

    /*
     * Multiplication by a constant operation. It returns another object with the result of the operation.
     */
    Matrix operator*(float) const;

    /*
     * Multiplication by a matrix operation. It returns another object with the result of the operation. If
     * the dimentions of the matrices don't match(A.cols() != B.rows(), with A*B), the operation will 
     * return a null matrix.
     */
    Matrix operator*(const Matrix &) const;

    /*
     * Addition of two matrices. It returns another object with the result of the operation. If the 
     * dimentions of the matrices don't match(A.rows() != B.rows() || A.cols() != B.cols(), with A+B),
     * then the operation will return a null matrix.
     */
    Matrix operator+(const Matrix &) const;

    /*
     * Return the inverse of the matrix. It returns another object with the result of the operation. 
     * If the determinant is equal to 0, then the operation will return a null matrix.
     */
    Matrix invert();

    /*
     * Return the determinant of the matrix.
     */
    float determinant(); 
    
    /*
     * Return the transpose of the matrix. It returns another object with the result of the operation.
     */
    Matrix traspose();

    /*
     * return the matrix attached in the position specified. It return another object with the result
     * of the operation. If the position specified overpass the dimentions of the matrix, then the 
     * operation will return a null matrix.
     */
    Matrix matrix_attached(unsigned, unsigned);
};

/*
 * Return an identity matrix with the dimention passed by parameter.
 */
Matrix identity(unsigned);

/*
 * Return a matrix with the dimentions passed by parameter, and fill it with the floating point parameter
 */
Matrix mfo(unsigned, unsigned, float);

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
