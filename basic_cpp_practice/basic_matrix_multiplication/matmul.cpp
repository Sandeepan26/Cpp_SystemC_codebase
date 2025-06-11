#include<iostream>
#include<typeinfo>
#include<cstdlib>

#define num_rows 10
#define num_cols 10

template <typename T>
T** matrix_multiplication(T **mat_a, T **mat_b)
{   
     T **res_mat = (int**)malloc(sizeof(T*) * num_rows);

     for(uint t = 0; t < num_rows; ++t)
     {
        res_mat[t] = (int*)malloc(sizeof(T) * num_cols);
     }

    for(size_t f = 0; f < num_rows; ++f)
    {   
        for(size_t g = 0; g < num_cols; ++g)
        {
            for(size_t h = 0; h < num_rows; ++h)
            {
                res_mat[f][h] += mat_a[f][h] * mat_b[h][g];
            }
        }
    }
    
    return res_mat;
}

int main()
{
    std::cout <<"Okay" << std::endl;

    int **arr_1 = (int**)malloc(num_rows * sizeof(int*));

    for(uint i = 0; i < num_rows; ++i)
    {
        arr_1[i] = (int*)malloc(num_cols * sizeof(int));
    }

    int **arr_2 = (int**)malloc(num_rows * sizeof(int*));

    for(uint i_1 = 0; i_1 < num_rows; ++i_1)
    {
        arr_2[i_1] = (int*)malloc(num_cols * sizeof(int));
    }

    for(size_t k = 0; k < num_rows; ++k)
    {
        for(size_t l = 0; l < num_cols; ++l)
        {
            arr_1[k][l] = 2;
            arr_2[k][l] = 1;
        }
    }
    auto result = matrix_multiplication<int>(arr_1, arr_2);

    //printing results
    for(size_t v = 0; v < num_rows; ++v)
    {
        for(size_t v_1 = 0; v_1 < num_cols; ++v_1)
        {
            std::cout << "Result [" << v << "]" << "[" << v_1 << "]: " << result[v][v_1] << std::endl;  
              
        }
    }

    free(arr_1);
    free(arr_2);

    return 0;
}