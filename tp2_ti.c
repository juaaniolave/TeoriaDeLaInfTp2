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
   int  totalPalabras        = 0;
   int  totalPalabrasArchivo = 0;

   int i, j, k;
   int encontrada            = 0;
   int alfabeto[MAX_ALFABET] = {0};

   FILE* archivo = fopen(nombre_archivo,"rt");

   while (fscanf(archivo, "%s", palabra) == 1) {
      totalPalabrasArchivo++;
      
      // Busca la palabra en el array
      for (i = 0 ; i < totalPalabras ; i++) {
         if (strcmp(vec_pal[i].palabra, palabra) == 0) {
            vec_pal[i].frecuencia++;
               encontrada = 1;
               break;
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
         
         for (j = 0 ; j < strlen(vec_pal[totalPalabras].palabra) ; j++) {
            if (alfabeto[vec_pal[totalPalabras].palabra[j]] != 0)
               alfabeto[vec_pal[totalPalabras].palabra[j]] = 1;   
         }
      }
   }

   // Calcula la probabilidad de aparición para cada palabra
   for (int i = 0 ; i < totalPalabras ; i++) {
      vec_pal[i].probabilidad = (double)vec_pal[i].frecuencia / totalPalabrasArchivo;
   }

    // Imprime las palabras y sus probabilidades
   for (int i = 0 ; i < totalPalabras ; i++) {
      printf("Palabra: %s, Frecuencia: %d, Probabilidad: %.4f\n", vec_pal[i].palabra, vec_pal[i].frecuencia, vec_pal[i].probabilidad);
   }
   
   //Imprime el alfabeto codigo
   printf("--- Alfabeto codigo ---\n");
   for (k = 0 ; k < MAX_ALFABET ; k++) {
      printf("%c \n",alfabeto[k]);
   }
   
   fclose(archivo);
}
