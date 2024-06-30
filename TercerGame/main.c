#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define FILA 10
#define COLUMNA 10

typedef struct
{

    int posV; //Movimiento Filas
    int posH; //Movimiento Columnas

}posicion;

typedef struct
{
    bool select;
    int value;

}mapeado;

void inicializar(mapeado map[][COLUMNA]);
void mostrarTitulo();
bool movimiento(posicion *Jug, mapeado map[][COLUMNA], bool win);
void mostrarMapa(mapeado map[][COLUMNA], posicion Jug, bool lost, bool win);
void generarBum(mapeado map[][COLUMNA], int dif, posicion jug);
int dificultad(bool bloq);
void limpiar(mapeado map[][COLUMNA]);
int comprobarMinas(mapeado map[][COLUMNA], int posA, int posB, int *rept);
bool comprobarWin(mapeado map[][COLUMNA], int dif, bool *bloq);
bool menu();
void limpiarMinas(mapeado map[][COLUMNA]);

int main()
{
    posicion jugador = {0, 0};
    mapeado mapa[FILA][COLUMNA];
    int dificul;
    int turno;
    bool perder;
    bool win;
    bool rest;
    bool desblock = true;


    do
    {
        turno = 0;
        win = false;
        perder = false;
        inicializar(mapa);

        system("cls");

        mostrarTitulo();



        dificul = dificultad(desblock);



        mostrarMapa(mapa, jugador, perder, win);

        while(perder == false && win == false)
        {

            perder = movimiento(&jugador, mapa, win);
            win = comprobarWin(mapa, dificul, &desblock);


            if( (turno == 0 || dificul == 24) && perder == false && win == false)
            {
                if(dificul == 24)
                    limpiarMinas(mapa);

                generarBum(mapa, dificul, jugador);
                turno++;

            }

            if(perder == false && win == false)
                mostrarMapa(mapa, jugador, perder, win);

            win = comprobarWin(mapa, dificul, &desblock);

            if(perder == true)
            {
                mostrarMapa(mapa, jugador, perder, win);
                printf("\n\n");
                if(dificul == 8)
                    printf("\033[31mHAS PERDIDO!! \033[0m(Dificultad: \033[32mF\240cil\033[0m)\n");
                else if(dificul == 12)
                    printf("\033[31mHAS PERDIDO!! \033[0m(Dificultad: \033[33mMedio\033[0m)\n");
                else if(dificul == 20)
                    printf("\033[31mHAS PERDIDO!! \033[0m(Dificultad: \033[38;5;208mDif\241cil\033[0m)\n");
                else
                    printf("\033[31mHAS PERDIDO!! \033[0m(Dificultad: \033[31mInterminable\033[0m)\n");
                printf("------------------------------------\n\n\n");
            }

            if(win == true)
            {
                mostrarMapa(mapa, jugador, perder, win);

                printf("\n\n");
                if(dificul == 8)
                    printf("\033[32mFELICIDADES!! HAS GANADO \033[0m(Dificultad: \033[32mF\240cil\033[0m)\n");
                else if(dificul == 12)
                    printf("\033[32mFELICIDADES!! HAS GANADO \033[0m(Dificultad: \033[33mMedio\033[0m)\n");
                else if(dificul == 20)
                    printf("\033[32mFELICIDADES!! HAS GANADO \033[0m(Dificultad: \033[38;5;208mDif\241cil\033[0m)\n");
                else
                    printf("\033[32mFELICIDADES!! HAS GANADO \033[0m(Dificultad: \033[31mInterminable\033[0m)\n");
                printf("----------------------------------------------\n\n\n");

            }


        }

        rest = menu();

    }while(rest == true);

    return 0;

}

