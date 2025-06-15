//C++ header includes
#include<iostream>
#include<typeinfo>
#include<cstdlib>

/*
    Preprocessor directives to define the dimensions of matrices
    Can also be done via "const" keyword
*/
#define num_rows_matrix_1 10
#define num_cols_matrix_1 10
#define num_rows_matrix_2 10
#define num_cols_matrix_2 10

/*
    * This is a template function which takes pointers as arguments and 
    * return pointer pointing to the result of matrix multiplication
    * This is one approach for matrix multiplication
    * It checks the condition of matrix multiplication first and if it
    * is satisfied, then approaches for the operation
    * template <typename T> is a template to for the function to perform
    * matrix multiplication on the specified datatypes for making it flexible 
    * for any data type
*/
template <typename T>
T** matrix_multiplication(T **mat_a, T **mat_b)
{   
      
    if(num_cols_matrix_1 == num_rows_matrix_2)
    {
        T **res_mat = (int**)malloc(sizeof(T*) * num_rows_matrix_1);

        for(uint t = 0; t < num_rows_matrix_1; ++t)
        {
           res_mat[t] = (int*)malloc(sizeof(T) * num_cols_matrix_2);
        }

        for(size_t f = 0; f < num_rows_matrix_1; ++f)
        {   
            for(size_t g = 0; g < num_cols_matrix_2; ++g)
            {
                for(size_t h = 0; h < num_rows_matrix_2; ++h)
                {
                    res_mat[f][h] += mat_a[f][h] * mat_b[h][g];
                }
            }
        }
        return res_mat;
    }
    else
    {
        std::cout << "Matrix multiplication is not possible, please check the dimensions of the matrices" << std::endl;
        
    }
    
}

int main()
{
    //std::cout <<"Okay" << std::endl;

    int **arr_1 = (int**)malloc(num_rows_matrix_1 * sizeof(int*));

    for(uint i = 0; i < num_rows_matrix_1; ++i)
    {
        arr_1[i] = (int*)malloc(num_cols_matrix_1 * sizeof(int));
    }

    int **arr_2 = (int**)malloc(num_rows_matrix_2 * sizeof(int*));

    for(uint i_1 = 0; i_1 < num_rows_matrix_2; ++i_1)
    {
        arr_2[i_1] = (int*)malloc(num_cols_matrix_2 * sizeof(int));
    }

    for(size_t k = 0; k < num_rows_matrix_1; ++k)
    {
        for(size_t l = 0; l < num_cols_matrix_1; ++l)
        {
            arr_1[k][l] = (l << 2);
            
        }
    }

     for(size_t k_s = 0; k_s < num_rows_matrix_2; ++k_s)
    {
        for(size_t l_s = 0; l_s < num_cols_matrix_2; ++l_s)
        {
            arr_2[k_s][l_s] = (l_s << 4);
        }
    }

    auto result = matrix_multiplication<int>(arr_1, arr_2);

    //printing matrices
    std::cout << "-----------------------Printing Elements of Array 1------------------------" << std::endl;
    for(size_t x = 0; x < num_rows_matrix_1; ++x)
    {
        for(size_t y = 0; y < num_cols_matrix_1; ++y)
        {
            std::cout << "Array 1 [" << x << "]" << "[" << y << "]: " << arr_1[x][y] << std::endl;  
              
        }
    }
    std::cout << "----------------------Elements printed for Array 1------------------------"<<std::endl;

    std::cout << "--------------------------Printing Elements of Array 2---------------------" << std::endl;
    for(size_t w = 0; w < num_rows_matrix_2; ++w)
    {
        for(size_t q = 0; q < num_cols_matrix_2; ++q)
        {
            std::cout << "Array 2 [" << q << "]" << "[" << q << "]: " << arr_2[w][q] << std::endl;  
              
        }
    }
    
    std::cout << "-------------------------Elements printed for Array 2--------------------------------" << std::endl;

    //printing results
    std::cout << "----------------------------Printing elements of resultant array--------------------------" << std::endl;
    for(size_t v = 0; v < num_rows_matrix_1; ++v)
    {
        for(size_t v_1 = 0; v_1 < num_cols_matrix_2; ++v_1)
        {
            std::cout << "Result [" << v << "]" << "[" << v_1 << "]: " << result[v][v_1] << std::endl;  
              
        }
    }

    std::cout << "-------------------------Elements of the resultant matrix printed-----------------------------" << std::endl;

    free(arr_1);
    free(arr_2);

    return 0;
}