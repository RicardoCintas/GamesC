#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define FILAS 3
#define COLUMNAS 3

struct player
{
    char name[10];        //Nombre del jugador
    int posA;            //Posición vertical
    int posB;           //Posicón horizontal

}jugador[2];

void titulo();
int modoJuego();
void introducirNombres(struct player jug[], int value);
void resetMap(int map[][COLUMNAS]);
bool menu();
void comprobarPos(int mapa[][COLUMNAS], int *posA, int *posB, int value);
int dificulJuego();
void comprobarVacio(int map[][COLUMNAS], int *posA, int *posB);
bool movimientoJ(struct player *Jug, int map[][COLUMNAS], int value, int modo, int dif, int cont);
void mostrarMapa(int map[][COLUMNAS], struct player J, int turn);
void mostrarPlayer(int value, struct player pos[]);
bool comprobarWin(int mapa[][COLUMNAS], struct player J[], int modo, int dificul);

int main(void)
{
    int mapa[FILAS][COLUMNAS];
    int modo;
    int cont;
    bool win;
    bool repeticion;
    bool reset;
    int dificul = 0;


    strcpy(jugador[0].name, "IA");
    strcpy(jugador[1].name, "IA");

    system("cls");
    titulo();

    modo = modoJuego();
    system("cls");

    if(modo == 1)
    {
        titulo();
        dificul = dificulJuego();
        system("cls");
    }

    titulo();
    introducirNombres(jugador, modo);
    system("cls");

    do
    {
        srand(time(NULL));

        system("cls");
        titulo();
        resetMap(mapa);
        win = false;
        repeticion = true;


        while(win == false)
        {

            if(repeticion == true)
            {
                if(dificul != 3)
                {
                    mostrarPlayer(1, jugador);
                    mostrarMapa(mapa, jugador[0], 1);
                }

                else
                {
                    mostrarPlayer(2, jugador);
                    mostrarMapa(mapa, jugador[1], 2);
                }
            }

            repeticion = true;

            cont = 0;
            while(repeticion == true)
            {

                if(dificul == 3)
                    repeticion = movimientoJ(&jugador[1], mapa, 2, modo, dificul, cont);
                else
                    repeticion = movimientoJ(&jugador[0], mapa, 1, modo, dificul, cont);

                system("cls");
                titulo();

                if(repeticion == false)
                {
                    win = comprobarWin(mapa, jugador, modo, dificul);

                    if(dificul != 3)
                    {
                        jugador[0].posA = 0;
                        jugador[0].posB = 0;
                    }

                    else
                    {
                        jugador[1].posA = 0;
                        jugador[1].posB = 0;
                    }
                }

                if(repeticion == false && win == false)
                {
                    if(dificul != 3)
                        mostrarPlayer(2, jugador);
                    else
                        mostrarPlayer(1, jugador);
                }

                else if(repeticion == true && win == false)
                {
                    if(dificul != 3)
                        mostrarPlayer(1, jugador);
                    else
                        mostrarPlayer(2, jugador);
                }

                if(repeticion == true)
                {
                    if(dificul != 3)
                        mostrarMapa(mapa, jugador[0], 1);
                    else
                        mostrarMapa(mapa, jugador[1], 2);
                }
                else
                {
                    if(dificul != 3)
                        mostrarMapa(mapa, jugador[1], 2);
                    else
                        mostrarMapa(mapa, jugador[0], 1);
                }

                cont++;

            }

            if(win == false)
                repeticion = true;

            cont = 0;

            while(repeticion == true)
            {

                if(dificul == 3)
                    repeticion = movimientoJ(&jugador[0], mapa, 1, modo, dificul, cont);
                else
                    repeticion = movimientoJ(&jugador[1], mapa, 2, modo, dificul, cont);

                system("cls");
                titulo();

                if(repeticion == false)
                {
                    win = comprobarWin(mapa, jugador, modo, dificul);

                    if(dificul != 3)
                    {
                        jugador[1].posA = 0;
                        jugador[1].posB = 0;
                    }

                    else
                    {
                        jugador[0].posA = 0;
                        jugador[0].posB = 0;
                    }
                }

                if(repeticion == false && win == false)
                    if(dificul != 3)
                    {
                        mostrarPlayer(1, jugador);
                    }

                    else
                    {
                        mostrarPlayer(2, jugador);
                    }

                else if(repeticion == true && win == false)
                {
                    if(dificul != 3)
                    {
                        mostrarPlayer(2, jugador);
                    }

                    else
                    {
                        mostrarPlayer(1, jugador);
                    }
                }

                if(repeticion == true)
                    if(dificul != 3)
                    {
                        mostrarMapa(mapa, jugador[1], 2);
                    }

                    else
                    {
                        mostrarMapa(mapa, jugador[0], 1);
                    }

                else
                {
                    if(dificul != 3)
                    {
                        mostrarMapa(mapa, jugador[0], 1);
                    }

                    else
                    {
                        mostrarMapa(mapa, jugador[1], 2);
                    }
                }

                cont++;
            }

        }

        reset = menu();

    }while(reset == true);


    return 0;
}

