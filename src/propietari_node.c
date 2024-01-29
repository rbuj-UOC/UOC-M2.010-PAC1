/* 
 * File:   propietari_node.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "propietari_node.h"

/* la funció node_propietari_ultim retorna cert si el node en qüestió és
 * l'últim, altrament fals
 */
bool node_propietari_ultim(node_propietari_t node) {
    return (node.seguent->seguent == NULL) ? true : false;
}

/* la funció node_propietari_primer retorna cert si el node en qüestió és
 * el primer, altrament fals
 */
bool node_propietari_primer(node_propietari_t node) {
    return (node.anterior->anterior == NULL) ? true : false;
}

/* la funció node_propietari_seguent retorna el següent node
 */
node_propietari_t *node_propietari_seguent(node_propietari_t node) {
    return node.seguent;
}

/* la funció node_propietari_anterior retorna l'anterior node
 */
node_propietari_t *node_propietari_anterior(node_propietari_t node) {
    return node.anterior;
}

/* Crea un nou node en memòria amb les dades del propietari retornant el
 * seu apuntador
 */
node_propietari_t *node_propietari_crear(char **nom, char **email, unsigned long idPropietari) {
    node_propietari_t *node = (node_propietari_t *) malloc(sizeof (node_propietari_t));
    node->idPropietari = idPropietari;
    node->nom = *nom;
    node->email = *email;
    return node;
}

/* Allinera la memoria assignada a un node
 */
void node_propietari_allibera_node(node_propietari_t *node) {
    free(node->email);
    free(node->nom);
    free(node);
}

void node_propietari_situa(node_propietari_t *node_anterior, node_propietari_t *node, node_propietari_t *node_seguent) {
    node->anterior = node_anterior;
    node->seguent = node_seguent;
    node_seguent->anterior = node;
    node_anterior->seguent = node;
}