bool movimiento(posicion *Jug, mapeado map[][COLUMNA], bool win)
{
    int mov;
    bool lost = false;
    bool repet;

    do
    {
        repet = true;
        mov = getch();

        switch(mov){

            case 72: if( (*Jug).posV > 0) //Arriba
                     {
                        (*Jug).posV--;
                     }

                break;

            case 77: if( (*Jug).posH < COLUMNA - 1) //Derecha
                     {
                        (*Jug).posH++;
                     }
                break;

            case 80: if( (*Jug).posV < FILA - 1) //Abajo
                     {
                        (*Jug).posV++;

                     }
                break;

            case 75: if( (*Jug).posH > 0) //Izquierda
                     {
                        (*Jug).posH--;

                     }
                break;

        case 13: if(map[(*Jug).posV][(*Jug).posH].value == 0 && map[(*Jug).posV][(*Jug).posH].select == false)
                     {
                        map[(*Jug).posV][(*Jug).posH].value = 2;
                        repet = false;
                     }

                    else if(map[(*Jug).posV][(*Jug).posH].value == 1 && map[(*Jug).posV][(*Jug).posH].select == false)
                    {
                        lost = true;
                        repet = false;
                    }

                break;

            case 8: if(map[(*Jug).posV][(*Jug).posH].select == false)
                        map[(*Jug).posV][(*Jug).posH].select = true;
                    else
                        map[(*Jug).posV][(*Jug).posH].select = false;
                break;

        }

        if(repet == true)
            mostrarMapa(map, *Jug, lost, win);

    }while(repet == true);

    return lost;

}

int dificultad(bool bloq)
{
    int opc;
    int value;

    printf("Elija la dificultad que desee: \n\n\n");

    printf("(1) -> \033[32mF\240cil\033[0m\n\n(2) -> \033[33mMedio\033[0m\n\n(3) -> \033[38;5;208mDif\241cil\033[0m\n\n(4) -> \033[31mInterminable\033[0m\n");

    do
    {
        fflush(stdin);


        while(scanf("%d", &opc) == 0 || opc < 1 || opc > 4)
        {
            printf("\tError!!\nDebe elegir una de las opciones anteriores\n");
            fflush(stdin);
        }

        if(opc == 4 && bloq == true)
            printf("\tAdvertencia!\nDebes superar la dificultad: \033[38;5;208mDif\241cil\033[0m para acceder a dicha opci\242n\n");


    }while(opc == 4 && bloq == true);

    if(opc == 1)
        value = 8;
    else if(opc == 2)
        value = 12;
    else if(opc == 3)
        value = 20;
    else
        value = 24;

    return value;

}

void mostrarMapa(mapeado map[][COLUMNA], posicion Jug, bool lost, bool win)
{
    int i, j;
    int sum = 0;
    int repeticion;

    do
    {
        repeticion = 1;
        system("cls");

        mostrarTitulo();

        for(i = 0; i < FILA; i++)
        {
            for(j = 0; j < COLUMNA; j++)
            {
                    //Posición del jugador
                if(i == Jug.posV && j == Jug.posH)
                {
                    if(lost == false && map[i][j].value < 2 && map[i][j].select == true) // Casilla roja
                        printf("\033[32m[\033[31m%c\033[32m]\033[0m", 254);

                    else if(lost == false && map[i][j].value < 2)  // Casilla blanca
                        printf("\033[32m[\033[0m%c\033[32m]\033[0m", 254);

                    else if(lost == true && map[i][j].value == 1) // Casilla Mina (Perdido)
                        printf("\033[32m[\033[31m%c\033[32m]\033[0m", 15);

                    else if(map[i][j].value >= 2) //Casilla Número de Bombas
                    {
                        sum = comprobarMinas(map, i, j, &repeticion);

                        if(sum != 0)
                        {
                            if(sum <= 2)
                                printf("\033[32m[\033[33m%d\033[32m]\033[0m", sum);
                            else if(sum <= 4)
                                printf("\033[32m[\033[38;5;208m%d\033[32m]\033[0m", sum);
                            else
                                printf("\033[32m[\033[31m%d\033[32m]\033[0m", sum);
                        }
                        else
                            printf("\033[32m[ ]\033[0m");
                    }


                }

                    //Casillas Sueltas
                else if(map[i][j].value >= 2) // Numeración
                {
                    sum = comprobarMinas(map, i, j, &repeticion);

                    if(sum != 0)
                    {
                        if(sum <= 2)
                            printf(" \033[33m%d\033[0m ", sum);
                        else if(sum <= 4)
                            printf(" \033[38;5;208m%d\033[0m ", sum);
                        else
                            printf(" \033[31m%d\033[0m ", sum);
                    }
                    else
                        printf("   ");
                }

                else if(lost == false && win == false && map[i][j].select == false /*&& map[i][j].value == 0*/) // Casilla blanca
                    printf(" %c ", 254);

//                else if(lost == false && win == false && map[i][j].select == false && map[i][j].value == 1) //Mostrar Minas Siempre
//                    printf(" \033[31m%c\033[0m ", 15);

                else if(lost == false && win == false && map[i][j].select == true) // Casilla roja
                    printf(" \033[31m%c\033[0m ", 254);

                else if(map[i][j].value == 1) // Casilla mina (Ganado - perdido)
                    printf(" \033[31m%c\033[0m ", 15);

                else // Casilla Blanca (Ganado - perdido)

                    printf(" %c ", 254);


            }

            printf("\n");
        }



    }while(repeticion == -1);
}

