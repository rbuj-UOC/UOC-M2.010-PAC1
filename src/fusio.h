/* 
 * File:   fusio.h
 * Author: robert
 *
 * Created on 1 / novembre / 2011, 19:04
 */

#ifndef FUSIO_H
#define	FUSIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "propietari_llista.h"
#include "propietat_llista.h"
#include "transmissio_llista.h"
#include "fitxers.h"

void fusio(char *any, llista_propietaris_t *llista_propietaris, llista_propietaris_t *llista_propietaris_nous, llista_propietats_t *llista_propietats, llista_transmissions_t *llista_transmissions);
void fusio_propietaris(llista_propietaris_t *llista_propietaris, llista_propietaris_t *llista_propietaris_nous);
void fusio_participacions(llista_propietats_t *llista_propietats, llista_transmissions_t llista_transmissions);
void fusio_propietaris_propietats(llista_propietaris_t *llista_propietaris, llista_propietats_t llista_propietats);
void fusio_fitxer(char *any, llista_propietaris_t llista_propietaris, llista_propietats_t llista_propietats);
void fusio_fitxer_propietats(FILE *fp, llista_propietats_t llista);
void fusio_fitxer_propietaris(FILE *fp, llista_propietaris_t llista);

#endif	/* FUSIO_H */
