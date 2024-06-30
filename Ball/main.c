#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define FILA 8
#define COLUMNA 29


typedef struct
{
    int posA;
    int posB;

}ball;

typedef struct
{
    int posV;
    int posH;

}player;

void mostrarTitulo();
bool menu();
int modo;
void mostrarControles(int mod);
void actualizarJug(int *posJ1, int *posJ2, int mod);
void movimiento(ball *pos, bool *inv_fila, bool *inv_columna, int pos_jug1, int pos_jug2, bool *lost, int mod);
void mostrar(ball pos, int posJug1, int posJug2, int mod);
void limpiar();
int modoJuego();
void mensajeFinal(int mod, ball pos);
void moverCursor();
void ocultarCursor();

int main(void)
{
    int pos_jug1 = FILA / 2;
    int pos_jug2 = FILA / 2;

    ball position;
    bool inv_fila = false;
    bool inv_columna = false;
    bool perder = false;
    bool rest = false;


    do
    {

        ocultarCursor();
        limpiar();
        ocultarCursor();

        mostrarTitulo();

        modo = modoJuego();

        ocultarCursor();
        limpiar();
        ocultarCursor();

        mostrarTitulo();
        mostrarControles(modo);

        ocultarCursor();
        limpiar();
        ocultarCursor();

        srand(time(NULL));

        position.posA = rand() % (FILA - 2) + 1;
        position.posB = COLUMNA / 2;
        perder = false;

        mostrarTitulo();
        mostrar(position, pos_jug1, pos_jug2, modo);
        system("pause");

        ocultarCursor();
        limpiar();
        ocultarCursor();

        mostrarTitulo();

        while(perder == false)
        {

            movimiento(&position, &inv_fila, &inv_columna, pos_jug1, pos_jug2, &perder, modo);
            mostrar(position, pos_jug1, pos_jug2, modo);



            if(kbhit() == 1 && perder == false)
            {
                actualizarJug(&pos_jug1, &pos_jug2, modo);
            }

            if(perder == false)
            {
                ocultarCursor();
                limpiar();
                ocultarCursor();
                mostrarTitulo();
            }




        }

        mensajeFinal(modo, position);

        rest = menu();

    }while(rest == true);

    return 0;
}

int modoJuego()
{
    int opc;

    printf("Elija el modo de juego que desee: \n\n(1) -> Un Jugador\n(2) -> Multijugador\n---------------------------------\n");

    while(scanf("%d", &opc) == 0 || opc < 1 || opc > 2)
    {
        printf("\tError!!\nDebes introducir una de las opciones anteriores\n");
        fflush(stdin);
    }

    return opc;
}

void mostrar(ball pos, int posJug1, int posJug2, int mod)
{
    int i;
    int j;

    for (i = 0; i < FILA; i++) {
         for (j = 0; j < COLUMNA; j++) {
             if (i == 0 && j == 0)
             {
                 printf("\033[38;5;208m%c", 201); // Esquina superior izquierda
             }

             else if (i == 0 && j == COLUMNA - 1)
             {
                 printf("\033[38;5;208m%c\033[0m", 187); // Esquina superior derecha
             }

             else if(i == posJug1 && j == COLUMNA - 1)
             {
                 printf("\033[31m|\033[0m"); //Jugador 1
             }

             else if (i == FILA - 1 && j == 0)
             {
                 printf("\033[38;5;208m%c\033[0m", 200); // Esquina inferior izquierda
             }

             else if (i == FILA - 1 && j == COLUMNA - 1)
             {
                 printf("\033[38;5;208m%c\033[0m", 188); // Esquina inferior derecha
             }

             else if (i == 0 || i == FILA - 1)
             {
                 printf("\033[38;5;208m%c\033[0m", 205); // Bordes horizontales
             }

             else if(j == 0 && mod == 1)
             {
                    printf("\033[38;5;208m%c\033[0m", 186); // Borde Vertical

             }


             else if(i == posJug2 && j == 0)
             {
                 printf("\033[32m|\033[0m"); // Jugador 1



             }

             else if (i == pos.posA && j == pos.posB)
             {
                 printf("\033[33m%c\033[0m", 79); // Posición de la pelota
             }

             else
             {
                 printf(" "); // Espacio vacío
             }
         }
         printf("\n");
     }
}