void generarBum(mapeado map[][COLUMNA], int dif, posicion jug)
{
    int A, B, i, j;
    int n = dif;

    srand(time(NULL));

    while(dif > 0)
    {
        A = rand() % 10;
        B = rand() % 10;

        if(n != 24)
        {
            if(map[A][B].value == 0)
                map[A][B].value = 1;
            else
                dif++;

            for (i = jug.posV - 1; i <= jug.posV + 1; i++) {
                for (j = jug.posH - 1; j <= jug.posH + 1; j++) {
                    if (i >= 0 && i < FILA && j >= 0 && j < COLUMNA) {
                        if(map[i][j].value == 1)
                        {
                            map[i][j].value = 0;
                            dif++;
                        }
                    }
                }
            }
        }
        else
        {
            if(A != jug.posV && B != jug.posH)
                map[A][B].value = 1;
            else
                dif++;
        }




        dif--;
    }

}

void limpiar(mapeado map[][COLUMNA])
{

    int i, j;

    for(i = 0; i < FILA; i++)
        for(j = 0; j < COLUMNA; j++)
            map[i][j].value = 0;
}

int comprobarMinas(mapeado map[][COLUMNA], int posA, int posB, int *rept)
{
    int suma = 0;
    int i, j;
      for (i = posA - 1; i <= posA + 1; i++) {
          for (j = posB - 1; j <= posB + 1; j++) {
              if (i >= 0 && i < 10 && j >= 0 && j < 10 && map[i][j].value == 1 && (i != posA || j != posB)) {
                  suma++;
              }
          }
      }

      if (suma == 0 && map[posA][posB].value != 3) {
          map[posA][posB].value = 3;

          for (i = posA - 1; i <= posA + 1; i++) {
              for (j = posB - 1; j <= posB + 1; j++) {
                  if (i >= 0 && i < 10 && j >= 0 && j < 10 && map[i][j].value == 0 && (i != posA || j != posB)) {
                      map[i][j].value = 2;
                  }
              }
          }


          *rept = -1;
      }

    return suma;
}

bool comprobarWin(mapeado map[][COLUMNA], int dif, bool *bloq)
{
    int i, j, cont = 0;
    bool win = false;

    for(i = 0; i < FILA; i++)
        for(j = 0; j < COLUMNA; j++)
            if(map[i][j].value >= 2)
                cont++;

    if(cont + dif == 100)
        win = true;

    if(win == true && dif == 20)
            *bloq = false;


    return win;
}

void mostrarTitulo()
{
    printf("\t\t\033[31m%c \033[33mBUSCA MINAS \033[31m%c\033[0m\n\t\t\033[33m---------------\033[0m\n", 15, 15);
}

void inicializar(mapeado map[][COLUMNA])
{
    int i, j;
    for(i = 0; i < FILA; i++)
        for(j = 0; j < COLUMNA; j++)
        {
            map[i][j].value = 0;
            map[i][j].select = false;
        }
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

void limpiarMinas(mapeado map[][COLUMNA])
{
    int i, j;

    for(i = 0; i < FILA; i++)
        for(j = 0; j < COLUMNA; j++)
            if(map[i][j].value == 1)
                map[i][j].value = 0;
}
