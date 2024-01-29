/* 
 * File:   dia.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "dia.h"
/* Converteix un text sense espais a una fraccio
 */
void text2dia(char *text, dia_t *dia) {
    char *p_start = text, *p_end = NULL;
    char *temp;
    size_t start, end, width;
    /*
     * any
     */
    p_end = strstr(p_start, "-");
    start = strlen(p_start);
    end = strlen(p_end);
    width = start - end;
    temp = (char *) malloc(sizeof (char) * (width + 1));
    strncpy(temp, p_start, width);
    temp[width] = '\0';
    (*dia).any = (unsigned int) atoi(temp);
    free((char *) temp);
    temp = NULL;
    /*
     * mes
     */
    p_start = p_end + 1;
    p_end = strstr(p_start, "-");
    start = strlen(p_start);
    end = strlen(p_end);
    width = start - end;
    temp = (char *) malloc(sizeof (char) * (width + 1));
    strncpy(temp, p_start, width);
    temp[width] = '\0';
    (*dia).mes = (unsigned int) atoi(temp);
    free((char *) temp);
    temp = NULL;
    /*
     * dia
     */
    p_start = p_end + 1;
    width = strlen(p_start);
    temp = (char *) malloc(sizeof (char) * (width + 1));
    strncpy(temp, p_start, width);
    (*dia).dia = (unsigned int) atoi(temp);
    free((char *) temp);
}

void dia_copia(dia_t *dia_desti, dia_t dia_origen) {
    (*dia_desti).dia = dia_origen.dia;
    (*dia_desti).mes = dia_origen.mes;
    (*dia_desti).any = dia_origen.any;
}

void dia_assigna(dia_t *dia_desti, unsigned int dia, unsigned int mes, unsigned int any) {
    (*dia_desti).dia = dia;
    (*dia_desti).mes = mes;
    (*dia_desti).any = any;
}
