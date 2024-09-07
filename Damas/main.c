#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <windows.h>


#define N 8




        /*Declaración de estructuras*/

typedef struct{
int f;  //Posición del jugador ---Filas---
int c;  //Posición del jugador ---Columnas---
}posJug;


typedef struct{
int fichSelect[2]; //Posición de la ficha
bool uso;
}posFicha;

        /*Declaración de Funciones*/
/*-----------------------------------------------------*/

void mostrarTablero(int tablero[][N], bool tableroJugable[][N], posFicha jugada, posJug pos, int turn);
bool movimiento(int tablero[][N], bool tableroLock[][N], bool tableroJugable[][N], posJug *pos, posFicha *jugada, int turn, bool *first, bool *comer);
void resetPosiblesJugadas(int tablero[][N]);
bool tieneQueComer(bool tableroLock[][N], int tablero[][N], int posFichaF, int posFichaC, int turn, bool *found);
void bloquearTablero(bool tableroLock[][N]);
void desbloquearTablero(bool tableroLock[][N]);
void comprobarReina(int tablero[][N], int turn);
void tableroJugadasReset(bool tableroJugadas[][N]);
void dondePuedoMoverme(int tablero[][N], bool tableroJugable[][N], int posFichaF, int posFichaC, int turn, bool comer);
void moverFicha(int tablero[][N], posJug posJ, posFicha posF, bool comer, int turn);
bool comprobarWin (int tablero[][N], int turn);
void mensajeFelicitacion (int turn);
void hideCursor();
void mostrarControles();
int menuJuego();
bool reset();
void tableroReset(int tablero[][N]);


int main() {

    /*Tablero de Juego*/
    int tablero[N][N] = {
        {0, 2, 0, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 0, 2, 0},
        {0, 2, 0, 2, 0, 2, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0}


    };


        /*Tablero Candado*/
    bool tableroLock[N][N] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    bool tableroJugable[N][N] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    posJug pos1;


    posJug pos2;

    posFicha jugada;


    bool first;
    bool comer;
    bool win;
    int modo;

    hideCursor();


    do{
        //Reiniciamos los tableros
        tableroReset(tablero);
        desbloquearTablero(tableroLock);
        tableroJugadasReset(tableroJugable);


        jugada.uso = false;

        pos1.c = 1, pos1.f = 4;//Posición Inicial del jugador 1

        pos2.c = 0, pos2.f = 3;//Posición Inicial del jugador 2

        system("cls");
        modo = menuJuego();
        mostrarControles();
        system("pause");
        do{
            first = true;
            comer = false;
            win = comprobarWin(tablero, 2);
            if(!win){
                do{ //Turno del jugador1

                    system("cls");
                    mostrarTablero(tablero, tableroJugable, jugada, pos1, 1);

                }while(!movimiento(tablero, tableroLock, tableroJugable, &pos1, &jugada, 1, &first, &comer));
            }
            else{
                system("cls");
                mostrarTablero(tablero, tableroJugable, jugada, pos2, 2);
                if(modo == 1)
                    mensajeFelicitacion(2);
                else
                    mensajeFelicitacion(1);

            }
            if(!win){
                comprobarReina(tablero, 1);


                first = true;
                comer = false;
                win = comprobarWin(tablero, 1);
                if(!win){
                    do{ //Turno del jugador2

                        system("cls");
                        mostrarTablero(tablero, tableroJugable, jugada, pos2, 2);

                    }while(!movimiento(tablero, tableroLock, tableroJugable, &pos2, &jugada, 2, &first, &comer));
                }
                else{
                    system("cls");
                    mostrarTablero(tablero, tableroJugable, jugada, pos1, 1);
                    if(modo == 1)
                        mensajeFelicitacion(1);
                    else
                        mensajeFelicitacion(2);
                }
                comprobarReina(tablero, 2);
            }

        }while(!win);

    }while(reset());

    return 0;
}

        /*Implementación de Funciones*/
