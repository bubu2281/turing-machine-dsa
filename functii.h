/* STEFAN Alexandru - 315CB */

#include <stdio.h>

//Asignarea unui cod fiecarei operatii 
#define move_left '1'
#define move_right '2'
#define move_left_char '3'
#define move_right_char '4'
#define write '5'
#define insert_left '6'
#define insert_right '7'
#define execute '8'
#define show '9'
#define show_current 'A'
#define undo 'B'
#define redo 'C'

typedef struct banda {
    char info;
    struct banda *prev, *next;
}*TBanda, TElement;

typedef struct banda2 {
    TBanda list;
    TBanda *finger;
}*TBanda2, TEl2;

typedef struct coada {
    TBanda start, finish;
}*TCoada, TElCoada;

typedef struct stiva {
    TBanda *info;
    struct stiva *next;
}*TStiva, TElStiva;

//Functii pentru lista
TBanda InitL();                                            
void AddL(TBanda *banda);                                 
void PrintL(TBanda banda, TBanda *deget, FILE *output);     
void DestroyL(TBanda *banda);                               

//Functii pentru Coada
TCoada InitQ();
void AddQ(TCoada *coada, char x);
void PrintQ(TCoada coada, FILE *output);
void DestroyQ(TCoada *coada);
void ExtrQ(TCoada *coada, char *x);

//Functii pentru stiva
void AddS(TStiva *s, TBanda *poz);
void ExtrS(TStiva *s, TBanda **poz);
void PrintS(TStiva s, FILE *output);
void DestroyS(TStiva *s);

//Functii pentru  prelucrarea benzii
int MOVE_LEFT(TBanda2 *B);
void MOVE_RIGHT(TBanda2 *B);
void MOVE_LEFT_CHAR(TBanda2 *B, char ch, FILE *output);
void MOVE_RIGHT_CHAR(TBanda2 *B, char ch);
void WRITE (TBanda2 *B, char ch);
void INSERT_LEFT(TBanda2 *B, char ch, FILE *output);
void INSERT_RIGHT(TBanda2 *B, char ch);
void SHOW(TBanda2 *B, FILE *output);
void SHOW_CURRENT(TBanda2 *B, FILE *output);
void UNDO(TBanda2 *b, TStiva *undo_stiva, TStiva *redo_stiva);
void REDO(TBanda2 *b, TStiva *undo_stiva, TStiva *redo_stiva);
void EXECUTE(TBanda2 *B, TCoada *coadaOP, FILE *output, TStiva *undo_stiva);

char ConvertOp(char *op); //Functie ce converteste operatiile(string) in codul aferent lor
void AddOpQ(TCoada *coada, char op, FILE *input, FILE *output, TBanda2 *banda, TStiva *undo_stiva, TStiva *redo_stiva);