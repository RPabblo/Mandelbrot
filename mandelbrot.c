#include <stdio.h>

// Para melhor performance, compile com
// gcc -O3 mandelbrot.c -o mandelbrot

int mandelbrot(double cr, double ci, int MAX_ITER)
{
    /* 
    Função que recebe um número complexo (cr + ci * i) e retorna o número de 
    iterações até o módulo do número complexo z ultrapasssar 2. Se não ultrapassar,
    então o número retornado será igual a MAX_ITER.

    A fórmula que gera o Conjunto de Mandelbrot é a seguinte: z = z * z + c.

    Por questão de performance, as operações com números complexos foram feitas utilizando
    de números reais. 

    Um número complexo tem a forma z = a + bi.
    A multiplicação de números complexos (a + bi)(c + di) pode ser feita da seguinte forma:

    (aa - bb) + (ab + ba)i. Essa é a forma utilizada a seguir. 
    5 e 3
    25 - 9
    2 
    */
   
    double atemp = 0.0, btemp = 0.0;
    double a = atemp * atemp;
    double b = btemp * btemp;
    int n;

    for(n = 0; ((a + b) <= 4) && n < MAX_ITER; n++) {
        btemp = 2 * atemp * btemp + ci; 
        atemp = a - b + cr;
         
        /*  O quadrado do módulo do número complexo é obtido por Pitágoras: |z|^2 = a^2 + b^2
        As variáveis a e b guardam os quadrados de atemp e btemp, respectivamente.
        Se o quadrado do módulo passar de 4, a função retorna.  */
        a = atemp * atemp;
        b = btemp * btemp;    
    }
    return n;
}

int main(void)
{
    // Aréa a ser visualizada, definida pelos intervalos na reta real e na reta imaginária.
    const double RE_INICIO = -0.7709551;
    const double RE_FINAL = -0.7709511;
    const double IM_INICIO = -0.115619;
    const double IM_FINAL = -0.115623;

    // Número de iterações; para um zoom mais profundo, é recomendado um número maior delas.
    const int MAX_ITER = 600;

    // Tamanho da imagem, em pixels.
    double COMP = 4000;
    double ALT = 4000;

    // Intervalo de cores; 255 para o intervalo RGB.
    const int maxcolor = 255;

    const double pixel_comp = (RE_FINAL - RE_INICIO) / COMP;
    const double pixel_alt = (IM_FINAL - IM_INICIO) / ALT;

    char color[3];

    int x, y;
    int iter;
    double cr, ci;

    // Abre arquivo .ppm no modo de escrita em binário.
    FILE* fp = fopen("fractal.ppm", "wb");
    fprintf(fp, "P6\n %d\n %d\n %d\n", (int) COMP, (int) ALT, maxcolor);

    for(y = 0; y < ALT; y++)
    {
        ci = IM_INICIO + y * pixel_alt;

        for(x = 0; x < COMP; x++)
        {
            cr = RE_INICIO + x * pixel_comp;        

            iter = mandelbrot(cr, ci, MAX_ITER);

            // Aqui, o ponto está dentro do Conjunto
            if(iter == MAX_ITER) {
                color[0] = 255;
                color[1] = 255;
                color[2] = 255; // Branco
            }

            // Já aqui, está fora. As cores são definidas de acordo com o número de iterações
            // necessárias até o número 'explodir' ao infinito */
            else if(iter < 0.37 * MAX_ITER) {
                color[0] = 0;
                color[1] = 0;
                color[2] = 0; // Preto
            }
            else if(iter < 0.39 * MAX_ITER) {
                color[0] = 5;
                color[1] = 0;
                color[2] = 10; // Roxo
            }
            else if(iter < 0.41 * MAX_ITER) {
                color[0] = 10;
                color[1] = 0;
                color[2] = 20; // Roxo
            }
            else if(iter < 0.43 * MAX_ITER) {
                color[0] = 20;
                color[1] = 0;
                color[2] = 40; // Roxo
            }
            else if(iter < 0.45 * MAX_ITER) {
                color[0] = 40;
                color[1] = 0;
                color[2] = 60; // Roxo
            }
            else if(iter < 0.47 * MAX_ITER) {
                color[0] = 65;
                color[1] = 0;
                color[2] = 90; // Roxo
            }
            else if(iter < 0.49 * MAX_ITER) {
                color[0] = 90;
                color[1] = 0;
                color[2] = 120; // Roxo
            }
            else if(iter < 0.51 * MAX_ITER) {
                color[0] = 120;
                color[1] = 0;
                color[2] = 160; // Roxo
            }
            else if(iter < 0.53 * MAX_ITER) {
                color[0] = 180;
                color[1] = 0;
                color[2] = 90; // Lilás
            }
            else if(iter < 0.56 * MAX_ITER) {
                color[0] = 180;
                color[1] = 0;
                color[2] = 0; // Vermelho
            }
            else if(iter < 0.59 * MAX_ITER) {
                color[0] = 240;
                color[1] = 10;
                color[2] = 0; // Vermelho
            }
            else if(iter < 0.62 * MAX_ITER) {
                color[0] = 250;
                color[1] = 70;
                color[2] = 0; // Vermelho
            }
            else if(iter < 0.66 * MAX_ITER) {
                color[0] = 230;
                color[1] = 100;
                color[2] = 0; // Laranja
            }
            else if(iter < 0.72 * MAX_ITER) {
                color[0] = 240;
                color[1] = 140;
                color[2] = 0; // Laranja
            }
            else if(iter < 0.8 * MAX_ITER) {
                color[0] = 255;
                color[1] = 180;
                color[2] = 0; // Laranja
            }
            else if(iter < 0.9 * MAX_ITER) {
                color[0] = 255;
                color[1] = 255;
                color[2] = 0; // Amarelo
            }
            else if(iter >= 0.9 * MAX_ITER) {
                color[0] = 245;
                color[1] = 245;
                color[2] = 70; // Amarelo
            }
            fwrite(color, 1, 3, fp);
        }
    }

    fclose(fp);
    
    return 0;
}