void mostrarTablero(int tablero[][N], bool tableroJugable[][N], posFicha jugada, posJug pos, int turn) {
    int i, j;
    printf("\n\n\n\n\n\n\n\n");

    if(turn == 1)
        printf("--TURNO DEL JUGADOR \033[33mAMARILLO\033[0m--\n\n");
    else
        printf("--TURNO DEL JUGADOR \033[31mROJO\033[0m--\n\n");
    // Dibuja la parte superior del tablero
    printf("\t\t\t      1  2  3  4  5  6  7  8\n");
    printf("\t\t\t    --------------------------\n");

    for (i = 0; i < N; i++) {
        printf("\t\t\t  %d |", i + 1);  // Muestra el número de fila

        for (j = 0; j < N; j++) {
            if( (i+j) % 2 != 0){  // Solo las celdas jugables
                if(tableroJugable[i][j] == true && (pos.f == i && pos.c == j))//Celdas Jugables
                    printf("\033[32m[.]\033[0m");
                else if(tableroJugable[i][j] == true)
                    printf(" \033[32m.\033[0m ");
                else if (tablero[i][j] == 0 && pos.f == i && pos.c == j) // Espacio en blanco
                    printf("[ ]");
                else if(tablero[i][j] == 0)
                    printf("   ");

                    /*Jugador Amarillo*/
                else if( (jugada.fichSelect[0] == i && jugada.fichSelect[1] == j) && (tablero[i][j] == 1 && jugada.uso == true))
                    printf("\033[32m[\033[33mO\033[32m]\033[0m");//Seleccionada
                else if( (jugada.fichSelect[0] == i && jugada.fichSelect[1] == j) && (tablero[i][j] == 3 && jugada.uso == true))
                    printf("\033[32m[\033[33m%c\033[32m]\033[0m", 226);//Seleccionanda Dama
                else if (tablero[i][j] == 1 && pos.f == i && pos.c == j)
                    printf("[\033[33mO\033[0m]");//Posicionada
                else if (tablero[i][j] == 3 && pos.f == i && pos.c == j)
                     printf("[\033[33m%c\033[0m]", 226);//Posicionada Dama
                else if (tablero[i][j] == 1)
                    printf(" \033[33mO\033[0m ");//Ficha
                else if (tablero[i][j] == 3)
                    printf(" \033[33m%c\033[0m ", 226);//Dama

                    /*Jugador Rojo*/
                else if ( (jugada.fichSelect[0] == i && jugada.fichSelect[1] == j) && (tablero[i][j] == 2 && jugada.uso == true))
                    printf("\033[32m[\033[31mO\033[0m\033[32m]\033[0m");//Seleccionada
                else if ( (jugada.fichSelect[0] == i && jugada.fichSelect[1] == j) && (tablero[i][j] == 4 && jugada.uso == true))
                    printf("\033[32m[\033[31m%c\033[0m\033[32m]\033[0m", 226);//Seleccionanda Dama
                else if (tablero[i][j] == 2 && pos.f == i && pos.c == j)
                    printf("[\033[31mO\033[0m]");//Posicionada
                else if (tablero[i][j] == 4 && pos.f == i && pos.c == j)
                    printf("[\033[31m%c\033[0m]", 226);//Posicionada Dama
                else if (tablero[i][j] == 2)
                    printf(" \033[31mO\033[0m ");//Ficha
                else if (tablero[i][j] == 4)
                    printf(" \033[31m%c\033[0m ", 226);//Dama





            } else {
                if(pos.f == i && pos.c == j)
                    printf("[%c]", 219);
                else
                    printf(" %c ", 219); // Celda no jugable
            }
        }

        printf("|\n"); // Cierra la fila del tablero
        printf("\t\t\t    --------------------------\n"); // Dibuja la línea separadora
    }
}

bool movimiento(int tablero[][N], bool tableroLock[][N], bool tableroJugable[][N], posJug *pos, posFicha *jugada, int turn, bool *first, bool *comer){
    int mov;
    bool next = false;

    mov = getch();

    switch(mov){

    case 72: if( (*pos).f > 0) //Arriba
        {
            (*pos).f--;
        }

        break;

    case 77: if( (*pos).c < N - 1) //Derecha
        {
            (*pos).c++;
        }
        break;

    case 80: if( (*pos).f < N - 1) //Abajo
        {
            (*pos).f++;

        }
        break;

    case 75: if( (*pos).c > 0) //Izquierda
        {
            (*pos).c--;

        }
        break;


    case 13: //Enter
        //Analiza si en el tablero existen jugadas de comer (Prioridad de Fichas)
        if( (*first) == true){
            bool found = false;
            int i, j;
            for(i = 0; i < N; i++)
                for(j = 0; j < N; j++)
                    if(tablero[i][j] == turn || (tablero[i][j] == 3 && turn == 1) || (tablero[i][j] == 4 && turn == 2))
                        if( (tieneQueComer(tableroLock, tablero, i, j, turn, &found)) == true ){
                            (*comer) = true;
                        }
            if(!(*comer)){
                desbloquearTablero(tableroLock);
            }
            (*first) = false;
        }

        //Seleccion de Fichas
        if( (tablero[ (*pos).f ][ (*pos).c] == turn || (tablero[ (*pos).f ][ (*pos).c] == 3 && turn == 1) || (tablero[ (*pos).f ][ (*pos).c] == 4 && turn == 2) )&& tableroLock[ (*pos).f ] [(*pos).c] == true){
            //Se utiliza la estructura que guarda la selección
            (*jugada).uso = true;
            (*jugada).fichSelect[0] = (*pos).f;
            (*jugada).fichSelect[1] = (*pos).c;
            tableroJugadasReset(tableroJugable);

            dondePuedoMoverme(tablero, tableroJugable, (*jugada).fichSelect[0], (*jugada).fichSelect[1], turn, (*comer));
        }

        //Movimiento de Fichas
        if((*jugada).uso == true && tableroJugable[(*pos).f][(*pos).c] == true){
            (*jugada).uso = false;
            moverFicha(tablero, (*pos), (*jugada), (*comer), turn);
            tableroJugadasReset(tableroJugable);

            if((*comer) == true){
                bool found = false;
                next = !tieneQueComer(tableroLock, tablero, (*pos).f, (*pos).c, turn, &found);
            }
            else
                next = true;
        }


        break;
    case 32: //Espacio
    {
            /*Opciones de Desarrollo y Debugeo*/
        int x, z;
        for(x = 0; x < N; x++){        /*Observar tablero de candados*/
            for(z = 0; z < N; z++)
                printf(" %d ", tableroLock[x][z]);
            printf("\n");
        }
        printf("--------------------\n");
        for(x = 0; x < N; x++){        /*Observar tablero jugable*/
            for(z = 0; z < N; z++)
                printf(" %d ", tableroJugable[x][z]);
            printf("\n");
        }
        system("pause");
        break;
    }



    }
    return next;
}

