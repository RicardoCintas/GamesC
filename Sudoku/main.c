#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

#define FILA 9
#define COLUMNA 9

                /*Declaración de estructuras*/

typedef struct{
    int f;  //Posición del jugador ---Filas---
    int c;  //Posición del jugador ---Columnas---
}posJug;

typedef struct{
    int x[81];  //Jugada del jugador ---Filas---
    int y[81];  //Jugada del jugador ---Columnas---
    int tamLog;
}jugadas;

typedef struct{
    int num;
    bool locked;
}numero;

numero matrizSudoku[FILA][COLUMNA] = {}; /*Tablero de Juego*/

                /*Declaración de Funciones*/
/*-----------------------------------------------------*/

void hideCursor();
void inicializarSudoku(numero (*matriz)[][COLUMNA]);
void generarAleatorios(posJug *Jug, jugadas *jugad);
void mostrado(posJug pos);
bool comprobarWin();
void interactuar(posJug *Jug, jugadas *jugad, int dificult);
bool permitirJugada(int posF, int posC, int num);
bool analizarPos(int posY, int posX, jugadas Jugad);
void eliminarJugada(jugadas *Jugad, int posY, int posX);
int menu();
bool menuRestar();
void mostrarControles();

                /*Función Principal*/
/*-----------------------------------------------------*/
int main(void)
{

    hideCursor();
    bool win = false;
    int dificult;
    posJug pos;

    jugadas jugad;

    do{
        jugad.tamLog = 0;
        pos.c = 0, pos.f = 0;

        dificult = menu();


        if(dificult != 0){
            inicializarSudoku(&matrizSudoku);
            pos.c = 0, pos.f = 0;
        }

        mostrarControles();
        system("pause");
        system("cls");

        while(!win && dificult != 0){
            system("cls");
            mostrado(pos);
            interactuar(&pos, &jugad, dificult);
            win = comprobarWin();

        }

        if(dificult == 0)
            printf("\n\n\n\033[38;5;208m---Vuelva a jugar pronto---\033[0m\n");
        else
            printf("\n\n\n\033[38;5;208m---FELICIDADES HAS COMPLETADO EL SUDOKU---\033[0m\n\n");


    }while(menuRestar());

    return 0;
}

                /*Implementación de Funciones*/
/*-----------------------------------------------------*/

void mostrado(posJug pos) {
    int fila, columna;
    for (fila = 0; fila < 9; fila++) {
        for (columna = 0; columna < 9; columna++) {
            if ( (pos.f == fila && pos.c == columna) && matrizSudoku[fila][columna].num != 0)
                if(matrizSudoku[fila][columna].locked == false)
                    printf("[%d]", matrizSudoku[fila][columna].num);
                else
                    printf("[\033[38;5;208m%d\033[0m]", matrizSudoku[fila][columna].num);
            else if(pos.f == fila && pos.c == columna)
                printf("[ ]");

            else if(matrizSudoku[fila][columna].num != 0)
                if(matrizSudoku[fila][columna].locked == false)
                   printf(" %d ", matrizSudoku[fila][columna].num);

                else
                    printf(" \033[38;5;208m%d\033[0m ", matrizSudoku[fila][columna].num);

            else
                printf("   ");

            if ((columna + 1) % 3 == 0 && columna != 8) {
                printf("|");  // Separador de submatrices
            }
        }
        printf("\n");

        if ((fila + 1) % 3 == 0 && fila != 8) {
            printf("-----------------------------\n");  // Línea horizontal entre submatrices
        }
    }
}


