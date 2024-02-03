
template<typename T> 
concept IntFloat = std::floating_point <T> || std::integral <T>;

template<IntFloat T> requires arithmetric<T>
class Matrix<T> {
private:
    T * _data_;
    unsigned _rows_;
    unsigned _columns_;
public:
    
    #include "./matrix_files_int/basic_operations.cpp"
    
    #include "./matrix_files_int/get_info.cpp"
    
    #include "./matrix_files_int/col_row_manipulation.cpp"
    
    #include "./matrix_files_int/cast.cpp"
    
    #include "./matrix_files_int/is_methods.cpp"
    
    #include "./matrix_files_int/traspose.cpp"
  
    #include "./matrix_files_int/attached.cpp"
    
    #include "./matrix_files_int/mult_methods.cpp"

    #include "./matrix_files_int/add_method.cpp"

    #include "./matrix_files_int/invert.cpp"
    
    #include "./matrix_files_int/determinant.cpp"
};  

