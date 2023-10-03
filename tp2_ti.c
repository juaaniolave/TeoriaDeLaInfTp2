#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_PALABRA 50
#define MAX_ALFABET 256

void lee_archivo (char*);

int main(int argc, char *argv[]) {
   
   char* extension_txt = ".txt";
   char *nombre_archivo=NULL;
   int n=3;


   for (int i = 1; i < argc; i++) {
      char *param = argv[i];
      if (strstr(param, extension_txt) != NULL)  //.bin
      nombre_archivo = param;
   }
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
   int  totalFrecuenciaPalabras = 0;

   int i, j, k, m, longitud;
   int encontrada;
   int alfabeto[MAX_ALFABET] = {0}; //inicializa todas las componentes en 0
   double entropia=0;
   double longitudMedia=0;
   FILE* archivo = fopen(nombre_archivo,"rt");

   if (archivo == NULL){
      printf("No se pudo abrir el archivo");
      exit (-1);
   }

   while (fscanf(archivo, "%s", palabra) == 1) {
      encontrada = 0;
      // Busca la palabra en el array
      for (i = 0 ; i < totalPalabras ; i++) {
         if (strcmp(vec_pal[i].palabra, palabra) == 0) {
            vec_pal[i].frecuencia++;
            encontrada = 1;
            totalFrecuenciaPalabras++;
            break; //corta el for si la encontro
         }
      }

      // Si la palabra no se encontró, se agrega al array
      if (!encontrada) {
         strcpy(vec_pal[totalPalabras].palabra, palabra);
         vec_pal[totalPalabras].frecuencia = 1;
         totalPalabras++;
         totalFrecuenciaPalabras++;

         //Para alfabeto código: (B)
         /*Recorro cada palabra nueva y pongo en 1 el vector del alfabeto si hay
         alguna palabra existente no marcada*/
         
         longitud = strlen(vec_pal[totalPalabras - 1].palabra);
         for (j = 0 ; j < longitud ; j++) 
            alfabeto[(int)(vec_pal[totalPalabras - 1].palabra[j])] = 1;   
      }
   }

   // Calcula la probabilidad de aparición para cada palabra
   for (int m = 0 ; m < totalPalabras ; m++){ 
      vec_pal[m].probabilidad = (double)vec_pal[m].frecuencia / totalFrecuenciaPalabras;
      if(vec_pal[m].probabilidad != 0){
         entropia+=vec_pal[m].probabilidad*log2(1/vec_pal[m].probabilidad);
         longitudMedia+=strlen(vec_pal[m].palabra)*vec_pal[m].probabilidad;
      }
   }

    // Imprime las palabras y sus probabilidades
   for (int n = 0 ; n < totalPalabras ; n++) 
      printf("Palabra: %s\t Frecuencia: %d\t Probabilidad: %.4f\n", vec_pal[n].palabra, vec_pal[n].frecuencia, vec_pal[n].probabilidad);
   

   printf("\nLa entropia de la fuente es: %.2f bits\n", entropia);
   printf("La longitud media del codigo es :%.2f\n", longitudMedia);
   //Imprime el alfabeto codigo
   printf("\n--- Alfabeto codigo ---\n");
   
   for (k = 0 ; k < MAX_ALFABET ; k++) 
      if (alfabeto[k])
      printf("Componente %d:  %c \n", k,(char)k);
   
   fclose(archivo);
}
