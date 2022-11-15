#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

typedef struct
{
    char nombreYApellido[30];
    char dni[8];
    char calleYAltura[30];
    char telefono[15];
} cliente;

typedef struct
{
    cliente dato;
    int baja;
    int admin;
    struct nodoArbol * der;
    struct nodoArb * izq;
} nodoArb;


#endif
