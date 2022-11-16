#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#define usuarios.dat
#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#include "conio.h"
const int adminPass = 1234;
typedef struct
{
    char nombreYApellido[30];
    char dni[8];
    char calleYAltura[30];
    char telefono[15];
    char pass[20];
    int admin;
    int baja;
} cliente;

int main()
{
    menuAdministrador();
    //menuPrincipal();
}
void menuPrincipal()
{
    system("cls");
    int opcionMenu = 0;
    int usuarioValido = -1;
    int admin = -1;
    char dni[8];
    char pass[20];
    while(opcionMenu != 1 && opcionMenu!=2 && opcionMenu!=3)
    {
        printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
        printf("\n\t\t\t\t%cMENU PRINCIPAL%c",186,186);
        printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
        printf("\nElija una opcion\n1:Iniciar sesion\n2:Registrarse\n3:Registrar administrador\n4:Salir   ");
        fflush(stdin);
        scanf("%i", &opcionMenu);
        if(opcionMenu != 1 && opcionMenu!=2 && opcionMenu!=3 && opcionMenu!=4)
        {
            printf("\nEl numero ingresado no corresponde a ninguna de las opciones, ingrese nuevamente...\n\n");
            Sleep(700);
            system("cls");
        }
    }

    switch(opcionMenu)
    {
    case 1:
        system("cls");
        cartelIniciarSesion();
        printf("\n\tIngrese dni: ");
        fflush(stdin);
        gets(dni);
        printf("\n\tIngrese contrasenia: ");
        fflush(stdin);
        ocultarPass(pass);
        usuarioValido = verificarUsuario(dni, pass);
        printf("\nVerificar usuario termina");
        admin = checkAdmin(dni);
        if(usuarioValido == 1)
        {
            if(admin == 0)
            {
                menuUsuario();
            }

            else
            {
                printf("ACA VA EL MENU ADMIN");///borrar printf y poner menu admin
            }

        }
        else
        {
            printf("\n\tUsuario no encontrado, sera redirigido al menu principal...");
            system("pause");
            menuPrincipal();
        }
        break;
    case 2:
        system("cls");
        RegistrarUsuario();
        menuPrincipal();
        break;
    case 3:
        system("cls");
        RegistrarAdministrador();
        menuPrincipal();
    case 4:
        return 0;
        break;
    }

}
void RegistrarUsuario()
{
    cliente a;
    int flagValidacion = -1;

    printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,187);
    printf("\n\t\t\t\t%cREGISTRARSE%c",186,186);
    printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,188);
    printf("\n\n\t DNI : ");
    fflush(stdin);
    gets(a.dni);

    flagValidacion = verificarDni(a.dni);
    system("pause");
    if(flagValidacion == 0)
    {
        system("pause");
        printf("\n\t Nombre y apellido : ");
        fflush(stdin);
        gets(a.nombreYApellido);
        printf("\n\t Calle y altura : ");
        fflush(stdin);
        gets(a.calleYAltura);
        printf("\n\t Contrasenia : ");
        fflush(stdin);
        ocultarPass(a.pass);
        a.admin=0;
        a.baja=0;
        printf("\n\n\t Telefono : ");
        fflush(stdin);
        gets(a.telefono);


        guardarUsuario(a);
        printf("\n\nUsuario creado exitosamente");
        seraRedirigidoAlMenuPrincipal();
    }
    else
    {
        printf("\n\n\t DNI YA EXISTENTE. ");
        seraRedirigidoAlMenuPrincipal();
    }
}

void guardarUsuario(cliente a)
{
    FILE * pArchUsuarios = fopen("usuarios.dat","ab");
    if(pArchUsuarios!=NULL)
    {
        fwrite(&a,sizeof(cliente),1,pArchUsuarios);
        fclose(pArchUsuarios);
    }
}

