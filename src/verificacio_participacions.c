/* 
 * File:   verificacio_participacions.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "verificacio_participacions.h"

void verificacio_participacions(llista_propietats_t llista_propietats, llista_transmissions_t llista_transmissions) {
    llista_propietats_verifica(llista_propietats);
    llista_transmissions_verifica(llista_transmissions);
}
