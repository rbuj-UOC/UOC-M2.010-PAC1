/* 
 * File:   propietari_node.h
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#ifndef PROPIETARI_NODE_H
#define	PROPIETARI_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "boolean.h"

typedef struct node_propietari_s {
    unsigned long idPropietari;
    char *nom;
    char *email;
    struct node_propietari_s *anterior;
    struct node_propietari_s *seguent;
} node_propietari_t, *ptr_node_propietari_t;

bool node_propietari_ultim(node_propietari_t node);
bool node_propietari_primer(node_propietari_t node);
node_propietari_t *node_propietari_seguent(node_propietari_t node);
node_propietari_t *node_propietari_anterior(node_propietari_t node);
node_propietari_t *node_propietari_crear(char **nom, char **email, unsigned long idPropietari);
void node_propietari_allibera_node(node_propietari_t *node);
void node_propietari_situa(node_propietari_t *node_anterior, node_propietari_t *node, node_propietari_t *node_seguent);

#endif	/* PROPIETARI_NODE_H */
