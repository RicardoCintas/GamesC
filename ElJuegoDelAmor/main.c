#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

#define FILAS 15
#define COLUMNAS 30

struct player{

    char nombre[10];
    int posX;
    int posY;
    int value;
    int puntos;

}jugador[2];

void hideCursor();
void mostrarTitulo();
bool comprobarWin(struct player jugador[], int modo);
void moverseJugPlayer(struct player *jugador1, int mapa[][COLUMNAS], struct player *rival);
void moverseJugIA(struct player *jugador, int mapa[][COLUMNAS], struct player *compu, int *posXcorz, int *posYcorz, int *cont);
bool ganar();
void llenadoNombres(struct player jugador[], int modo);
int elegirModalidad();
void mostrarControles(struct player jugador[], int modo);
void mostrarMapa(int mapa[][COLUMNAS], struct player jugador[]);
void inicializarMapa(struct player jugador[], int modo, int mapa[][COLUMNAS]);
void generarCorazones(int mapa[][COLUMNAS]);
int movimientoIA(struct player compu, int posXcorz, int posYcorz, int mapa[][COLUMNAS], int *cont);
void buscarCorazonCercano(struct player compu, int *posXcorz, int *posYcorz, int mapa[][COLUMNAS]);
bool reset();

int main(void)
{

    int mapa[FILAS][COLUMNAS] = {};
    int modo;
    int cont;
    bool fin;
    bool first;
    int posXcorz, posYcorz;

    hideCursor();
    system("cls");

    mostrarTitulo();
    modo = elegirModalidad();
    mostrarTitulo();
    llenadoNombres(jugador, modo);
    mostrarControles(jugador, modo);
    do{
        //Inicialización
        cont = 0;
        fin = false;
        first = true;
        posXcorz = -1, posYcorz = -1;


        inicializarMapa(jugador, modo, mapa);
        generarCorazones(mapa);

        while(!fin){
            system("cls");
            mostrarMapa(mapa, jugador);
            if(first == true)
                system("pause");
            fin = comprobarWin(jugador, modo);

            if(modo == 2 && !fin)          //Player vs Player
                moverseJugPlayer(&jugador[0], mapa, &jugador[1]);

            else if(modo == 1 && !fin)    //Player vs IA
                moverseJugIA(&jugador[0], mapa, &jugador[1], &posXcorz, &posYcorz, &cont);
            first = false;
        }


    }while(reset());

    return 0;
}

bool comprobarWin(struct player jugador[], int modo){
    bool win1 = false, win2 = false;

    if( (jugador[0].puntos > jugador[1].puntos) && (jugador[0].puntos + jugador[1].puntos == 14) )
        win1 = true;

    else if( (jugador[1].puntos > jugador[0].puntos) && (jugador[0].puntos + jugador[1].puntos == 14) )
        win2 = true;

    else if(jugador[0].puntos + jugador[1].puntos == 14){
        win1 = true;
        win2 = true;
    }

        //Mensajes de Ganador vs player

    if(modo == 2){
        if( (win1 == true) && (win2 == true) )
            printf("\033[32mFELICIDADES!!\033[0m AMBOS HAN EMPATADO\n------------------------------\n\n");

        else if(win1 == true)
            printf("\033[32mFELICIDADES!!\033[34m%s\033[0m HA GANADO\n------------------------------\n\n", jugador[0].nombre);

        else if(win2 == true)
            printf("\033[32mFELICIDADES!! \033[31m%s\033[0m HA GANADO\n------------------------------\n\n", jugador[1].nombre);

    }

    else if(modo == 1){
        if( (win1 == true) && (win2 == true) )
            printf("\033[32mFELICIDADES!!\033[0m AMBOS HAN EMPATADO\ncasi le ganas...\n------------------------------\n\n");

        else if(win1 == true)
            printf("\033[32mFELICIDADES!!\033[0m HAS GANADO\n BIEN HECHO\n------------------------------\n\n");

        else if(win2 == true)
            printf("\033[31m%s\033[0m HA GANADO\nPor eso est\240s solo...\n------------------------------\n\n", jugador[1].nombre);
    }



    return win1 == true || win2 == true ? true : false;
}

