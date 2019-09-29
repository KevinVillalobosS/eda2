/* Directivas
Estandar de entrada y salida (stdio)*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "estructuras2.h"

int anchoPixeles;
int altoPixeles;
int anchoImagen;
int altoImagen;

pixel* agregarPixel(pixel *lista, int rojo, int verde, int azul);

int obtenerLen(pixel *lista){
    pixel *aux;
    aux = lista;
    int contador = 0;
    while (aux != NULL){
        aux = aux->siguientePixel;
        contador = contador + 1;
    }
    return contador;
}

int obtenerLargo(similitud *lista){
    similitud *aux;
    aux = lista;
    int contador = 0;
    while (aux != NULL){
        aux = aux->siguienteSimilitud;
        contador = contador + 1;
    }
    return contador;
}


similitud* obtenerPosicion(similitud* lista, int indice){
    similitud* aux;
    aux = lista;
    int iterador = 0;
    while (aux != NULL){
        if (iterador == indice){
            return aux;
        }else{
            iterador = iterador + 1;
            aux = aux->siguienteSimilitud;
        }
    }
    return NULL;
}



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

    return rotada;
}


similitud* agregarCoincidencia(similitud *listaSimilitudes, int cantidadPixeles){
    if(cantidadPixeles == 0){
        return listaSimilitudes;
    }else{
        similitud *nuevaSimilitud, *aux, *aux1;
        nuevaSimilitud = (similitud*)malloc(sizeof(similitud));
        nuevaSimilitud-> cantidadPixeles = cantidadPixeles;
        nuevaSimilitud-> repeticiones = 1;
        nuevaSimilitud-> siguienteSimilitud = NULL;
        if(listaSimilitudes == NULL){
            listaSimilitudes = nuevaSimilitud;
        }else{
            aux1 = NULL;
            aux = listaSimilitudes;
            while (aux->siguienteSimilitud != NULL){
                if (aux->cantidadPixeles == cantidadPixeles){
                    //en caso de ya existir la cantidad de pixeles, simplemente se aumentan las repeticiones y se libera la memoria
                    aux->repeticiones = aux->repeticiones + 1;
                    free(nuevaSimilitud);
                    return listaSimilitudes;
                }else if(cantidadPixeles > aux->cantidadPixeles){
                    if (aux1 == NULL){
                        //debe ser el primero de la lista
                        nuevaSimilitud->siguienteSimilitud = aux;
                        listaSimilitudes = nuevaSimilitud;  
                    }else{
                        //el elemento anterior en aux1 apunta a nuevaSimilitud
                        aux1->siguienteSimilitud = nuevaSimilitud;
                        //nuevaSimilitud apunta al elemento actual en aux
                        nuevaSimilitud->siguienteSimilitud = aux;
                    }
                    return listaSimilitudes;
                }else{
                    aux1 = aux;
                    aux = aux->siguienteSimilitud;
                }
            }
            aux->siguienteSimilitud = nuevaSimilitud;  
        }
    }
    return listaSimilitudes;
}

/*ENTRADA: 
Dos matrices, con el mismo ancho y alto, además de un entero contador el cual acumula las veces que se verifica la igualdad
SALIDA: 
Entero con el contador actualizado en caso de encontrarse igualdad, o entero con el mismo valor del contador de entrada en caso de no encontrarse igualdad*/
similitud* verificarIgualdad(pixel* porRevisar, pixel* pixeles, similitud* similitudes){
    if (porRevisar == NULL){
        return similitudes;
    }else{
        bool sonIguales = true; 
        int total = anchoPixeles*altoPixeles;
        int contador = 0;
        for (int i=0; i<total; i++){
            if (porRevisar->Red == pixeles->Red && porRevisar->Green == pixeles->Green && porRevisar->Blue == pixeles->Blue ){
                /*se encontro una coincidencia*/
                contador = contador + 1;
            }
            porRevisar = porRevisar->siguientePixel;
            pixeles = pixeles->siguientePixel;
        }
        /*enviarlo a un 'agregar coincidencia', ahí hay que revisar si la cantidad de pixeles ya se encontraba antes*/
        similitudes = agregarCoincidencia(similitudes, contador);
        return similitudes;    
    }
}

