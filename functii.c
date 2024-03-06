/* STEFAN Alexandru - 315CB */

#include "functii.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//alocare banda cu santinela si punerea caracterului # pe primul nod
TBanda InitL() {
    TBanda banda =  malloc(sizeof(TElement));
    if(!banda) {
        return NULL;
    }
    banda->next = malloc(sizeof(TElement));
    if(!banda->next) {
        free(banda);
        return NULL;
    }
    banda->prev = NULL;
    banda->next->info = '#';
    banda->next->next = NULL;
    banda->next->prev = banda;
    return banda;
}

//adaugare celula in banda, implicit cu # la info
void AddL(TBanda *banda) {
    TBanda aux = *banda;
    while(aux->next != NULL) {
        aux = aux->next;
    }
    TBanda celula = malloc(sizeof(TElement));
    aux->next = celula;
    celula->prev = aux;
    celula->next = NULL;
    celula->info = '#';
}

//printeaza banda, luand in considerare poziia degetului
//ar putea fi implementata si doar cu un singur parametru de tip TBanda2,
//dar am scris-o inainte de a declara structura ce contine atat banda cat si degetul
void PrintL(TBanda banda, TBanda *deget, FILE *output) {
    if(banda == NULL) {
        fprintf(output, "VID (NULL)\n");
        return;
    }
    if(banda->next != NULL) {
        banda = banda->next;
    }
    while(banda) {
        if(deget == NULL || banda != *deget){
            fprintf(output, "%c", banda->info);
        } else {
            fprintf(output, "|%c|", banda->info);
        }
        banda = banda->next;
    }
    fprintf(output, "\n");
}

//dezalocare memorie banda
void DestroyL(TBanda *banda) {
    TBanda aux = *banda;
    *banda = (*banda)->next;
    while(*banda) {
        free(aux);
        aux = *banda;
        *banda = (*banda)->next;
    }
    free(aux);
    *banda = NULL;
}

//initializare coada
TCoada InitQ() {
        TCoada c;
    c = (TCoada)malloc(sizeof(TElCoada));
    if ( ! c ) return NULL;

    c->start = c->finish = NULL;
    return c;
}

//adauga nod in coada cu nod->info = x
void AddQ(TCoada *coada, char x) {
        TBanda aux;
    aux = (TBanda)malloc(sizeof(TElement));
    if ( ! aux) return;

    aux->info = x; aux->next = NULL;

    if ((*coada)->finish != NULL)
        (*coada)->finish->next = aux;
    else                            
        (*coada)->start = aux;
    (*coada)->finish = aux;  	            
    return;
}

//afiseaza elementele cozii
//nu este apelata in varianta finala a temei, dar m-am folosit de ea
//pe parcurs pentru a face debugging, mai exact sa vizualizez coada, ca sa imi
//dau seama cum se comporta
void PrintQ(TCoada coada, FILE *output) {
    TBanda santinela = coada->start;
    if(coada->start == NULL) {
        fprintf(output, "VID (NULL)\n");
        return;
    }
    while(coada->start) {
        fprintf(output, "%c", coada->start->info);
        coada->start = coada->start->next;
    }
    fprintf(output, "\n");
    coada->start = santinela;
}

//dezalocare memorie coada
void DestroyQ(TCoada *coada) {
    TBanda p, aux;
    p = (*coada)->start;
    while(p)
    {
        aux = p;
        p = p->next;
        free(aux);
    }
    free(*coada);
    *coada = NULL;
}

//extragere element din coada si retinere in var x
void ExtrQ(TCoada *coada, char *x) {
    if((*coada)->start->next == NULL) {
        TBanda aux = (*coada)->start;
        *x = aux->info;
        free(aux);
        (*coada)->start = NULL;
        (*coada)->finish = NULL;
        return;
    }
    if ((*coada)->start) {
        *x = (*coada)->start->info;
        TBanda aux = (*coada)->start;
        (*coada)->start = (*coada)->start->next;
        free(aux);
        return;
        } else {
        return;
        }
}

//adaugare element in stiva
void AddS(TStiva *s, TBanda *poz) {
    TStiva aux = malloc(sizeof(TElStiva));
    aux->next = (*s);
    aux->info = poz;
    (*s) = aux;
}

//distrugere stiva
void DestroyS(TStiva *s) {
    while((*s)) {
        TStiva aux = (*s);
        (*s) = (*s)->next;
        free(aux); 
    }
}

//extragere element din stiva
void ExtrS(TStiva *s, TBanda **poz) {
    (*poz) = (*s)->info;
    TStiva aux = (*s);
    (*s) = (*s)->next;
    free(aux);
}

