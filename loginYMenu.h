#ifndef LOGINYMENU_H_INCLUDED
#define LOGINYMENU_H_INCLUDED
#include "pedido.h"
#include "comida.h"
typedef struct
{
    char nombreYApellido[30];
    char dni[9];
    char calleYAltura[30];
    char telefono[15];
    char pass[20];
    int admin;
    int baja;
} cliente;

pedidoCelda *listaPedidoCelda;
cliente usuarioLogeado;

void menuPrincipal();
void RegistrarUsuario();
void guardarUsuario(cliente a);
int verificarDni(char dni[]);
void muestraUnUsuario(cliente a);
void muestraUsuarios();
void ocultarPass(char pass[20]);
int verificarUsuario(char dni[],char pass[]);
int checkAdmin(char dni[]);
void cartelIniciarSesion();
void seraRedirigidoAlMenuPrincipal();
void seraRedirigidoAlMenuUsuario();
void RegistrarAdministrador();
void menuUsuario();
void menuAdministrador();
int devolverOpcionMenu();

#endif // LOGINYMENU_H_INCLUDED