/*ENTRADA: 
La matriz de la imagen que debe ser buscada y un doble puntero a la imagen grande.
Ademas, ingresa un entero que indicara la rotacion que tiene la imagen que debe ser buscada, pues el algoritmo cambia levente entre las 
rotaciones 0 y 180 contra las rotaciones 90 y 270.
SALIDA: 
Muestra por pantalla la cantidad de veces que se encuentra el pixel pixeles en el pixel imagen.*/
similitud* buscarImagen(pixel *pixeles, pixel *imagen, similitud* similitudes){  
    int i,j,k,m;
    int total = (anchoImagen) * (altoImagen);
    total = total - ( (altoPixeles-1)*anchoImagen + anchoPixeles  );
    pixel *copiaPixeles;
    pixel *copiaImagen;
    j = 0;
    for (i=0; i< total; i++){
        pixel *porRevisar = NULL;
        k = 0; //para recorrer la lista de pixeles
        m = 0; //variable auxiliar para extraer exactamente el ancho de pixeles dentro de la imagen
        copiaImagen = imagen;
        copiaPixeles = pixeles;

        if(j + anchoPixeles <= anchoImagen){
            while(k < anchoPixeles*altoPixeles){
                if(copiaImagen == NULL){
                    printf("null %d \n", i);
                    porRevisar = NULL;
                    break;
                }
             
                if (m == anchoPixeles){
                   
                    m = 0;
                    while (m < anchoImagen - anchoPixeles + 1){
                         copiaImagen = copiaImagen->siguientePixel;
                         m = m + 1;
                    }
                    m = 0;
                }
              
                porRevisar = agregarPixel(porRevisar, copiaImagen->Red, copiaImagen->Green, copiaImagen->Blue);
              
                k = k + 1;
                m = m + 1;
                copiaImagen = copiaImagen->siguientePixel;
            }
        }else if(j == anchoImagen){
            j = 0;
        }
        /*Una vez saliendo del ciclo anterior, se debiese haber generado una lista con los elementos a revisar.*/
        similitudes = verificarIgualdad(porRevisar, pixeles, similitudes);
        imagen = imagen->siguientePixel;
        j = j + 1;
    }
    return similitudes;
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
//calcula promedio
double calcularMedia(similitud *listaSimilitudes){
    similitud *aux = listaSimilitudes;
    int acumulador = 0;
    int cantidadElementos = 0;
    while (aux != NULL){
        acumulador = acumulador + (aux->cantidadPixeles*aux->repeticiones);
        cantidadElementos = cantidadElementos + 1*aux->repeticiones;
        aux = aux->siguienteSimilitud;
    }
    double media = (double) acumulador/cantidadElementos;
    return media;

}
//calcula desviación estandar
double calcularDesviacion(similitud *listaSimilitudes, double media){
    similitud *aux = listaSimilitudes;
    double acumulador = 0;
    int cantidadElementos = 0;
    while (aux != NULL){
        acumulador = acumulador + (pow((aux->cantidadPixeles-media),2))*aux->repeticiones;
        cantidadElementos = cantidadElementos + 1*aux->repeticiones;
        aux = aux->siguienteSimilitud;
    }
    printf("%f %d\n",acumulador, cantidadElementos);
    double division = acumulador/cantidadElementos;
    double desvEst = sqrt(division);
    return desvEst;
}

//listaSimilitudes: numPixeles, cantidadRepeticiones, siguienteSimilitud
int imprimirRespuesta(similitud *listaSimilitudes){
    double media = calcularMedia(listaSimilitudes);
    double desvEstandar = calcularDesviacion(listaSimilitudes, media);
    similitud *mayorSimilitud = listaSimilitudes;
    similitud *menorSimilitud  = listaSimilitudes;
    while (menorSimilitud->siguienteSimilitud != NULL){
        menorSimilitud = menorSimilitud->siguienteSimilitud;
    }
    printf("Mayor similitud: %d pixeles encontrado %d veces\n", mayorSimilitud->cantidadPixeles, mayorSimilitud->repeticiones);
    printf("Menor similitud: %d pixeles encontrado %d veces\n", menorSimilitud->cantidadPixeles, menorSimilitud->repeticiones);
    printf("Media: %f pixeles\n", media);
    printf("Desviacion estandar: %f\n", desvEstandar);
    return 0;

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
            if (pixel == 248 && pixel2 == 200 && pixel3 == 128){
                int acs = obtenerLen(imagen);
                printf("hey oh %d\n", acs);
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
      //Se abre el archivo con la sub-imagen
    FILE *archivo0;
    archivo0 = fopen("buscarR.in","r");
    //Se extraen los valores de ancho y alto
	char auxLectura0;
    auxLectura0 = fscanf(archivo0, "%d[^ ]", &anchoPixeles);
    auxLectura0 = fscanf(archivo0, "%d[^\n]", &altoPixeles);
    listaPixeles *subImagen = NULL;
    //lista pixeles, encargada de almacenar los elementos de la sub-imagen
    pixel *pixeles = NULL;
    pixeles = leer(pixeles, subImagen, auxLectura0,archivo0);
    //al terminar el ciclo, el puntero pixeles apuntara al final de la lista
    
    //while(pixeles != NULL){
    //   printf("%d %d %d \n", pixeles->Red, pixeles->Green, pixeles->Blue);
    //    pixeles = pixeles->siguientePixel;
    //}
    //Se cierra el archivo
    fclose(archivo0);
    //pixel *rotado90 = NULL;
    //rotado90 = rotar90(pixeles, rotado90, anchoPixeles, altoPixeles); //funciona:3
    
    //pixel *rotado180 = NULL;
    //rotado180 = rotar90(rotado90, rotado180, altoPixeles, anchoPixeles);     

    //----------------------------------------------------------------------------------------------//
    FILE *archivo1;
    archivo1 = fopen("imagenR.in","r");
	char auxLectura1;
    auxLectura1 = fscanf(archivo1, "%d[^ ]", &anchoImagen);
    auxLectura1 = fscanf(archivo1, "%d[^\n]", &altoImagen);
    //se genera y reserva memoria para un doble puntero al array 2D de estructura pixel que almacenara los datos de la imagen
    pixel *imagen = NULL;
    //Se lee la imagen grande
    imagen = leerImagen(imagen,auxLectura1,archivo1);
    //Se cierra el archivo
    fclose(archivo1);



    similitud *similitudes = NULL;
    similitudes = buscarImagen(pixeles, imagen, similitudes);

    while(similitudes != NULL){
        printf("%d %d\n", similitudes->cantidadPixeles, similitudes->repeticiones);
        similitudes = similitudes->siguienteSimilitud;
    }

    
    return 0;
}

/* Función main inicia la ejecución del programa */
int main(){
    leerInstrucciones();
    
} /* fin de main */