void titulo()
{
    printf("\t\t\t'\033[31mCERITO \033[34mCRUZ\033[0m'\n\t\t\t-------------\n");
}

void introducirNombres(struct player jug[], int value)
{
    int n;

    for(n = 0; n < value; n++)
    {
        printf("Introduzca el nombre del jugador #%d:\n", n + 1);
        fflush(stdin);
        gets(jug[n].name);
    }
}

void mostrarMapa(int map[][COLUMNAS], struct player J, int turn)
{
    int i, j;

    printf("\n");
    printf("      0   1   2\n");
    printf("    |---|---|---|\n");

    for(i = 0; i < FILAS; i++) {
        printf(" %d  |", i);

        for(j = 0; j < COLUMNAS; j++) {
            if (map[i][j] == 1)
                printf(" \033[34mX\033[0m |");

            else if(map[i][j] == 2)
                printf(" \033[31mO\033[0m |");

            else if(J.posA == i && J.posB == j)
            {
                if(turn == 2)
                    printf(" \033[31m+\033[0m |");
                else
                    printf(" \033[34m+\033[0m |");
            }

            else if(map[i][j] == 0)
                printf("   |");

        }

        printf("\n    |---|---|---|\n");
    }
}

bool movimientoJ(struct player *Jug, int map[][COLUMNAS], int value, int modo, int dif, int cont)
{
    bool mal = false;
    bool rept = true;
    int mov = 0;
    int num;


    int posW_A;   //Fila a jugar
    int posW_B;  //Columna a jugar

    do
    {
        num = 5;

        posW_A = -1;
        posW_B = -1;

        if(value == 2)
            comprobarVacio(map, &posW_A, &posW_B);

        if(value == 2 && dif != 1)
            comprobarPos(map, &posW_A, &posW_B, 1);

        if(value == 2 && dif != 1)
            comprobarPos(map, &posW_A, &posW_B, 2);


        if(value == 2 && modo == 1 && posW_A ==  -1 && posW_B == -1)
        {

            num = rand() % num;

            if(num < 1 && dif != 3)
                mov = 13;

            else if(num < 2)
                mov = 72;

            else if(num < 3)
                mov = 77;

            else if(num < 4)
                mov = 80;

            else if(num < 5)
                mov = 75;

            if(num < 1 && dif == 3 && map[0][0] != 0 && map[0][2] != 0 && map[1][1] != 0 && map[2][0] != 0 && map[2][2] != 0)
                mov = 13;

            if(dif == 3 && cont > 3)
            {
                if( ((*Jug).posA == 0 && (*Jug).posB == 0) || ((*Jug).posA == 0 && (*Jug).posB == 2) || ((*Jug).posA == 1 && (*Jug).posB == 1) || ((*Jug).posA == 2 && (*Jug).posB == 0) || ((*Jug).posA == 2 && (*Jug).posB == 2))
                {
                    if(map[(*Jug).posA][(*Jug).posB] == 0)
                        mov = 13;
                }
            }
        }

        else if(value == 2 && modo == 1 && posW_A != -1 && posW_B != -1)
        {
            if( (*Jug).posA == posW_A && (*Jug).posB == posW_B) //Enter
                mov = 13;

            else if( (*Jug).posA > posW_A) //Arriba
                mov = 72;

            else if( (*Jug).posA < posW_A) //Abajo
                mov = 80;

            else if( (*Jug).posB > posW_B) //Izquierda
                mov = 75;

            else if( (*Jug).posB < posW_B) //Derecha
                mov = 77;
        }

        else
        {
            fflush(stdin);
            mov = getch();
        }

        mal = false;

        switch(mov){

            case 72: if( (*Jug).posA > 0) //Arriba
                         (*Jug).posA--;
                break;

            case 77: if( (*Jug).posB < COLUMNAS - 1) //Derecha
                         (*Jug).posB++;
                break;

            case 80: if( (*Jug).posA < FILAS - 1) //Abajo
                         (*Jug).posA++;
                break;

            case 75: if( (*Jug).posB > 0) //Izquierda
                         (*Jug).posB--;
                break;

            case 13: if(map[(*Jug).posA][(*Jug).posB] == 0)
                     {
                        if(value == 1)
                            map[(*Jug).posA][(*Jug).posB] = 1;
                        else
                            map[(*Jug).posA][(*Jug).posB] = 2;

                        rept = false;
                     }

                     else
                        mal = true;

                break;

            default: mal = true;
        }

    }while(mal == true);

    if(value == 1)
        jugador[0] = *Jug;
    else
        jugador[1] = *Jug;

    return rept;


}

