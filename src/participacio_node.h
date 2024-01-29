/* 
 * File:   participacio_node.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef PARTICIPACIO_NODE_H
#define	PARTICIPACIO_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "boolean.h"
#include "operacio.h"
#include "fraccio.h"

typedef struct node_participacio_s {
    unsigned long id;
    fraccio_t participacio;
    struct node_participacio_s *anterior;
    struct node_participacio_s *seguent;
} node_participacio_t, *ptr_node_participacio_t;

bool node_participacio_ultim(node_participacio_t node);
bool node_participacio_primer(node_participacio_t node);
node_participacio_t *node_participacio_seguent(node_participacio_t node);
node_participacio_t *node_participacio_anterior(node_participacio_t node);
node_participacio_t *node_participacio_crear(unsigned long id, fraccio_t fraccio);
void node_participacio_alliberar_node(node_participacio_t *node);

#endif	/* PARTICIPACIO_NODE_H */

