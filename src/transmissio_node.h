/* 
 * File:   transmissio_node.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef TRANSMISSIO_NODE_H
#define	TRANSMISSIO_NODE_H

#include "registre_llista.h"
#include "dia.h"

typedef struct node_transmissio_s {
    unsigned long idPropietariAnterior;
    char *motiu;
    dia_t data_transmissio;
    llista_registres_t llista_registres;
    struct node_transmissio_s *anterior;
    struct node_transmissio_s *seguent;
} node_transmissio_t, *ptr_node_transmissio_t;

bool node_transmissio_ultim(node_transmissio_t node);
bool node_transmissio_primer(node_transmissio_t node);
node_transmissio_t *node_transmissio_seguent(node_transmissio_t node);
node_transmissio_t *node_transmissio_anterior(node_transmissio_t node);
node_transmissio_t *node_transmissio_crear(unsigned long idPropietariAnterior, dia_t data_transmissio, char **motiu);
void node_transmissio_alliberar_node(node_transmissio_t *node);

void node_transmissio_afegir_registre(node_transmissio_t *node, unsigned long idPropietat);
void node_transmissio_eliminar_registre(node_transmissio_t *node, unsigned long idPropietat);
void node_transmissio_eliminar_registres(node_transmissio_t *node);

void node_transmissio_afegir_participacio_registre(node_transmissio_t *node, unsigned long idPropietat, unsigned long idPropietari, fraccio_t participacio);
void node_transmissio_eliminar_participacio_registre(node_transmissio_t *node, unsigned long idPropietat, unsigned long idPropietari);
void node_transmissio_eliminar_participacions_registre(node_transmissio_t *node, unsigned long idPropietat);

void node_transmissio_verifica(node_transmissio_t *node);

#endif	/* TRANSMISSIO_NODE_H */

