/* 
 * File:   participacio_llista.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef PARTICIPACIO_LLISTA_H
#define	PARTICIPACIO_LLISTA_H

#include "participacio_node.h"

typedef struct llista_participacions_s {
    ptr_node_participacio_t ptr_node_participacio;
    node_participacio_t *node_fantasma_esquerra;
    node_participacio_t *node_fantasma_dreta;
    unsigned long numelem;
} llista_participacions_t;

void llista_participacions_crear_llista(llista_participacions_t *llista);
void llista_participacions_netejar_llista(llista_participacions_t *llista);
void llista_participacions_destrueix_llista(llista_participacions_t *llista);

void llista_participacions_afegir_node(llista_participacions_t *llista, unsigned long id, fraccio_t fraccio);
void llista_participacions_eliminar_id(llista_participacions_t *llista, unsigned long id);
void llista_participacions_eliminar_node(llista_participacions_t *llista, node_participacio_t *node);

bool llista_participacions_esta_buida(llista_participacions_t llista);
bool llista_participacions_existeix_id(llista_participacions_t llista, unsigned long id);
void llista_participacions_cerca_id(llista_participacions_t llista, unsigned long id, ptr_node_participacio_t *iterador);
bool llista_participacions_troba_id(llista_participacions_t llista, unsigned long id, ptr_node_participacio_t *iterador);

fraccio_t llista_participacions_suma_participacions(llista_participacions_t llista);
void llista_participacions_verifica(llista_participacions_t llista, operacio op, unsigned long identificadors[], int num_identificadors);

#endif	/* PARTICIPACIO_LLISTA_H */

