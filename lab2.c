#include "conio2.h"
#include <conio.h>
#include <process.h>
#include <stdio.h>  // no se nesecita para el programa pero lo pongo
#include <stdlib.h> // para pausas
#include <string.h>
#include <unistd.h>
#include <windows.h> // para hacer la estructura del gotoxy

#define ESCAPE_KEY 27
#define H 100
#define V 40

static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;
text_info __text_info = {1, 1, LIGHTGRAY + (BLACK << 4), LIGHTGRAY + (BLACK << 4), 80, 25};
static int __CONIO_TOP = 0;
static int __CONIO_LEFT = 0;

static void __fill_text_info(void)
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    __CONIO_LEFT = info.srWindow.Left;
    __CONIO_TOP = info.srWindow.Top;
    __text_info.curx = info.dwCursorPosition.X - __CONIO_LEFT + 1;
    __text_info.cury = info.dwCursorPosition.Y - __CONIO_TOP + 1;
    __text_info.attribute = info.wAttributes;
    __text_info.screenwidth = info.srWindow.Right - info.srWindow.Left + 1;
    __text_info.screenheight = info.srWindow.Bottom - info.srWindow.Top + 1;
}

//VARIABLES PARA CONTROLAR LOS DIFERENTES MENUS
int pos = 0, fin = 0;
int repite = 1;
int repite2 = 1;
int repite3 = 1;
char key, opcion;

//DEFINICION E INICIALIZACION DE LOS MENUS
char opciones1[6][40] = {"1. Pantalla de presentaci\xF3n",
                         "2. Cargar el conjunto referencia (R)",
                         "3. Funci\xF3n caracter\xEDstica de U",
                         "4. Funci\xF3n caracter\xEDstica de A y B",
                         "5. Operaciones de conjuntos",
                         "6. Salir del programa"};

char opciones2[4][40] = {"1. Uni\xF3n",
                         "2. Intersecci\xF3n",
                         "3. Complemento absoluto de A",
                         "4. Retornar al men\xFA"};

//ORGANOS
char organos[21][40] = {"Cerebro", "lengua", "ojo",
                        "Pulmones", "coraz\xF3n", "timo",
                        "o\xEDdo", "Est\xF3mago", "h\xEDgado", "ri\xF1ones", "p\xFAncreas", "bazo",
                        "Pene", "cl\xEDtoris", "test\xEDculos", "\xFAtero", "pr\xF3stata", "vejiga",
                        "huesos", "m\xFAsculos", "piel"};

char *organo_escogido[5];
char menu_organo_escogido[5][40];

int U[5];
int A[5] = {0};
int B[5] = {0};

void menu_principal();
void menu_secundario();
void cargar_conjunto_refernencia();
void funcion_caracteristica_universo();
void settextxy(int, int, char *, int, int);
void presentacion();
void cargar_conjunto_A();

//* FUNCIONES PARA LA UI DE LA APLICACION
void imprime_menu(char menu[][40], int pos, int n);
void marco(int, int, int, int);
void textbackground(int);
void gotoxy(int, int);
void clreol(void);
void highvideo(void);
void lowvideo(void);
void textcolor(int);
void _setcursor(int);
int ventana(int, int);
void encabezado(int, int);
/*
*                                ██████   ██████   █████████   █████ ██████   █████
*                               ░░██████ ██████   ███░░░░░███ ░░███ ░░██████ ░░███ 
*                                ░███░█████░███  ░███    ░███  ░███  ░███░███ ░███ 
*                                ░███░░███ ░███  ░███████████  ░███  ░███░░███░███ 
*                                ░███ ░░░  ░███  ░███░░░░░███  ░███  ░███ ░░██████ 
*                                ░███      ░███  ░███    ░███  ░███  ░███  ░░█████ 
*                                █████     █████ █████   █████ █████ █████  ░░█████
*                               ░░░░░     ░░░░░ ░░░░░   ░░░░░ ░░░░░ ░░░░░    ░░░░░ 
*/
int main(void)
{
    ventana(H, V);
    menu_principal();

    return EXIT_SUCCESS;
}

