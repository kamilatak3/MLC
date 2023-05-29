#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float sigmoidf(float x){
    return 1.f/(1.f+expf(-x));
}

float train[][3] = {
    {0,0,0},
    {1,0,0},
    {0,1,0},
    {1,1,1},
};

#define TRAIN_SIZE sizeof(train)/sizeof(train[0])
float x1;
float x2;
float guess;
float dist;
float eps = 1e-3;
float rate = 1e-3;

float loss(float w1, float w2, float b){
    float result= 0.0f;
    for(int i = 0; i < TRAIN_SIZE; i++){
        x1 = train[i][0];
        x2 = train[i][1];
        guess = sigmoidf(x1*w1 + x2*w2 + b);
        dist = guess - train[i][2];
        result += dist*dist;
    }
    result /= TRAIN_SIZE;
    return result;
}

float rand_float(){
    return (float)rand()/(float)RAND_MAX;
}


int main(){
    srand(time(0));
    float w1 = rand_float();
    float w2 = rand_float();
    float b = rand_float();
    //printf("w1: %f w2: %f",w1,w2);


    for(size_t i = 0; i < 100000; i++){
        float c = loss(w1,w2, b);
        float dw1 = (loss(w1+eps, w2, b) - c)/eps;
        float dw2 = (loss(w1, w2+eps, b) - c)/eps;
        float db = (loss(w1, w2, b+eps) - c)/eps;

        w1 -= rate*dw1;
        w2 -= rate* dw2;
        b -= rate*db;
        printf("w1: %f w2: %f loss: %f bias: %f\n",w1,w2,loss(w1,w2, b), b);
    }

    for(size_t i = 0; i<2; i++){
        for(size_t j = 0; j < 2; j++){
            printf("%zu | %zu = %f\n", i, j, sigmoidf(i*w1 + j*w2 + b));
        }
    }
    return 0;
}