bool tieneQueComer(bool tableroLock[][N], int tablero[][N], int posFichaF, int posFichaC, int turn, bool *found){
    /*--Turno jugador Rojo para Dama*/
    if(turn == 2 && tablero[posFichaF][posFichaC] == 4){


        int i, j;
        bool Notfound;
        /*Comprueba la izquierda Abajo*/
        i = posFichaF, j = posFichaC;
        Notfound = false;
        while( (i+1 < N) && (j-1 >= 0) && !Notfound){
            i++, j--;
            if(tablero[i][j] == 2 || tablero[i][j] == 4)
                Notfound = true;

            else if(tablero[i][j] == 1 || tablero[i][j] == 3)
                if((i+1 < N) && (j-1 >= 0)){
                    if(tablero[++i][--j] == 0){
                        if(!(*found)){//Cuando se encuentra la primera jugada de comer, se bloquea todo el tablero y solo se permite que se juegue en esa ficha
                            bloquearTablero(tableroLock);
                            (*found) = true;
                        }
                        tableroLock[posFichaF][posFichaC] = true;
                        return true;
                    }
                    else
                        Notfound = true;
                }

        }
        /*Comprueba la Derecha Abajo*/
        i = posFichaF, j = posFichaC;
        Notfound = false;
        while( (i+1 < N) && (j+1 < N) && !Notfound){
            i++, j++;

            if(tablero[i][j] == 2 || tablero[i][j] == 4)
                Notfound = true;

            else if(tablero[i][j] == 1 || tablero[i][j] == 3)
                if((i+1 < N) && (j+1 < N)){
                    if(tablero[++i][++j] == 0){
                        if(!(*found)){//Cuando se encuentra la primera jugada de comer, se bloquea todo el tablero y solo se permite que se juegue en esa ficha
                            bloquearTablero(tableroLock);
                            (*found) = true;
                        }
                        tableroLock[posFichaF][posFichaC] = true;
                        return true;
                    }

                    else
                       Notfound = true;
                }


        }

        /*Comprueba la Izquierda Arriba*/
        i = posFichaF, j = posFichaC;
        Notfound = false;
        while( (i-1 >= 0) && (j-1 >= 0) && !Notfound){
            i--, j--;

            if(tablero[i][j] == 2 || tablero[i][j] == 4)
                Notfound = true;

            if(tablero[i][j] == 1 || tablero[i][j] == 3)
                if((i-1 >= 0) && (j-1 >= 0)){
                    if(tablero[--i][--j] == 0){
                        if(!(*found)){//Cuando se encuentra la primera jugada de comer, se bloquea todo el tablero y solo se permite que se juegue en esa ficha
                            bloquearTablero(tableroLock);
                            (*found) = true;
                        }
                        tableroLock[posFichaF][posFichaC] = true;
                        return true;
                    }

                    else
                        Notfound = true;
                }


        }

        /*Comprueba la Derecha Arriba*/
        i = posFichaF, j = posFichaC;
        Notfound = false;
        while( (i-1 >= 0) && (j+1 < N) && !Notfound){
            i--, j++;

            if(tablero[i][j] == 2 || tablero[i][j] == 4)
                Notfound = true;

            if(tablero[i][j] == 1 || tablero[i][j] == 3)
                if((i-1 >= 0) && (j+1 < N)){
                    if(tablero[--i][++j] == 0){
                        if(!(*found)){//Cuando se encuentra la primera jugada de comer, se bloquea todo el tablero y solo se permite que se juegue en esa ficha
                            bloquearTablero(tableroLock);
                            (*found) = true;
                        }
                        tableroLock[posFichaF][posFichaC] = true;
                        return true;
                    }

                    else
                        Notfound = true;
                }

        }


    }


    /*--Turno jugador Amarillo para Dama*/
    else if(turn == 1 && tablero[posFichaF][posFichaC] == 3){


        int i, j;
        bool Notfound;

        /*Comprueba la izquierda Abajo*/
        i = posFichaF, j = posFichaC;
        Notfound = false;
        while( (i+1 < N) && (j-1 >= 0) && !Notfound){
            i++, j--;

            if(tablero[i][j] == 1 || tablero[i][j] == 3)
                Notfound = true;

            if(tablero[i][j] == 2 || tablero[i][j] == 4)
                if((i+1 < N) && (j-1 >= 0)){
                    if(tablero[++i][--j] == 0){
                        if(!(*found)){//Cuando se encuentra la primera jugada de comer, se bloquea todo el tablero y solo se permite que se juegue en esa ficha
                            bloquearTablero(tableroLock);
                            (*found) = true;
                        }
                        tableroLock[posFichaF][posFichaC] = true;
                        return true;
                    }

                    else
                        Notfound = true;
                }

        }
        /*Comprueba la Derecha Abajo*/
        i = posFichaF, j = posFichaC;
        Notfound = false;
        while( (i+1 < N) && (j+1 < N) && !Notfound){
            i++, j++;

            if(tablero[i][j] == 1 || tablero[i][j] == 3)
                Notfound = true;

            if(tablero[i][j] == 2 || tablero[i][j] == 4)
                if((i+1 < N) && (j+1 < N)){
                    if(tablero[++i][++j] == 0){
                        if(!(*found)){//Cuando se encuentra la primera jugada de comer, se bloquea todo el tablero y solo se permite que se juegue en esa ficha
                            bloquearTablero(tableroLock);
                            (*found) = true;
                        }
                        tableroLock[posFichaF][posFichaC] = true;
                        return true;
                    }

                    else
                        Notfound = true;
                }

        }

        /*Comprueba la Izquierda Arriba*/
        i = posFichaF, j = posFichaC;
        Notfound = false;
        while( (i-1 >= 0) && (j-1 >= 0) && !Notfound){
            i--, j--;

            if(tablero[i][j] == 1 || tablero[i][j] == 3)
                Notfound = true;

            if(tablero[i][j] == 2 || tablero[i][j] == 4)
                if((i-1 >= 0) && (j-1 >= 0)){
                    if(tablero[--i][--j] == 0){
                        if(!(*found)){//Cuando se encuentra la primera jugada de comer, se bloquea todo el tablero y solo se permite que se juegue en esa ficha
                            bloquearTablero(tableroLock);
                            (*found) = true;
                        }
                        tableroLock[posFichaF][posFichaC] = true;
                        return true;
                    }

                    else
                        Notfound = true;
                }

        }

        /*Comprueba la Derecha Arriba*/
        i = posFichaF, j = posFichaC;
        Notfound = false;
        while( (i-1 >= 0) && (j+1 < N) && !Notfound){
            i--, j++;

            if(tablero[i][j] == 1 || tablero[i][j] == 3)
                Notfound = true;

            if(tablero[i][j] == 2 || tablero[i][j] == 4)
                if((i-1 >= 0) && (j+1 < N)){
                    if(tablero[--i][++j] == 0){
                        if(!(*found)){//Cuando se encuentra la primera jugada de comer, se bloquea todo el tablero y solo se permite que se juegue en esa ficha
                            bloquearTablero(tableroLock);
                            (*found) = true;
                        }
                        tableroLock[posFichaF][posFichaC] = true;
                        return true;
                    }

                    else
                        Notfound = true;
                }

        }


    }





    /*--Turno jugador Rojo para fichas--*/
    else if(turn == 2){
            /*Comprueba a la izquierda*/
        if( (posFichaF + 1 < N && posFichaC - 1 >= 0) && (tablero[posFichaF+1][posFichaC-1] == 1 || tablero[posFichaF+1][posFichaC-1] == 3))//Hay una ficha rival
            if( (posFichaF+2 < N && posFichaC-2 >= 0) && tablero[posFichaF+2][posFichaC-2] == 0){//Luego de la ficha del rival existe una casilla vacía
                if(!(*found)){//Cuando se encuentra la primera jugada de comer, se bloquea todo el tablero y solo se permite que se juegue en esa ficha
                    bloquearTablero(tableroLock);
                    (*found) = true;
                }
                tableroLock[posFichaF][posFichaC] = true;
                return true;
            }
            /*Comprueba a la derecha*/
        if((posFichaF + 1 < N && posFichaC + 1 < N) && (tablero[posFichaF+1][posFichaC+1] == 1 || tablero[posFichaF+1][posFichaC+1] == 3))
            if( (posFichaF+2 < N && posFichaC+2 < N) && tablero[posFichaF+2][posFichaC+2] == 0){
                if(!(*found)){
                    bloquearTablero(tableroLock);
                    (*found) = true;
                }
                tableroLock[posFichaF][posFichaC] = true;
                return true;
            }
    }

        /*--Turno del jugador Amarillo para fichas--*/
    else if(turn == 1){
            /*Comprueba a la izquierda*/
        if( (posFichaF - 1 >= 0 && posFichaC - 1 >= 0) && (tablero[posFichaF-1][posFichaC-1] == 2 || tablero[posFichaF-1][posFichaC-1] == 4))//Hay una ficha rival
            if( (posFichaF-2 >= 0 && posFichaC-2 >= 0) && tablero[posFichaF-2][posFichaC-2] == 0){//Luego de la ficha del rival existe una casilla vacía
                if(!(*found)){//Cuando se encuentra la primera jugada de comer, se bloquea todo el tablero y solo se permite que se juegue en esa ficha
                    bloquearTablero(tableroLock);
                    (*found) = true;
                }
                tableroLock[posFichaF][posFichaC] = true;
                return true;
            }
            /*Comprueba a la derecha*/
        if((posFichaF - 1 >= 0 && posFichaC + 1 < N) && (tablero[posFichaF-1][posFichaC+1] == 2 || tablero[posFichaF-1][posFichaC+1] == 4))
            if( (posFichaF-2 >= 0 && posFichaC+2 < N) && tablero[posFichaF-2][posFichaC+2] == 0){
                if(!(*found)){
                    bloquearTablero(tableroLock);
                    (*found) = true;
                }
                tableroLock[posFichaF][posFichaC] = true;
                return true;
            }
    }

    return false;


}