void menu_principal()
{
    _setcursor(0);
    do
    {
        pos = 0;
        fin = 0;
        repite = 1;

        imprime_menu(opciones1, pos, 6);
        _setcursor(0);
        do
        {

            key = getch();
            switch (key)
            {
            case 72:
                if (pos == 0)
                    pos = 5;
                else
                    pos--;
                break;
            case 80:
                if (pos == 5)
                    pos = 0;
                else
                    pos++;
                break;
            case 13:
                fin = 1;
            }

            _setcursor(0);
            imprime_menu(opciones1, pos, 6);

        } while (!fin);

        switch (pos)
        {
        case 0:
            presentacion();
            break;

        case 1:
            cargar_conjunto_refernencia();
            break;

        case 2:
            funcion_caracteristica_universo();
            break;

        case 3:
            cargar_conjunto_A();
            break;

        case 4:
            menu_secundario();
            break;

        case 5:
            system("cls");
            repite = 0;
            break;
        }

    } while (repite);

    //return 0;
}

void menu_secundario()
{
    _setcursor(0);
    do
    {
        pos = 0;
        fin = 0;
        repite2 = 1;

        _setcursor(0);
        imprime_menu(opciones2, pos, 4);
        do
        {

            key = getch();
            switch (key)
            {
            case 72:
                if (pos == 0)
                    pos = 3;
                else
                    pos--;
                break;
            case 80:
                if (pos == 3)
                    pos = 0;
                else
                    pos++;
                break;
            case 13:
                fin = 1;
            }

            _setcursor(0);
            imprime_menu(opciones2, pos, 4);

        } while (!fin);

        switch (pos)
        {
        case 0:
            break;

        case 1:
            break;

        case 2:
            break;

        case 3:
            system("cls");
            repite2 = 0;
            break;
        }

    } while (repite2);

    //return 0;
}

void imprime_menu(char menu[][40], int pos, int n)
{
    int i;
    system("cls");
    marco(1, 1, H, V);
    encabezado(7, 3);
    gotoxy(2, V - 3);
    printf("%c", 24);
    gotoxy(2, V - 4);
    printf("%c", 25);
    cprintf("   FLECHAS PARA MOVER");
    gotoxy((H / 2) - 2, 9);
    cprintf("MENU");
    for (i = 0; i < n; i++)
    {
        if (pos == i)
        {
            highvideo();
            textbackground(2);
            gotoxy((H / 2) - 15, i + 11);
            cprintf("%s", menu[i]);
            lowvideo();
            textbackground(0);
        }
        else
        {
            gotoxy((H / 2) - 15, i + 11);
            cprintf("%s", menu[i]);
        }
    }
}

void cargar_conjunto_refernencia()
{
    pos = 0;
    fin = 0;
    repite3 = 1;

    imprime_menu(organos, pos, 21);
    _setcursor(0);
    do
    {
        gotoxy(50, 14);
        printf("ESCOJA 5 ORGANOS PARA FORMAR ");
        gotoxy(50, 15);
        printf("EL CONJUNTO REFERENCIA");
        gotoxy(50, 16);
        printf("PORFAVOR NO REPETIR");
        gotoxy(50, 18);
        printf("%i escojidos de 5", fin);
        key = getch();
        switch (key)
        {
        case 72:
            if (pos == 0)
                pos = 20;
            else
                pos--;
            break;
        case 80:
            if (pos == 20)
                pos = 0;
            else
                pos++;
            break;
        case 13:
            organo_escogido[fin] = organos[pos];
            ++fin;
        }
        _setcursor(0);
        imprime_menu(organos, pos, 21);
    } while (fin <= 4);

    system("cls");
    marco(1, 1, H, V);
    encabezado(7, 3);
    gotoxy(2, 10);
    printf("ORGANOS ESCOGIDOS PARA FORMAR CONJUNTO REFERENCIA (R)\n");
    gotoxy(2, 11);
    printf("(R) = { ");
    for (int i = 0; i <= 4; i++)
    {
        if (i < 4)
        {
            cprintf("%s, ", organo_escogido[i]);
        }
        else
        {
            cprintf("%s }", organo_escogido[i]);
        }
        strcpy(menu_organo_escogido[i], organo_escogido[i]);
    }

    settextxy(H / 2 - 11, V - 3, "PRECIONE PARA CONTINUAR", 3, 1000);

    getchar();
}

