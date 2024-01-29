/* 
 * File:   propietat_llista.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */


#ifndef PROPIETAT_LLISTA_H
#define	PROPIETAT_LLISTA_H

#include "propietat_node.h"

typedef struct llista_propietats_s {
    ptr_node_propietat_t punter;
    node_propietat_t *node_fantasma_esquerra;
    node_propietat_t *node_fantasma_dreta;
    unsigned long numelem;
} llista_propietats_t;

void llista_propietats_crear_llista(llista_propietats_t *llista);
void llista_propietats_netejar_llista(llista_propietats_t *llista);
void llista_propietats_destrueix_llista(llista_propietats_t *llista);
bool llista_propietats_esta_buida(llista_propietats_t llista);
void llista_propietats_afegir_node(llista_propietats_t *llista, char **nom, fraccio_t fraccio, unsigned long idPropietat);
void llista_propietats_eliminar_id(llista_propietats_t *llista, unsigned long idPropietat);
void llista_propietats_eliminar_node(llista_propietats_t *llista, node_propietat_t *node);
void llista_propietats_cercar_idPropietat(llista_propietats_t llista, unsigned long idPropietat, ptr_node_propietat_t *iterador);
bool llista_propietats_troba_idPropietat(llista_propietats_t llista, unsigned long idPropietat, ptr_node_propietat_t *iterador);
bool llista_propietats_existeix_idPropietat(llista_propietats_t llista, unsigned long idPropietat);

void llista_propietats_afegir_particio_node(llista_propietats_t llista, unsigned long idPropietat, unsigned long idPropietari, fraccio_t fraccio);
void llista_propietats_eliminar_particio_node(llista_propietats_t llista, unsigned long idPropietat, unsigned long idPropietari);
fraccio_t llista_propietats_suma_participacions_generals(llista_propietats_t llista);
void llista_propietats_verifica(llista_propietats_t llista_propietats);


#endif	/* PROPIETAT_LLISTA_H */

