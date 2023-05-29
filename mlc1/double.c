#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
};

float rand_float(){
    return (float)rand() / (float)RAND_MAX;
}

#define TRAIN_SIZE sizeof(train)/sizeof(train[0])

float loss(float w){
    float result = 0.0f;
    for(int i = 0; i < TRAIN_SIZE; i++){
        float x = train[i][0];
        float y = train[i][1];
        float guess = x * w;
        float dist_to_actual = guess - y;
        result += dist_to_actual*dist_to_actual;
        //printf("Actual %f, Guess %f\n",y, guess);
    }
        return result /= TRAIN_SIZE;
}




int main(){

    /// y = x*w
    //srand(time(0));
    srand(69);
    float w = rand_float()*10.f;
    printf("%f\n", loss(w));
    float eps = 1e-3;
    float rate = 1e-3;
    float derivative_loss = 0.0f;
    float move_dist = 0.0f;
    int tries = 0;

    for(;;){
    derivative_loss = (loss(w + eps) - loss(w))/eps;
    move_dist = derivative_loss*rate;
    w -= move_dist;
    printf("%f\n", loss(w));
    tries++;
    if(loss(w)<eps){
        break;
    }
} 
    printf("Multiple by: %f\n", w);
    printf("Founf in %d tries.\n", tries);

    return 0;
}