//afiseaza stiva
//la fel ca la afiseaza coada, m-am folosit de ea pentru a faace debugging
void PrintS(TStiva s, FILE *output) {
    while(s) {
        fprintf(output, "%c ", (*(s->info))->info);
        s = s->next;
    }
    fprintf(output, "\n");
}


int MOVE_LEFT(TBanda2 *B) {
    /*verifica daca degetul se afla pe prima pozitia a benzii*/
    if( (*((*B)->finger))->prev->prev == NULL ) {
        return 0;
    }
    (*B)->finger = &( ( *( (*B)->finger ) )->prev );
    return 1;
}

void MOVE_RIGHT(TBanda2 *B) {
    if ( (*((*B)->finger))->next == NULL ) {
        AddL(&(*B)->list);
    }
    (*B)->finger = &((*((*B)->finger))->next);
}

void MOVE_LEFT_CHAR(TBanda2 *B, char ch, FILE *output) {
    TBanda *aux = (*B)->finger;
    while( ((*aux)->prev->prev != NULL ) && (*aux)->info != ch ) {
        aux = &(*aux)->prev;
    }
    if( (*aux)->info == ch ) {
        (*B)->finger = aux;
        return;
    }
    if((*aux)->prev->prev == NULL) {
        fprintf(output,"ERROR\n");
        return;
    }
}

void MOVE_RIGHT_CHAR(TBanda2 *B, char ch) {
    TBanda *aux = (*B)->finger;
    while( ((*aux)->next != NULL ) && (*aux)->info != ch ) {
        aux = &(*aux)->next;
    }
    if( (*aux)->info == ch ) {
        (*B)->finger = aux;
        return;
    }
    if( (*aux)->next == NULL ) {
        AddL(&(*B)->list);
        (*B)->finger = &(*aux)->next;
        return;
    }
}

void WRITE (TBanda2 *B, char ch) {
    (*((*B)->finger))->info = ch;
}

void INSERT_LEFT(TBanda2 *B, char ch, FILE *output) {
    if( (*((*B)->finger))->prev->prev == NULL ) {
        fprintf(output, "ERROR\n");
        return;
    }
    TBanda nod = malloc(sizeof(TElement));
    nod->info = ch;
    nod->next = (*((*B)->finger));
    nod->prev = (*((*B)->finger))->prev;
    (*((*B)->finger))->prev->next = nod;
    nod->next->prev = nod;
    (*B)->finger = &(nod->prev->next);
}

void INSERT_RIGHT(TBanda2 *B, char ch) {
    if( (*((*B)->finger))->next == NULL ) {
        AddL(&(*B)->list);
        (*((*B)->finger))->next->info = ch;
        (*B)->finger = &(*((*B)->finger))->next;
        return;
    }
    TBanda nod = malloc(sizeof(TElement));
    nod->info = ch;
    nod->next = (*((*B)->finger))->next;
    nod->prev = (*((*B)->finger));
    (*((*B)->finger))->next->prev = nod;
    nod->prev->next = nod;
    (*B)->finger = &(nod->prev->next);
}

void SHOW(TBanda2 *B, FILE *output) {
    PrintL((*B)->list, (*B)->finger, output);
}

void SHOW_CURRENT(TBanda2 *B, FILE *output) {
    fprintf(output, "%c\n", (*((*B)->finger))->info);
}

void UNDO(TBanda2 *b, TStiva *undo_stiva, TStiva *redo_stiva) {
    TBanda *aux;
    TBanda *poz = &(*((*b)->finger));
    ExtrS(undo_stiva, &aux);
    AddS(redo_stiva, poz);
    (*b)->finger = aux;
}

void REDO(TBanda2 *b, TStiva *undo_stiva, TStiva *redo_stiva) {
    TBanda *aux;
    TBanda *poz = &(*((*b)->finger));
    ExtrS(redo_stiva, &aux);
    AddS(undo_stiva, poz);
    (*b)->finger = aux;
}

