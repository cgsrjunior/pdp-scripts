#include <stdio.h>
#include <math.h>
#include <omp.h>

#define MAX_ITER 14000

#define pontoX 0.0
#define pontoY 0.0
#define ALTURA 768
#define LARGURA 1024


float mandelbrot(float oX, float oY, float pX, float pY, int iter){
    float eX, eY, dist;

    eX = (oX * oX) - (oY * oY) + pX;
    eY = (2 * oX * oY) + pY;

    if(iter >= MAX_ITER)
            return iter;

    dist = sqrtf((eX*eX) + (eY * eY));

    if(dist <= 2.00){
            return mandelbrot(eX, eY, pX, pY, ++iter);
    }

    return dist;

}

/*Função para converter o valor do pixel para o valor do plano complexo.*/
void convertePixel(int pX, int pY, float *x, float *y){
    int coordX0;
    int coordY0;
    float scaleX;
    float scaleY;

    coordX0 = (LARGURA/3.0) * 2.0;
    coordY0 = (ALTURA/2) * 1;

    scaleX = 3.0 / LARGURA;
    scaleY = 2.0 / ALTURA;

    *x = (pX * scaleX) - 2.0;

    if(pY > coordY0){
            *y = -1 + ((ALTURA - pY) * scaleY);
    }
    else{
            *y = ((pY - (ALTURA/2)) * scaleY);
    }
}

int main(int argc, char **argv){

    float cX, cY;
    int x, y, iter;
    double initTime = omp_get_wtime();
    #pragma omp parallel private(x,y, cX, cY, iter)
    {
        #pragma omp for schedule(dynamic,4)
        for(x = 0; x < ALTURA; x++){
            for(y = 0; y < LARGURA; y++){
                convertePixel(y, x,&cY, &cX);
                iter = mandelbrot(pontoY, pontoX, cY, cX, 0);
                //Alternative Method:
                //iter = mandelbrot(pontoY, pontoX, cY, cX, 0);
            }
        }
    }
    printf("Total time = %.5lf\n", omp_get_wtime() - initTime);
    return 0;
}