int verificarDni(char dni[])
{
    cliente a;
    int flag = 0;

    FILE * pArchUsuario = fopen("usuarios.dat","rb");
    if(pArchUsuario!=NULL)
    {
        while(fread(&a,sizeof(cliente),1,pArchUsuario)>0)
        {
            if(strcmp(dni,a.dni)==0)
            {
                flag=1;
            }
        }
        fclose(pArchUsuario);
    }
    return flag;
}

void muestraUnUsuario(cliente a)
{
    printf("\n\t Nombre y apellido................: %s",a.nombreYApellido);
    printf("\n\t Dni................: %s",a.dni);
    printf("\n\t Telefono................: %s",a.telefono);
    printf("\n\t Direccion................: %s",a.calleYAltura);
    if(a.admin == 1)
    {
        printf("\n\tAdministrador................ Si");
    }
    else
        printf("\n\tAdministrador................ No");
    printf("\n\t____________________________________");
}

void muestraUsuarios()
{
    cliente a;
    FILE * pArchUsuarios = fopen("usuarios.dat","rb");
    if(pArchUsuarios!=NULL)
    {
        while(fread(&a,sizeof(cliente),1,pArchUsuarios)>0)
        {
            if(a.baja==0)
            {
                muestraUnUsuario(a);
            }
        }
        fclose(pArchUsuarios);
    }
}

void ocultarPass(char pass[20])
{


    int i=0;
    char aux;
    while(aux=getch())
    {
        if (aux == TECLA_ENTER)
        {
            pass[i] = '\0';
            break;
        }

        if(aux!=TECLA_ENTER)
        {
            if(aux==TECLA_BACKSPACE)
            {
                if(i>0)
                {
                    pass[i]--;
                    i--;
                    printf("\b \b");
                }
            }
            else
            {
                printf("*", aux);
                pass[i]=aux;
                i++;
            }
        }
    }

}

int verificarUsuario(char dni[],char pass[])
{
    cliente a;
    int flag = -1;
    FILE *pArchUsuarios = fopen("usuarios.dat","rb");
    if(pArchUsuarios != NULL)
    {
        while(fread(&a,sizeof(cliente),1,pArchUsuarios)>0)
        {
            if(strcmp(a.dni,dni) == 0)
            {
                if(strcmp(a.pass,pass)==0)
                {
                    if(a.baja == 0)
                    {
                        flag = 1;
                    }
                }
                if(flag==1)
                {
                    return 1;
                }
                else
                    return -1;
            }
        }
    }
}

int checkAdmin(char dni[])
{
    cliente a;
    int admin = 0;
    int flag = -1;
    FILE *pArchUsuarios = fopen("usuarios.dat","rb");
    if(pArchUsuarios != NULL)
    {
        while(fread(&a,sizeof(cliente),1,pArchUsuarios)>0)
        {
            if(strcmp(a.dni, dni)==0)
            {
                admin = a.admin;
            }
        }
    }
    return admin;
}

void cartelIniciarSesion()
{
    printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
    printf("\n\t\t\t\t%cINICIAR SESION%c",186,186);
    printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
}

void seraRedirigidoAlMenuPrincipal()
{
    printf("\n\nSera redirigido al menu principal\n");
    Sleep(1000);
    printf("3...");
    Sleep(1000);
    printf("2...");
    Sleep(1000);
    printf("1...");
    Sleep(1000);

}
void seraRedirigidoAlMenuUsuario()
{
    printf("\n\nSera redirigido al menu usuario\n");
    Sleep(1000);
    printf("3...");
    Sleep(1000);
    printf("2...");
    Sleep(1000);
    printf("1...");
    Sleep(1000);

}