/*in functia EXECUTE, m-am folosit de un switch pentru fiecare operatie din coada
In coada am retinut atat operatia in sine cat si parametrul ei, adica daca am 
WRITE $ retin in coada separat si "WRITE" si "$". Dar pentru ca in coada
pot retine doar elemente de tip char(pentru ca asa am facut structura,
pentru simplitate), a trebuit sa convertesc fiecare operatie intr-un caracter
Adica, daca MOVE_LEFT = '1' si WRITE = '2' atunci daca apelam MOVE_LEFT si WRITE $
coada va arata asa 12$.
Cand se executa extragem operatia si verificam daca are sau nu nevoie de parametru,
in caz negativ o executam, in caz afirmativ extragem si acel parametru din coada si 
dupa apelam cu paramentrul respectiv
Codul fiecarei operatie este definit la inceputul fisierului functii.h  */
void EXECUTE(TBanda2 *B, TCoada *coadaOP, FILE *output, TStiva *undo_stiva) {
    char auxOp;
    ExtrQ(coadaOP, &auxOp);
    switch (auxOp) {
        case move_left: {
            //retinem pozitia in undo doar daca operatia s-a efectuat cu succesc
            if (MOVE_LEFT(B)) {
                AddS(undo_stiva, &((*((*B)->finger))->next));
            }
            break;
        }
        case move_right: {
            AddS(undo_stiva, (*B)->finger);
            MOVE_RIGHT(B);
            break;
        }
        case move_left_char: {
            char auxOp2;
            ExtrQ(coadaOP, &auxOp2);
            AddS(undo_stiva, (*B)->finger);
            MOVE_LEFT_CHAR(B, auxOp2, output);
            break;
        }
        case move_right_char: {
            char auxOp2;
            ExtrQ(coadaOP, &auxOp2);
            AddS(undo_stiva, (*B)->finger);
            MOVE_RIGHT_CHAR(B, auxOp2);
            break;
        }
        case write: {
            char auxOp2;
            ExtrQ(coadaOP, &auxOp2);
            WRITE(B, auxOp2);
            break;
        }
        case insert_left: {
            char auxOp2;
            ExtrQ(coadaOP, &auxOp2);
            INSERT_LEFT(B, auxOp2, output);
            break;
        }
        case insert_right: {
            char auxOp2;
            ExtrQ(coadaOP, &auxOp2);
            INSERT_RIGHT(B, auxOp2);
            break;
        }
    }
}

//functia care converteste fiecare operatie in codul ei aferent
//codurile sunt definite in functii.h
char ConvertOp(char *op) {
    if( !strcmp(op, "MOVE_LEFT") ) {
        return move_left;
    }
    if( !strcmp(op, "MOVE_RIGHT") ) {
        return move_right;
    }
    if( !strcmp(op, "MOVE_LEFT_CHAR") ) {
        return move_left_char;
    }
    if( !strcmp(op, "MOVE_RIGHT_CHAR") ) {
        return move_right_char;
    }
    if( !strcmp(op, "WRITE") ) {
        return write;
    }
    if( !strcmp(op, "INSERT_LEFT") ) {
        return insert_left;
    }
    if( !strcmp(op, "INSERT_RIGHT") ) {
        return insert_right;
    }
    if( !strcmp(op, "EXECUTE") ) {
        return execute;
    }
    if( !strcmp(op, "SHOW") ) {
        return show;
    }
    if( !strcmp(op, "SHOW_CURRENT") ) {
        return show_current;
    }
    if( !strcmp(op, "UNDO") ) {
        return undo;
    }
    if( !strcmp(op, "REDO") ) {
        return redo;
    }
}

//functia care executa pe loc operatia sau o adauga in coada impreuna cu parametrul ei(daca este cazul)
void AddOpQ(TCoada *coada, char op, FILE *input, FILE *output, TBanda2 *banda, TStiva *undo_stiva, TStiva *redo_stiva) {
    switch (op) {
        case undo: {
            UNDO(banda, undo_stiva, redo_stiva);
            break;
        }
        case redo: {
            REDO(banda, undo_stiva, redo_stiva);
            break;
        }
        case show_current: {
            SHOW_CURRENT(banda, output);
            break;
        }
        case show: {
            SHOW(banda, output);
            break;
        }
        case move_left: {
            AddQ(coada, op);
            break;
        }
        case move_right: {
            AddQ(coada, op);
            break;
        }
        case move_left_char: {
            AddQ(coada, op);
            char aux;
            fscanf(input,"%c",&aux);
            AddQ(coada, aux);
            break;
        }
        case move_right_char: {
            AddQ(coada, op);
            char aux;
            fscanf(input,"%c",&aux);
            AddQ(coada, aux);
            break;
        }
        case write: {
            AddQ(coada, op);
            char aux;
            fscanf(input,"%c",&aux);
            AddQ(coada, aux);
            break;
        }
        case insert_left: {
            AddQ(coada, op);
            char aux;
            fscanf(input,"%c",&aux);
            AddQ(coada, aux);
            break;
        }
        case insert_right: {
            AddQ(coada, op);
            char aux;
            fscanf(input,"%c",&aux);
            AddQ(coada, aux);
            break;
        }
        case execute: {
            EXECUTE(banda, coada, output, undo_stiva);
            break;
        }
    }
}