void movimiento(ball *pos, bool *inv_fila, bool *inv_columna, int pos_jug1, int pos_jug2, bool *lost, int mod)
{
        // ****mov -> 1****
    if((*pos).posA < FILA - 2 && (*pos).posB < COLUMNA - 2 && *inv_fila == false && *inv_columna == false)
    {
        (*pos).posA++;
        (*pos).posB++;
    }

        // camb -> 3
    else if((*pos).posA == FILA - 2 && (*pos).posB == COLUMNA - 2 && *inv_columna == false && *inv_fila == false)
    {
        *inv_fila = true;
        *inv_columna = true;
    }
        // camb -> 4
    else if((*pos).posA == FILA - 2 && *inv_columna == false && *inv_fila == false)
    {
        *inv_fila = true;
    }
        // camb -> 2
    else if((*pos).posB == COLUMNA - 2 && (*pos).posA == pos_jug1 && *inv_columna == false && *inv_fila == false)
    {
        *inv_columna = true;
    }
        // camb -> 3
    else if( (*pos).posB == COLUMNA - 2 && (*pos).posA == pos_jug1 - 1 && *inv_columna == false && *inv_fila == false)
    {

        *inv_fila = true;
        *inv_columna = true;
    }




        // ****mov -> 2****
    else if( (*pos).posA < FILA - 2 && (*pos).posB > 1 && *inv_fila == false && *inv_columna == true)
    {
        (*pos).posA++;
        (*pos).posB--;
    }
        // camb -> 4
    else if( (*pos).posB == 1 && (*pos).posA == FILA - 2 && *inv_fila == false && *inv_columna == true)
    {
        *inv_fila = true;
        *inv_columna = false;
    }
        // camb -> 3
    else if( (*pos).posA == FILA - 2 && *inv_fila == false && *inv_columna == true)
        *inv_fila = true;

        // camb -> 1
    else if( (*pos).posB == 1 && *inv_fila == false && *inv_columna == true && mod == 1)
        *inv_columna = false;

    else if( (*pos).posB == 1 && (*pos).posA == pos_jug2 && *inv_fila == false && *inv_columna == true && mod == 2)
        *inv_columna = false;



        // camb -> 4
    else if( (*pos).posB == 1 && (*pos).posA == pos_jug2 - 1 && *inv_fila == false && *inv_columna == true && mod == 2)
    {
        *inv_fila = true;
        *inv_columna = false;
    }


        // *****mov -> 3*****
    else if( (*pos).posA > 1 && (*pos).posB > 1 && *inv_fila == true && *inv_columna == true)
    {
        (*pos).posA--;
        (*pos).posB--;
    }

        // camb -> 1
    else if( (*pos).posB == 1 && (*pos).posA == 1 && *inv_fila == true && *inv_columna == true)
    {
        *inv_fila = false;
        *inv_columna = false;
    }

        // camb -> 2
    else if( (*pos).posA == 1 && *inv_fila == true && *inv_columna == true)
        *inv_fila = false;

        // camb -> 4
    else if( (*pos).posB == 1 && *inv_fila == true && *inv_columna == true && mod == 1)
        *inv_columna = false;

    else if( (*pos).posB == 1 && (*pos).posA == pos_jug2 && *inv_fila == true && *inv_columna == true && mod == 2)
        *inv_columna = false;

        // camb -> 1
    else if( (*pos).posB == 1 && (*pos).posA == pos_jug2 + 1 && *inv_fila == true && *inv_columna == true && mod == 2)
    {
        *inv_fila = false;
        *inv_columna = false;
    }


        // *****mov -> 4******
    else if( (*pos).posA > 1 && (*pos).posB < COLUMNA - 2 && *inv_fila == true && *inv_columna == false)
    {
        (*pos).posA--;
        (*pos).posB++;
    }
        // camb -> 2
    else if( (*pos).posA == 1 && (*pos).posB == COLUMNA - 2 && *inv_fila == true && *inv_columna == false)
    {
        *inv_columna = true;
        *inv_fila = false;
    }

        // camb -> 1
    else if( (*pos).posA == 1 && *inv_fila == true && *inv_columna == false)
    {
        *inv_fila = false;
    }

        // camb -> 3
    else if((*pos).posB == COLUMNA - 2 && (*pos).posA == pos_jug1 && *inv_fila == true && *inv_columna == false)
    {
        *inv_columna = true;
    }
        // camb -> 2
    else if((*pos).posB == COLUMNA - 2 && (*pos).posA == pos_jug1 + 1 && *inv_fila == true && *inv_columna == false)
    {

        *inv_columna = true;
        *inv_fila = false;
    }
    else
        *lost = true;

}

