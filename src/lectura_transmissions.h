/* 
 * File:   lectura_transmissions.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef LECTURA_TRANSMISSIONS_H
#define	LECTURA_TRANSMISSIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fitxers.h"
#include "linies.h"
#include "propietari_llista.h"
#include "transmissio_llista.h"

void lectura_transmissions(llista_propietaris_t *llista,  llista_transmissions_t *llista_transmissions, char* any);
void tractar_propietari_linia_transmissions(llista_propietaris_t *llista, char *linia, bool *tractament_propietaris, bool *tractament_transmissions);
void tractar_transmissio_linia_transmissions(llista_transmissions_t *llista, char *linia, bool *tractament_propietaris, bool *tractament_transmissions, unsigned long *idPropietariAnterior, dia_t *data_transmissio);
void netejar_memoria_transmissions(llista_propietaris_t *llista_propietaris, llista_transmissions_t *llista_transmissions);


#endif	/* LECTURA_TRANSMISSIONS_H */

