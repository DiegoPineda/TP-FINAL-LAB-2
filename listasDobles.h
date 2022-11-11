#ifndef LISTASDOBLES_H_INCLUDED
#define LISTASDOBLES_H_INCLUDED

///Estructuras para el manejo de listas dobles:

typedef struct
{
    usuario dato;
    struct nodo2* anterior;
    struct nodo2* siguiente;
} nodo2;

typedef struct
{
    struct nodo2* adelante;
    struct nodo2* atras;
} fila;


///Funciones multi-uso:
nodo2* inicLista();
nodo2* crearNodo(jugador dato);
nodo2* agregarPrincipio(nodo2* lista,nodo2* nuevoNodo);
nodo2* buscarUltimo(nodo2* lista);
nodo2* agregarFinal(nodo2* lista,nodo2* nuevoNodo);
nodo2* agregarEnOrden(nodo2* lista,nodo2* nuevoNodo);
char preguntar();
void mostrarLista(nodo2* lista);
///Funciones para el ejercicio 1:
nodo2* cargarLista(nodo2* lista);
nodo2* borrarNodo(char nombre[20],nodo2* lista);

///Funciones para el ejercicio 3:
void inicFila(fila* cola);
void mostrarFila(fila* cola);
void agregaFinal(fila* cola, nodo2* nuevoNodo);
void leerFila(fila* cola);
int filavacia(fila* cola);

#endif // LISTASDOBLES_H_INCLUDED
