#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float sigmoidf(float x){
    return 1.f/(1.f+expf(-x));
}
//XOR GATE
float train[][3] = {
    {0,0,0},
    {1,0,1},
    {0,1,1},
    {1,1,0},
};

#define TRAIN_SIZE sizeof(train)/sizeof(train[0])
//inputs
float x1;
float x2;

//neurons
float n1;
float n2;
float n3;

//distance of error
float dist;

//learning rate
float eps = 1e-1;
float rate = 1e-1;


float loss(float w1, float w2, float b1, float w3, float w4, float b2, float w5, float w6, float b3){
    float result= 0.0f;
    for(int i = 0; i < TRAIN_SIZE; i++){

        x1 = train[i][0];
        x2 = train[i][1];

        //n1 get inputs from x1 and x2
        n1 = sigmoidf(x1*w1 + x2*w2 + b1);
        

        //n2 get inputs from x1 and x2
        n2 = sigmoidf(x1*w3 + x2*w4 + b2);
        
        

        //n3 get inputs from n1 and n2
        n3 = sigmoidf(n1*w5 + n2*w6 + b3);
        dist = n3 - train[i][2];
        result += dist*dist;
    }
    result /= TRAIN_SIZE;
    return result;
}

//randomized float
float rand_float(){
    return (float)rand()/(float)RAND_MAX;
}


int main(){
    srand(time(0));
    //n1 x1, x2
    float w1 = rand_float();
    float w2 = rand_float();
    float b1 = rand_float();


    //n2 x1, x2
    float w3 = rand_float();
    float w4 = rand_float();
    float b2 = rand_float();

    //n3 n1, n2
    float w5 = rand_float();
    float w6 = rand_float();
    float b3 = rand_float();




    for(size_t i = 0; i < 100000; i++){
        float c = loss(w1, w2, b1, w3, w4, b2, w5, w6, b3);
        float dw1 = (loss(w1+eps, w2, b1, w3, w4, b2, w5, w6, b3) - c)/eps;
        float dw2 = (loss(w1, w2+eps, b1, w3, w4, b2, w5, w6, b3) - c)/eps;
        float db1 = (loss(w1, w2, b1+eps, w3, w4, b2, w5, w6, b3) - c)/eps;
        float dw3 = (loss(w1, w2, b1, w3+eps, w4, b2, w5, w6, b3) - c)/eps;
        float dw4 = (loss(w1, w2, b1, w3, w4+eps, b2, w5, w6, b3) - c)/eps;
        float db2 = (loss(w1, w2, b1, w3, w4, b2+eps, w5, w6, b3) - c)/eps;
        float dw5 = (loss(w1, w2, b1, w3, w4, b2, w5+eps, w6, b3) - c)/eps;
        float dw6 = (loss(w1, w2, b1, w3, w4, b2, w5, w6+eps, b3) - c)/eps;
        float db3 = (loss(w1, w2, b1, w3, w4, b2, w5, w6, b3+eps) - c)/eps;






        w1 -= rate*dw1;
        w2 -= rate* dw2;
        b1 -= rate*db1;
        w3 -= rate*dw3;
        w4 -= rate* dw4;
        b2 -= rate*db2;
        w5 -= rate*dw5;
        w6 -= rate* dw6;
        b3 -= rate*db3;


        printf("w1: %f w2: %f loss: %f\n",w1,w2,loss(w1,w2, b1, w3, w4, b2, w5, w6, b3));
    }

    for (size_t i = 0; i < 2; i++) {
    for (size_t j = 0; j < 2; j++) {
        x1 = i;
        x2 = j;
        n1 = sigmoidf(x1 * w1 + x2 * w2 + b1);
        n2 = sigmoidf(x1 * w3 + x2 * w4 + b2);
        printf("%zu | %zu = %f\n", i, j, sigmoidf(n1 * w5 + n2 * w6 + b3));
    }
}
    return 0;
}