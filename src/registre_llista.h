/* 
 * File:   registre_llista.h
 * Author: robert
 *
 * Created on 31 / octubre / 2011, 15:48
 */

#ifndef REGISTRE_LLISTA_H
#define	REGISTRE_LLISTA_H

#include "registre_node.h"

typedef struct llista_registres_s {
    ptr_node_registre_t punter;
    node_registre_t *node_fantasma_esquerra;
    node_registre_t *node_fantasma_dreta;
    unsigned long numelem;
} llista_registres_t;

void llista_registres_crear_llista(llista_registres_t *llista);
void llista_registres_netejar_llista(llista_registres_t *llista);
void llista_registres_destrueix_llista(llista_registres_t *llista);

void llista_registres_afegir_node(llista_registres_t *llista, unsigned long idPropietat);
void llista_registres_eliminar_id(llista_registres_t *llista, unsigned long idPropietat);
void llista_registres_eliminar_node(llista_registres_t *llista, node_registre_t *node);

bool llista_registres_esta_buida(llista_registres_t llista);
bool llista_registres_existeix_idPropietat(llista_registres_t llista, unsigned long idPropietat);
void llista_registres_cercar_idPropietat(llista_registres_t llista, unsigned long idPropietat, ptr_node_registre_t *iterador);
bool llista_registres_troba_idPropietat(llista_registres_t llista, unsigned long idPropietat, ptr_node_registre_t *iterador);


void llista_registres_afegir_participacio_node(llista_registres_t llista, unsigned long idPropietat, unsigned long idPropietari, fraccio_t participacio);
void llista_registres_eliminar_participacio_node(llista_registres_t llista, unsigned long idPropietat, unsigned long idPropietari);



void llista_registres_verifica(llista_registres_t llista, unsigned long idPropietariAnterior);

#endif	/* REGISTRE_LLISTA_H */

