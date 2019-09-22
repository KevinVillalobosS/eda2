/* Directivas
Estandar de entrada y salida (stdio)*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "estructuras2.h"

int anchoPixeles;
int altoPixeles;
int anchoImagen;
int altoImagen;

pixel* agregarPixel(pixel *lista, int rojo, int verde, int azul);

pixel* obtenerIndice(pixel* lista, int indice){
    pixel* aux;
    aux = lista;
    int iterador = 0;
    while (aux != NULL){
        if (iterador == indice){
            return aux;
        }else{
            iterador = iterador + 1;
            aux = aux->siguientePixel;
        }
    }
    return NULL;
}

pixel* rotar90(pixel* aRotar, pixel* rotada, int ancho, int alto){
    int aux = ancho*alto - ancho;
    int aux2;
    int iterador = 0;
    printf("he llegado aca, comienza mi trabajo\n");
    while (iterador < ancho){
        aux2 = aux;
        int iterador2 = 0;
        while (iterador2 < alto){
            pixel* temporal = obtenerIndice(aRotar, aux2); //obtengo el pixel ubicado en la posicion aux2
            rotada = agregarPixel(rotada, temporal->Red, temporal->Green, temporal->Blue);
            aux2 = aux2 - ancho;
            iterador2 = iterador2 + 1;
        }
        aux = aux + 1;
        iterador = iterador + 1;
    }
    printf("pude salir del ciclo");

    return rotada;
}


similitud* agregarCoincidencia(similitud *listaSimilitudes, int cantidadPixeles){
    similitud *nuevaSimilitud, *aux, *aux1;
    nuevaSimilitud = (similitud*)malloc(sizeof(similitud));
    nuevaSimilitud-> cantidadPixeles = cantidadPixeles;
    nuevaSimilitud-> siguienteSimilitud = NULL;
    if(listaSimilitudes == NULL){
        listaSimilitudes = nuevaSimilitud;
    }else{
        aux1 = NULL;
        aux = listaSimilitudes;
        while (aux->siguienteSimilitud != NULL){
            if (aux->cantidadPixeles == cantidadPixeles){
                aux->repeticiones = aux->repeticiones + 1;
                break;
            }else if(cantidadPixeles > aux->cantidadPixeles){
                if (aux1 == NULL){
                    //debe ser el primero de la lista
                    nuevaSimilitud->siguienteSimilitud = aux;
                }else{
                    //el elemento anterior en aux1 apunta a nuevaSimilitud
                    aux1->siguienteSimilitud = nuevaSimilitud;
                    //nuevaSimilitud apunta al elemento actual en aux
                    nuevaSimilitud->siguienteSimilitud = aux;
                }
                break;

            }else{
                aux1 = aux;
                aux = aux->siguienteSimilitud;
            }
        }
        aux->siguienteSimilitud = nuevaSimilitud;  
    }
    return listaSimilitudes;
}

/*ENTRADA: 
Dos matrices, con el mismo ancho y alto, además de un entero contador el cual acumula las veces que se verifica la igualdad
SALIDA: 
Entero con el contador actualizado en caso de encontrarse igualdad, o entero con el mismo valor del contador de entrada en caso de no encontrarse igualdad*/
int verificarIgualdad(pixel* porRevisar, pixel* pixeles){
    bool sonIguales = true;
    int total = anchoPixeles*altoPixeles;
    int contador = 0;
    for (int i=0; i<total; i++){
        if (porRevisar->Red == pixeles->Red && porRevisar->Green == pixeles->Green && porRevisar->Blue == pixeles->Blue ){
            /*se encontro una coincidencia*/
            contador = contador + 1;
        }
    }
    /*enviarlo a un 'agregar coincidencia', ahí hay que revisar si la cantidad de pixeles ya se encontraba antes*/
    return 0;    
}

/*ENTRADA: 
La matriz de la imagen que debe ser buscada y un doble puntero a la imagen grande.
Ademas, ingresa un entero que indicara la rotacion que tiene la imagen que debe ser buscada, pues el algoritmo cambia levente entre las 
rotaciones 0 y 180 contra las rotaciones 90 y 270.
SALIDA: 
Muestra por pantalla la cantidad de veces que se encuentra el pixel pixeles en el pixel imagen.*/
void buscarImagen(pixel *pixeles, pixel *imagen){  
    int i,j,k,m;
    int total = anchoImagen * altoImagen;
    for (i=0; i< total; i++){
            j = i;
            pixel *porRevisar = NULL;
            k = 0;
            m = 0;
            while(k < anchoPixeles*altoPixeles){
                    if (m == anchoPixeles){
                        m = 0;
                        j=0;
                        while (j < anchoImagen - anchoPixeles){
                            imagen = imagen->siguientePixel;
                            j = j + 1;
                        }
                    }
                    porRevisar = agregarPixel(porRevisar, imagen->Red, imagen->Green, imagen->Blue);
                    k = k + 1;
                    m = m + 1;
                    imagen = imagen->siguientePixel;
            }
            /*Una vez saliendo del ciclo anterior, se debiese haber generado una lista con los elementos a revisar.*/
            printf("encontre una coincidencia con iterador igual a %i \n",i);
            /*verificarIgualdad(porRevisar, pixeles);
                    if (!(sePaso)){
                        contador = verificarIgualdad(porRevisar, pixeles, contador);
                    }/*end if !sePaso*/
             
    }
    /*printf("Cantidad para rotacion %i: %i\n", indicador, contador);*/
}