void bloquearTablero(bool tableroLock[][N]){
    int i, j;

    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            tableroLock[i][j] = false;
}

void desbloquearTablero(bool tableroLock[][N]){
    int i, j;

    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            tableroLock[i][j] = true;
}

void comprobarReina(int tablero[][N], int turn){
    if(turn == 1){
        int i;
        for(i = 0; i < N; i++)
            if(tablero[0][i] == turn){
                tablero[0][i] = 3;
            }

    }

    else if(turn == 2){
        int i;
        for(i = 0; i < N; i++)
            if(tablero[N-1][i] == turn){
                tablero[N-1][i] = 4;
            }
    }
}

void dondePuedoMoverme(int tablero[][N], bool tableroJugable[][N], int posFichaF, int posFichaC, int turn, bool comer){



    /*--Turno jugador Rojo--*/
    if(turn == 2){
        /*Dama Roja*/
        if(tablero[posFichaF][posFichaC] == 4){
             int i, j;
             int cont;
             bool found;

             /*Comprueba a la izquierda arriba DAMA*/
             cont = 0;
             found = false;
             i = posFichaF, j = posFichaC;
             while( (i-1 >=0 && j-1 >= 0) && cont < 2){
                 i--, j--;


                 //Movimiento sin comer
                 if(tablero[i][j] == 0 && !comer)
                     tableroJugable[i][j] = true;

                 //Movimiento comiendo
                 else if( (tablero[i][j] == 0 && found == true) && comer){
                     tableroJugable[i][j] = true;
                 }


                 //Comprobar si hay una ficha del rival
                 else if(tablero[i][j] == 1 || tablero[i][j] == 3){
                     cont++;
                     if( (i-1 >= 0 && j-1 >= 0) && tablero[i-1][j-1] == 0)
                         found = true;

                     else
                         cont = 2;
                 }
                 //Ficha Mia
                 else if(tablero[i][j] == 2 || tablero[i][j] == 4)
                     cont = 2;

             }




            /*Comprueba a la derecha arriba DAMA*/
            cont = 0;
            i = posFichaF, j = posFichaC;
            found = false;
            while( (i-1 >= 0 && j+1 < N) && cont < 2){
                i--, j++;



                //Movimiento sin comer
                if(tablero[i][j] == 0 && !comer){
                    tableroJugable[i][j] = true;
                }

                //Movimiento  comiendo
                else if((tablero[i][j] == 0 && found == true) && comer){
                    tableroJugable[i][j] = true;
                }


                //Comprobar si hay una ficha del rival
                if(tablero[i][j] == 1 || tablero[i][j] == 3){
                    cont++;
                    if( (i-1 >= 0 && j+1 < N) && tablero[i-1][j+1] == 0){
                        found = true;
                    }

                    else
                        cont = 2;
                }
                //Ficha Mia
                else if(tablero[i][j] == 2 || tablero[i][j] == 4)
                    cont = 2;

            }





            /*Comprueba a la izquierda abajo DAMA*/
            cont = 0;
            i = posFichaF, j = posFichaC;
            found = false;
            while( (i+1 < N && j-1 >= 0) && cont < 2){
                i++, j--;

                //Movimiento sin comer
                if(tablero[i][j] == 0 && !comer){
                    tableroJugable[i][j] = true;
                }

                //Movimiento comiendo
                else if((tablero[i][j] == 0 && found == true) && comer){
                    tableroJugable[i][j] = true;
                }

                //Comprobar si hay una ficha del rival
                else if(tablero[i][j] == 1 || tablero[i][j] == 3){
                    cont++;
                    if( (i+1 < N && j-1 >= 0) && tablero[i+1][j-1] == 0){
                        found = true;
                    }

                    else
                        cont = 2;
                }
                //Ficha Mia
                else if(tablero[i][j] == 2 || tablero[i][j] == 4)
                    cont = 2;



            }



            /*Comprueba a la derecha abajo DAMA*/
            cont = 0;
            i = posFichaF, j = posFichaC;
            found = false;
            while( (i+1 < N && j+1 < N) && cont < 2){
                i++, j++;


                //Movimiento sin comer
                if(tablero[i][j] == 0 && !comer){
                    tableroJugable[i][j] = true;
                }

                //Movimiento comiendo
                else if((tablero[i][j] == 0 && found == true) && comer){
                    tableroJugable[i][j] = true;
                }

                //Comprobar si hay una ficha del rival
                else if(tablero[i][j] == 1 || tablero[i][j] == 3){
                    cont++;
                    if( (i+1 < N && j+1 < N) && tablero[i+1][j+1] == 0){
                        found = true;
                    }

                    else
                        cont = 2;
                }
                //Ficha Mia
                else if(tablero[i][j] == 2 || tablero[i][j] == 4)
                    cont = 2;

            }
        }

        /*Ficha Roja*/
        if(tablero[posFichaF][posFichaC] == 2){
            /*Comprueba a la izquierda para Comer*/
            if( (posFichaF + 1 < N && posFichaC - 1 >= 0) && comer && (tablero[posFichaF+1][posFichaC-1] == 1 || tablero[posFichaF+1][posFichaC-1] == 3)){//Hay una ficha rival
                if( (posFichaF+2 < N && posFichaC-2 >= 0) && tablero[posFichaF+2][posFichaC-2] == 0){//Luego de la ficha del rival existe una casilla vacía
                    tableroJugable[posFichaF+2][posFichaC-2] = true;
                }
            }

            /*Comprueba a la derecha para Comer*/
            if((posFichaF + 1 < N && posFichaC + 1 < N) && comer && (tablero[posFichaF+1][posFichaC+1] == 1 || tablero[posFichaF+1][posFichaC+1] == 3)){
                if( (posFichaF+2 < N && posFichaC+2 < N) && tablero[posFichaF+2][posFichaC+2] == 0){
                    tableroJugable[posFichaF+2][posFichaC+2] = true;
                }
            }
            /*Comprueba a la izquierda*/
            if( (posFichaF + 1 < N && posFichaC - 1 >= 0) && tablero[posFichaF+1][posFichaC-1] == 0 && !comer)
                tableroJugable[posFichaF+1][posFichaC-1] = true;





            /*Comprueba a la derecha*/
            if((posFichaF + 1 < N && posFichaC + 1 < N) && tablero[posFichaF+1][posFichaC+1] == 0 && !comer)
                tableroJugable[posFichaF+1][posFichaC+1] = true;
        }


    }

    /*--Turno jugador Amarillo--*/
    if(turn == 1){
        /*Dama Amarilla*/
        if(tablero[posFichaF][posFichaC] == 3){
             int i, j;
             int cont;
             bool found;



             /*Comprueba a la izquierda arriba DAMA*/
             cont = 0;
             found = false;
             i = posFichaF, j = posFichaC;
             while( (i-1 >=0 && j-1 >= 0) && cont < 2){
                 i--, j--;


                 //Movimiento sin comer
                 if(tablero[i][j] == 0 && !comer)
                     tableroJugable[i][j] = true;

                 //Movimiento comiendo
                 else if((tablero[i][j] == 0 && found == true) && comer){
                     tableroJugable[i][j] = true;
                 }


                 //Comprobar hay una ficha del rival
                 else if(tablero[i][j] == 2 || tablero[i][j] == 4){
                     cont++;
                     if( (i-1 >= 0 && j-1 >= 0) && tablero[i-1][j-1] == 0){
                         found = true;
                     }

                     else
                         cont = 2;
                 }
                 //Ficha Mia
                 else if(tablero[i][j] == 1 || tablero[i][j] == 3)
                     cont = 2;

             }




            /*Comprueba a la derecha arriba DAMA*/
            cont = 0;
            i = posFichaF, j = posFichaC;
            found = false;
            while( (i-1 >= 0 && j+1 < N) && cont < 2){
                i--, j++;



                //Movimiento sin comer
                if(tablero[i][j] == 0 && !comer){
                    tableroJugable[i][j] = true;
                }

                //Movimiento  comiendo
                else if((tablero[i][j] == 0 && found == true) && comer){
                    tableroJugable[i][j] = true;
                }


                //Comprobar si hay una ficha del rival
                if(tablero[i][j] == 2 || tablero[i][j] == 4){
                    cont++;
                    if( (i-1 >= 0 && j+1 < N) && tablero[i-1][j+1] == 0)
                        found = true;
                    else
                        cont = 2;
                }
                //Ficha Mia
                else if(tablero[i][j] == 1 || tablero[i][j] == 3)
                    cont = 2;

            }





            /*Comprueba a la izquierda abajo DAMA*/
            cont = 0;
            i = posFichaF, j = posFichaC;
            found = false;
            while( (i+1 < N && j-1 >= 0) && cont < 2){
                i++, j--;

                //Movimiento sin comer
                if(tablero[i][j] == 0 && !comer){
                    tableroJugable[i][j] = true;
                }

                //Movimiento comiendo
                else if((tablero[i][j] == 0 && found == true) && comer){
                    tableroJugable[i][j] = true;
                }

                //Comprobar si hay una ficha del rival
                else if(tablero[i][j] == 2 || tablero[i][j] == 4){
                    cont++;
                    if( (i+1 < N && j-1 >= 0) && tablero[i+1][j-1] == 0){
                        found = true;
                    }

                    else
                        cont = 2;
                }
                //Ficha Mia
                else if(tablero[i][j] == 1 || tablero[i][j] == 3)
                    cont = 2;



            }



            /*Comprueba a la derecha abajo DAMA*/
            cont = 0;
            i = posFichaF, j = posFichaC;
            found = false;
            while( (i+1 < N && j+1 < N) && cont < 2){
                i++, j++;


                //Movimiento sin comer
                if(tablero[i][j] == 0 && !comer){
                    tableroJugable[i][j] = true;
                }

                //Movimiento comiendo
                else if((tablero[i][j] == 0 && found == true) && comer){
                    tableroJugable[i][j] = true;
                }

                //Comprobar si hay una ficha del rival
                else if(tablero[i][j] == 2 || tablero[i][j] == 4){
                    cont++;
                    if( (i+1 < N && j+1 < N) && tablero[i+1][j+1] == 0)
                        found = true;

                    else
                        cont = 2;
                }
                //Ficha Mia
                else if(tablero[i][j] == 1 || tablero[i][j] == 3)
                    cont = 2;



            }

        }

        /*Ficha Amarilla*/
        else if(tablero[posFichaF][posFichaC] == 1){
            /*Comprueba a la izquierda para Comer*/
            if( (posFichaF - 1 >= 0 && posFichaC - 1 >= 0) && comer && (tablero[posFichaF-1][posFichaC-1] == 2 || tablero[posFichaF-1][posFichaC-1] == 4)){//Hay una ficha rival
                if( (posFichaF-2 >= 0 && posFichaC-2 >= 0) && tablero[posFichaF-2][posFichaC-2] == 0){//Luego de la ficha del rival existe una casilla vacía
                    tableroJugable[posFichaF-2][posFichaC-2] = true;
                }
            }

            /*Comprueba a la derecha para Comer*/
            if((posFichaF - 1 >= 0 && posFichaC + 1 < N) && comer && ( (tablero[posFichaF-1][posFichaC+1] == 2) || (tablero[posFichaF-1][posFichaC+1] == 4)) ){
                if( (posFichaF-2 >= 0 && posFichaC+2 < N) && tablero[posFichaF-2][posFichaC+2] == 0){
                    tableroJugable[posFichaF-2][posFichaC+2] = true;
                }
            }

            /*Comprueba a la izquierda*/
            if( (posFichaF - 1 >= 0 && posFichaC - 1 >= 0) && tablero[posFichaF-1][posFichaC-1] == 0 && !comer)
                tableroJugable[posFichaF-1][posFichaC-1] = true;




            /*Comprueba a la derecha*/
            if((posFichaF - 1 >= 0 && posFichaC + 1 < N) && tablero[posFichaF-1][posFichaC+1] == 0 && !comer)
                tableroJugable[posFichaF-1][posFichaC+1] = true;
        }


    }



}