void RegistrarAdministrador()
{
    int adminCheck = 0;
    printf("\nIngrese contrasenia de administrador para continuar: ");
    fflush(stdin);
    scanf("%d", &adminCheck);
    if(adminCheck == adminPass)
    {
        cliente a;
        int flagValidacion = -1;

        printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,187);
        printf("\n\t\t\t\t%cREGISTRARSE%c",186,186);
        printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,188);
        printf("\n\n\t DNI : ");
        fflush(stdin);
        gets(a.dni);

        flagValidacion = verificarDni(a.dni);
        if(flagValidacion == 0)
        {
            printf("\n\t Nombre y apellido : ");
            fflush(stdin);
            gets(a.nombreYApellido);
            printf("\n\t Calle y altura : ");
            fflush(stdin);
            gets(a.calleYAltura);
            printf("\n\t Contrasenia : ");
            fflush(stdin);
            ocultarPass(a.pass);
            a.admin=1;
            a.baja=0;
            printf("\n\n\t Telefono : ");
            fflush(stdin);
            gets(a.telefono);


            guardarUsuario(a);
            printf("\n\nUsuario de administrador creado exitosamente");
            seraRedirigidoAlMenuPrincipal();
        }
        else
        {
            printf("\n\n\t Dni ya existente. ");
            seraRedirigidoAlMenuPrincipal();
        }
    }
    else
    {
        printf("\nContrasenia de administrador incorrecta...");
        seraRedirigidoAlMenuPrincipal();
    }

}

void menuUsuario()
{
    printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,187);
    printf("\n\t\t\t\t%cMENU USUARIO%c",186,186);
    printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,188);
    int opcionUsuario;
    printf("\nElija una opcion\n1:Ver catalogo de productos\n2:Hacer un nuevo pedido\n3:Cancelar un pedido\n4:Volver al menu principal   ");
    fflush(stdin);
    scanf("%i", &opcionUsuario);
    if(opcionUsuario != 1 && opcionUsuario!=2 && opcionUsuario!=3)
    {
        printf("\nEl numero ingresado no corresponde a ninguna de las opciones, ingrese nuevamente...\n\n");
        Sleep(700);
        system("cls");
    }
    switch(opcionUsuario)
    {
    case 1:
        ///FUNCION MOSTRAR PRODUCTOS
        seraRedirigidoAlMenuUsuario();
        menuUsuario();
        break;
    case 2:
        ///FUNCION HACER UN NUEVO PEDIDO
        seraRedirigidoAlMenuUsuario();
        menuUsuario();
        break;
    case 3:
        ///FUNCION CANCELAR UN PEDIDO
        seraRedirigidoAlMenuUsuario;
        menuUsuario();
        break;
    case 4:
        seraRedirigidoAlMenuPrincipal;
        menuPrincipal();
        break;
    }
}

void menuAdministrador()
{
        printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
        printf("\n\t\t\t\t%cMENU ADMINISTRADOR%c",186,186);
        printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
    int opcionUsuario;
    printf("\nElija una opcion\n1:Ver catalogo de productos\n2:Hacer un nuevo pedido\n3:Cancelar un pedido\n4:Modificar productos\n5:Dar de baja usuario\nVolver al menu principal   ");
    fflush(stdin);
    scanf("%i", &opcionUsuario);
    if(opcionUsuario != 1 && opcionUsuario!=2 && opcionUsuario!=3)
    {
        printf("\nEl numero ingresado no corresponde a ninguna de las opciones, ingrese nuevamente...\n\n");
        Sleep(700);
        system("cls");
    }
    switch(opcionUsuario)
    {
    case 1:
        ///FUNCION MOSTRAR PRODUCTOS
        seraRedirigidoAlMenuUsuario();
        menuUsuario();
        break;
    case 2:
        ///FUNCION HACER UN NUEVO PEDIDO
        seraRedirigidoAlMenuUsuario();
        menuUsuario();
        break;
    case 3:
        ///FUNCION CANCELAR UN PEDIDO
        seraRedirigidoAlMenuUsuario;
        menuUsuario();
        break;
    case 4:
        seraRedirigidoAlMenuPrincipal;
        menuPrincipal();
        break;
    }
}
