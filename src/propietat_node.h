/*
 * File:   propietat_node.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef PROPIETAT_NODE_H
#define	PROPIETAT_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "boolean.h"
#include "fraccio.h"
#include "participacio_llista.h"

typedef struct node_propietat_s {
    unsigned long idPropietat;
    char *nom;
    fraccio_t participacio_general;
    llista_participacions_t llista_participacions;
    struct node_propietat_s *anterior;
    struct node_propietat_s *seguent;
} node_propietat_t, *ptr_node_propietat_t;

bool node_propietat_ultim(node_propietat_t node);
bool node_propietat_primer(node_propietat_t node);
node_propietat_t *node_propietat_seguent(node_propietat_t node);
node_propietat_t *node_propietat_anterior(node_propietat_t node);
node_propietat_t *node_propietat_crear(char **nom, fraccio_t fraccio, unsigned long idPropietat);
void node_propietat_alliberar_node(node_propietat_t *node);

void node_propietat_afegir_participacio(node_propietat_t *node, fraccio_t fraccio, unsigned long idPropietari);
void node_propietat_eliminar_participacio(node_propietat_t *node, unsigned long idPropietari);
void node_propietat_eliminar_participacions(node_propietat_t *node);

void node_propietat_verifica(node_propietat_t *node);

#endif	/* PROPIETAT_NODE_H */

