/* 
 * File:   transmissio_llista.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "transmissio_llista.h"
#include "propietat_node.h"

void llista_transmissions_crear_llista(llista_transmissions_t *llista) {
    (*llista).punter = NULL;
    (*llista).numelem = 0;
    ((*llista).node_fantasma_esquerra) = (node_transmissio_t *) malloc(sizeof (node_transmissio_t));
    ((*llista).node_fantasma_esquerra)->data_transmissio.any = 0;
    ((*llista).node_fantasma_esquerra)->data_transmissio.mes = 0;
    ((*llista).node_fantasma_esquerra)->data_transmissio.dia = 0;
    ((*llista).node_fantasma_esquerra)->idPropietariAnterior = 0;
    ((*llista).node_fantasma_esquerra)->motiu = NULL;
    ((*llista).node_fantasma_esquerra)->llista_registres.numelem = 0;
    ((*llista).node_fantasma_esquerra)->llista_registres.punter = NULL;
    ((*llista).node_fantasma_esquerra)->llista_registres.node_fantasma_dreta = NULL;
    ((*llista).node_fantasma_esquerra)->llista_registres.node_fantasma_esquerra = NULL;
    ((*llista).node_fantasma_dreta) = (node_transmissio_t *) malloc(sizeof (node_transmissio_t));
    ((*llista).node_fantasma_dreta)->data_transmissio.any = 0;
    ((*llista).node_fantasma_dreta)->data_transmissio.mes = 0;
    ((*llista).node_fantasma_dreta)->data_transmissio.dia = 0;
    ((*llista).node_fantasma_dreta)->idPropietariAnterior = 0;
    ((*llista).node_fantasma_dreta)->motiu = NULL;
    ((*llista).node_fantasma_dreta)->llista_registres.numelem = 0;
    ((*llista).node_fantasma_dreta)->llista_registres.punter = NULL;
    ((*llista).node_fantasma_dreta)->llista_registres.node_fantasma_dreta = NULL;
    ((*llista).node_fantasma_dreta)->llista_registres.node_fantasma_esquerra = NULL;
    ((*llista).node_fantasma_esquerra)->anterior = NULL;
    ((*llista).node_fantasma_esquerra)->seguent = ((*llista).node_fantasma_dreta);
    ((*llista).node_fantasma_dreta)->anterior = ((*llista).node_fantasma_esquerra);
    ((*llista).node_fantasma_dreta)->seguent = NULL;
}

void llista_transmissions_netejar_llista(llista_transmissions_t *llista) {
    while (llista_transmissions_esta_buida(*llista) == false) {
        node_transmissio_t *node = (*llista).punter;
        llista_transmissions_eliminar_node(llista, node);
    }
}

void llista_transmissions_destrueix_llista(llista_transmissions_t *llista) {
    llista_transmissions_netejar_llista(llista);
    ((*llista).node_fantasma_esquerra)->seguent = NULL;
    ((*llista).node_fantasma_dreta)->anterior = NULL;
    free((node_transmissio_t *) (*llista).node_fantasma_dreta);
    free((node_transmissio_t *) (*llista).node_fantasma_esquerra);
    (*llista).node_fantasma_dreta = NULL;
    (*llista).node_fantasma_esquerra = NULL;
}

bool llista_transmissions_esta_buida(llista_transmissions_t llista) {
    return (llista.numelem == 0) ? true : false;
}

void llista_transmissions_afegir_node(llista_transmissions_t *llista, unsigned long idPropietariAnterior, dia_t data_transmissio, char **motiu) {
    node_transmissio_t *nou_node;
    ptr_node_transmissio_t iterador;
    if (llista_transmissions_esta_buida(*llista) == true) {
        nou_node = node_transmissio_crear(idPropietariAnterior, data_transmissio, motiu);
        nou_node->anterior = (*llista).node_fantasma_esquerra;
        nou_node->seguent = (*llista).node_fantasma_dreta;
        ((*llista).node_fantasma_dreta)->anterior = nou_node;
        ((*llista).node_fantasma_esquerra)->seguent = nou_node;
        (*llista).punter = nou_node;
    } else {
        if (llista_transmissions_existeix((*llista), idPropietariAnterior, data_transmissio) == false) {
            llista_transmissions_cercar((*llista), idPropietariAnterior, data_transmissio, &iterador);
            nou_node = node_transmissio_crear(idPropietariAnterior, data_transmissio, motiu);
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

void llista_transmissions_eliminar_id(llista_transmissions_t *llista, unsigned long idPropietariAnterior, dia_t data_transmissio) {
    ptr_node_transmissio_t iterador;
    if (llista_transmissions_troba_idPropietariAnterior(*llista, idPropietariAnterior, data_transmissio, &iterador) == true) {
        llista_transmissions_eliminar_node(llista, iterador);
    }
}

void llista_transmissions_eliminar_node(llista_transmissions_t *llista, node_transmissio_t *node) {
    if ((node->anterior)->anterior == NULL) {
        (*llista).punter = node->seguent;
    }
    (node->anterior)->seguent = node->seguent;
    (node->seguent)->anterior = node->anterior;
    (node)->anterior = NULL;
    (node)->seguent = NULL;
    (*llista).numelem = (*llista).numelem - 1;
    node_transmissio_alliberar_node(node);
}

bool llista_transmissions_troba_idPropietariAnterior(llista_transmissions_t llista, unsigned long idPropietariAnterior, dia_t data_transmissio, ptr_node_transmissio_t *iterador) {
    node_transmissio_t *node = llista.punter;
    (*iterador) = NULL;
    bool trobat = false;
    (void) data_transmissio;

    if (llista_transmissions_esta_buida(llista) == false) {
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->idPropietariAnterior == idPropietariAnterior) ? true : false;
            (*iterador) = node;
            node = node_transmissio_seguent(*node);
        }
    }
    return trobat;
}

bool llista_transmissions_existeix(llista_transmissions_t llista, unsigned long idPropietariAnterior, dia_t data_transmissio) {
    bool trobat = false;
    node_transmissio_t *node = llista.punter;
    (void) data_transmissio;

    if (llista_transmissions_esta_buida(llista) == false) {
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->idPropietariAnterior == idPropietariAnterior) ? true : false;
            node = node_transmissio_seguent(*node);
        }
    }

    return trobat;
}

void llista_transmissions_cercar(llista_transmissions_t llista, unsigned long idPropietariAnterior, dia_t data_transmissio, ptr_node_transmissio_t *iterador) {
    (*iterador) = NULL;
    (void) data_transmissio;

    if (llista_transmissions_esta_buida(llista) == false) {
        node_transmissio_t *node = llista.punter;
        bool trobat = false;
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->idPropietariAnterior > idPropietariAnterior) ? true : false;
            if (trobat == false) {
                node = node_transmissio_seguent(*node);
            }
        }
        node = node_transmissio_anterior(*node);
        (*iterador) = node;
    }
}

/*
 * Registres
 */