void actualizarJug(int *posJ1, int *posJ2, int mod)
{
    char opc;

    opc = getch();

    switch(opc)
    {
            //Jugador 2
        case 72: if(*posJ1 - 1 > 0) //Arriba
                     (*posJ1)--;
            break;

        case 80: if(*posJ1 + 1 < FILA - 1) //Abajo
                     (*posJ1)++;
            break;

            //Jugador 1
        case 'w': if(mod != 1)
                      if(*posJ2 - 1 > 0) //Arriba
                         (*posJ2)--;
            break;

        case 's': if(mod != 1)
                      if(*posJ2 + 1 < FILA - 1) //Abajo
                         (*posJ2)++;
            break;
    }

}

void limpiar()
{
    system("cls");
}

bool menu()
{
    char opc[5];
    bool yes;
    bool mal = false;

    printf("\n\n");

    do
    {
        if(mal == false)
            printf("Desea volver a jugar? :\n\033[32m[\033[0mY\033[32m]\033[0m / \033[31m[\033[0mN\033[31m]\033[0m\n");

        mal = false;

        fflush(stdin);
        gets(opc);

        if(strcmpi(opc, "Y") == 0)
            yes = true;

        else if(strcmpi(opc, "N") == 0)
            yes = false;

        else
        {
            printf("\tError!\nDebes digitar una de las opciones anteriores\n");
            mal = true;
        }

    }while(mal == true);

    return yes;


}

void mensajeFinal(int mod, ball pos)
{
    if(mod == 1)
        printf("\033[31mHAS PERDIDO\033[0m !!\n\n");

    else
    {
        if(pos.posB == COLUMNA - 2)
            printf("HA GANADO EL \033[32mJUGADOR 1\033[0m\n\n");
        else
            printf("HA GANADO EL \033[31mJUGADOR 2\033[0m\n\n");
    }
}

void mostrarTitulo()
{
    printf("\t\t'\033[38;5;208mJUEGO DEL PONG\033[0m'\n\t\t --------------\n");
}

void ocultarCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void mostrarControles(int mod)
{
    if(mod == 2)
    {
        printf("CONTROLES:\n---------\n");
        printf("\t\033[32mJugador 1:\033[0m\n ( w ): %c\t ( s ): %c\n\n", 24, 25);
        printf("\t\033[31mJugasor 2:\033[0m\n (FLECHA ARRIBA): %c\t (FLECHA ABAJO): %c\n\n\n\n\n", 24, 25);
    }
    else
        printf("CONTROLES:\n---------\n (FLECHA ARRIBA): %c\t (FLECHA ABAJO): %c\n\n\n\n\n", 24, 25);
    system("pause");
}