void mostrarPlayer(int value, struct player pos[])
{
    printf("Turno de %s\n", value == 1 ? pos[0].name : pos[1].name);
    printf("Coordenadas: (%d ; %d)\n\n\n", value == 1 ? pos[0].posA : pos[1].posA, value == 1 ? pos[0].posB : pos[1].posB);
}

bool comprobarWin(int mapa[][COLUMNAS], struct player J[], int modo, int dificul)
{
    bool ganar = false;
    bool tabla = true;
    int i, j;

    for(i = 0; i < FILAS && ganar == false; i++) //Verificar si hubo ganador
    {
        if(mapa[i][i] != 0)
        {
            if(i == 0)
            {

                if(mapa[i][i] == mapa[i + 1][i] && mapa[i + 1][i] == mapa[i + 2][i]) //Analizar Fila 0
                    ganar = true;

                if(mapa[i][i] == mapa[i][i + 1] && mapa[i][i + 1] == mapa[i][i + 2]) //Analizar Columna 0
                    ganar = true;

                if(mapa[i][i] == mapa[i + 1][i + 1] && mapa[i + 1][i + 1] == mapa[i + 2][i + 2]) //Analizar Diagonal (1)
                    ganar = true;
            }

            else if(i == 1)
            {
                if(mapa[i][i] == mapa[i][i - 1] && mapa[i][i - 1] == mapa[i][i + 1])
                    ganar = true;

                if(mapa[i][i] == mapa[i + 1][i] && mapa[i + 1][i] == mapa[i - 1][i])
                    ganar = true;

                if(mapa[i][i] == mapa[i - 1][i + 1] && mapa[i - 1][i + 1] == mapa[i + 1][i - 1])
                    ganar = true;
            }

            else if(i == 2)
            {
                if(mapa[i][i] == mapa[i - 1][i] && mapa[i - 1][i] == mapa[i - 2][i])
                    ganar = true;

                if(mapa[i][i] == mapa[i][i - 1] && mapa[i][i - 1] == mapa[i][i - 2])
                    ganar = true;
            }
        }
    }

    if(ganar == false)
    {
        for(i = 0; i < FILAS; i++)
            for(j = 0; j < COLUMNAS; j++)
                if(mapa[i][j] == 0)
                    tabla = false;
    }

    if(ganar == true)
    {
        if(modo == 2)
            printf("\033[32mFelicidades!!\033[0m ha ganado %s\n----------------------------\n", mapa[i - 1][i - 1] == 1 ? J[0].name : J[1].name);
        else if(dificul == 1 && mapa[i - 1][i - 1] == 1)
            printf("\033[32mFelicidades!!\033[0m le has ganado a IA-\033[32mF\240cil\033[0m\n------------------------------\n");
        else if(dificul == 2 && mapa[i - 1][i - 1] == 1)
            printf("\033[32mFelicidades!!\033[0m le has ganado a IA-\033[33mMedia\033[0m\n------------------------------\n");
        else if(dificul == 3 && mapa[i - 1][i - 1] == 1)
            printf("\033[32mFelicidades!!\033[0m le has ganado a IA-\033[31mImposible\033[0m\n------------------------------\n");
        else
            printf("\033[31mGAME OVER!! \033[0m\n");
    }

    else if(tabla == true)
    {
        printf("-TABLA-\n--------\n(Ning\243n jugador result\242 ganador)\n\n");
        ganar = true;
    }


    return ganar;

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
            printf("Desea volver a jugar? :\n\033[32m[\033[0mYES\033[32m]\033[0m / \033[31m[\033[0mNO\033[31m]\033[0m\n");

        mal = false;

        fflush(stdin);
        gets(opc);

        if(strcmpi(opc, "YES") == 0)
            yes = true;

        else if(strcmpi(opc, "NO") == 0)
            yes = false;

        else
        {
            printf("\tError!\nDebes digitar una de las opciones anteriores\n");
            mal = true;
        }

    }while(mal == true);

    return yes;


}

void resetMap(int map[][COLUMNAS])
{
    int i, j;

    for(i = 0; i < FILAS; i++)
        for(j = 0; j < COLUMNAS; j++)
            map[i][j] = 0;
}