pixel* agregarPixel(pixel *lista, int rojo, int verde, int azul){
    pixel *nuevoPixel, *aux;
    nuevoPixel = (pixel*)malloc(sizeof(pixel));
    nuevoPixel -> Red = rojo;
    nuevoPixel -> Green = verde;
    nuevoPixel -> Blue = azul;
    nuevoPixel -> siguientePixel = NULL;
    if(lista == NULL){
        lista = nuevoPixel;
    }else{
        aux = lista;
        while (aux->siguientePixel != NULL){
            aux = aux->siguientePixel;
        }
        aux->siguientePixel = nuevoPixel;  
    }
    return lista;
}

/*ENTRADA: 
Ingresa una *Matriz, un char auxLectura y un FILE *archivo, el primer argumento apunta hacia donde estara la matriz
matriz, la cual almacenara los datos existentes en el archivo que se ubica en *archivo. 
AuxLectura almacena las lineas y ayuda a separar los elementos.
SALIDA: 
Modifica pixel (*matriz), dejando los datos encontrados en archivo en la primera estructura*/
pixel* leer(pixel *pixeles, listaPixeles *subImagen, char auxLectura, FILE *archivo){
    int pixel; 
	int pixel2; 
	int pixel3; 
	char* coma = (char*)malloc(4*sizeof(char)); 
    /*Ciclo encargado de recorrer el archivo para extraer los datos*/
	for (int i = 0; i < altoPixeles; i++){
        for (int j = 0; j < anchoPixeles; j++){
            if (j == anchoPixeles-1){
                auxLectura = fscanf(archivo, "%d %c %d %c %d\n", &pixel, coma, &pixel2, coma, &pixel3); 
            }else{
                auxLectura = fscanf(archivo, "%d %c %d %c %d", &pixel, coma, &pixel2, coma, &pixel3); 
            }
            pixeles = agregarPixel(pixeles, pixel, pixel2, pixel3);
            /*printf("%d %d %d \n", pixel, pixel2, pixel3);*/
        }
    }  
    return pixeles;
}

/*ENTRADA: 
Ingresa una **imagen, un char auxLectura y un FILE *archivo, el primer argumento apunta hacia donde estara la matriz
imagen, la cual almacenara los datos existentes en el archivo que se ubica en *archivo. 
AuxLectura almacena las lineas y ayuda a separar los elementos.
SALIDA: 
Modifica pixel (**imagen), dejando los datos encontrados en archivo en la primera estructura*/
pixel* leerImagen(pixel *imagen, char auxLectura, FILE *archivo){
    int pixel; 
	int pixel2; 
	int pixel3; 
	char* coma = (char*)malloc(4*sizeof(char)); 
    /*Ciclo encargado de recorrer el archivo para extraer los datos*/
	for (int i = 0; i < altoImagen; i++){
        for (int j = 0; j < anchoImagen; j++){
            if (j == anchoImagen-1){
                auxLectura = fscanf(archivo, "%d %c %d %c %d\n", &pixel, coma, &pixel2, coma, &pixel3); 
            }else{
                auxLectura = fscanf(archivo, "%d %c %d %c %d", &pixel, coma, &pixel2, coma, &pixel3); 
            }
            imagen = agregarPixel(imagen, pixel, pixel2, pixel3);
        }
    }  
    return imagen;
}
/*ENTRADA: 
Funcion encargada del ciclo principal, no recibe entradas.
Se encarga de realizar las llamadas respectivas a las demas funciones en base a los nombres claves entregados en el enunciado: buscar.in e imagen.in
Realiza las reservas de memoria correspondientes, y libera dicha memoria cuando es necesario. 
SALIDA: 
entero que indicara que el programa se ejecuto correctamente*/
int leerInstrucciones (){ 
    /*Se abre el archivo con la sub-imagen*/
    FILE *archivo0;
    archivo0 = fopen("buscarR.in","r");
    /*Se extraen los valores de ancho y alto*/
	char auxLectura0;
    auxLectura0 = fscanf(archivo0, "%d[^ ]", &anchoPixeles);
    auxLectura0 = fscanf(archivo0, "%d[^\n]", &altoPixeles);
    listaPixeles *subImagen = NULL;
    /*lista pixeles, encargada de almacenar los elementos de la sub-imagen*/
    pixel *pixeles = NULL;
    pixeles = leer(pixeles, subImagen, auxLectura0,archivo0);
    /*al terminar el ciclo, el puntero pixeles apuntara al final de la lista*/
    
    /*while(pixeles != NULL){
        printf("%d %d %d \n", pixeles->Red, pixeles->Green, pixeles->Blue);
        pixeles = pixeles->siguientePixel;
    }*/
    /*Se cierra el archivo*/
    fclose(archivo0);


    pixel *rotado90 = NULL;
    rotado90 = rotar90(pixeles, rotado90, anchoPixeles, altoPixeles); //funciona:3

    pixel *rotado180 = NULL;
    rotado180 = rotar90(rotado90, rotado180, altoPixeles, anchoPixeles); 




    while(rotado180 != NULL){
        printf("%d %d %d \n", rotado180->Red, rotado180->Green, rotado180->Blue);
        rotado180 = rotado180->siguientePixel;
    }

    
    FILE *archivo1;
    archivo1 = fopen("imagen.in","r");
	char auxLectura1;
    auxLectura1 = fscanf(archivo1, "%d[^ ]", &anchoImagen);
    auxLectura1 = fscanf(archivo1, "%d[^\n]", &altoImagen);
    /*se genera y reserva memoria para un doble puntero al array 2D de estructura pixel que almacenara los datos de la imagen*/
    pixel *imagen = NULL;
    /*Se lee la imagen grande*/
    imagen = leerImagen(imagen,auxLectura1,archivo1);
    /*Se cierra el archivo*/
    fclose(archivo1);


    return 0;
}

/* Función main inicia la ejecución del programa */
int main(){
    leerInstrucciones();
    
} /* fin de main */