void mostrarTitulo(){
    printf("\x1b[38;2;255;105;180m\n"); //Color
    printf(" %c%c%c %c      %c %c %c %c%c%c %c%c%c%c %c%c%c%c   %c%c%c  %c%c%c %c      %c%c  %c    %c %c%c%c%c %c%c%c%c\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219 ,219 ,219 ,219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219,219,219,219,219,219,219,219,219,219,219,219,219);
    printf(" %c   %c      %c %c %c %c   %c    %c  %c   %c  %c %c   %c     %c  %c %c%c  %c%c %c  %c %c   %c\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf(" %c%c  %c      %c %c %c %c%c  %c %c%c %c  %c   %c  %c %c%c  %c     %c  %c %c %c%c %c %c  %c %c   %c\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf(" %c   %c    %c %c %c %c %c   %c  %c %c  %c   %c  %c %c   %c     %c%c%c%c %c    %c %c  %c %c %c%c\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf(" %c%c%c %c%c%c  %c%c%c %c%c%c %c%c%c %c%c%c%c %c%c%c%c   %c%c%c  %c%c%c %c%c%c   %c  %c %c    %c %c%c%c%c %c   %c\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0m\n--------------------------------------------------------------------------------\n"); //Quitar Color

}

int elegirModalidad(){

    int modo;
    bool error;


    printf("Digite la modalidad:\n\n(1) -> Solo (jugar con la IA)\n(2) -> En Pareja (con tu crush)\n\n");

    do{
        error = false;

        if(scanf("%d", &modo)==0 || modo > 2 || modo < 1){
            error = true;
            printf("\033[31mError!\033[0m\nModalidad fuera de rango o inv\240lida\n");
            fflush(stdin);
        }

    }while(error == true);

    system("cls");
    return modo;
}

void inicializarMapa(struct player jugador[], int modo, int mapa[][COLUMNAS]){
    int opcion;

    //mostrarTitulo();
    //Posición Inicial de ambos
    jugador[0].posX = 1;
    jugador[0].posY = 1;
    jugador[0].value = 0;
    jugador[0].puntos = 0;

    jugador[1].posX = COLUMNAS - 2;
    jugador[1].posY = FILAS - 2;
    jugador[1].value = 0;
    jugador[1].puntos = 0;

    //Crear mapeado aleatorio
    int i, j;
    srand(time(NULL));

    if(modo == 2)
        opcion = rand() % 3;
    else
        opcion = rand() % 3 + 3;

    if(opcion == 0){
        //Laberinto
        int map[FILAS][COLUMNAS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 1, 0, 0, 0, 0, 0, 0, 0, 1, 9, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 1, 0, 0, 0, 0, 0, 0, 0, 1, 9, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
            {9, 9, 9, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 9, 9, 9},
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 9, 1, 0, 0, 0, 0, 0, 0, 0, 1, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 9, 1, 0, 0, 0, 0, 0, 0, 0, 1, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };

        for(i = 0; i < FILAS; i++)
            for(j = 0; j < COLUMNAS; j++)
                mapa[i][j] = map[i][j];

    }

    else if(opcion == 1){
        //Corazón
        int map[FILAS][COLUMNAS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 9, 9, 1, 1, 1, 9, 9, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 9, 9, 9, 1, 9, 9, 9, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 9, 9, 9, 9, 9, 9, 9, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 9, 9, 9, 9, 9, 9, 9, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 1, 9, 9, 9, 9, 9, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 1, 9, 9, 9, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 9, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };

        for(i = 0; i < FILAS; i++)
            for(j = 0; j < COLUMNAS; j++)
                mapa[i][j] = map[i][j];

    }

    else if(opcion == 2){
        //Love Plus
        int map[FILAS][COLUMNAS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 0, 1, 9, 9, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 0, 1, 9, 9, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 0, 1, 9, 9, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 1, 0, 0, 0, 1, 9, 9, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 0, 1, 9, 9, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };

        for(i = 0; i < FILAS; i++)
            for(j = 0; j < COLUMNAS; j++)
                mapa[i][j] = map[i][j];
    }

    else if(opcion == 3){

        int map[FILAS][COLUMNAS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };

        for(i = 0; i < FILAS; i++)
            for(j = 0; j < COLUMNAS; j++)
                mapa[i][j] = map[i][j];

    }

    else if(opcion == 4){

        int map[FILAS][COLUMNAS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };

        for(i = 0; i < FILAS; i++)
            for(j = 0; j < COLUMNAS; j++)
                mapa[i][j] = map[i][j];

    }

    else if(opcion == 5){

        int map[FILAS][COLUMNAS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };

        for(i = 0; i < FILAS; i++)
            for(j = 0; j < COLUMNAS; j++)
                mapa[i][j] = map[i][j];

    }

    system("cls");

}

void mostrarMapa(int mapa[][COLUMNAS], struct player jugador[]){
    int i, j;
    for(i = 0; i < FILAS; i++){
        for(j = 0; j < COLUMNAS; j++){
            //Mostrar al Jugador 1
            if(jugador[0].posX == j && jugador[0].posY == i)
                printf("\033[34m%c\033[0m", 2);

            else if(jugador[1].posX == j && jugador[1].posY == i)
                printf("\033[31m%c\033[0m", 2);

            else if(mapa[i][j] == 1)
                printf("\033[35m%c\033[0m", 219);

            else if(mapa[i][j] == 3)
                printf("\x1b[38;2;255;105;180m%c\033[0m", 3);

            else
                printf(" ");

        }
        printf("\n");
    }

    printf("\033[34m        %d\033[0m              \033[31m%d\033[0m\n------------------------------\n", jugador[0].puntos, jugador[1].puntos);

    printf("Corazones Restantes: %d\n", 14 - (jugador[0].puntos + jugador[1].puntos));
}


void moverseJugPlayer(struct player *jugador, int mapa[][COLUMNAS], struct player *rival){

    char mov = 0;

    if(kbhit() == 1){
        mov = getch();
        switch(mov){

            case 72: (*jugador).value = 1;
                break;

            case 77: (*jugador).value = 3;
                break;

            case 80: (*jugador).value = 2;
                break;

            case 75: (*jugador).value = 4;
                break;
        }

        switch(mov){

            case 'w': (*rival).value = 1;
                break;

            case 'd': (*rival).value = 3;
                break;

            case 's': (*rival).value = 2;
                break;

            case 'a': (*rival).value = 4;
                break;
        }
    }
            /*Movimientos de Jugador1*/
    //Moverse Derecha
    if( mapa[jugador->posY][jugador->posX + 1] != 1 && (jugador->posX + 1 != rival->posX || jugador->posY != rival->posY) && jugador->value == 3)
        (*jugador).posX++;
    //Moverse Abajo
    else if( mapa[jugador->posY + 1][jugador->posX] != 1 && (jugador->posY + 1 != rival->posY || jugador->posX != rival->posX) && jugador->value == 2)
        (*jugador).posY++;
    //Moverse Izquierda
    else if( mapa[jugador->posY][jugador->posX - 1] != 1 && (jugador->posX - 1 != rival->posX || jugador->posY != rival->posY) && jugador->value == 4)
        (*jugador).posX--;
    //Moverse Arriba
    else if( mapa[jugador->posY - 1][jugador->posX] != 1 && (jugador->posY - 1 != rival->posY || jugador->posX != rival->posX) && jugador->value == 1)
        (*jugador).posY--;
    //Parar
    else
        (*jugador).value = 0;

        /*Movimientos de Jugador2*/
    //Moverse Derecha
    if( mapa[rival->posY][rival->posX + 1] != 1 && (rival->posX + 1 != jugador->posX || rival->posY != jugador->posY) && rival->value == 3)
        (*rival).posX++;
    //Moverse Abajo
    else if( mapa[rival->posY + 1][rival->posX] != 1 && (rival->posY + 1 != jugador->posY || rival->posX != jugador->posX) && rival->value == 2)
        (*rival).posY++;
    //Moverse Izquierda
    else if( mapa[rival->posY][rival->posX - 1] != 1 && (rival->posX - 1 != jugador->posX || rival->posY != jugador->posY) && rival->value == 4)
        (*rival).posX--;
    //Moverse Arriba
    else if( mapa[rival->posY - 1][rival->posX] != 1 && (rival->posY - 1 != jugador->posY || rival->posX != jugador->posX) && rival->value == 1)
        (*rival).posY--;
    //Parar
    else
        (*rival).value = 0;


    //Capturar corazón Jug 1
    if(mapa[jugador->posY][jugador-> posX] == 3){
        jugador->puntos++;
        mapa[jugador->posY][jugador->posX] = 0;
    }

    //Capturar corazón Jug 2
    if(mapa[rival->posY][rival-> posX] == 3){
        rival->puntos++;
        mapa[rival->posY][rival->posX] = 0;
    }


}

void moverseJugIA(struct player *jugador, int mapa[][COLUMNAS], struct player *compu, int *posXcorz, int *posYcorz, int *cont) {
    char mov = 0;


    if(kbhit() == 1){
        mov = getch();
        switch(mov){

            case 72: (*jugador).value = 1;
                break;

            case 77: (*jugador).value = 3;
                break;

            case 80: (*jugador).value = 2;
                break;

            case 75: (*jugador).value = 4;
                break;
        }

    }
            /*Movimientos de Jugador*/
    //Moverse Derecha
    if( mapa[jugador->posY][jugador->posX + 1] != 1 && (jugador->posX + 1 != compu->posX || jugador->posY != compu->posY) && jugador->value == 3)
        (*jugador).posX++;
    //Moverse Abajo
    else if( mapa[jugador->posY + 1][jugador->posX] != 1 && (jugador->posY + 1 != compu->posY || jugador->posX != compu->posX) && jugador->value == 2)
        (*jugador).posY++;
    //Moverse Izquierda
    else if( mapa[jugador->posY][jugador->posX - 1] != 1 && (jugador->posX - 1 != compu->posX || jugador->posY != compu->posY) && jugador->value == 4)
        (*jugador).posX--;
    //Moverse Arriba
    else if( mapa[jugador->posY - 1][jugador->posX] != 1 && (jugador->posY - 1 != compu->posY || jugador->posX != compu->posX) && jugador->value == 1)
        (*jugador).posY--;
    //Parar
    else
        (*jugador).value = 0;

        /*Movimiento de la Computadora*/
    if(mapa[*posYcorz][*posXcorz] != 3 || *cont == 1)
        buscarCorazonCercano(*compu, &(*posXcorz), &(*posYcorz), mapa);
    //printf("%d--%d", *posXcorz, *posYcorz);

    (*compu).value = movimientoIA(*compu, *posXcorz, *posYcorz, mapa, &(*cont));

        /*Movimientos de Jugador2*/
    //Moverse Derecha
    if( mapa[compu->posY][compu->posX + 1] != 1 && (compu->posX + 1 != jugador->posX || compu->posY != jugador->posY) && compu->value == 3)
        (*compu).posX++;
    //Moverse Abajo
    else if( mapa[compu->posY + 1][compu->posX] != 1 && (compu->posY + 1 != jugador->posY || compu->posX != jugador->posX) && compu->value == 2)
        (*compu).posY++;
    //Moverse Izquierda
    else if( mapa[compu->posY][compu->posX - 1] != 1 && (compu->posX - 1 != jugador->posX || compu->posY != jugador->posY) && compu->value == 4)
        (*compu).posX--;
    //Moverse Arriba
    else if( mapa[compu->posY - 1][compu->posX] != 1 && (compu->posY - 1 != jugador->posY || compu->posX != jugador->posX) && compu->value == 1)
        (*compu).posY--;
    //Parar
    else
    (*compu).value = 0;

    //Capturar corazón Jug
    if(mapa[jugador->posY][jugador-> posX] == 3){
        jugador->puntos++;
        mapa[jugador->posY][jugador->posX] = 0;
    }

    //Capturar corazón IA
    if(mapa[compu->posY][compu-> posX] == 3){
        compu->puntos++;
        mapa[compu->posY][compu->posX] = 0;
    }

}

void generarCorazones(int mapa[][COLUMNAS]){
    int cant = 0;
    int posX, posY;
    srand(time(NULL));
    while(cant < 14){

        posY = (rand() % FILAS);
        posX = (rand() % COLUMNAS);

        if(mapa[posY][posX] != 1 && mapa[posY][posX] != 9  && mapa[posY][posX] != 3 && (posY != 1 || posX != 1) && (posY != FILAS - 2 || posX != COLUMNAS - 2)){
            mapa[posY][posX] = 3;
            cant++;
        }
    }
}

void mostrarControles(struct player jugador[], int modo){
    system("cls");
    printf("\t\t\tCONTROLES\n\t\t\t---------\n");
    //Multijugador
    if(modo == 2){
        printf("\033[34m%s\033[0m:\n \t\t [ FlechaArriba ]\n[ FlechaIzquierda ]\t\t[ FlechaDerecha ]\n \t\t [ FlechaAbajo ]", jugador[0].nombre);
        printf("\n\n");
        printf("\033[31m%s\033[0m:\n    [ W ]\n[ A ]    [ D ]\n    [ S ]", jugador[1].nombre);
    }
    //Solo
    else{
        printf("\033[34m%s\033[0m:\n \t\t [ FlechaArriba ]\n[ FlechaIzquierda ]\t\t[ FlechaDerecha ]\n \t\t [ FlechaAbajo ]", jugador[0].nombre);
    }
    printf("\n\nCONSIGUE LOS 14\x1b[38;2;255;105;180m%c\033[0m Y GANAAA!!!\n\n", 3);
    system("pause");


}

void llenadoNombres(struct player jugador[], int modo){
    //Nombres de los jugadores
    if(modo == 1){
        strcpy(jugador[0].nombre, "Player");
        strcpy(jugador[1].nombre, "IA");

    }

    if(modo == 2){
        bool ok = true;
        printf("Digite su nombre: \n");
        do{
            ok = true;
            fflush(stdin);
            gets(jugador[0].nombre);

            if(jugador[0].nombre[0] == '\0'){
                ok = false;
                printf("\033[31mError!\033[0m\nEl nombre no puede quedar en blanco\nDigitelo nuevamente:\n");
            }
        }while(!ok);

        ok = true;

        printf("Digite el nombre de su Pareja: \n");
        do{
            ok = true;
            fflush(stdin);
            gets(jugador[1].nombre);

            if(jugador[1].nombre[0] == '\0'){
                ok = false;
                printf("\033[31mError!\033[0m\nEl nombre no puede quedar en blanco\nDigitelo nuevamente:\n");
            }
        }while(!ok);

    }
}

void buscarCorazonCercano(struct player compu, int *posXcorz, int *posYcorz, int mapa[][COLUMNAS]){
    int i, j;
    int ampliador = 0;
    bool encontrado = false;

    do{
        i = (compu.posY - 1) - ampliador;
        j = (compu.posX - 1) - ampliador;
            //Analizar abajo
        for(; i <= (compu.posY + 1) + ampliador && !encontrado && i < FILAS; i++)
            if(mapa[i][j] == 3 && i < FILAS - 1 && i > 0 && j < COLUMNAS - 1 && j > 0){
                encontrado = true;
                (*posXcorz) = j;
                (*posYcorz) = i;
            }

            //Analizar derecha
        for(; j <= (compu.posX + 1) + ampliador  && !encontrado && j < COLUMNAS; j++)
                if(mapa[i][j] == 3 && j > 0 && j < COLUMNAS && i < FILAS && i > 0){
                    encontrado = true;
                    (*posXcorz) = j;
                    (*posYcorz) = i;
                }

            //Analizar arriba
        for(; i >= (compu.posY - 1) - ampliador && !encontrado && i > 0; i--)
            if(mapa[i][j] == 3 && i < FILAS && i > 0 && j < COLUMNAS && j > 0){
                encontrado = true;
                (*posXcorz) = j;
                (*posYcorz) = i;
            }

            //Analizar izquierda
        for(; j >= (compu.posX - 1) - ampliador && !encontrado && j > 0; j--)
            if(mapa[i][j] == 3 && j < COLUMNAS && j > 0 && i < FILAS && i > 0){
                encontrado = true;
                (*posXcorz) = j;
                (*posYcorz) = i;
            }

        ampliador++;
    }while(!encontrado);

}

int movimientoIA(struct player compu, int posXcorz, int posYcorz, int mapa[][COLUMNAS], int *cont){
    int mov = 0;
    int elegir;

    if(compu.posX < posXcorz && mapa[compu.posY][compu.posX + 1] != 1 && *cont == 0)
        mov = 3;
    else if(compu.posX > posXcorz && mapa[compu.posY][compu.posX - 1] != 1 && *cont == 0)
        mov = 4;

    else if(compu.posY < posYcorz && mapa[compu.posY + 1][compu.posX] != 1 && *cont == 0)
        mov = 2;
    else if(compu.posY > posYcorz && mapa[compu.posY - 1][compu.posX] != 1 && *cont == 0)
        mov = 1;

    else{
        if(*cont == 0){
            (*cont) = 25;
        }

        elegir = rand() % 7;

        switch (elegir) {
        case 0:
            mov = 1;
            break;
        case 1:
            mov = 2;
            break;
        case 2:
            mov = 3;
            break;
        case 3:
            mov = 4;
            break;
        }
        (*cont)--;
    }

    return mov;
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Ocultar el cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
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
