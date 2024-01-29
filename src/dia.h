/* 
 * File:   dia.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef DIA_H
#define	DIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dia_s{
    unsigned int dia;
    unsigned int mes;
    unsigned int any;
} dia_t;

void text2dia(char *text, dia_t *dia);
void dia_copia(dia_t *dia_desti, dia_t dia_origen);
void dia_assigna(dia_t *dia_desti, unsigned int dia, unsigned int mes, unsigned int any);

#endif	/* DIA_H */

