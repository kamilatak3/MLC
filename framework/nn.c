#define NN_IMPLEMENTATION
#include "nn.h"
#include <time.h>

int main(void){
    srand(time(0));
    Mat a = mat_alloc(1,2);
    mat_rand(a, 10, 0);

    Mat b = mat_alloc(2,2);

    mat_rand(b, 10, 0);

    Mat dst = mat_alloc(1,2);

    mat_dot(dst,a,b);
    mat_print(a);

    printf("--------------------\n");
    mat_print(b);


    printf("--------------------\n");

    mat_print(dst);
    return 0;
}