#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX 7
//-------------------------------------------------------
//Variables globales
int movs;
char D1[15] = "    [-1-]    ", D2[15] = "   [--2--]   ", D3[15] = "  [---3---]  ", D4[15] = " [----4----] ", D5[15] = "[-----5-----]", TV[15] = "     | |     "; 
char D1B[15] = "____[-1-]____", D2B[15] = "___[--2--]___", D3B[15] = "__[---3---]__", D4B[15] = "_[----4----]_", TVB[15] = "_____| |_____";
//-------------------------------------------------------

//-------------------------------------------------------
//Estructuras
struct Torre1{
    int numdisco;
    int valor;
    struct Torre1 *left;
    struct Torre1 *right;
};
struct Torre2{
    int numdisco;
    int valor;
    struct Torre2 *left;
    struct Torre2 *right;
};
struct Torre3{
    int numdisco;
    int valor;
    struct Torre3 *left;
    struct Torre3 *right;
};

struct Pila1{
    struct Torre1 *vectorre1[MAX];
    int top;
};
struct Pila2{
    struct Torre2 *vectorre2[MAX];
    int top;
};
struct Pila3{
    struct Torre3 *vectorre3[MAX];
    int top;
};
//-------------------------------------------------------

//-------------------------------------------------------
//Funciones encargadas de crear los discos
struct Torre1 *crearDisco1(int val, int disco){
    struct Torre1 *nuevo = (struct Torre1 *)malloc(sizeof(struct Torre1));
    nuevo->left = NULL;
    nuevo->right = NULL;
    nuevo->valor = val;
    nuevo->numdisco = disco;
    return nuevo;
}
struct Torre2 *crearDisco2(int val, int disco){
    struct Torre2 *nuevo = (struct Torre2 *)malloc(sizeof(struct Torre2));
    nuevo->left = NULL;
    nuevo->right = NULL;
    nuevo->valor = val;
    nuevo->numdisco = disco;
    return nuevo;
}
struct Torre3 *crearDisco3(int val, int disco){
    struct Torre3 *nuevo = (struct Torre3 *)malloc(sizeof(struct Torre3));
    nuevo->left = NULL;
    nuevo->right = NULL;
    nuevo->valor = val;
    nuevo->numdisco = disco;
    return nuevo;
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funciones encargadas de insertar un disco a una torre
void insertar1(struct Torre1 *nodo, int disco, int val) {
    if (val > nodo->valor) {
        if (nodo->right == NULL) {
            nodo->right = crearDisco1(val, disco);
        } else {
            insertar1(nodo->right, disco, val);
        }
    } else {
        if (nodo->left == NULL) {
            nodo->left = crearDisco1(val, disco);
        } else {
            insertar1(nodo->left, disco, val);
        }
    }
}
void insertar2(struct Torre2 *nodo, int disco, int val) {
    if (val > nodo->valor) {
        if (nodo->right == NULL) {
            nodo->right = crearDisco2(val, disco);
        } else {
            insertar2(nodo->right, disco, val);
        }
    } else {
        if (nodo->left == NULL) {
            nodo->left = crearDisco2(val, disco);
        } else {
            insertar2(nodo->left, disco, val);
        }
    }
}
void insertar3(struct Torre3 *nodo, int disco, int val) {
    if (val > nodo->valor) {
        if (nodo->right == NULL) {
            nodo->right = crearDisco3(val, disco);
        } else {
            insertar3(nodo->right, disco, val);
        }
    } else {
        if (nodo->left == NULL) {
            nodo->left = crearDisco3(val, disco);
        } else {
            insertar3(nodo->left, disco, val);
        }
    }
}
//-------------------------------------------------------

//-------------------------------------------------------
// Funciones para buscar un disco en una torre
bool busqueda1(struct Torre1* arbol, int disco, int valor) {
    if (arbol == NULL) {
        return false;
    }
    else if (arbol->numdisco == disco){
        return true;
    }
    else if (valor < arbol->valor) {
        return busqueda1(arbol->left, disco, valor);
    }
    else {
        return busqueda1(arbol->right, disco, valor);
    }
}
bool busqueda2(struct Torre2* arbol, int disco, int valor) {
    if (arbol == NULL) {
        return false;
    }
    else if (arbol->numdisco == disco){
        return true;
    }
    else if (valor < arbol->valor) {
        return busqueda2(arbol->left, disco, valor);
    }
    else {
        return busqueda2(arbol->right, disco, valor);
    }
}
bool busqueda3(struct Torre3* arbol, int disco, int valor) {
    if (arbol == NULL) {
        return false;
    }
    else if (arbol->numdisco == disco){
        return true;
    }
    else if (valor < arbol->valor) {
        return busqueda3(arbol->left, disco, valor);
    }
    else {
        return busqueda3(arbol->right, disco, valor);
    }
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funciones para verificar si el disco elegido es el menor
void inorden1(struct Torre1 *arbol, int *min){
    if(arbol == NULL){
        return;
    }
    inorden1(arbol->left, min);
    if(arbol->numdisco < *min){
        *min = arbol->numdisco;
    }
    inorden1(arbol->right, min);
}
void inorden2(struct Torre2 *arbol, int *min){
    if(arbol == NULL){
        return;
    }
    inorden2(arbol->left, min);
    if(arbol->numdisco < *min){
        *min = arbol->numdisco;
    }
    inorden2(arbol->right, min);
}
void inorden3(struct Torre3 *arbol, int *min){
    if(arbol == NULL){
        return;
    }
    inorden3(arbol->left, min);
    if(arbol->numdisco < *min){
        *min = arbol->numdisco;
    }
    inorden3(arbol->right, min);
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funciones para eliminar los discos
struct Torre1 *eliminar1(struct Torre1* arbol, int disco, bool *band, int min, int val) {
    if (val < arbol->valor) {
        arbol->left = eliminar1(arbol->left, disco, band, min, val);
    }
    else if (val > arbol->valor) {
        arbol->right = eliminar1(arbol->right, disco, band, min, val);
    }
    else if (val == arbol->valor){
        //condiciones de eliminacion
        if((arbol->left != NULL && arbol->right == NULL)||(arbol->left == NULL && arbol->right != NULL)||(arbol->left != NULL && arbol->right != NULL)){
            printf("|-----------------------------------------------------|\n");
            printf("| [A]               DISCO BLOQUEADO    1              |\n");
            printf("|-----------------------------------------------------|\n");
            system("pause");
            *band = false;
        }
        //caso hoja
        if(arbol->left == NULL && arbol->right == NULL){
            if(min != disco){
                printf("|-----------------------------------------------------|\n");
                printf("| [B]               DISCO BLOQUEADO    1              |\n");
                printf("|-----------------------------------------------------|\n");
                system("pause");
                *band = false;
            }
            else{
                free(arbol);
                return NULL;
            }
        }
    }
    return arbol;
}
struct Torre2 *eliminar2(struct Torre2* arbol, int disco, bool *band, int min, int val) {
    if (val < arbol->valor) {
        arbol->left = eliminar2(arbol->left, disco, band, min, val);
    }
    else if (val > arbol->valor) {
        arbol->right = eliminar2(arbol->right, disco, band, min, val);
    }
    else if (val == arbol->valor){
        //condiciones de eliminacion
        if((arbol->left != NULL && arbol->right == NULL)||(arbol->left == NULL && arbol->right != NULL)||(arbol->left != NULL && arbol->right != NULL)){
            printf("|-----------------------------------------------------|\n");
            printf("| [A]               DISCO BLOQUEADO    2              |\n");
            printf("|-----------------------------------------------------|\n");
            system("pause");
            *band = false;
        }
        //caso hoja
        if(arbol->left == NULL && arbol->right == NULL){
            if(min != disco){
                printf("|-----------------------------------------------------|\n");
                printf("| [B]               DISCO BLOQUEADO    2              |\n");
                printf("|-----------------------------------------------------|\n");
                *band = false;
            }
            else{
                free(arbol);
                return NULL;
            }
        }
    }
    return arbol;
}
struct Torre3 *eliminar3(struct Torre3* arbol, int disco, bool *band, int min, int val) {
    if (val < arbol->valor) {
        arbol->left = eliminar3(arbol->left, disco, band, min, val);
    }
    else if (val > arbol->valor) {
        arbol->right = eliminar3(arbol->right, disco, band, min, val);
    }
    else if (val == arbol->valor){
        //condiciones de eliminacion
        if((arbol->left != NULL && arbol->right == NULL)||(arbol->left == NULL && arbol->right != NULL)||(arbol->left != NULL && arbol->right != NULL)){
            printf("|-----------------------------------------------------|\n");
            printf("| [A]               DISCO BLOQUEADO    3              |\n");
            printf("|-----------------------------------------------------|\n");
            system("pause");
            *band = false;
        }
        //caso hoja
        if(arbol->left == NULL && arbol->right == NULL){
            if(min != disco){
                printf("|-----------------------------------------------------|\n");
                printf("| [B]               DISCO BLOQUEADO    3              |\n");
                printf("|-----------------------------------------------------|\n");
                system("pause");
                *band = false;
            }
            else{
                free(arbol);
                return NULL;
            }
        }
    }
    return arbol;
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funciones de las pilas de las torres
void inicializarPila1(struct Pila1* pila){
    pila->top = -1;
}
void inicializarPila2(struct Pila2* pila){
    pila->top = -1;
}
void inicializarPila3(struct Pila3* pila){
    pila->top = -1;
}

int pilaVacia1(struct Pila1* pila) {
    return (pila->top == -1);
}
int pilaVacia2(struct Pila2* pila) {
    return (pila->top == -1);
}
int pilaVacia3(struct Pila3* pila) {
    return (pila->top == -1);
}

int pilaLlena1(struct Pila1* pila) {
    return (pila->top == MAX - 1);
}
int pilaLlena2(struct Pila2* pila) {
    return (pila->top == MAX - 1);
}
int pilaLlena3(struct Pila3* pila) {
    return (pila->top == MAX - 1);
}

void push1(struct Pila1* pila, struct Torre1* nodo) {
    if (pilaLlena1(pila)) {
        printf("Error: Pila llena\n");
        return;
    }
    pila->vectorre1[++(pila->top)] = nodo;
}
void push2(struct Pila2* pila, struct Torre2* nodo) {
    if (pilaLlena2(pila)) {
        printf("Error: Pila llena\n");
        return;
    }
    pila->vectorre2[++(pila->top)] = nodo;
}
void push3(struct Pila3* pila, struct Torre3* nodo) {
    if (pilaLlena3(pila)) {
        printf("Error: Pila llena\n");
        return;
    }
    pila->vectorre3[++(pila->top)] = nodo;
}

struct Torre1* pop1(struct Pila1* pila) {
    if (pilaVacia1(pila)) {
        printf("Error: Pila vacia\n");
        return NULL;
    }
    return pila->vectorre1[(pila->top)--];
}
struct Torre2* pop2(struct Pila2* pila) {
    if (pilaVacia2(pila)) {
        printf("Error: Pila vacia\n");
        return NULL;
    }
    return pila->vectorre2[(pila->top)--];
}
struct Torre3* pop3(struct Pila3* pila) {
    if (pilaVacia3(pila)) {
        printf("Error: Pila vacia\n");
        return NULL;
    }
    return pila->vectorre3[(pila->top)--];
}

void Torre1Vec1(struct Torre1* raiz, int vector[], int n) {
    if (raiz == NULL){
        return;
    }
    struct Pila1 pila;
    inicializarPila1(&pila);
    struct Torre1* actual = raiz;
    int i = 0;
    while (actual != NULL || !pilaVacia1(&pila)) {
        while (actual != NULL) {
            vector[i++] = actual->numdisco;
            push1(&pila, actual);
            actual = actual->left;
        }
        
        actual = pop1(&pila);
        actual = actual->right;
    }
}
void Torre2Vec2(struct Torre2* raiz, int vector[], int n) {
    if (raiz == NULL){
        return;
    }
    struct Pila2 pila;
    inicializarPila2(&pila);
    struct Torre2* actual = raiz;
    int i = 0;
    while (actual != NULL || !pilaVacia2(&pila)) {
        while (actual != NULL) {
            vector[i++] = actual->numdisco;
            push2(&pila, actual);
            actual = actual->left;
        }
        
        actual = pop2(&pila);
        actual = actual->right;
    }
}
void Torre3Vec3(struct Torre3* raiz, int vector[], int n) {
    if (raiz == NULL){
        return;
    }
    struct Pila3 pila;
    inicializarPila3(&pila);
    struct Torre3* actual = raiz;
    int i = 0;
    while (actual != NULL || !pilaVacia3(&pila)) {
        while (actual != NULL) {
            vector[i++] = actual->numdisco;
            push3(&pila, actual);
            actual = actual->left;
        }
        
        actual = pop3(&pila);
        actual = actual->right;
    }
}

void ordenvector(int vector[], int n) {
    int i, j, aux;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (vector[j] > vector[j + 1]) {
                aux = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = aux;
            }
        }
    }
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funcion de impresion de torres
void ImprimirTorres(struct Torre1* raizT1, struct Torre2* raizT2, struct Torre3* raizT3){
    int MAT[MAX][3] = {0};
    int vec1[MAX] = {0};
    int vec2[MAX] = {0};
    int vec3[MAX] = {0};
    int n = MAX, i, j;
    char T1[15], T2[15], T3[15];
    Torre1Vec1(raizT1, vec1, n);
    Torre2Vec2(raizT2, vec2, n);
    Torre3Vec3(raizT3, vec3, n);
    ordenvector(vec1, n);
    ordenvector(vec2, n);
    ordenvector(vec3, n);
    for(i = 0; i < MAX; i++){
        for(j = 0; j < 3; j++){
            if(j == 0){MAT[i][j] = vec1[i];}
            if(j == 1){MAT[i][j] = vec2[i];}
            if(j == 2){MAT[i][j] = vec3[i];}
        }
    }
    printf("|-----------------------------------------------------|\n");
    printf("| - - - - TORRE DE HANOI - - - Francisco Rial - - - - |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|                                                     |\n");
    printf("|                                                     |\n");
    printf("|           ___           ___           ___           |\n");
    printf("|           | |           | |           | |           |\n");
    printf("|           | |           | |           | |           |\n");
    for(i = 1; i < 6; i++){
        for(j = 0; j < 3; j++){
            if(j == 0){
                if(MAT[i][0] == 0){strcpy(T1, TV);}
                if(MAT[i][0] == 1){strcpy(T1, D1);}
                if(MAT[i][0] == 2){strcpy(T1, D2);}
                if(MAT[i][0] == 3){strcpy(T1, D3);}
                if(MAT[i][0] == 4){strcpy(T1, D4);}
                if(MAT[i][0] == 5){strcpy(T1, D5);}
                if(MAT[i][0] == 0 && i == 5){strcpy(T1, TVB);}
                if(MAT[i][0] == 1 && i == 5){strcpy(T1, D1B);}
                if(MAT[i][0] == 2 && i == 5){strcpy(T1, D2B);}
                if(MAT[i][0] == 3 && i == 5){strcpy(T1, D3B);}
                if(MAT[i][0] == 4 && i == 5){strcpy(T1, D4B);}
            }
            if(j == 1){
                if(MAT[i][1] == 0){strcpy(T2, TV);}
                if(MAT[i][1] == 1){strcpy(T2, D1);}
                if(MAT[i][1] == 2){strcpy(T2, D2);}
                if(MAT[i][1] == 3){strcpy(T2, D3);}
                if(MAT[i][1] == 4){strcpy(T2, D4);}
                if(MAT[i][1] == 5){strcpy(T2, D5);}
                if(MAT[i][1] == 0 && i == 5){strcpy(T2, TVB);}
                if(MAT[i][1] == 1 && i == 5){strcpy(T2, D1B);}
                if(MAT[i][1] == 2 && i == 5){strcpy(T2, D2B);}
                if(MAT[i][1] == 3 && i == 5){strcpy(T2, D3B);}
                if(MAT[i][1] == 4 && i == 5){strcpy(T2, D4B);}
            }
            if(j == 2){
                if(MAT[i][2] == 0){strcpy(T3, TV);}
                if(MAT[i][2] == 1){strcpy(T3, D1);}
                if(MAT[i][2] == 2){strcpy(T3, D2);}
                if(MAT[i][2] == 3){strcpy(T3, D3);}
                if(MAT[i][2] == 4){strcpy(T3, D4);}
                if(MAT[i][2] == 5){strcpy(T3, D5);}
                if(MAT[i][2] == 0 && i == 5){strcpy(T3, TVB);}
                if(MAT[i][2] == 1 && i == 5){strcpy(T3, D1B);}
                if(MAT[i][2] == 2 && i == 5){strcpy(T3, D2B);}
                if(MAT[i][2] == 3 && i == 5){strcpy(T3, D3B);}
                if(MAT[i][2] == 4 && i == 5){strcpy(T3, D4B);}
            }
        }
        if(i == 5){
            printf("|______%s_%s_%s______|\n", T1, T2, T3);
        }else{
            printf("|      %s %s %s      |\n", T1, T2, T3);
        }
    }
    printf("|_____________________________________________________|\n");
    printf("|                                                     |\n");
    printf("|-----------------------------------------------------|\n");
    if(movs >= 10){
        printf("|               MOVIMIENTOS USADOS [%d]               |\n", movs);
    }else{
        printf("|               MOVIMIENTOS USADOS [%d]                |\n", movs);
    }
    printf("|-----------------------------------------------------|\n");
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funcion encargada de mover los discos de una torre a otra
void movimientos(struct Torre1 *raizT1, struct Torre2 *raizT2, struct Torre3 *raizT3, int disco, int val){
    char opt;
    int op, min1 = 10, min2 = 10, min3 = 10;
    bool band = false, bandera = true, T1 = false, T2 = false, T3 = false;
    T1 = busqueda1(raizT1, disco, val);
    T2 = busqueda2(raizT2, disco, val);
    T3 = busqueda3(raizT3, disco, val);
    inorden1(raizT1, &min1);
    inorden2(raizT2, &min2);
    inorden3(raizT3, &min3);
    printf("               ELIJA LA TORRE [1][2][3]: ");
    scanf(" %c",&opt);
    op = (int)opt - 48;
    if(op < 1 || op > 3){
        printf("|-----------------------------------------------------|\n");
        printf("|                   NO EXISTE TORRE                   |\n");
        printf("|-----------------------------------------------------|\n");
        system("pause");
    }
    else{
        if((T1 == true && op == 1)||(T2 == true && op == 2)||(T3 == true && op == 3)){
            printf("|-----------------------------------------------------|\n");
            printf("|                  DISCO YA EN TORRE                  |\n");
            printf("|-----------------------------------------------------|\n");
            system("pause");
            band = true;
        }
        if(band == false){
            if(T1 == true){
                if(min1 == disco){
                    
                    if(disco > min2 && op == 2){
                        printf("|-----------------------------------------------------|\n");
                        printf("|               DISCO DE MAYOR DIAMETRO               |\n");
                        printf("|-----------------------------------------------------|\n");
                        system("pause");
                    }
                    if(disco < min2 && op == 2){
                        raizT1 = eliminar1(raizT1, disco, &bandera, min1, val);
                        if(bandera == true){
                            insertar2(raizT2, disco, val);
                            movs = movs + 1;
                        }
                    }
                    if(disco > min3 && op == 3){
                        printf("|-----------------------------------------------------|\n");
                        printf("|               DISCO DE MAYOR DIAMETRO               |\n");
                        printf("|-----------------------------------------------------|\n");
                        system("pause");
                    }
                    if(disco < min3 && op == 3){
                        raizT1 = eliminar1(raizT1, disco, &bandera, min1, val);
                        if(bandera == true){
                            insertar3(raizT3, disco, val);
                            movs = movs + 1;
                        }
                    }
                }else{
                    printf("|-----------------------------------------------------|\n");
                    printf("|                   DISCO BLOQUEADO                   |\n");
                    printf("|-----------------------------------------------------|\n");
                    system("pause");
                }
            }
            if(T2 == true){
                if(min2 == disco){
                    if(disco > min1 && op == 1){
                        printf("|-----------------------------------------------------|\n");
                        printf("|               DISCO DE MAYOR DIAMETRO               |\n");
                        printf("|-----------------------------------------------------|\n");
                        system("pause");
                    }
                    if(disco < min1 && op == 1){
                        raizT2 = eliminar2(raizT2, disco, &bandera, min2, val);
                        if(bandera == true){
                            insertar1(raizT1, disco, val);
                            movs = movs + 1;
                        }
                    }
                    if(disco > min3 && op == 3){
                        printf("|-----------------------------------------------------|\n");
                        printf("|               DISCO DE MAYOR DIAMETRO               |\n");
                        printf("|-----------------------------------------------------|\n");
                        system("pause");
                    }
                    if(disco < min3 && op == 3){
                        raizT2 = eliminar2(raizT2, disco, &bandera, min2, val);
                        if(bandera == true){
                            insertar3(raizT3, disco, val);
                            movs = movs + 1;
                        }
                    }
                }else{
                    printf("|-----------------------------------------------------|\n");
                    printf("|                   DISCO BLOQUEADO                   |\n");
                    printf("|-----------------------------------------------------|\n");
                    system("pause");
                }
            }
            if(T3 == true){
                if(min3 == disco){
                    if(disco > min1 && op == 1){
                        printf("|-----------------------------------------------------|\n");
                        printf("|               DISCO DE MAYOR DIAMETRO               |\n");
                        printf("|-----------------------------------------------------|\n");
                        system("pause");
                    }
                    if(disco < min1 && op == 1){
                        raizT3 = eliminar3(raizT3, disco, &bandera, min3, val);
                        if(bandera == true){
                            insertar1(raizT1, disco, val);
                            movs = movs + 1;
                        }
                    }
                    if(disco > min2 && op == 2){
                        printf("|-----------------------------------------------------|\n");
                        printf("|               DISCO DE MAYOR DIAMETRO               |\n");
                        printf("|-----------------------------------------------------|\n");
                        system("pause");
                    }
                    if(disco < min2 && op == 2){
                        raizT3 = eliminar3(raizT3, disco, &bandera, min3, val);
                        if(bandera == true){
                            insertar2(raizT2, disco, val);
                            movs = movs + 1;
                        }
                    }
                }else{
                    printf("|-----------------------------------------------------|\n");
                    printf("|                   DISCO BLOQUEADO                   |\n");
                    printf("|-----------------------------------------------------|\n");
                    system("pause");
                }
            }
        }
    }
    system("cls");
}
//-------------------------------------------------------

//-------------------------------------------------------
//Como jugar - reglas
void ComoJugar(){
    system("cls");
    printf("|-----------------------------------------------------|\n");
    printf("|                  REGLAS DEL JUEGO:                  |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|UNICA REGLA: NO SE PUEDE COLOCAR DISCOS DE MAYOR     |\n");
    printf("|DIAMETRO ENCIMA DE UNO DE MENOR DIAMETRO.            |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|                 OBJETIVOS DEL JUEGO                 |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|-PASAR TODOS LOS DISCOS DE LA TORRE 1 A LA TORRE 3   |\n");
    printf("|-HACERLO EN LA MENOR CANTIDAD DE MOVIMIENTOS POSIBLES|\n");
    printf("|-DIVERTIRSE ^^                                       |\n");
    printf("|-----------------------------------------------------|\n");
    system("pause");
    system("cls");
    printf("|-----------------------------------------------------|\n");
    printf("|                     COMO JUGAR:                     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|AL INICIAR EL JUEGO EN LA DIFICULTAD ELEGIDA, SE LE  |\n");
    printf("|MOSTRARAN LAS TORRES CON SUS RESPECTIVAS CANTIDADES  |\n");
    printf("|DE DISCOS.                                           |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|-LO PRIMERO QUE SE LE PEDIRA ES QUE ELIJA QUE DISCO  |\n");
    printf("|DESEA MOVER Y LUEGO LE PEDIRA A QUE TORRE SE MOVERA. |\n");
    printf("|-EL MOVIMIENTO SE REALIZARA CORRECTAMENTE SOLO SI SE |\n");
    printf("|RESPETA LA REGLA DEL JUEGO.                          |\n");
    printf("|-EL JUEGO FINALIZARA UNA VEZ TODOS LOS DISCOS SE     |\n");
    printf("|ENCUENTREN EN LA TORRE NUMERO 3.   ~DIVIERTASE :)~   |\n");
    printf("|-----------------------------------------------------|\n");
    system("pause");
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funciones de dificultad
void modoFacil(){
    movs = 0;
    system("cls");
    struct Torre1 *raizT1 = crearDisco1(10,10);
    struct Torre2 *raizT2 = crearDisco2(10,10);
    struct Torre3 *raizT3 = crearDisco3(10,10);
    insertar1(raizT1, 3, 2);
    insertar1(raizT1, 2, 3);
    insertar1(raizT1, 1, 1);
    int fin = 3, op, val;
    char opc;
    bool D1T3 = false, D2T3 = false, D3T3 = false;
    do{
        ImprimirTorres(raizT1, raizT2, raizT3);
        printf("                 SELECCIONE EL DISCO: ");
        scanf(" %c",&opc);
        op = (int)opc - 48;
        if(op < 1 || op > 3){
            printf("|-----------------------------------------------------|\n");
            printf("|                 NO EXISTE ESE DISCO                 |\n");
            printf("|-----------------------------------------------------|\n");
            system("pause");
            system("cls");
        }
        else{
            if(op == 1){val = 1;}
            if(op == 2){val = 3;}
            if(op == 3){val = 2;} 
            movimientos(raizT1, raizT2, raizT3, op, val);
            D1T3 = busqueda3(raizT3, 1, 1);
            D2T3 = busqueda3(raizT3, 2, 3);
            D3T3 = busqueda3(raizT3, 3, 2);
            if(D1T3 == true && D2T3 == true && D3T3 == true){
                printf("|-----------------------------------------------------|\n");
                printf("| - - - - TORRE DE HANOI - - - Francisco Rial - - - - |\n");
                printf("|-----------------------------------------------------|\n");
                printf("|                                                     |\n");
                printf("|                                                     |\n");
                printf("|           ___           ___           ___           |\n");
                printf("|           | |           | |           | |           |\n");
                printf("|           | |           | |           | |           |\n");
                printf("|           | |           | |           | |           |\n");
                printf("|           | |           | |           | |           |\n");
                printf("|           | |           | |          [-1-]          |\n");
                printf("|           | |           | |         [--2--]         |\n");
                printf("|___________| |___________| |________[---3---]________|\n");
                printf("|_____________________________________________________|\n");
                printf("|                                                     |\n");
                printf("|-----------------------------------------------------|\n");
                printf("|                  FELICITACIONES ^^                  |\n");
                printf("|               MOVIMIENTOS MINIMOS [7]               |\n");
                if(movs >= 10){
                printf("|               MOVIMIENTOS USADOS [%d]               |\n", movs);
                }else{
                printf("|               MOVIMIENTOS USADOS [%d]                |\n", movs);}
                printf("|-----------------------------------------------------|\n");
                fin = 0;
            }
        }
    }while(fin != 0);
    system("pause");
    system("cls");
}
void modoMedio(){
    movs = 0;
    system("cls");
    struct Torre1 *raizT1 = crearDisco1(10,10);
    struct Torre2 *raizT2 = crearDisco2(10,10);
    struct Torre3 *raizT3 = crearDisco3(10,10);
    insertar1(raizT1, 4, 3);
    insertar1(raizT1, 3, 4);
    insertar1(raizT1, 2, 2);
    insertar1(raizT1, 1, 1);
    int fin = 4, op, val;
    char opc;
    bool D1T3 = false, D2T3 = false, D3T3 = false, D4T3 = false;
    do{        
        ImprimirTorres(raizT1, raizT2, raizT3);
        printf("                 SELECCIONE EL DISCO: ");
        scanf(" %c",&opc);
        op = (int)opc - 48;
        if(op < 1 || op > 4){
            printf("|-----------------------------------------------------|\n");
            printf("|                 NO EXISTE ESE DISCO                 |\n");
            printf("|-----------------------------------------------------|\n");
            system("pause");
            system("cls");
        }
        else{
            if(op == 1){val = 1;}
            if(op == 2){val = 2;}
            if(op == 3){val = 4;}
            if(op == 4){val = 3;}
            movimientos(raizT1, raizT2, raizT3, op, val);
            D1T3 = busqueda3(raizT3, 1, 1);
            D2T3 = busqueda3(raizT3, 2, 2);
            D3T3 = busqueda3(raizT3, 3, 4);
            D4T3 = busqueda3(raizT3, 4, 3);
            if(D1T3 == true && D2T3 == true && D3T3 == true && D4T3 == true){
                printf("|-----------------------------------------------------|\n");
                printf("| - - - - TORRE DE HANOI - - - Francisco Rial - - - - |\n");
                printf("|-----------------------------------------------------|\n");
                printf("|                                                     |\n");
                printf("|                                                     |\n");
                printf("|           ___           ___           ___           |\n");
                printf("|           | |           | |           | |           |\n");
                printf("|           | |           | |           | |           |\n");
                printf("|           | |           | |           | |           |\n");
                printf("|           | |           | |          [-1-]          |\n");
                printf("|           | |           | |         [--2--]         |\n");
                printf("|           | |           | |        [---3---]        |\n");
                printf("|___________| |___________| |_______[----4----]_______|\n");
                printf("|_____________________________________________________|\n");
                printf("|                                                     |\n");
                printf("|-----------------------------------------------------|\n");
                printf("|                  FELICITACIONES ^^                  |\n");
                printf("|               MOVIMIENTOS MINIMOS [15]              |\n");
                if(movs >= 10){
                printf("|               MOVIMIENTOS USADOS [%d]               |\n", movs);
                }else{
                printf("|               MOVIMIENTOS USADOS [%d]                |\n", movs);}
                printf("|-----------------------------------------------------|\n");
                fin = 0;
            }
        }
    }while(fin != 0);
    system("pause");
    system("cls");
}
void modoDificil(){
    movs = 0;
    system("cls");
    struct Torre1 *raizT1 = crearDisco1(10,10);
    struct Torre2 *raizT2 = crearDisco2(10,10);
    struct Torre3 *raizT3 = crearDisco3(10,10);
    insertar1(raizT1, 5, 3);
    insertar1(raizT1, 4, 4);
    insertar1(raizT1, 3, 5);
    insertar1(raizT1, 2, 2);
    insertar1(raizT1, 1, 1);
    int fin = 5, op, val;
    char opc;
    bool D1T3 = false, D2T3 = false, D3T3 = false, D4T3 = false, D5T3 = false;
    do{        
        ImprimirTorres(raizT1, raizT2, raizT3);
        printf("                 SELECCIONE EL DISCO: ");
        scanf(" %c",&opc);
        op = (int)opc - 48;
        if(op < 1 || op > 5){
            printf("|-----------------------------------------------------|\n");
            printf("|                 NO EXISTE ESE DISCO                 |\n");
            printf("|-----------------------------------------------------|\n");
            system("pause");
            system("cls");
        }
        else{
            if(op == 1){val = 1;}
            if(op == 2){val = 2;}
            if(op == 3){val = 5;}
            if(op == 4){val = 4;}
            if(op == 5){val = 3;} 
            movimientos(raizT1, raizT2, raizT3, op, val);
            D1T3 = busqueda3(raizT3, 1, 1);
            D2T3 = busqueda3(raizT3, 2, 2);
            D3T3 = busqueda3(raizT3, 3, 5);
            D4T3 = busqueda3(raizT3, 4, 4);
            D5T3 = busqueda3(raizT3, 5, 3);
            if(D1T3 == true && D2T3 == true && D3T3 == true && D4T3 == true && D5T3 == true){
                printf("|-----------------------------------------------------|\n");
                printf("| - - - - TORRE DE HANOI - - - Francisco Rial - - - - |\n");
                printf("|-----------------------------------------------------|\n");
                printf("|                                                     |\n");
                printf("|                                                     |\n");
                printf("|           ___           ___           ___           |\n");
                printf("|           | |           | |           | |           |\n");
                printf("|           | |           | |           | |           |\n");
                printf("|           | |           | |          [-1-]          |\n");
                printf("|           | |           | |         [--2--]         |\n");
                printf("|           | |           | |        [---3---]        |\n");
                printf("|           | |           | |       [----4----]       |\n");
                printf("|___________| |___________| |______[-----5-----]______|\n");
                printf("|_____________________________________________________|\n");
                printf("|                                                     |\n");
                printf("|-----------------------------------------------------|\n");
                printf("|                  FELICITACIONES ^^                  |\n");
                printf("|               MOVIMIENTOS MINIMOS [31]              |\n");
                if(movs >= 10){
                printf("|               MOVIMIENTOS USADOS [%d]               |\n", movs);
                }else{
                printf("|               MOVIMIENTOS USADOS [%d]                |\n", movs);}
                printf("|-----------------------------------------------------|\n");
                fin = 0;
            }
        }
    }while(fin != 0);
    system("pause");
    system("cls");
}
//-------------------------------------------------------

//-------------------------------------------------------
//Funcion de eleccion de dificultad
void jugar(){
    char op;
    do{
        system("cls");
        printf("|-----------------------------------------------------|\n");
        printf("| - - - - TORRE DE HANOI - - - Francisco Rial - - - - |\n");
        printf("|-----------------------------------------------------|\n");
        printf("|                                                     |\n");
        printf("|         [FACIL]       [MEDIO]      [DIFICIL]        |\n");
        printf("|           ___           ___           ___           |\n");
        printf("|           | |           | |           | |           |\n");
        printf("|           | |           | |           | |           |\n");
        printf("|           | |           | |          [-1-]          |\n");
        printf("|           | |          [-1-]        [--2--]         |\n");
        printf("|          [-1-]        [--2--]      [---3---]        |\n");
        printf("|         [--2--]      [---3---]    [----4----]       |\n");
        printf("|________[---3---]____[----4----]__[-----5-----]______|\n");
        printf("|_____________________________________________________|\n");
        printf("|                                                     |\n");
        printf("|-----------------------------------------------------|\n");
        printf("|                 ELIJA LA DIFICULTAD                 |\n");
        printf("|               1: MODO FACIL[3 DISCOS]               |\n");
        printf("|               2: MODO MEDIO[4 DISCOS]               |\n");
        printf("|              3: MODO DIFICIL[5 DISCOS]              |\n");
        printf("|                     4: CANCELAR                     |\n");
        printf("|-----------------------------------------------------|\n");
        scanf(" %c",&op);
        switch(op){ 
            case '1':
                printf("|-----------------------------------------------------|\n");
                printf("|               INICIANDO MODO FACIL...               |\n");
                printf("|-----------------------------------------------------|\n");
                system("pause");
                modoFacil();
                op = '4';
                break;
            case '2':
                printf("|-----------------------------------------------------|\n");
                printf("|               INICIANDO MODO MEDIO...               |\n");
                printf("|-----------------------------------------------------|\n");
                system("pause");
                modoMedio();
                op = '4';
                break;
            case '3':
                printf("|-----------------------------------------------------|\n");
                printf("|              INICIANDO MODO DIFICIL...              |\n");
                printf("|-----------------------------------------------------|\n");
                system("pause");
                modoDificil();
                op = '4';
                break;
            case '4':
                printf("|-----------------------------------------------------|\n");
                printf("|                  VOLVIENDO AL MENU                  |\n");
                printf("|-----------------------------------------------------|\n");
                system("pause");
                break;
            default:
                printf("|-----------------------------------------------------|\n");
                printf("|                   OPCION INVALIDA                   |\n");
                printf("|-----------------------------------------------------|\n");
                system("pause");
                break;
        }
    }while(!((int)op == 52));
}
//-------------------------------------------------------

//------------------------------------------------------------------------------------
//Funcion main del juego
int main (int argc, char *argv[]){
    char op;
    do{
        printf("|-----------------------------------------------------|\n");
        printf("| - - - - TORRE DE HANOI - - - Francisco Rial - - - - |\n");
        printf("|-----------------------------------------------------|\n");
        printf("|                                                     |\n");
        printf("|                                                     |\n");
        printf("|           ___           ___           ___           |\n");
        printf("|           | |           | |           | |           |\n");
        printf("|           | |           | |           | |           |\n");
        printf("|           | |           | |           | |           |\n");
        printf("|           | |           | |           | |           |\n");
        printf("|           | |           | |           | |           |\n");
        printf("|           | |           | |           | |           |\n");
        printf("|___________| |___________| |___________| |___________|\n");
        printf("|_____________________________________________________|\n");
        printf("|                                                     |\n");
        printf("|-----------------------------------------------------|\n");
        printf("|                SELECCIONE UNA OPCION                |\n");
        printf("|                       1 JUGAR                       |\n");
        printf("|                2 REGLAS Y COMO JUGAR                |\n");
        printf("|                  3 SALIR DEL JUEGO                  |\n");
        printf("|-----------------------------------------------------|\n");
        scanf(" %c",&op);
        switch (op)
        {
        case '1':
            system("pause");
            jugar();
            break;
        case '2':
            system("pause");
            ComoJugar();
            break;
        case '3':
            printf("|-----------------------------------------------------|\n");
            printf("|          CERRANDO JUEGO. TENGA BUEN DIA :)          |\n");
            printf("|-----------------------------------------------------|\n");
            system("pause");
            break;
        default:
            printf("|-----------------------------------------------------|\n");
            printf("|             OPCION INGRESADA INCORRECTA             |\n");
            printf("|-----------------------------------------------------|\n");
            system("pause");
            break;
        }
        system("cls");
    }while(!((int)op == 51));
    return 0;
}
//------------------------------------------------------------------------------------