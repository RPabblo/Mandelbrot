// Made by: Rwann Pabblo
// Para melhor performance, compile com
// gcc -O3 -ffast-math mandelbrot.c -o mandelbrot

#include <stdio.h>
#include <math.h>
#include <complex.h>

void mandelbrot(double cr, double ci, int MAX_ITER, char color[], int offset, float pl);

void HSVtoRGB(float H, float s, float v, char color[]);

float normalizar(float nsmooth, int offset, float pl);

void paleta_temperature(float nsmooth, char color[], int offset, float pl);

void paleta_completa(float nsmooth, char color[], int offset, float pl);


int main(void)
{
// ============================================================================================


    // Área a ser visualizada, definida pelos intervalos na reta real e na reta imaginária.
    const double RE_INICIO = -0.789;
    const double RE_FINAL = -0.779;
    const double IM_INICIO = -0.134;
    const double IM_FINAL = -0.144;

    //Tamanho da imagem, em pixels.
    const double COMP = 1000;
    const double ALT = 1000;

    // Número de iterações; para um zoom mais profundo, é recomendado um número maior delas.
    const int MAX_ITER = 5000;

    // Desvio de cores; recomendado valores entre 0 e 360.
    const int offset = 51;

    /* Comprimento da peleta de cores. 
    Quanto maior o valor, maior a frequencia (rotatividade) de cores.
    Recomendado menor valor para zoom profundo. */
    const float pallete_lenght = 0.4;


// ============================================================================================


    // Intervalo de cores; 255 para o intervalo RGB.
    const int maxcolor = 255;

    const double pixel_comp = (RE_FINAL - RE_INICIO) / COMP;
    const double pixel_alt = (IM_FINAL - IM_INICIO) / ALT;

    // Guarda o valor de cada cor (R, G, B) em valores de 0 a 255.
    char color[3];

    // Parte real do número complexo.
    double cr;
    // Parte imaginária do número complexo.
    double ci;

    int x, y;

    // Abre arquivo .ppm no modo de escrita em binário.
    FILE* fp = fopen("fractal.ppm", "wb");
    fprintf(fp, "P6\n %d\n %d\n %d\n", (int) COMP, (int) ALT, maxcolor);

    for(y = 0; y < ALT; y++)
    {
        ci = IM_INICIO + y * pixel_alt;

        for(x = 0; x < COMP; x++)
        {
            cr = RE_INICIO + x * pixel_comp;        

            mandelbrot(cr, ci, MAX_ITER, color, offset, pallete_lenght);

            // Escreve no arquivo .ppm a cor de cada pixel.
            fwrite(color, 1, 3, fp);
        }
    }

    fclose(fp);
    
    return 0;
}



// Função que calcula e colore os pixels.
void mandelbrot(double cr, double ci, int MAX_ITER, char color[], int offset, float pl)
{
/*  O quadrado do módulo do número complexo é obtido por Pitágoras: |z|^2 = a^2 + b^2
    As variáveis a e b guardam os quadrados de atemp e btemp, respectivamente.
    Se o quadrado do módulo passar de 4, a função retorna. 
*/
    double atemp = 0.0, btemp = 0.0;
    double a = atemp * atemp;
    double b = btemp * btemp;
    int n;

    for(n = 0; (a + b) <= 4 && n < MAX_ITER; n++) {
        btemp = 2 * atemp * btemp + ci; 
        atemp = a - b + cr;

        a = atemp * atemp;
        b = btemp * btemp;    
    }

    // Verifica se o ponto está dentro do fractal.
    if (n == MAX_ITER) {
        color[0] = 0;
        color[1] = 0;
        color[2] = 0; // Preto
        return;
    }

    double complex z = a + b * I;

    // Caso cabs(z) não funcione, substitua por fabs(a + b).
    float nsmooth = n + 1 - log2(log2(cabs(z))) / log2(2);

    //paleta_completa(nsmooth, color, offset, pl);
    paleta_temperature(nsmooth, color, offset, pl);
}


// Função que "normaliza" o valor de nsmooth para dar rotatividade à paleta de cores.
float normalizar(float nsmooth, int offset, float pl)
{
    nsmooth = nsmooth * pl + offset;

    while(nsmooth > 360)
        nsmooth -= 360;

    if(nsmooth > 60 && nsmooth < 240)
        nsmooth += 180;

    while(nsmooth > 360)
        nsmooth -= 360;

    return nsmooth;
}


// Transforma cores HSV em RGB.
void HSVtoRGB(float H, float s, float v, char color[])
{
    // Hue = 0-360, Saturation = 0-1, Value = 0-1
    float C = s * v;
    float X = C * (1 - fabs(fmod(H / 60.0, 2) -1));
    float m = v - C;
    float r, g, b;

    if(H >= 0 && H < 60)
        r = C, g = X, b = 0;
  
    else if(H >= 240 && H < 300)
        r = X, g = 0, b = C;

    else if(H >= 300 && H <= 360)
        r = C, g = 0, b = X;

    else if(H >= 60 && H < 120)
        r = X, g = C, b = 0;

    else if(H >= 120 && H < 180)
        r = 0, g = C, b = X;

    else
        r = 0, g = X, b = C;

    color[0] = (r + m) * 255;
    color[1] = (g + m) * 255;
    color[2] = (b + m) * 255;
}


// Paleta de cores do azul ao amarelo.
void paleta_temperature(float nsmooth, char color[], int offset, float pl)
{
    nsmooth = normalizar(nsmooth, offset, pl);

    float w = 0;

    if(nsmooth >= 240)
        w = (nsmooth - 240) / 180;
    
    else if(nsmooth >= 0 && nsmooth <= 60)
        w = (nsmooth + 120) / 180;

    HSVtoRGB(nsmooth, 1.0f, w, color);
}


// Paleta de cores com todas as cores do espectro HSV / HSB.
void paleta_completa(float nsmooth, char color[], int offset, float pl)
{
    nsmooth = nsmooth * pl + offset;

    while(nsmooth > 360)
        nsmooth -= 360;

    HSVtoRGB(nsmooth, 1.0f, 1.0f, color);
}


/*
    Mandelbrot completo paleta completa 1:1
const double RE_INICIO = -2;
const double RE_FINAL = 0.5;
const double IM_INICIO = 1.25;
const double IM_FINAL = -1.25;


    Mini Mandelbrot temperature 16:9
const double RE_INICIO = -1.7864478;
const double RE_FINAL = -1.7864152;
const double IM_INICIO = -0.00000916875;
const double IM_FINAL = 0.00000916875;


    Mini mandelbrot paleta completa 1:1
const double RE_INICIO = -0.7709551;
const double RE_FINAL = -0.7709511;
const double IM_INICIO = -0.115619;
const double IM_FINAL = -0.115623;


    Seahorse valley zoom temperature 1:1
const double RE_INICIO = -0.789;
const double RE_FINAL = -0.779;
const double IM_INICIO = -0.134;
const double IM_FINAL = -0.144;
*/

