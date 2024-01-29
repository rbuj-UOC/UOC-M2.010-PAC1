/* 
 * File:   fitxers.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "fitxers.h"

FILE *obrir_fitxer(char *any, const char *desc) {
    size_t width = strlen(any) + strlen(desc);
    char *nom_fitxer = (char *) malloc((width + 1) * sizeof (char));
    strcpy(nom_fitxer, any);
    strcat(nom_fitxer, desc);
    return fopen(nom_fitxer, "rt");
}

FILE *crear_fitxer(char *any, const char *desc) {
    size_t width = strlen(any) + strlen(desc);
    char *nom_fitxer = (char *) malloc((width + 1) * sizeof (char));
    strcpy(nom_fitxer, any);
    strcat(nom_fitxer, desc);
    return fopen(nom_fitxer, "wt");
}

/* llegeix una línia (byref) d'un fitxer, retorna l'ultim caràcter llegit.
 */
int llegir_linia(FILE *fp, char **linia, int *longitud) {
    char ch;
    char *temporal = (char *) alloca(sizeof (char) * 1024);
    char *cursor = temporal;

    *longitud = 0;
    ch = (char) fgetc(fp);
    while ((ch != EOF) && (ch != 13) && (ch != 10)) {
        *cursor = ch;
        cursor++;
        *longitud = *longitud + 1;
        ch = (char) fgetc(fp);
    }
    if (*longitud > 0) {
        *cursor = '\0';
        *linia = strdup(temporal);
    }
    cursor = NULL;
    return ch;
}

