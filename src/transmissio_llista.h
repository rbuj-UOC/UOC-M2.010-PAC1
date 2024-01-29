/* 
 * File:   transmissio_llista.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef TRANSMISSIO_LLISTA_H
#define	TRANSMISSIO_LLISTA_H


#include "transmissio_node.h"

typedef struct llista_transmissions_s {
    ptr_node_transmissio_t punter;
    node_transmissio_t *node_fantasma_esquerra;
    node_transmissio_t *node_fantasma_dreta;
    unsigned long numelem;
} llista_transmissions_t;

void llista_transmissions_crear_llista(llista_transmissions_t *llista);
void llista_transmissions_netejar_llista(llista_transmissions_t *llista);
void llista_transmissions_destrueix_llista(llista_transmissions_t *llista);
bool llista_transmissions_esta_buida(llista_transmissions_t llista);
void llista_transmissions_afegir_node(llista_transmissions_t *llista, unsigned long idPropietariAnterior, dia_t data_transmissio, char **motiu);
void llista_transmissions_eliminar_id(llista_transmissions_t *llista, unsigned long idPropietariAnterior, dia_t data_transmissio);
void llista_transmissions_eliminar_node(llista_transmissions_t *llista, node_transmissio_t *node);
void llista_transmissions_cercar(llista_transmissions_t llista, unsigned long idPropietariAnterior, dia_t data_transmissio, ptr_node_transmissio_t *iterador);
bool llista_transmissions_troba_idPropietariAnterior(llista_transmissions_t llista, unsigned long idPropietariAnterior, dia_t data_transmissio, ptr_node_transmissio_t *iterador);
bool llista_transmissions_existeix(llista_transmissions_t llista, unsigned long idPropietariAnterior, dia_t data_transmissio);
/*
 * Registres
 */
void llista_transmissions_afegir_registre_node(llista_transmissions_t llista, unsigned long idPropietariAnterior, dia_t data_transmissio, unsigned long idPropietat);
void llista_transmissions_eliminar_registre_node(llista_transmissions_t llista, unsigned long idPropietariAnterior, dia_t data_transmissio, unsigned long idPropietat);
/*
 * Participacions
 */
void llista_transmissions_afegir_particio_registre_node(llista_transmissions_t llista, unsigned long idPropietariAnterior, dia_t data_transmissio, unsigned long idPropietat, unsigned long idNouPropietari, fraccio_t participacio);

void llista_transmissions_verifica(llista_transmissions_t llista);

#endif	/* TRANSMISSIO_LLISTA_H */