int modoJuego()
{
    int opc;

    printf("Elige un Modo de Juego:\n-----------------------\n\n(1) -> Un Jugador   (Player Vs IA)\n\n(2) -> Multijugador   (Player Vs Player)\n");

    while(scanf("%d", &opc) == 0 || opc < 1 || opc > 2)
    {
        printf("\tError!\nDebe digitar una de las opciones anteriores\n");
        fflush(stdin);
    }

    return opc;
}

int dificulJuego()
{
    int dif;

    printf("Digite la dificultad de la IA:\n\n(1) -> \033[32mF\240cil\033[0m\n\n(2) -> \033[33mMedia\033[0m\n\n(3) -> \033[31mImposible\033[0m\n\n");
    while(scanf("%d", &dif) == 0 || dif < 1 || dif > 3)
    {
        printf("\tError!\nDebe introducir una de las opciones anteriores\n");
        fflush(stdin);
    }

    return dif;
}

void comprobarPos(int mapa[][COLUMNAS], int *posA, int *posB, int value)
{
    int i, j;
    int a, b;
    int cant = 0;
    bool salir = false;

            //Comparar Ganar a Filas
    for(i = 0; i < FILAS && salir == false; i++)
    {
        for(j = 0; j < COLUMNAS && salir == false; j++)
        {
            if(mapa[i][j] == value)
                cant++;

            if(cant == 2)
            {
                a = j;

                if(a == 2)
                {
                    for(; a >= 0 && salir == false; a--)
                        if(mapa[i][a] == 0)
                        {
                            *posA = i;
                            *posB = a;
                            salir = true;
                        }
                }

                else
                {
                    for(; a < COLUMNAS && salir == false; a++)
                        if(mapa[i][a] == 0)
                        {
                            *posA = i;
                            *posB = a;
                            salir = true;
                        }
                }

            }
        }
        cant = 0;
    }




               //Comprobar Ganar Columnas
    for(j = 0; j < COLUMNAS && salir == false; j++)
    {
        for(i = 0; i < FILAS && salir == false; i++)
        {
            if(mapa[i][j] == value)
                cant++;

            if(cant == 2)
            {
                a = i;

                if(a == 2)
                {
                    for(; a >= 0 && salir == false; a--)
                        if(mapa[a][j] == 0)
                        {
                            *posA = a;
                            *posB = j;
                            salir = true;
                        }
                }

                else
                {
                    for(; a < FILAS && salir == false; a++)
                        if(mapa[a][j] == 0)
                        {
                            *posA = a;
                            *posB = j;
                            salir = true;
                        }
                }

            }
        }
        cant = 0;
    }


               //Comprobar Ganar Diagonal Principal
    for(i = 0; i < FILAS && salir == false; i++)
    {

        if(mapa[i][i] == value)
            cant++;

        if(cant == 2)
        {
            if(i == 2)
            {
                for(; i >= 0 && salir == false; i--)
                    if(mapa[i][i] == 0)
                    {
                        *posA = i;
                        *posB = i;
                        salir = true;
                    }
            }

            else
            {
                for(; i < FILAS && salir == false; i++)
                    if(mapa[i][i] == 0)
                    {
                        *posA = i;
                        *posB = i;
                        salir = true;
                    }
            }
        }
    }

    cant = 0;
    j = 2;
               //Comprobar Ganar Diagonal Secundaria
    for(i = 0; i < FILAS && salir == false; i++)
    {
        if(mapa[i][j] == value)
            cant++;

        if(cant == 2)
        {
            a = i;
            b = j;

            if(b == 0 && a == 2)
            {
                for(; a >= 0; a--)
                {
                    if(mapa[a][b] == 0)
                    {
                        *posA = a;
                        *posB = b;
                        salir = true;
                    }

                    b++;
                }
            }

            else
            {
                for(; a < FILAS; a++)
                {
                    if(mapa[a][b] == 0)
                    {
                        *posA = a;
                        *posB = b;
                        salir = true;
                    }

                    b--;
                }
            }
        }

        j--;
    }
}

void comprobarVacio(int map[][COLUMNAS], int *posA, int *posB)
{
    int i;
    int j, cont = 0;
    bool salir = false;

    for(i = 0; i < FILAS; i++)
        for(j = 0; j < COLUMNAS; j++)
        {
            if(map[i][j] == 0)
                cont++;

        }

    if(cont <= 3)
    {
        for(i = 0; i < FILAS && salir == false; i++)
            for(j = 0; j < COLUMNAS && salir == false; j++)
            {
                if(map[i][j] == 0)
                {
                    *posA = i;
                    *posB = j;
                    salir = true;
                }
            }
    }

}
