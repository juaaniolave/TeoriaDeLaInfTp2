#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PALABRA 50
#define MAX_ALFABET 256

int main () {
    char *nombre_archivo = NULL;
    lee_archivo(nombre_archivo);
}


void lee_archivo (char *nombre_archivo) {

   typedef struct {
      char   palabra[MAX_PALABRA];
      int    frecuencia;
      double probabilidad;
   } pal;

   char palabra[MAX_PALABRA];
   pal  vec_pal[1000];  // Suponemos un máximo de 1000 palabras diferentes
   int  totalPalabras = 0;

   int i, j, k, m, longitud;
   int encontrada;
   int alfabeto[MAX_ALFABET] = {0}; //inicializa todas las componentes en 0

   FILE* archivo = fopen(nombre_archivo,"rt");

   while (fscanf(archivo, "%s", palabra) == 1) {
      encontrada = 0;
      // Busca la palabra en el array
      for (i = 0 ; i < totalPalabras ; i++) {
         if (strcmp(vec_pal[i].palabra, palabra) == 0) {
            vec_pal[i].frecuencia++;
            encontrada = 1;
            break; //corta el for si la encontro
         }
      }

      // Si la palabra no se encontró, se agrega al array
      if (!encontrada) {
         strcpy(vec_pal[totalPalabras].palabra, palabra);
         vec_pal[totalPalabras].frecuencia = 1;
         totalPalabras++;

         //Para alfabeto código: (B)
         /*Recorro cada palabra nueva y pongo en 1 el vector del alfabeto si hay
         alguna palabra existente no marcada*/
         
         longitud = strlen(vec_pal[totalPalabras - 1].palabra);
         for (j = 0 ; j < longitud ; j++) 
            alfabeto[(int)(vec_pal[totalPalabras - 1].palabra[j])] = 1;   
      }
   }

   // Calcula la probabilidad de aparición para cada palabra
   for (int m = 0 ; m < totalPalabras ; m++) 
      vec_pal[m].probabilidad = (double)vec_pal[m].frecuencia / totalPalabras;

    // Imprime las palabras y sus probabilidades
   for (int n = 0 ; n < totalPalabras ; n++) 
      printf("Palabra: %s, Frecuencia: %d, Probabilidad: %.4f\n", vec_pal[n].palabra, vec_pal[n].frecuencia, vec_pal[n].probabilidad);
   
   //Imprime el alfabeto codigo
   printf("--- Alfabeto codigo ---\n");
   for (k = 0 ; k < MAX_ALFABET ; k++) 
      printf("Componente %d  =  %c \n", k,(char)k);
   
   fclose(archivo);
}
