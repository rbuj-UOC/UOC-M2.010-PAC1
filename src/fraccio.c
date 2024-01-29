/* 
 * File:   lines.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "linies.h"
#include "fraccio.h"

/* Converteix un text sense espais a una fraccio
 */
void text2fraccio(char *text, fraccio_t *fraccio) {
    char *p_start = text, *p_end = NULL;
    char *temp;
    size_t start, end, width;
    /*
     * numerador
     */
    p_end = strstr(p_start, "/");
    start = strlen(p_start);
    end = strlen(p_end);
    width = start - end;
    temp = (char *) malloc(sizeof (char) * (width + 1));
    strncpy(temp, p_start, width);
    temp[width] = '\0';
    (*fraccio).numerador = (unsigned long) atol(temp);
    free((char *) temp);
    temp = NULL;
    /*
     * denominador
     */
    p_start = p_end + 1;
    width = strlen(p_start);
    temp = (char *) malloc(sizeof (char) * (width + 1));
    strncpy(temp, p_start, width);
    (*fraccio).denominador = (unsigned long) atol(temp);
    free((char *) temp);
    temp = NULL;
    p_start = NULL;
    p_end = NULL;
    /* Comprovació
     */
    if (((*fraccio).numerador == 0) || ((*fraccio).denominador == 0)) {
        printf("Format de participació no acceptat: %s\n", text);
        exit(EXIT_FAILURE);
    }
    if ((*fraccio).numerador > (*fraccio).denominador) {
        printf("Format de participació no acceptat: %s\n", text);
        exit(EXIT_FAILURE);
    }
    /* simplificacio
     */
    fraccio_simplifica(fraccio);
}

void fraccio_copia(fraccio_t *fraccio_desti, fraccio_t fraccio_origen) {
    (*fraccio_desti).numerador = fraccio_origen.numerador;
    (*fraccio_desti).denominador = fraccio_origen.denominador;
}

void fraccio_assigna(fraccio_t *fraccio_desti, unsigned long numerador, unsigned long denominador) {
    (*fraccio_desti).numerador = numerador;
    (*fraccio_desti).denominador = denominador;
}

void fraccio_suma(fraccio_t *fraccio_desti, fraccio_t fraccio_a, fraccio_t fraccio_b) {
    (*fraccio_desti).numerador = (fraccio_a.numerador * fraccio_b.denominador)+(fraccio_b.numerador * fraccio_a.denominador);
    (*fraccio_desti).denominador = fraccio_a.denominador * fraccio_b.denominador;
    fraccio_simplifica(fraccio_desti);
}

void fraccio_multiplica(fraccio_t *fraccio_desti, fraccio_t fraccio_a, fraccio_t fraccio_b) {
    (*fraccio_desti).numerador = fraccio_a.numerador * fraccio_b.numerador;
    (*fraccio_desti).denominador = fraccio_a.denominador * fraccio_b.denominador;
    fraccio_simplifica(fraccio_desti);
}

/* simplificació pels nombres primers menors de 100
 */
void fraccio_simplifica(fraccio_t *fraccio_desti) {
    unsigned long factors[22] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89};
    int i;
    for (i = 0; i < 22; i++) {
        fraccio_simplifica_factor(fraccio_desti, factors[i]);
    }
}

void fraccio_simplifica_factor(fraccio_t *fraccio_desti, unsigned long factor) {
    while (((((*fraccio_desti).numerador) % factor) == 0) && ((((*fraccio_desti).denominador) % factor) == 0)) {
        (*fraccio_desti).numerador = (*fraccio_desti).numerador / factor;
        (*fraccio_desti).denominador = (*fraccio_desti).denominador / factor;
    }
}

bool fraccio_unitat(fraccio_t fraccio) {
    return (fraccio.numerador == fraccio.denominador) ? true : false;
}
