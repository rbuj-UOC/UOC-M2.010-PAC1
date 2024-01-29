/* 
 * File:   registre_llista.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "registre_llista.h"

void llista_registres_crear_llista(llista_registres_t *llista) {
    (*llista).punter = NULL;
    (*llista).numelem = 0;
    ((*llista).node_fantasma_esquerra) = (node_registre_t *) malloc(sizeof (node_registre_t));
    ((*llista).node_fantasma_esquerra)->idPropietat = 0;
    ((*llista).node_fantasma_esquerra)->llista_participacions.numelem = 0;
    ((*llista).node_fantasma_esquerra)->llista_participacions.ptr_node_participacio = NULL;
    ((*llista).node_fantasma_esquerra)->llista_participacions.node_fantasma_dreta = NULL;
    ((*llista).node_fantasma_esquerra)->llista_participacions.node_fantasma_esquerra = NULL;
    ((*llista).node_fantasma_dreta) = (node_registre_t *) malloc(sizeof (node_registre_t));
    ((*llista).node_fantasma_dreta)->idPropietat = 0;
    ((*llista).node_fantasma_dreta)->llista_participacions.numelem = 0;
    ((*llista).node_fantasma_dreta)->llista_participacions.ptr_node_participacio = NULL;
    ((*llista).node_fantasma_dreta)->llista_participacions.node_fantasma_dreta = NULL;
    ((*llista).node_fantasma_dreta)->llista_participacions.node_fantasma_esquerra = NULL;
    ((*llista).node_fantasma_esquerra)->anterior = NULL;
    ((*llista).node_fantasma_esquerra)->seguent = ((*llista).node_fantasma_dreta);
    ((*llista).node_fantasma_dreta)->anterior = ((*llista).node_fantasma_esquerra);
    ((*llista).node_fantasma_dreta)->seguent = NULL;
}

void llista_registres_netejar_llista(llista_registres_t *llista) {
    while (llista_registres_esta_buida(*llista) == false) {
        node_registre_t *node = (*llista).punter;
        llista_registres_eliminar_node(llista, node);
    }
}

void llista_registres_destrueix_llista(llista_registres_t *llista) {
    llista_registres_netejar_llista(llista);
    ((*llista).node_fantasma_esquerra)->seguent = NULL;
    ((*llista).node_fantasma_dreta)->anterior = NULL;
    free((node_registre_t *) (*llista).node_fantasma_dreta);
    free((node_registre_t *) (*llista).node_fantasma_esquerra);
    (*llista).node_fantasma_dreta = NULL;
    (*llista).node_fantasma_esquerra = NULL;
}

void llista_registres_afegir_node(llista_registres_t *llista, unsigned long idPropietat) {
    node_registre_t *nou_node;
    ptr_node_registre_t iterador;
    if (llista_registres_esta_buida(*llista) == true) {
        nou_node = node_registre_crear(idPropietat);
        nou_node->anterior = (*llista).node_fantasma_esquerra;
        nou_node->seguent = (*llista).node_fantasma_dreta;
        ((*llista).node_fantasma_dreta)->anterior = nou_node;
        ((*llista).node_fantasma_esquerra)->seguent = nou_node;
        (*llista).punter = nou_node;
    } else {
        if (llista_registres_existeix_idPropietat((*llista), idPropietat) == false) {
            llista_registres_cercar_idPropietat((*llista), idPropietat, &iterador);
            nou_node = node_registre_crear(idPropietat);
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

void llista_registres_eliminar_id(llista_registres_t *llista, unsigned long idPropietat){
    ptr_node_registre_t iterador;
    if (llista_registres_troba_idPropietat(*llista, idPropietat, &iterador) == true) {
        llista_registres_eliminar_node(llista, iterador);
    }
}

void llista_registres_eliminar_node(llista_registres_t *llista, node_registre_t *node) {
    if ((node->anterior)->anterior == NULL) {
        (*llista).punter = node->seguent;
    }
    (node->anterior)->seguent = node->seguent;
    (node->seguent)->anterior = node->anterior;
    (node)->anterior = NULL;
    (node)->seguent = NULL;
    (*llista).numelem = (*llista).numelem - 1;
    node_registre_alliberar_node(node);
}

bool llista_registres_esta_buida(llista_registres_t llista) {
    return (llista.numelem == 0) ? true : false;
}

bool llista_registres_existeix_idPropietat(llista_registres_t llista, unsigned long idPropietat) {
    node_registre_t *node = llista.punter;
    bool trobat = false;

    if (llista_registres_esta_buida(llista) == false) {
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->idPropietat == idPropietat) ? true : false;
            node = node_registre_seguent(*node);
        }
    }
    return trobat;
}

void llista_registres_cercar_idPropietat(llista_registres_t llista, unsigned long idPropietat, ptr_node_registre_t *iterador) {
    (*iterador) = NULL;

    if (llista_registres_esta_buida(llista) == false) {
        node_registre_t *node = llista.punter;
        bool trobat = false;
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->idPropietat > idPropietat) ? true : false;
            if (trobat == false) {
                node = node_registre_seguent(*node);
            }
        }
        node = node_registre_anterior(*node);
        (*iterador) = node;
    }
}

bool llista_registres_troba_idPropietat(llista_registres_t llista, unsigned long idPropietat, ptr_node_registre_t *iterador) {
    (*iterador) = NULL;
    bool trobat = false;

    if (llista_registres_esta_buida(llista) == false) {
        node_registre_t *node = llista.punter;
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->idPropietat == idPropietat) ? true : false;
            (*iterador) = node;
            node = node_registre_seguent(*node);
        }
    }
    return trobat;
}

void llista_registres_afegir_participacio_node(llista_registres_t llista, unsigned long idPropietat, unsigned long idPropietari, fraccio_t fraccio) {
    ptr_node_registre_t iterador;
    if (llista_registres_troba_idPropietat(llista, idPropietat, &iterador) == true) {
        node_registre_afegir_particio(iterador, fraccio, idPropietari);
    }
}

void llista_registres_eliminar_participacio_node(llista_registres_t llista, unsigned long idPropietat, unsigned long idPropietari) {
    ptr_node_registre_t iterador;
    if (llista_registres_troba_idPropietat(llista, idPropietat, &iterador) == true) {
        node_registre_eliminar_particio(iterador, idPropietari);
    }
}

void llista_registres_verifica(llista_registres_t llista, unsigned long idPropietariAnterior) {
    node_registre_t *node = llista.punter;
    if (llista_registres_esta_buida(llista) == false) {
        long unsigned int i;
        for (i = 0; i < llista.numelem; i++) {
            node_registre_verifica(node, idPropietariAnterior);
            node = node->seguent;
        }
    }
}
