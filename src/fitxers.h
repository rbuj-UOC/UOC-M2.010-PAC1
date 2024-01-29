/* 
 * File:   fitxers.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef FITXERS_H
#define	FITXERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "boolean.h"

FILE *obrir_fitxer(char *any, const char *desc);
FILE *crear_fitxer(char *any, const char *desc);
int llegir_linia(FILE *fp, char **linia, int *longitud);

#endif	/* FITXERS_H */

