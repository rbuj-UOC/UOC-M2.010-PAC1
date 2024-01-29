/* 
 * File:   linies.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef LINIES_H
#define	LINIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "boolean.h"

size_t elimina_caracter_linia(char **linia, size_t posi);
size_t formateja_linia(char **linia);
bool formateja_linia_inici(char **linia);
bool formateja_linia_espais(char **linia);
bool formateja_linia_tabuladors(char **linia);
bool linia_igual(char *linia, const char* cadena);

#endif	/* LINIES_H */

