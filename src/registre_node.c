/* 
 * File:   registre_node.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "registre_node.h"

bool node_registre_ultim(node_registre_t node) {
    return (node.seguent->seguent == NULL) ? true : false;
}

bool node_registre_primer(node_registre_t node) {
    return (node.anterior->anterior == NULL) ? true : false;
}

node_registre_t *node_registre_seguent(node_registre_t node) {
    return node.seguent;
}

node_registre_t *node_registre_anterior(node_registre_t node) {
    return node.anterior;
}

node_registre_t *node_registre_crear(unsigned long idPropietat) {
    node_registre_t *node = (node_registre_t *) malloc(sizeof (node_registre_t));
    node->idPropietat = idPropietat;
    llista_participacions_crear_llista(&node->llista_participacions);
    return node;
}

void node_registre_alliberar_node(node_registre_t *node) {
    llista_participacions_destrueix_llista(&(node->llista_participacions));
    free((node_registre_t *) node);
}

void node_registre_afegir_particio(node_registre_t *node, fraccio_t fraccio, unsigned long idPropietari) {
    llista_participacions_afegir_node(&(node->llista_participacions), idPropietari, fraccio);
}

void node_registre_eliminar_particio(node_registre_t *node, unsigned long idPropietari) {
    llista_participacions_eliminar_id(&(node->llista_participacions), idPropietari);
}

void node_registre_eliminar_particions(node_registre_t *node) {
    llista_participacions_netejar_llista(&(node->llista_participacions));
}

void node_registre_verifica(node_registre_t *node, unsigned long idPropietariAnterior) {
    unsigned long identificadors[2];
    identificadors[0]=idPropietariAnterior;
    identificadors[1]=node->idPropietat;
    llista_participacions_verifica(node->llista_participacions, transaccio, identificadors, 2);
}