void cargar_conjunto_A()
{
    pos = 0;
    fin = 0;
    repite3 = 1;
    char c;

    imprime_menu(menu_organo_escogido, pos, 5);
    do
    {

        key = getch();
        switch (key)
        {
        case 72:
            if (pos == 0)
                pos = 4;
            else
                pos--;
            break;
        case 80:
            if (pos == 4)
                pos = 0;
            else
                pos++;
            break;
        case 13:
            A[pos] = 1;
            ++fin;
        }
        imprime_menu(menu_organo_escogido, pos, 5);
        gotoxy(50, 20);
        printf(" \'s\' para escoger un nuevo elemento del universo ");
        gotoxy(50, 21);
        fflush(stdin);
        cscanf("%i", &c);
    } while (c != 's');

    system("cls");
    marco(1, 1, H, V);
    encabezado(7, 3);
    gotoxy(8, 13);
    printf("CONJUNTO A");
    gotoxy(8, 15);
    printf("A = { ");
    for (int i = 0; i <= 4; i++)
    {
        if (i < 4)
        {
            printf("%i, ", A[i]);
        }
        else
        {
            printf("%i }", A[i]);
        }
    }

    settextxy(H / 2 - 11, V - 3, "PRECIONE PARA CONTINUAR", 3, 1000);

    getchar();
}

void funcion_caracteristica_universo()
{
    system("cls");
    marco(1, 1, H, V);
    encabezado(7, 3);
    gotoxy(8, 13);
    printf("CONJUNTO REFERENCIA (R)");
    gotoxy(8, 15);
    printf("(R) = { ");
    for (int i = 0; i <= 4; i++)
    {
        U[i] = 1;
        if (i < 4)
        {
            cprintf("%s, ", organo_escogido[i]);
        }
        else
        {
            cprintf("%s }", organo_escogido[i]);
        }
    }
    gotoxy(60, 13);
    printf("FUNCION CARACTERISTICA DE U");
    gotoxy(60, 15);
    printf("U = { ");
    for (int j = 0; j <= 4; j++)
    {
        if (j < 4)
        {
            printf("%i, ", U[j]);
        }
        else
        {
            printf("%i }", U[j]);
        }
    }

    settextxy(H / 2 - 11, V - 3, "PRECIONE PARA CONTINUAR", 3, 1000);
    getch();
}

void presentacion()
{
    int tx = H / 2;
    int ty = 5;

    system("cls");
    system("COLOR F0");
    gotoxy(tx - (int)(35 / 2), ty);
    cprintf("UNIVERSIDAD TECNOLOGICA DE PANAM\xC1");
    gotoxy(tx - (int)(51 / 2), ty + 2);
    cprintf("FACULTAD DE INGENIERIA DE SISTEMAS COMPUTACIONALES");
    gotoxy(tx - (int)(45 / 2), ty + 4);
    cprintf("LIC. EN INGENIERIA EN SISTEMAS Y COMPUTACI\xD3N");
    gotoxy(tx - (int)(54 / 2), ty + 6);
    cprintf("DEPARTAMENTO DE COMPUTACI\xD3N Y SIMULACI\xD3N DE SISTEMAS");
    gotoxy(tx - (int)(42 / 2), ty + 12);
    cprintf("ESTRUCTURAS DISCRETAS PARA LA COMPUTACI\xD3N");
    gotoxy(tx - (int)(25 / 2), ty + 16);
    cprintf("TEMA: TEORIA DE CONJUNTO");
    gotoxy(tx - (int)(16 / 2), ty + 20);
    cprintf("PROGRAMADO POR:");
    gotoxy(tx - (int)(27 / 2), ty + 22);
    cprintf("ERNESTO S\xC1NCHEZ 9-743-681");

    settextxy(H / 2 - 11, V - 3, "PRECIONE PARA CONTINUAR", 3, 1000);
    getch();
    system("COLOR 0F");
}