void llista_transmissions_afegir_registre_node(llista_transmissions_t llista, unsigned long idPropietariAnterior, dia_t data_transmissio, unsigned long idPropietat) {
    ptr_node_transmissio_t iterador;
    if (llista_transmissions_troba_idPropietariAnterior(llista, idPropietariAnterior, data_transmissio, &iterador) == true) {
        node_transmissio_afegir_registre(iterador, idPropietat);
    }
}

void llista_transmissions_eliminar_registre_node(llista_transmissions_t llista, unsigned long idPropietariAnterior, dia_t data_transmissio, unsigned long idPropietat) {
    ptr_node_transmissio_t iterador;
    if (llista_transmissions_troba_idPropietariAnterior(llista, idPropietariAnterior, data_transmissio, &iterador) == true) {
        node_transmissio_eliminar_registre(iterador, idPropietat);
    }
}

/*
 * Participacions
 */

void llista_transmissions_afegir_particio_registre_node(llista_transmissions_t llista, unsigned long idPropietariAnterior, dia_t data_transmissio, unsigned long idPropietat, unsigned long idNouPropietari, fraccio_t fraccio_participacio) {
    ptr_node_transmissio_t iterador_llista_transmissions;
    if (llista_transmissions_troba_idPropietariAnterior(llista, idPropietariAnterior, data_transmissio, &iterador_llista_transmissions) == true) {
        node_transmissio_afegir_participacio_registre(iterador_llista_transmissions, idPropietat, idNouPropietari, fraccio_participacio);
    }
}

void llista_transmissions_verifica(llista_transmissions_t llista) {
    node_transmissio_t *node = llista.punter;
    if (llista_transmissions_esta_buida(llista) == false) {
        long unsigned int i;
        for (i = 0; i < llista.numelem; i++) {
            node_transmissio_verifica(node);
            node = node->seguent;
        }
    }
}
