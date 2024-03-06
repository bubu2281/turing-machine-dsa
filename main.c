/* STEFAN Alexandru - 315CB */

#include <stdio.h>
#include <stdlib.h>
#include "functii.h"
#include <string.h>

int main() {
    FILE *input = fopen("tema1.in","rt");
    FILE *output = fopen("tema1.out","wt");

    //initializarea benzii
    TBanda2 banda = malloc(sizeof(TEl2));
    banda->list = InitL();
    banda->finger = &(banda->list->next);

    TCoada coadaOp = InitQ();
    int num_op;
    TStiva undo_stiva = NULL, redo_stiva = NULL;

    //adaugam in stiva pentru undo pozitia initiala a degetului in caz de se apeleaza UNDO
    //dupa prima operatie ce modifica pozitia degetului
    AddS(&undo_stiva, banda->finger);

    fscanf(input, "%d", &num_op);
    for(int i = 0; i < num_op; i++) {
        char aux_op[30];
        /*am folosit in cadrul fscanf-ului parametrul "%s ", pentru a citi doar primul cuvant de
        pe linie. Spre exemplu daca pe linie se afla SHOW, atunci fscanf va citi doar atat, in schimb
        daca avem WRITE $, acesta va citi doar "WRITE", iar cursorul va ramane inainte de "$" urmand
        ca in functia AddOpQ sa se citeasca si simbolul.*/
        fscanf(input, "%s ", aux_op);
        AddOpQ(&coadaOp, ConvertOp(aux_op), input, output, &banda, &undo_stiva, &redo_stiva);
    }
    DestroyS(&undo_stiva);
    DestroyS(&redo_stiva);
    DestroyQ(&coadaOp);
    DestroyL(&(banda->list));
    free(banda);
    fclose(input);
    fclose(output);
    return 0;
}