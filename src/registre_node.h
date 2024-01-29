/* 
 * File:   registre_node.h
 * Author: robert
 *
 * Created on 31 / octubre / 2011, 15:48
 */

#ifndef REGISTRE_NODE_H
#define	REGISTRE_NODE_H

#include "participacio_llista.h"

typedef struct node_registre_s {
    unsigned long idPropietat;
    llista_participacions_t llista_participacions;
    struct node_registre_s *anterior;
    struct node_registre_s *seguent;
} node_registre_t, *ptr_node_registre_t;

bool node_registre_ultim(node_registre_t node);
bool node_registre_primer(node_registre_t node);
node_registre_t *node_registre_seguent(node_registre_t node);
node_registre_t *node_registre_anterior(node_registre_t node);
node_registre_t *node_registre_crear(unsigned long idPropietat);
void node_registre_alliberar_node(node_registre_t *node);
void node_registre_afegir_particio(node_registre_t *node, fraccio_t fraccio, unsigned long idPropietari);
void node_registre_eliminar_particio(node_registre_t *node, unsigned long idPropietari);
void node_registre_eliminar_particions(node_registre_t *node);

void node_registre_verifica(node_registre_t *node, unsigned long idPropietariAnterior);

#endif	/* REGISTRE_NODE_H */

