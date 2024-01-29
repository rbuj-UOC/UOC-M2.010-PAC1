/* 
 * File:   fraccio.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef FRACCIO_H
#define	FRACCIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fraccio_s{
    unsigned long numerador;
    unsigned long denominador;
} fraccio_t;

void text2fraccio(char *text, fraccio_t *fraccio);
void fraccio_copia(fraccio_t *traccio_desti, fraccio_t fraccio_origen);
void fraccio_assigna(fraccio_t *traccio_desti, unsigned long numerador, unsigned long denominador);
void fraccio_suma(fraccio_t *fraccio_desti, fraccio_t fraccio_a, fraccio_t fraccio_b);
void fraccio_multiplica(fraccio_t *fraccio_desti, fraccio_t fraccio_a, fraccio_t fraccio_b);
void fraccio_simplifica(fraccio_t *fraccio_desti);
void fraccio_simplifica_factor(fraccio_t *fraccio_desti, unsigned long factor);
bool fraccio_unitat(fraccio_t fraccio);

#endif	/* FRACCIO_H */