void interactuar(posJug *Jug, jugadas *jugad, int dificult){

    int mov;

    mov = getch();

    switch(mov){

    case 72: if( (*Jug).f > 0) //Arriba
        {
            (*Jug).f--;
        }

        break;

    case 77: if( (*Jug).c < COLUMNA - 1) //Derecha
        {
            (*Jug).c++;
        }
        break;

    case 80: if( (*Jug).f < FILA - 1) //Abajo
        {
            (*Jug).f++;

        }
        break;

    case 75: if( (*Jug).c > 0) //Izquierda
        {
            (*Jug).c--;

        }
        break;

                /*Cambiar Número en el tablero*/
    case '1':
        if(permitirJugada( (*Jug).f, (*Jug).c, 1) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
            matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 1;
            if(dificult == 2)
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked =  true;
            //guardamos la posición de la jugada
            (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
            (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
            (*jugad).tamLog++;
        }
        break;
    case '2':
        if(permitirJugada( (*Jug).f, (*Jug).c, 2) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
            matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 2;
            if(dificult == 2)
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked =  true;
            //guardamos la posición de la jugada
            (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
            (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
            (*jugad).tamLog++;
        }
        break;
    case '3':
        if(permitirJugada( (*Jug).f, (*Jug).c, 3) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
            matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 3;
            if(dificult == 2)
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked =  true;
            //guardamos la posición de la jugada
            (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
            (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
            (*jugad).tamLog++;
        }
        break;
    case '4':
        if(permitirJugada( (*Jug).f, (*Jug).c, 4) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
            matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 4;
            if(dificult == 2)
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked =  true;
            //guardamos la posición de la jugada
            (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
            (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
            (*jugad).tamLog++;
        }
        break;
    case '5':
        if(permitirJugada( (*Jug).f, (*Jug).c, 5) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
            matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 5;
            if(dificult == 2)
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked =  true;
            //guardamos la posición de la jugada
            (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
            (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
            (*jugad).tamLog++;
        }
        break;
    case '6':
        if(permitirJugada( (*Jug).f, (*Jug).c, 6) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
            matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 6;
            if(dificult == 2)
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked =  true;
            //guardamos la posición de la jugada
            (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
            (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
            (*jugad).tamLog++;
        }
        break;
    case '7':
        if(permitirJugada( (*Jug).f, (*Jug).c, 7) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
            matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 7;
            if(dificult == 2)
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked =  true;
            //guardamos la posición de la jugada
            (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
            (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
            (*jugad).tamLog++;
        }
        break;
    case '8':
        if(permitirJugada( (*Jug).f, (*Jug).c, 8) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
            matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 8;
            if(dificult == 2)
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked =  true;
            //guardamos la posición de la jugada
            (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
            (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
            (*jugad).tamLog++;
        }
        break;
    case '9':
        if(permitirJugada( (*Jug).f, (*Jug).c, 9) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
            matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 9;
            if(dificult == 2)
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked =  true;
            //guardamos la posición de la jugada
            (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
            (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
            (*jugad).tamLog++;
        }
        break;
        //Borrar Jugada
    case 8:
        if(matrizSudoku[ (*Jug).f ][ (*Jug).c ].num != 0 && matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked == false){
            eliminarJugada( &(*jugad), (*Jug).f, (*Jug).c );
            matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 0;
        }
        break;


    case 32:

        generarAleatorios(Jug, jugad);
        break;
    }
}


bool permitirJugada(int posF, int posC, int num){
    bool can = true;
    int i, j;

        //Analizar la Fila
    for(i = 0; i < COLUMNA; i++)
        if( (matrizSudoku[posF][i].num == num) && (posC != i) )
            can = false;

        //Analizar la columna
    for(i = 0; i < FILA; i++)
        if( (matrizSudoku[i][posC].num == num) && (posF != i) )
            can = false;

        //Buscar SubMatriz
    if(posF < 3){

        if(posC < 3){
            //Analizar SubMatriz--1--
            for(i = 0; i < 3; i++)
                for(j = 0; j < 3; j++)
                    if( matrizSudoku[i][j].num == num && ( posF != i && posC != j))
                        can = false;
        }

        else if(posC < 6){
            //Analizar SubMatriz--2--
            for(i = 0; i < 3; i++)
                for(j = 3; j < 6; j++)
                    if( matrizSudoku[i][j].num == num && ( posF != i && posC != j))
                        can = false;
        }

        else{
            //Analizar SubMatriz--3--
            for(i = 0; i < 3; i++)
                for(j = 6; j < 9; j++)
                    if( matrizSudoku[i][j].num == num && ( posF != i && posC != j))
                        can = false;
        }
    }

    else if(posF < 6){
        if(posC < 3){
            //Analizar SubMatriz--4--
            for(i = 3; i < 6; i++)
                for(j = 0; j < 3; j++)
                    if( matrizSudoku[i][j].num == num && ( posF != i && posC != j))
                        can = false;
        }

        else if(posC < 6){
            //Analizar SubMatriz--5--
            for(i = 3; i < 6; i++)
                for(j = 3; j < 6; j++)
                    if( matrizSudoku[i][j].num == num && ( posF != i && posC != j))
                        can = false;
        }

        else{
            //Analizar SubMatriz--6--
            for(i = 3; i < 6; i++)
                for(j = 6; j < 9; j++)
                    if( matrizSudoku[i][j].num == num && ( posF != i && posC != j))
                        can = false;
        }
    }

    else{
        if(posC < 3){
            //Analizar SubMatriz--7--
            for(i = 6; i < 9; i++)
                for(j = 0; j < 3; j++)
                    if( matrizSudoku[i][j].num == num && ( posF != i && posC != j))
                        can = false;
        }

        else if(posC < 6){
            //Analizar SubMatriz--8--
            for(i = 6; i < 9; i++)
                for(j = 3; j < 6; j++)
                    if( matrizSudoku[i][j].num == num && ( posF != i && posC != j))
                        can = false;
        }

        else{
            //Analizar SubMatriz--9--
            for(i = 6; i < 9; i++)
                for(j = 6; j < 9; j++)
                    if( matrizSudoku[i][j].num == num && ( posF != i && posC != j))
                        can = false;
        }
    }



    return can;

}

bool comprobarWin(){
    bool win = true;
    int i, j;

    for(i = 0; i < FILA && win == true; i++)
        for(j = 0; j < COLUMNA && win == true; j++)
           if(matrizSudoku[i][j].num == 0)
               win = false;

    return win;
}

void inicializarSudoku(numero (*matriz)[][COLUMNA]){
    int opc = rand() % 12;
    int i, j;

    switch (opc) {
    case 0:
    {
        int matrizNew[FILA][COLUMNA] = {{0,8,0, 5,7,6, 2,0,0},
                                        {0,0,0, 4,0,2, 0,0,0},
                                        {0,0,0, 0,3,9, 5,4,8},

                                        {6,3,0, 9,0,0, 8,5,2},
                                        {0,9,0, 2,0,0, 3,7,0},
                                        {8,0,0, 0,5,0, 6,9,4},

                                        {2,5,7, 6,0,3, 4,8,9},
                                        {3,0,8, 7,0,0, 0,2,5},
                                        {0,4,0, 0,0,0, 0,0,6}
                                       };
        for(i = 0; i < FILA; i++)
            for(j = 0; j < COLUMNA; j++){
                (*matriz)[i][j].num = matrizNew[i][j];
                if(matrizNew[i][j] != 0)
                    (*matriz)[i][j].locked = true;
                else
                    (*matriz)[i][j].locked = false;
            }

    }

        break;
    case 1:
    {
        int matrizNew[FILA][COLUMNA] = {{0,5,8, 0,6,4, 0,0,0},
                                        {6,0,9, 0,0,0, 0,4,0},
                                        {0,0,2, 3,7,0, 0,6,8},

                                        {0,8,7, 0,0,0, 0,5,0},
                                        {0,0,3, 8,0,0, 7,0,0},
                                        {5,0,0, 4,0,7, 0,0,2},

                                        {8,7,0, 0,4,6, 0,0,0},
                                        {0,0,0, 2,5,3, 8,0,0},
                                        {0,2,0, 0,8,0, 0,0,4}
                                       };
        for(i = 0; i < FILA; i++)
            for(j = 0; j < COLUMNA; j++){
                (*matriz)[i][j].num = matrizNew[i][j];
                if(matrizNew[i][j] != 0)
                    (*matriz)[i][j].locked = true;
                else
                    (*matriz)[i][j].locked = false;
            }




    }

        break;

    case 2:
    {
        int matrizNew[FILA][COLUMNA] = {{0,0,0, 4,0,0, 7,2,6},
                                        {0,0,2, 8,0,6, 0,3,9},
                                        {3,0,0, 7,0,0, 0,8,4},

                                        {0,0,4, 6,0,7, 8,1,3},
                                        {0,0,3, 5,4,0, 0,0,2},
                                        {9,0,0, 3,0,2, 4,6,0},

                                        {4,0,1, 2,6,0, 0,0,0},
                                        {2,7,0, 9,3,8, 6,4,0},
                                        {0,0,0, 1,0,4, 2,5,8}
                                       };
        for(i = 0; i < FILA; i++)
            for(j = 0; j < COLUMNA; j++){
                (*matriz)[i][j].num = matrizNew[i][j];
                if(matrizNew[i][j] != 0)
                    (*matriz)[i][j].locked = true;
                else
                    (*matriz)[i][j].locked = false;
            }


    }

        break;

    case 3:
    {
        int matrizNew[FILA][COLUMNA] = {{0,0,0, 0,0,0, 0,8,4},
                                        {5,0,0, 0,4,2, 6,0,0},
                                        {0,0,4, 0,0,0, 0,2,0},

                                        {0,4,0, 0,6,3, 7,0,0},
                                        {0,0,0, 0,0,1, 0,0,3},
                                        {6,3,0, 9,5,7, 2,0,0},

                                        {0,5,0, 0,0,9, 0,0,6},
                                        {3,2,0, 8,0,0, 1,0,9},
                                        {0,0,9, 5,0,0, 8,0,0}
                                       };
        for(i = 0; i < FILA; i++)
            for(j = 0; j < COLUMNA; j++){
                (*matriz)[i][j].num = matrizNew[i][j];
                if(matrizNew[i][j] != 0)
                    (*matriz)[i][j].locked = true;
                else
                    (*matriz)[i][j].locked = false;
            }
    }
        break;
    case 4:
    {
        int matrizNew[FILA][COLUMNA] = {{0,0,7, 0,4,0, 0,0,0},
                                        {6,3,0, 0,0,8, 4,0,0},
                                        {2,5,0, 3,0,0, 0,0,0},

                                        {9,0,0, 0,0,0, 2,0,0},
                                        {0,4,3, 9,2,0, 5,0,0},
                                        {5,7,2, 0,6,0, 0,0,0},

                                        {7,0,5, 0,0,0, 3,0,4},
                                        {0,0,8, 5,0,0, 0,2,0},
                                        {0,2,0, 8,3,0, 0,7,0}
                                       };
        for(i = 0; i < FILA; i++)
            for(j = 0; j < COLUMNA; j++){
                (*matriz)[i][j].num = matrizNew[i][j];
                if(matrizNew[i][j] != 0)
                    (*matriz)[i][j].locked = true;
                else
                    (*matriz)[i][j].locked = false;
            }
    }
        break;

    case 5:
    {
        int matrizNew[FILA][COLUMNA] = {{0,4,3, 0,6,0, 5,0,2},
                                        {0,2,0, 3,4,0, 0,6,7},
                                        {6,0,0, 2,0,0, 0,0,3},

                                        {0,3,0, 6,0,0, 0,7,0},
                                        {0,0,6, 0,7,0, 4,0,0},
                                        {5,7,4, 0,3,0, 0,0,8},

                                        {7,0,0, 0,0,0, 3,0,0},
                                        {0,5,8, 0,0,0, 0,0,6},
                                        {0,9,0, 0,0,0, 2,0,0}
                                       };
        for(i = 0; i < FILA; i++)
            for(j = 0; j < COLUMNA; j++){
                (*matriz)[i][j].num = matrizNew[i][j];
                if(matrizNew[i][j] != 0)
                    (*matriz)[i][j].locked = true;
                else
                    (*matriz)[i][j].locked = false;
            }
    }
        break;

    case 6:
    {
        int matrizNew[FILA][COLUMNA] = {{0,5,0, 0,0,1, 0,0,0},
                                        {0,0,0, 0,0,6, 0,7,0},
                                        {3,0,9, 0,4,0, 0,6,5},

                                        {0,0,8, 9,1,4, 0,0,0},
                                        {0,0,0, 0,6,7, 8,2,9},
                                        {0,9,7, 0,0,0, 0,0,4},

                                        {0,0,4, 1,0,0, 0,0,0},
                                        {0,7,0, 0,0,0, 6,9,1},
                                        {0,3,5, 0,0,0, 2,0,0}
                                       };
        for(i = 0; i < FILA; i++)
            for(j = 0; j < COLUMNA; j++){
                (*matriz)[i][j].num = matrizNew[i][j];
                if(matrizNew[i][j] != 0)
                    (*matriz)[i][j].locked = true;
                else
                    (*matriz)[i][j].locked = false;
            }
    }
        break;
    case 7:
    {
        int matrizNew[FILA][COLUMNA] = {{0,0,0, 8,0,2, 0,0,3},
                                        {4,0,0, 0,0,0, 0,0,0},
                                        {0,5,9, 0,0,7, 6,0,0},

                                        {0,2,0, 0,0,0, 0,6,9},
                                        {9,4,0, 0,0,0, 3,0,0},
                                        {0,8,0, 7,0,9, 2,0,5},

                                        {0,0,4, 0,0,1, 0,9,8},
                                        {5,0,0, 0,0,4, 0,0,0},
                                        {0,0,8, 2,0,5, 4,7,0}
                                       };
        for(i = 0; i < FILA; i++)
            for(j = 0; j < COLUMNA; j++){
                (*matriz)[i][j].num = matrizNew[i][j];
                if(matrizNew[i][j] != 0)
                    (*matriz)[i][j].locked = true;
                else
                    (*matriz)[i][j].locked = false;
            }
    }
        break;

    case 8:
    {
        int matrizNew[FILA][COLUMNA] = {{0,6,3, 0,0,0, 0,0,0},
                                        {0,9,0, 0,0,0, 0,0,0},
                                        {4,0,0, 0,0,0, 0,0,0},

                                        {0,0,7, 2,0,3, 0,5,8},
                                        {0,5,0, 0,4,0, 0,0,0},
                                        {0,0,8, 0,0,0, 2,0,4},

                                        {6,0,0, 0,0,0, 7,0,0},
                                        {0,0,5, 0,3,6, 0,0,0},
                                        {0,3,0, 8,7,0, 0,2,6}
                                       };
        for(i = 0; i < FILA; i++)
            for(j = 0; j < COLUMNA; j++){
                (*matriz)[i][j].num = matrizNew[i][j];
                if(matrizNew[i][j] != 0)
                    (*matriz)[i][j].locked = true;
                else
                    (*matriz)[i][j].locked = false;
            }
    }
        break;
    case 9:
    {
        int matrizNew[FILA][COLUMNA] = {{0,0,0, 0,7,8, 0,4,0},
                                        {0,7,0, 0,0,5, 0,0,3},
                                        {1,4,0, 6,0,0, 0,0,0},

                                        {0,0,5, 0,8,0, 2,0,0},
                                        {0,3,0, 0,0,4, 0,7,0},
                                        {0,6,0, 0,0,0, 0,0,5},

                                        {0,0,0, 0,0,0, 8,5,0},
                                        {0,0,0, 0,6,2, 0,0,0},
                                        {9,0,6, 5,0,3, 0,0,0}
                                       };
        for(i = 0; i < FILA; i++)
            for(j = 0; j < COLUMNA; j++){
                (*matriz)[i][j].num = matrizNew[i][j];
                if(matrizNew[i][j] != 0)
                    (*matriz)[i][j].locked = true;
                else
                    (*matriz)[i][j].locked = false;
            }
    }
        break;

    case 10:
    {
        int matrizNew[FILA][COLUMNA] = {{0,0,4, 0,0,0, 7,0,0},
                                        {0,0,0, 7,3,0, 0,9,0},
                                        {0,0,0, 0,8,0, 0,5,0},

                                        {9,5,0, 2,0,0, 6,4,0},
                                        {0,3,0, 9,0,0, 2,0,0},
                                        {4,0,0, 6,0,5, 0,0,0},

                                        {6,0,0, 0,0,0, 0,0,0},
                                        {0,0,8, 0,0,0, 0,7,0},
                                        {3,0,0, 0,2,1, 0,0,0}
                                       };
        for(i = 0; i < FILA; i++)
            for(j = 0; j < COLUMNA; j++){
                (*matriz)[i][j].num = matrizNew[i][j];
                if(matrizNew[i][j] != 0)
                    (*matriz)[i][j].locked = true;
                else
                    (*matriz)[i][j].locked = false;
            }
    }
        break;


    case 11:
    {
        int matrizNew[FILA][COLUMNA] = {{0,0,3, 7,9,0, 6,0,0},
                                        {2,7,0, 0,0,0, 0,0,0},
                                        {0,0,6, 0,0,8, 3,0,0},

                                        {0,8,5, 0,0,3, 0,0,4},
                                        {0,0,0, 0,0,0, 0,7,0},
                                        {0,0,0, 6,1,0, 0,9,0},

                                        {3,0,0, 0,2,0, 0,0,0},
                                        {0,6,0, 0,0,9, 0,0,0},
                                        {5,1,9, 0,0,0, 0,2,0}
                                       };
        for(i = 0; i < FILA; i++)
            for(j = 0; j < COLUMNA; j++){
                (*matriz)[i][j].num = matrizNew[i][j];
                if(matrizNew[i][j] != 0)
                    (*matriz)[i][j].locked = true;
                else
                    (*matriz)[i][j].locked = false;

            }
    }
        break;
    }



}

void generarAleatorios(posJug *Jug, jugadas *jugad){

    int dif = 81, mov;
    srand(time(NULL));
    bool correct;

    while(dif > 0)
    {


        correct = false;

        while(!correct){

            (*Jug).f = rand() % FILA;
            (*Jug).c = rand() % COLUMNA;

            if(matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0)
                correct = analizarPos((*Jug).f, (*Jug).c, *jugad);
        }

        mov = (rand() % 9) + 1;

        switch(mov){
        case 1:
            if(permitirJugada( (*Jug).f, (*Jug).c, 1) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 1;
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked = false;
                //guardamos la posición de la jugada
                (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
                (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
                (*jugad).tamLog++;
                dif--;
            }
            break;
        case 2:
            if(permitirJugada( (*Jug).f, (*Jug).c, 2) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 2;
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked = false;
                //guardamos la posición de la jugada
                (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
                (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
                (*jugad).tamLog++;
                dif--;
            }
            break;
        case 3:
            if(permitirJugada( (*Jug).f, (*Jug).c, 3) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 3;
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked = false;
                //guardamos la posición de la jugada
                (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
                (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
                (*jugad).tamLog++;
                dif--;
            }
            break;
        case 4:
            if(permitirJugada( (*Jug).f, (*Jug).c, 4) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 4;
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked = false;
                //guardamos la posición de la jugada
                (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
                (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
                (*jugad).tamLog++;
                dif--;
            }
            break;
        case 5:
            if(permitirJugada( (*Jug).f, (*Jug).c, 5) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 5;
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked = false;
                //guardamos la posición de la jugada
                (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
                (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
                (*jugad).tamLog++;
                dif--;
            }
            break;
        case 6:
            if(permitirJugada( (*Jug).f, (*Jug).c, 6) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 6;
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked = false;
                //guardamos la posición de la jugada
                (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
                (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
                (*jugad).tamLog++;
                dif--;
            }
            break;
        case 7:
            if(permitirJugada( (*Jug).f, (*Jug).c, 7) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 7;
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked = false;
                //guardamos la posición de la jugada
                (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
                (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
                (*jugad).tamLog++;
                dif--;
            }
            break;
        case 8:
            if(permitirJugada( (*Jug).f, (*Jug).c, 8) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 8;
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked = false;
                //guardamos la posición de la jugada
                (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
                (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
                (*jugad).tamLog++;
                dif--;
            }
            break;
        case 9:
            if(permitirJugada( (*Jug).f, (*Jug).c, 9) == true && matrizSudoku[ (*Jug).f ][ (*Jug).c ].num == 0){
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].num = 9;
                matrizSudoku[ (*Jug).f ][ (*Jug).c ].locked = false;
                //guardamos la posición de la jugada
                (*jugad).y[ (*jugad).tamLog ] = (*Jug).f;
                (*jugad).x[ (*jugad).tamLog ] = (*Jug).c;
                (*jugad).tamLog++;
                dif--;
            }
            break;
        }

        system("cls");
        mostrado(*Jug);
        printf("\n--Presione una tecla para detener el AutoCompletado--\n");
        if(kbhit() != 0)
            dif = 0;



    }


}

bool analizarPos(int posY, int posX, jugadas Jugad){
    bool correct = true;
    int i;

    for(i = 0; i < Jugad.tamLog && correct == true; i++)
        if(Jugad.x[i] == posX && Jugad.y[i] == posY)
            correct = false;

    return correct;


}

void eliminarJugada(jugadas *Jugad, int posY, int posX){
    int i;
    bool found = false;


    for(i = 0; i < (*Jugad).tamLog-1; i++)
        if( ((*Jugad).y[i] == posY && (*Jugad).x[i] == posX) || found == true){
            found = true;
            (*Jugad).y[i] = (*Jugad).y[i+1];
            (*Jugad).x[i] = (*Jugad).x[i+1];
        }

    if(found == true || ( (*Jugad).y[(*Jugad).tamLog-1] == posY && (*Jugad).x[(*Jugad).tamLog-1] == posX) )
        (*Jugad).tamLog--;


}

int menu(){
    int opcion;

    do {
        int i;
        system("cls");


        printf("\t\t\t\033[38;5;208mSUDOKU\033[0m");
        printf("\n\n");
        printf("\033[38;5;208m%c", 201); // Esquina superior izquierda
        for(i = 0; i < 52; i++)
            printf("\033[38;5;208m%c\033[0m", 205); //Bordes horizontales
        printf("\033[38;5;208m%c\033[0m\n", 187); // Esquina superior derecha

        printf("\033[38;5;208m%c\033[0m\t\t    Men\243 de Opciones\t\t     \033[38;5;208m%c\033[0m\n", 186, 186);
        printf("\033[38;5;208m%c----------------------------------------------------%c\033[0m\n", 186, 186);
        printf("\033[38;5;208m%c\033[0m 1. Modo Casual (permite borrar jugadas anteriores) \033[38;5;208m%c\033[0m\n", 186, 186);
        printf("\033[38;5;208m%c\033[0m 2. Modo Profesional (no se pueden borrar jugadas)  \033[38;5;208m%c\033[0m\n", 186, 186);
        printf("\033[38;5;208m%c\033[0m 0. SALIR                                           \033[38;5;208m%c\033[0m\n", 186, 186);
        printf("\033[38;5;208m%c\033[0m", 200); //Esquina inferior izquierda
        for(i = 0; i < 52; i++)
            printf("\033[38;5;208m%c\033[0m", 205); //Bordes horizontales
        printf("\033[38;5;208m%c\033[0m", 188); //Esquina inferior derecha


        printf("\n---Ingrese una opci\242n---\n\n");
        scanf("%d", &opcion);


    } while (opcion > 2 || opcion < 0);

    return opcion;

}

bool menuRestar(){
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

void mostrarControles(){
    system("cls");
    printf("\t\t\t\033[38;5;208mCONTROLES\033[0m\n\t\t\t---------\n");

    printf("\n\033[38;5;208mMovimiento:\033[0m\n \t\t [ FlechaArriba ]\n[ FlechaIzquierda ]\t\t\t[ FlechaDerecha ]\n \t\t [ FlechaAbajo ]");

    printf("\n\n\033[38;5;208mInteracci\242n:\033[0m\t[N\243meros]\n\n");

    printf("\033[38;5;208mAutoCompletado:\033[0m [Espacio]\n\n");
    printf("\033[38;5;208mBorrarJugada:\033[0m [Retroceso]\n\n");
    printf("--------------------------------------------------------\n");

}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Ocultar el cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
