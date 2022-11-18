#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#define usuarios.dat
#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#include "conio.h"
#include "comida.h"
#include "pedido.h"
#include "postres.h"
#include "bebidas.h"
#include "loginYMenu.h"
#include "arbol.h"
const int adminPass = 1234;

int validos;
int validosBebida;
int validosPostre;
CatComida Categorias[10];
CeldaPostre Categoriaspos[10];
CeldaBebida CategoriasBeb[10];
pedidoCelda *listaPedidoCelda;
nodoArbol *listaClientes;




int main()
{

    validos = leerArvchivoComidas(Categorias, 10);
    validosBebida = leerArvchivoBebida(CategoriasBeb, 10);
    validosPostre = leerArvchivoPostres(Categoriaspos, 10);
    listaPedidoCelda=inicLista();
    listaPedidoCelda=leerPedidos(listaPedidoCelda);
    listaClientes = inicArbol();
    listaClientes = leerArvchivoClientes(listaClientes);
    menuPrincipal();

    return 0;
}


void menuPrincipal()
{
    system("cls");
    int opcionMenu = 0;
    int usuarioValido = -1;
    int admin = -1;
    char dni[9];
    char pass[20];
    do
    {
        printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
        printf("\n\t\t\t\t%cMENU PRINCIPAL%c",186,186);
        printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
        printf("\nElija una opcion\n1.Iniciar sesion\n2.Registrarse\n3.Registrar administrador\n0.Salir\n");
        fflush(stdin);
        scanf("%i", &opcionMenu);

        switch(opcionMenu)
        {
        case 1:
        {
            system("cls");
            cartelIniciarSesion();
            printf("\n\tIngrese dni: ");
            fflush(stdin);
            gets(dni);
            printf("\n\tIngrese contrasenia: ");
            fflush(stdin);
            ocultarPass(pass);
            usuarioValido = verificarUsuario(dni, pass);
            admin = checkAdmin(dni);
            if(usuarioValido == 1)
            {
                if(admin == 0)
                {
                    system("cls");
                    menuUsuario();
                }

                else
                {
                    system("cls");
                    menuAdministrador();
                }

            }else
            {
                printf("\n\tUsuario no encontrado, sera redirigido al menu principal...");
                system("pause");
            }
        break;
        }

        case 2:
        {
            system("cls");
            RegistrarUsuario();
            system("cls");
            break;
        }

        case 3:
        {
            system("cls");
            RegistrarAdministrador();
            system("cls");
            break;
        }

        case 0:
        {
            return 0;
            break;
        }

        default:
        {
            system("cls");
            printf("\nEl numero ingresado no corresponde a ninguna de las opciones, ingrese nuevamente...\n\n");
            break;
        }

        }
    }while(opcionMenu!=0);

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
            if(strcmpi(a.dni,dni) == 0)
            {
                if(strcmpi(a.pass,pass)==0)
                {
                    if(a.baja == 0)
                    {
                        flag = 1;
                        usuarioLogeado=a;
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
    int opcionUsuario;
    do
    {
        printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,187);
        printf("\n\t\t\t\t%cMENU USUARIO%c",186,186);
        printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,188);
        printf("\nElija una opcion\n1.Ver catalogo de productos\n2.Hacer un nuevo pedido\n3.Modificar un pedido\n4.Cancelar un pedido\n5.Ver mis pedidos\n6.Dejar una sugerencia\n0.Volver al menu principal\n");
        fflush(stdin);
        scanf("%i", &opcionUsuario);
        switch(opcionUsuario)
        {
        case 1:
            elegirMenu();
            break;
        case 2:
            ///FUNCION HACER UN NUEVO PEDIDO
            system("cls");
            listaPedidoCelda=hacerPedido(Categorias,validos);
            system("cls");

            break;
        case 3:
            ///FUNCION MODIFICAR UN PEDIDO
            break;
        case 4:
            ///CANCELAR UN PEDIDO
            break;
        case 5:
            ///Ver mis pedidos
            system("cls");
            mostrarListaPedidos(listaPedidoCelda);
            break;
        case 6:
            ///DEJAR UNA SUGERENCIA
            break;
        case 0:
            seraRedirigidoAlMenuPrincipal();
            break;
        default:
            system("cls");
            printf("\nEl numero ingresado no corresponde a ninguna de las opciones, ingrese nuevamente...\n\n");
            break;
        }
    }while(opcionUsuario!=0);
    system("cls");
}

void menuAdministrador()
{
    printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
    printf("\n\t\t\t\t%cMENU ADMINISTRADOR%c",186,186);
    printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
    int opcionUsuario;

    do
    {
        printf("\nElija una opcion\n1:Productos\n2:Usuarios\n3:Cancelar un pedido\n4:Dar de baja usuario\n0:Volver al menu principal\n");
        fflush(stdin);
        scanf("%i", &opcionUsuario);
        switch(opcionUsuario)
        {
        case 1:
            ///FUNCION MOSTRAR PRODUCTOS
            adminProductos();
            break;
        case 2:
            ///FUNCION HACER UN NUEVO PEDIDO
            listaPedidoCelda=hacerPedido(Categorias,validos);
            seraRedirigidoAlMenuUsuario();
            menuUsuario();
            break;
        case 3:
            ///FUNCION CANCELAR UN PEDIDO
            seraRedirigidoAlMenuUsuario;
            menuUsuario();
            break;
        case 4:
            inorder(listaClientes);
            listaClientes = bajaLogicaCliente(listaClientes);
            system("pause");
            system("cls");
            inorder(listaClientes);
            system("pause");
            system("cls");
            break;
        case 0:

            seraRedirigidoAlMenuPrincipal();
            break;

        default:
            printf("\nEl numero ingresado no corresponde a ninguna de las opciones, ingrese nuevamente...\n\n");
            Sleep(700);
            system("cls");
            break;
        }
    }while(opcionUsuario!=0);
    system("cls");
}

void adminProductos()
{
    int opcion;
    do
    {
        printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
        printf("\n\t\t\t\t%cABM PRODUCTOS%c",186,186);
        printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
        printf("1.Comida\n2.Bebida\n3.Postre\n0.Salir\n");
        fflush(stdin);
        scanf("%i",&opcion);
        switch(opcion)
        {
        case 1:
            {
                system("cls");
                validos = menuComidas(Categorias, validos);
                break;
            }
        case 2:
            {
                system("cls");
                validosBebida = menuBebida(CategoriasBeb, validosBebida);
                break;
            }
        case 3:
            {
                system("cls");
                validosPostre = menuPostre(Categoriaspos, validosPostre);
                break;
            }
        case 0:
            {
                system("cls");
                break;
            }
        default:
            {
                system("cls");
                printf("Opcion incorrecta, ingrese de nuevo\n");
            }
        }
    }while(opcion!=0);
}

int devolverOpcionMenu()
{
    int opcionMenu;
    printf("\nQue menu desea visualizar?\n1: Menu de comidas\n2: Menu de bebidas\n3: Menu de postres\n\t\t\t");
    fflush(stdin);
    scanf("%d", &opcionMenu);
    return opcionMenu;
}

void elegirMenu()
{
            int opcionMenu = devolverOpcionMenu();
            do
            {
                if(opcionMenu!=1 && opcionMenu!=2 && opcionMenu!=3)
                {
                    system("cls");
                    printf("\nEl numero ingresado no corresponde a una de las opciones\nIngrese nuevamente\n");
                    opcionMenu = devolverOpcionMenu();
                }
            }while(opcionMenu!=1 && opcionMenu!=2 && opcionMenu!=3);

            if(opcionMenu == 1)
            {
            system("cls");
            mostrarArchiComidas();
            }

            else if(opcionMenu == 2)
            {
                system("cls");
            mostrarArchiBebida();
            }

            else if(opcionMenu == 3)
            {
                system("cls");
            mostrarArchivoPos();
            }
}
