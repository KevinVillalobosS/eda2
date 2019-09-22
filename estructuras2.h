typedef struct pixel{
        int Red;
        int Green;
        int Blue;
        struct pixel *siguientePixel;
}pixel;

typedef struct listaPixeles{
        struct pixel *primerPixel;
        struct pixel *ultimoPixel;
}listaPixeles;

typedef struct similitud{
        int cantidadPixeles;
        int repeticiones;
        struct similitud *siguienteSimilitud;
}similitud;