void tableroJugadasReset(bool tableroJugadas[][N]){
    int i, j;
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            tableroJugadas[i][j] = false;
}

void moverFicha(int tablero[][N], posJug posJ, posFicha posF, bool comer, int turn){

    /*Mover Amarillo*/
    if(turn == 1){
        if(tablero[posF.fichSelect[0]][posF.fichSelect[1]] == 3)
            tablero[posJ.f][posJ.c] = 3;
        else if(tablero[posF.fichSelect[0]][posF.fichSelect[1]] == 1){
            tablero[posJ.f][posJ.c] = 1;
        }


        tablero[posF.fichSelect[0]][posF.fichSelect[1]] = 0;
        if(comer){
            int i = posJ.f, j = posJ.c;
            bool found = false;

            while( (i != posF.fichSelect[0] && j != posF.fichSelect[1]) && !found){
                //Comiendo izquierda arriba
                if(i < posF.fichSelect[0] && j < posF.fichSelect[1]){
                    i++, j++;
                    //Ficha del rival a comer
                    if(tablero[i][j] == 2 || tablero[i][j] == 4){
                        tablero[i][j] = 0;
                        found = true;
                    }
                }

                //Comiendo derecha arriba
                else if(i < posF.fichSelect[0] && j > posF.fichSelect[1]){
                    i++, j--;
                    //Ficha del rival a comer
                    if(tablero[i][j] == 2 || tablero[i][j] == 4){
                        tablero[i][j] = 0;
                        found = true;
                    }
                }

                //Comiendo izquierda abajo
                else if(i > posF.fichSelect[0] && j < posF.fichSelect[1]){
                    i--, j++;
                    //Ficha del rival a comer
                    if(tablero[i][j] == 2 || tablero[i][j] == 4){
                        tablero[i][j] = 0;
                        found = true;
                    }
                }

                //Comiendo derecha abajo
                else if(i > posF.fichSelect[0] && j > posF.fichSelect[1]){
                    i--, j--;
                    //Ficha del rival a comer
                    if(tablero[i][j] == 2 || tablero[i][j] == 4){
                        tablero[i][j] = 0;
                        found = true;
                    }
                }
            }
        }





    }

    /*Mover Rojo*/
    if(turn == 2){

        if(tablero[posF.fichSelect[0]][posF.fichSelect[1]] == 4)
            tablero[posJ.f][posJ.c] = 4;
        else
            tablero[posJ.f][posJ.c] = turn;

        tablero[posF.fichSelect[0]][posF.fichSelect[1]] = 0;

        if(comer){
            int i = posJ.f, j = posJ.c;
            bool found = false;

            while( (i != posF.fichSelect[0] && j != posF.fichSelect[1]) && !found){
                //Comiendo izquierda arriba
                if(i < posF.fichSelect[0] && j < posF.fichSelect[1]){
                    i++, j++;
                    //Ficha del rival a comer
                    if(tablero[i][j] == 1 || tablero[i][j] == 3){
                        tablero[i][j] = 0;
                        found = true;
                    }
                }

                //Comiendo derecha arriba
                else if(i < posF.fichSelect[0] && j > posF.fichSelect[1]){
                    i++, j--;
                    //Ficha del rival a comer
                    if(tablero[i][j] == 1 || tablero[i][j] == 3){
                        tablero[i][j] = 0;
                        found = true;
                    }
                }

                //Comiendo izquierda abajo
                else if(i > posF.fichSelect[0] && j < posF.fichSelect[1]){
                    i--, j++;
                    //Ficha del rival a comer
                    if(tablero[i][j] == 1 || tablero[i][j] == 3){
                        tablero[i][j] = 0;
                        found = true;
                    }
                }

                //Comiendo derecha abajo
                else if(i > posF.fichSelect[0] && j > posF.fichSelect[1]){
                    i--, j--;
                    //Ficha del rival a comer
                    if(tablero[i][j] == 1 || tablero[i][j] == 3){
                        tablero[i][j] = 0;
                        found = true;
                    }
                }
            }
        }



    }

}
bool comprobarWin (int tablero[][N], int turn){

    int i, j;
    bool found = false;
    int dama, ficha;

    if(turn == 1){
        ficha = 2;
        dama = 4;
    }

    else{
        ficha = 1;
        dama = 3;
    }

    for(i=0; found == false && i < N; i++){
        for(j=0; found == false && j < N; j++){
            if( (i+j) % 2 != 0)
                if(tablero[i][j]==ficha || tablero[i][j]==dama){
                    found = true;
            }

        }

    }

    return !found;
}

