/* 
 * File:   propietari_llista.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "propietari_llista.h"

void llista_propietaris_crear_llista(llista_propietaris_t *llista) {
    (*llista).punter = NULL;
    (*llista).numelem = 0;
    ((*llista).node_fantasma_esquerra) = (node_propietari_t *) malloc(sizeof (node_propietari_t));
    ((*llista).node_fantasma_esquerra)->idPropietari = 0;
    ((*llista).node_fantasma_esquerra)->nom = NULL;
    ((*llista).node_fantasma_esquerra)->email = NULL;
    ((*llista).node_fantasma_dreta) = (node_propietari_t *) malloc(sizeof (node_propietari_t));
    ((*llista).node_fantasma_dreta)->idPropietari = 0;
    ((*llista).node_fantasma_dreta)->nom = NULL;
    ((*llista).node_fantasma_dreta)->email = NULL;
    ((*llista).node_fantasma_esquerra)->anterior = NULL;
    ((*llista).node_fantasma_esquerra)->seguent = ((*llista).node_fantasma_dreta);
    ((*llista).node_fantasma_dreta)->anterior = ((*llista).node_fantasma_esquerra);
    ((*llista).node_fantasma_dreta)->seguent = NULL;
}

/* la funció llista_propietari_netejar elimina tots els nodes de la llista
 */
void llista_propietaris_netejar_llista(llista_propietaris_t *llista) {
    while (llista_propietaris_esta_buida(*llista) == false) {
        node_propietari_t *node = (*llista).punter;
        llista_propietaris_eliminar_node(llista, node);
    }
}

void llista_propietaris_destrueix_llista(llista_propietaris_t *llista) {
    llista_propietaris_netejar_llista(llista);
    ((*llista).node_fantasma_esquerra)->seguent = NULL;
    ((*llista).node_fantasma_dreta)->anterior = NULL;
    free((node_propietari_t *) (*llista).node_fantasma_dreta);
    free((node_propietari_t *) (*llista).node_fantasma_esquerra);
    (*llista).node_fantasma_dreta = NULL;
    (*llista).node_fantasma_esquerra = NULL;
}

/* la funció llista_propietari_buida retorna cert si la llista està buida,
 * és a dir, no conté elements, altrament retorna fals.
 */
bool llista_propietaris_esta_buida(llista_propietaris_t llista) {
    return (llista.numelem == 0) ? true : false;
}

/* Afegeix els propietaris a la llista de forma ordenada segons el seu identificador (idPropietari)
 * Si la llista està buida la inicialitza.
 */
void llista_propietaris_afegir_node(llista_propietaris_t *llista, char **nom, char **email, unsigned long idPropietari) {
    node_propietari_t *nou_node;
    ptr_node_propietari_t iterador;
    if (llista_propietaris_esta_buida(*llista) == true) {
        nou_node = node_propietari_crear(nom, email, idPropietari);
        node_propietari_situa((*llista).node_fantasma_esquerra, nou_node, (*llista).node_fantasma_dreta);
        (*llista).punter = nou_node;
    } else {
        if (llista_propietaris_existeix_idPropietari((*llista), idPropietari) == false) {
            llista_propietaris_cerca_idPropietari((*llista), idPropietari, &iterador);
            nou_node = node_propietari_crear(nom, email, idPropietari);
            nou_node->anterior = iterador;
            nou_node->seguent = iterador->seguent;
            (iterador->seguent)->anterior = nou_node;
            iterador->seguent = nou_node;
            if (iterador->anterior == NULL) {
                (*llista).punter = nou_node;
            }
        }
    }
    (*llista).numelem++;
}

void llista_propietaris_eliminar_id(llista_propietaris_t *llista, unsigned long idPropietari){
    ptr_node_propietari_t iterador;
    if (llista_propietaris_troba_idPropietari(*llista, idPropietari, &iterador) == true) {
        llista_propietaris_eliminar_node(llista, iterador);
    }
}

/* Elimina un node de la llista i allibera la memoria assignada
 */
void llista_propietaris_eliminar_node(llista_propietaris_t *llista, node_propietari_t *node) {
    if ((node->anterior)->anterior == NULL) {
        (*llista).punter = node->seguent;
    }
    (node->anterior)->seguent = node->seguent;
    (node->seguent)->anterior = node->anterior;
    (node)->anterior = NULL;
    (node)->seguent = NULL;
    (*llista).numelem = (*llista).numelem - 1;
    node_propietari_allibera_node(node);
}

/* comprova si ja existeix a la llista l'identificador
 */
bool llista_propietaris_existeix_idPropietari(llista_propietaris_t llista, unsigned long idPropietari) {
    node_propietari_t *node = llista.punter;
    bool trobat = false;

    if (llista_propietaris_esta_buida(llista) == false) {
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->idPropietari == idPropietari) ? true : false;
            node = node_propietari_seguent(*node);
        }
    }
    return trobat;
}

/* la funció node_propietari_troba_idPropietari retorna cert si existeix un node
 * amb un identificador idèntic a la llista. Modifica el valor passat per refe-
 * rència iterador, amb l'iterador que compleix la condició, o el darrer si no 
 * fos així, retornant fals.
 */
bool llista_propietaris_troba_idPropietari(llista_propietaris_t llista, unsigned long idPropietari, ptr_node_propietari_t *iterador) {
    node_propietari_t *node = llista.punter;
    (*iterador) = NULL;
    bool trobat = false;

    if (llista_propietaris_esta_buida(llista) == false) {
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->idPropietari == idPropietari) ? true : false;
            (*iterador) = node;
            node = node_propietari_seguent(*node);
        }
    }
    return trobat;
}

/* la funció llista_propietari_cerca_idPropietari retorna cert si existeix un node
 * amb un identificador superior a la llista. Modifica el valor passat per refe-
 * rència iterador, amb l'iterador que compleix la condició, o el darrer si no
 * fos així, retornant fals.
 */
void llista_propietaris_cerca_idPropietari(llista_propietaris_t llista, unsigned long idPropietari, ptr_node_propietari_t *iterador) {
    (*iterador) = NULL;

    if (llista_propietaris_esta_buida(llista) == false) {
        node_propietari_t *node = llista.punter;
        bool trobat = false;
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->idPropietari > idPropietari) ? true : false;
            if (trobat == false) {
                node = node_propietari_seguent(*node);
            }
        }
        node = node_propietari_anterior(*node);
        (*iterador) = node;
    }
}

void llista_propietaris_fusiona(llista_propietaris_t *llista_desti, llista_propietaris_t *llista_origen) {
    unsigned long i, numelem = llista_origen->numelem;
    node_propietari_t *desa;
    for (i = 0; i < numelem; i++) {
        desa = (llista_origen->punter)->seguent;
        node_propietari_situa(llista_desti->node_fantasma_dreta->anterior, llista_origen->punter, llista_desti->node_fantasma_dreta);
        llista_desti->numelem++;
        llista_origen->numelem--;
        llista_origen->punter = desa;
    }
    llista_origen->node_fantasma_dreta->anterior = llista_origen->node_fantasma_esquerra;
    llista_origen->node_fantasma_esquerra->seguent = llista_origen->node_fantasma_dreta;
    llista_origen->punter = NULL;
}
