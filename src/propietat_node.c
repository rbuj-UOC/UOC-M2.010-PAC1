/* 
 * File:   propietat_node.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "propietat_node.h"

void node_propietat_eliminar_particions(node_propietat_t *node);

bool node_propietat_ultim(node_propietat_t node) {
    return (node.seguent->seguent == NULL) ? true : false;
}

bool node_propietat_primer(node_propietat_t node) {
    return (node.anterior->anterior == NULL) ? true : false;
}

node_propietat_t *node_propietat_seguent(node_propietat_t node) {
    return node.seguent;
}

node_propietat_t *node_propietat_anterior(node_propietat_t node) {
    return node.anterior;
}

node_propietat_t *node_propietat_crear(char **nom, fraccio_t fraccio, unsigned long idPropietat) {
    node_propietat_t *node = (node_propietat_t *) malloc(sizeof (node_propietat_t));
    node->idPropietat = idPropietat;
    node->nom = *nom;
    fraccio_copia(&(node->participacio_general), fraccio);
    llista_participacions_crear_llista(&(node->llista_participacions));
    return node;
}

void node_propietat_alliberar_node(node_propietat_t *node) {
    free((char *) node->nom);
    llista_participacions_destrueix_llista(&(node->llista_participacions));
    free((node_propietat_t *) node);
}

/*
 * Participacions
 */

void node_propietat_afegir_participacio(node_propietat_t *node, fraccio_t fraccio, unsigned long idPropietari) {
    llista_participacions_afegir_node(&(node->llista_participacions), idPropietari, fraccio);
}

void node_propietat_eliminar_participacio(node_propietat_t *node, unsigned long idPropietari) {
    llista_participacions_eliminar_id(&(node->llista_participacions), idPropietari);
}

void node_propietat_eliminar_particions(node_propietat_t *node) {
    llista_participacions_netejar_llista(&(node->llista_participacions));
}

void node_propietat_verifica(node_propietat_t *node){
    unsigned long identificadors[1];
    identificadors[0]=node->idPropietat;
    llista_participacions_verifica(node->llista_participacions, propietat, identificadors, 1);
}
