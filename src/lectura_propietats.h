/* 
 * File:   lectura_propietats.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef LECTURA_PROPIETATS_H
#define	LECTURA_PROPIETATS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fitxers.h"
#include "linies.h"
#include "propietari_llista.h"
#include "propietat_llista.h"

void lectura_propietats(llista_propietaris_t *llista_propietaris, llista_propietats_t *llista_propietats, char* any);
void tractar_propietat_linia_propietats( llista_propietats_t *llista, char *linia, bool *tractament_propietaris, bool *tractament_propietats);
void tractar_propietari_linia_propietats(llista_propietaris_t *llista, char *linia, bool *tractament_propietaris, bool *tractament_propietats);
void netejar_memoria_propietats(llista_propietaris_t *llista_propietaris, llista_propietats_t *llista_propietats);

#endif	/* LECTURA_PROPIETATS_H */