/* Paleta de cores Rainbow

            // Aqui, o ponto está dentro do Conjunto
            if(iter == MAX_ITER) {
                color[0] = 255;
                color[1] = 255;
                color[2] = 255; // Branco
            }

            // Já aqui, está fora. As cores são definidas de acordo com o número de iterações
            // necessárias até o número 'explodir' ao infinito
            else if(iter < 0.37 * MAX_ITER) {
                color[0] = 0;
                color[1] = 0;
                color[2] = 0; // Preto
            }
            else if(iter < 0.4 * MAX_ITER) {
                color[0] = 0;
                color[1] = 0;
                color[2] = 40; // Azul
            }
            else if(iter < 0.43 * MAX_ITER) {
                color[0] = 0;
                color[1] = 0;
                color[2] = 100; // Azul
            }
            else if(iter < 0.46 * MAX_ITER) {
                color[0] = 10;
                color[1] = 80;
                color[2] = 200; // Azul claro
            }
            else if(iter < 0.5 * MAX_ITER) {
                color[0] = 0;
                color[1] = 220;
                color[2] = 0; // Verde
            }
            else if(iter < 0.55 * MAX_ITER) {
                color[0] = 100;
                color[1] = 255;
                color[2] = 0; // Verde limão
            }
            else if(iter < 0.6 * MAX_ITER) {
                color[0] = 255;
                color[1] = 255;
                color[2] = 0; // Amarelo
            }
            else if(iter < 0.65 * MAX_ITER) {
                color[0] = 255;
                color[1] = 110;
                color[2] = 0; // Laranja
            }
            else if(iter < 0.85 * MAX_ITER) {
                color[0] = 255;
                color[1] = 0;
                color[2] = 0; // Vermelho
            }
            else if(iter >= 0.85 * MAX_ITER) {
                color[0] = 255;
                color[1] = 0;
                color[2] = 180; // Lilás
            }
        
*/