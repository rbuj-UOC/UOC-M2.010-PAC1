/* 
 * File:   transmissio_node.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "transmissio_node.h"

bool node_transmissio_ultim(node_transmissio_t node) {
    return (node.seguent->seguent == NULL) ? true : false;
}

bool node_transmissio_primer(node_transmissio_t node) {
    return (node.anterior->anterior == NULL) ? true : false;
}

node_transmissio_t *node_transmissio_seguent(node_transmissio_t node) {
    return node.seguent;
}

node_transmissio_t *node_transmissio_anterior(node_transmissio_t node) {
    return node.anterior;
}

node_transmissio_t *node_transmissio_crear(unsigned long idPropietariAnterior, dia_t data_transmissio, char **motiu) {
    node_transmissio_t *node = (node_transmissio_t *) malloc(sizeof (node_transmissio_t));
    node->idPropietariAnterior = idPropietariAnterior;
    node->motiu = *motiu;
    dia_copia(&(node->data_transmissio), data_transmissio);
    llista_registres_crear_llista(&node->llista_registres);
    return node;
}

void node_transmissio_alliberar_node(node_transmissio_t *node) {
    free((char *) node->motiu);
    llista_registres_destrueix_llista(&(node->llista_registres));
    free((node_transmissio_t *) node);
}

/*
 * Registres
 */
void node_transmissio_afegir_registre(node_transmissio_t *node, unsigned long idPropietat) {
    llista_registres_afegir_node(&(node->llista_registres), idPropietat);
}

void node_transmissio_eliminar_registre(node_transmissio_t *node, unsigned long idPropietat) {
    llista_registres_eliminar_id(&(node->llista_registres), idPropietat);
}

void node_transmissio_eliminar_registres(node_transmissio_t *node) {
    llista_registres_destrueix_llista(&(node->llista_registres));
}

/*
 * Participacions
 */
void node_transmissio_afegir_participacio_registre(node_transmissio_t *node, unsigned long idPropietat, unsigned long idPropietari, fraccio_t participacio) {
    llista_registres_afegir_participacio_node(node->llista_registres, idPropietat, idPropietari, participacio);
}

void node_transmissio_eliminar_participacio_registre(node_transmissio_t *node, unsigned long idPropietat, unsigned long idPropietari) {
    llista_registres_eliminar_participacio_node(node->llista_registres, idPropietat, idPropietari);
}

void node_transmissio_verifica(node_transmissio_t *node) {
    llista_registres_verifica(node->llista_registres, node->idPropietariAnterior);
}