void encabezado(int x, int y)
{
    textcolor(3);
    marco(6, 2, 95, 9);
    gotoxy(x, y);
    cprintf("  ______    ______   .__   __.        __   __    __  .__   __. .___________.  ______   \n");
    gotoxy(x, y + 1);
    cprintf(" /      |  /  __  \\  |  \\ |  |       |  | |  |  |  | |  \\ |  | |           | /  __  \\  \n");
    gotoxy(x, y + 2);
    cprintf("|  ,----' |  |  |  | |   \\|  |       |  | |  |  |  | |   \\|  | `---|  |----`|  |  |  | \n");
    gotoxy(x, y + 3);
    cprintf("|  |      |  |  |  | |  . `  | .--.  |  | |  |  |  | |  . `  |     |  |     |  |  |  | \n");
    gotoxy(x, y + 4);
    cprintf("|  `----. |  `--'  | |  |    | |  `--'  | |  `--'  | |  |\\   |     |  |     |  `--'  | \n");
    gotoxy(x, y + 5);
    cprintf(" \\______|  \\______/  |__| \\__|  \\______/   \\______/  |__| \\__|     |__|      \\______/  \n");
    textcolor(15);
}

void marco(int x, int y, int l, int b)
{
    int i, m;
    gotoxy(x, y);
    printf("%c", 201);
    for (i = x + 1; i < l - 1; i++)
    {
        gotoxy(i, y);
        printf("%c", 205);
    }
    gotoxy(i, y);
    printf("%c", 187);

    for (m = y + 1; m < b; m++)
    {
        gotoxy(x, m);
        for (i = x; i < l; i++)
        {
            if (i == x || i == l - 1)
            {
                gotoxy(i, m);
                printf("%c", 186);
            }
        }
    }

    gotoxy(x, m);
    printf("%c", 200);
    for (i = x + 1; i < l - 1; i++)
    {
        gotoxy(i, m);
        printf("%c", 205);
    }
    gotoxy(i, m);
    printf("%c", 188);
}

void textbackground(int color)
{
    __BACKGROUND = color;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), __FOREGROUND + (color << 4));
}

void highvideo(void)
{
    if (__FOREGROUND < DARKGRAY)
        textcolor(__FOREGROUND + 8);
}

void lowvideo(void)
{
    if (__FOREGROUND > LIGHTGRAY)
        textcolor(__FOREGROUND - 8);
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = __CONIO_LEFT + x - 1;
    c.Y = __CONIO_TOP + y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void textcolor(int color)
{
    __FOREGROUND = color;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));
}

void _setcursor(int type)
{
    CONSOLE_CURSOR_INFO Info;

    if (type == 0)
    {
        Info.bVisible = FALSE;
    }
    else
    {
        Info.dwSize = type;
        Info.bVisible = TRUE;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

int ventana(int Ancho, int Alto)
{
    COORD Coordenada;
    Coordenada.X = Ancho;
    Coordenada.Y = Alto;

    SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Right = Ancho - 1;
    Rect.Bottom = Alto - 1;

    // Ajustar el buffer al nuevo tamaño
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), Coordenada);

    // Cambiar tamaño de consola a lo especificado en el buffer
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &Rect);
    return 1;
}

void clreol(void)
{
    COORD coord;
    DWORD written;

    __fill_text_info();
    coord.X = __CONIO_LEFT + __text_info.curx - 1;
    coord.Y = __CONIO_TOP + __text_info.cury - 1;

    FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), __FOREGROUND + (__BACKGROUND << 4),
                               __text_info.screenwidth - __text_info.curx + 1, coord, &written);
    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', __text_info.screenwidth - __text_info.curx + 1, coord, &written);
    gotoxy(__text_info.curx, __text_info.cury);
}

void settextxy(int x, int y, char *buf, int timestoBlink, int delayMilliSecs)
{
    COORD ord;
    ord.X = x;
    ord.Y = y;

    int len = strlen(buf);
    char *p = new char[len + 1];
    memset(p, 32, len);
    p[len] = '\0';

    for (int i = 0; i < timestoBlink; i++)
    {
        gotoxy(x, y);
        //std::cout << p;
        printf("%s", p);
        Sleep(300);
        gotoxy(x, y);
        //std::cout << buf;
        printf("%s", buf);
        Sleep(delayMilliSecs);
    }
}