void mensajeFelicitacion(int turn){
    if(turn == 1){
        printf("\n\n\033[33m");
        printf("  *************************************************\n");
        printf("  *         FELICIDADES HA GANADO !!              *\n");
        printf("  *                                               *\n");
        printf("  *************************************************\n\033[0m");
    }
    else{
        printf("\n\n\033[31m");
        printf("  *************************************************\n");
        printf("  *         FELICIDADES HA GANADO !!              *\n");
        printf("  *                                               *\n");
        printf("  *************************************************\n\033[0m");
    }
}

void mostrarControles(){
    system("cls");
    printf("\t\t\t\033[31mCONTROLES\033[0m\n\t\t\t---------\n");

    printf("\033[31mMovimiento:\033[33m\n \t\t [ FlechaArriba ]\n[ FlechaIzquierda ]\t\t[ FlechaDerecha ]\n \t\t [ FlechaAbajo ]");

    printf("\n\n\033[31mInteracci\242n:\t\033[33m[ENTER]\033[0m\n\n");


}

int menuJuego(){

    int opcion;

    do {
        int i;
        system("cls");


        printf("\t\t\t\033[38;5;208mJuego de Damas\033[0m");
        printf("\n\n");
        printf("\033[38;5;208m%c", 201); // Esquina superior izquierda
        for(i = 0; i < 64; i++)
            printf("\033[38;5;208m%c\033[0m", 205); //Bordes horizontales
        printf("\033[38;5;208m%c\033[0m\n", 187); // Esquina superior derecha

        printf("\033[38;5;208m%c\033[0m\t\t    Men\243 de Opciones de Juego\t\t     \033[38;5;208m    %c\033[0m\n", 186, 186);
        printf("\033[38;5;208m%c----------------------------------------------------------------%c\033[0m\n", 186, 186);
        printf("\033[38;5;208m%c\033[0m 1. Modo Damas (Gana el que capture todas las fichas del rival)\033[38;5;208m %c\033[0m\n", 186, 186);
        printf("\033[38;5;208m%c\033[0m 2. Modo Come-Come (Gana el que le capturen todas las fichas)\033[38;5;208m   %c\033[0m\n", 186, 186);
        printf("\033[38;5;208m%c\033[0m 0. SALIR                                           \033[38;5;208m            %c\033[0m\n", 186, 186);
        printf("\033[38;5;208m%c\033[0m", 200); //Esquina inferior izquierda
        for(i = 0; i < 64; i++)
            printf("\033[38;5;208m%c\033[0m", 205); //Bordes horizontales
        printf("\033[38;5;208m%c\033[0m", 188); //Esquina inferior derecha


        printf("\n---Ingrese una opci\242n---\n\n");
        scanf("%d", &opcion);


    } while (opcion > 2 || opcion < 0);

    return opcion;

}

bool reset(){

    char opc[1];
    bool yes;
    bool mal = false;

    printf("\n\n");

    do{
        if(mal == false)
            printf("Desea volver a jugar? :\n\033[32m[\033[0mY\033[32m]\033[0m (Para volver a Jugar) / \033[31m[\033[0mN\033[31m]\033[0m (Para Salir)\n");

        mal = false;

        fflush(stdin);
        gets(opc);

        if(strcmpi(opc, "Y") == 0 || strcmpi(opc, "y") == 0)
            yes = true;

        else if(strcmpi(opc, "N") == 0 || strcmpi(opc, "N") == 0)
            yes = false;

        else{
            printf("\033[31mError!\033[0m\nDebes digitar una de las opciones anteriores:\n");
            mal = true;
        }

    }while(mal == true);

    return yes;

}

void tableroReset(int tablero[][N]){
    int i, j;
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++){
            if( (i+j) % 2 != 0){ //Celdas con fichas
                if( i < 3)//Fichas Jugador Rojo
                    tablero[i][j] = 2;
                else if(i > 4)//Fichas Jugador Amarillo
                    tablero[i][j] = 1;
                else
                    tablero[i][j] = 0;


            }
            else
                tablero[i][j] = 0;
        }

}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Ocultar el cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
