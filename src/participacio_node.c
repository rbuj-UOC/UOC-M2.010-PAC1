/* 
 * File:   participacio.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "participacio_node.h"

/* la funció node_participacio_ultim retorna cert si el node en qüestió és
 * l'últim, altrament fals
 */
bool node_participacio_ultim(node_participacio_t node) {
    return (node.seguent->seguent == NULL) ? true : false;
}

/* la funció node_participacio_primer retorna cert si el node en qüestió és
 * el primer, altrament fals
 */
bool node_participacio_primer(node_participacio_t node) {
    return (node.anterior->anterior == NULL) ? true : false;
}

/* la funció node_participacio_seguent retorna el següent node
 */
node_participacio_t *node_participacio_seguent(node_participacio_t node) {
    return node.seguent;
}

/* la funció node_participacio_anterior retorna l'anterior node
 */
node_participacio_t *node_participacio_anterior(node_participacio_t node) {
    return node.anterior;
}

/* Crea un nou node en memòria amb les dades del propietari retornant el
 * seu apuntador
 */
node_participacio_t *node_participacio_crear(unsigned long id, fraccio_t fraccio) {
    node_participacio_t *node = (node_participacio_t *) malloc(sizeof (node_participacio_t));
    node->id = id;
    fraccio_copia(&(node->participacio), fraccio);
    return node;
}

/* Allinera la memoria assignada a un node
 */
void node_participacio_alliberar_node(node_participacio_t *node) {
    free((node_participacio_t *) node);
}
