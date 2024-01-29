/* 
 * File:   propietari_llista.h
 * Author: robert
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef PROPIETARI_LLISTA_H
#define	PROPIETARI_LLISTA_H

#include "propietari_node.h"

typedef struct llista_propietaris_s {
    ptr_node_propietari_t punter;
    node_propietari_t *node_fantasma_esquerra;
    node_propietari_t *node_fantasma_dreta;
    unsigned long numelem;
} llista_propietaris_t;

void llista_propietaris_crear_llista(llista_propietaris_t *llista);
void llista_propietaris_netejar_llista(llista_propietaris_t *llista);
void llista_propietaris_destrueix_llista(llista_propietaris_t *llista);

void llista_propietaris_afegir_node(llista_propietaris_t *llista, char **nom, char **email, unsigned long idPropietari);
void llista_propietaris_eliminar_id(llista_propietaris_t *llista, unsigned long idPropietari);
void llista_propietaris_eliminar_node(llista_propietaris_t *llista, node_propietari_t *node);

bool llista_propietaris_esta_buida(llista_propietaris_t llista);
bool llista_propietaris_troba_idPropietari(llista_propietaris_t llista, unsigned long idPropietari, ptr_node_propietari_t *iterador);
bool llista_propietaris_existeix_idPropietari(llista_propietaris_t llista, unsigned long idPropietari);
void llista_propietaris_cerca_idPropietari(llista_propietaris_t llista, unsigned long idPropietari, ptr_node_propietari_t *iterador);

void llista_propietaris_fusiona(llista_propietaris_t *llista_desti, llista_propietaris_t *llista_origen);

#endif	/* PROPIETARI_LLISTA_H */

