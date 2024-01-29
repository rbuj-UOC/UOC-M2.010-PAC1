/* 
 * File:   participacio.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "participacio_llista.h"

void llista_participacions_crear_llista(llista_participacions_t *llista) {
    (*llista).ptr_node_participacio = NULL;
    (*llista).numelem = 0;
    ((*llista).node_fantasma_esquerra) = (node_participacio_t *) malloc(sizeof (node_participacio_t));
    ((*llista).node_fantasma_esquerra)->id = 0;
    ((*llista).node_fantasma_esquerra)->participacio.denominador = 0;
    ((*llista).node_fantasma_esquerra)->participacio.numerador = 0;
    ((*llista).node_fantasma_dreta) = (node_participacio_t *) malloc(sizeof (node_participacio_t));
    ((*llista).node_fantasma_dreta)->id = 0;
    ((*llista).node_fantasma_dreta)->participacio.numerador = 0;
    ((*llista).node_fantasma_dreta)->participacio.denominador = 0;
    ((*llista).node_fantasma_esquerra)->anterior = NULL;
    ((*llista).node_fantasma_esquerra)->seguent = ((*llista).node_fantasma_dreta);
    ((*llista).node_fantasma_dreta)->anterior = ((*llista).node_fantasma_esquerra);
    ((*llista).node_fantasma_dreta)->seguent = NULL;
}

/* la funció llista_participacions_netejar_llista elimina tots els nodes de la llista
 */
void llista_participacions_netejar_llista(llista_participacions_t *llista) {
    while (llista_participacions_esta_buida(*llista) == false) {
        node_participacio_t *node = (*llista).ptr_node_participacio;
        llista_participacions_eliminar_node(llista, node);
    }
    (*llista).numelem = 0;
}

void llista_participacions_destrueix_llista(llista_participacions_t *llista) {
    llista_participacions_netejar_llista(llista);
    ((*llista).node_fantasma_esquerra)->seguent = NULL;
    ((*llista).node_fantasma_dreta)->anterior = NULL;
    free((node_participacio_t *) (*llista).node_fantasma_dreta);
    free((node_participacio_t *) (*llista).node_fantasma_esquerra);
    (*llista).node_fantasma_dreta = NULL;
    (*llista).node_fantasma_esquerra = NULL;
}

/* la funció llista_participacions_esta_buida retorna cert si la llista està buida,
 * és a dir, no conté elements, altrament retorna fals.
 */
bool llista_participacions_esta_buida(llista_participacions_t llista) {
    return (llista.numelem == 0) ? true : false;
}

void llista_participacions_afegir_node(llista_participacions_t *llista,
        unsigned long id, fraccio_t fraccio) {
    node_participacio_t *nou_node;
    ptr_node_participacio_t iterador;
    if (llista_participacions_esta_buida(*llista) == true) {
        nou_node = node_participacio_crear(id, fraccio);
        nou_node->anterior = (*llista).node_fantasma_esquerra;
        nou_node->seguent = (*llista).node_fantasma_dreta;
        ((*llista).node_fantasma_dreta)->anterior = nou_node;
        ((*llista).node_fantasma_esquerra)->seguent = nou_node;
        (*llista).ptr_node_participacio = nou_node;
    } else {
        if (llista_participacions_existeix_id((*llista), id) == false) {
            llista_participacions_cerca_id((*llista), id, &iterador);
            nou_node = node_participacio_crear(id, fraccio);
            nou_node->anterior = iterador;
            nou_node->seguent = iterador->seguent;
            (iterador->seguent)->anterior = nou_node;
            iterador->seguent = nou_node;
            if (iterador->anterior == NULL) {
                (*llista).ptr_node_participacio = nou_node;
            }
        }
    }
    (*llista).numelem++;
}

void llista_participacions_eliminar_id(llista_participacions_t *llista, unsigned long id) {
    ptr_node_participacio_t iterador;
    if (llista_participacions_troba_id(*llista, id, &iterador) == true) {
        llista_participacions_eliminar_node(llista, iterador);
    }
}

/* Elimina un node de la llista i allibera la memoria assignada
 */
void llista_participacions_eliminar_node(llista_participacions_t *llista, node_participacio_t *node) {
    if ((node->anterior)->anterior == NULL) {
        (*llista).ptr_node_participacio = node->seguent;
    }
    (node->anterior)->seguent = node->seguent;
    (node->seguent)->anterior = node->anterior;
    (node)->anterior = NULL;
    (node)->seguent = NULL;
    (*llista).numelem = (*llista).numelem - 1;
    node_participacio_alliberar_node(node);
}

void llista_participacions_cerca_id(llista_participacions_t llista, unsigned long id, ptr_node_participacio_t * iterador) {
    (*iterador) = NULL;

    if (llista_participacions_esta_buida(llista) == false) {
        node_participacio_t *node = llista.ptr_node_participacio;
        bool trobat = false;
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->id > id) ? true : false;
            if (trobat == false) {
                node = node_participacio_seguent(*node);
            }
        }
        node = node_participacio_anterior(*node);
        (*iterador) = node;
    }
}

/* comprova si ja existeix a la llista l'identificador
 */
bool llista_participacions_existeix_id(llista_participacions_t llista, unsigned long id) {
    bool trobat = false;

    if (llista_participacions_esta_buida(llista) == false) {
        node_participacio_t *node = llista.ptr_node_participacio;
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->id == id) ? true : false;
            node = node_participacio_seguent(*node);
        }
    }
    return trobat;
}

bool llista_participacions_troba_id(llista_participacions_t llista, unsigned long id, ptr_node_participacio_t * iterador) {
    node_participacio_t *node = llista.ptr_node_participacio;
    bool trobat = false;

    if (llista_participacions_esta_buida(llista) == false) {
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->id == id) ? true : false;
            (*iterador) = node;
            node = node_participacio_seguent(*node);
        }
    }
    return trobat;
}

fraccio_t llista_participacions_suma_participacions(llista_participacions_t llista) {
    fraccio_t participacio;
    node_participacio_t *node = llista.ptr_node_participacio;
    ptr_node_participacio_t iterador = node;
    fraccio_assigna(&participacio, 1, 1);
    if (llista_participacions_esta_buida(llista) == false) {
        fraccio_copia(&participacio, node->participacio);
        node = node_participacio_seguent(*iterador);
        while (node_participacio_ultim(*iterador) == false) {
            fraccio_suma(&participacio, participacio, node->participacio);
            node = node_participacio_seguent(*iterador);
            iterador = node;
        }
    }
    return participacio;
}

void llista_participacions_verifica(llista_participacions_t llista, operacio op, unsigned long identificadors[], int num_identificadors) {
    fraccio_t fraccio_verificacio;
    if (fraccio_unitat(fraccio_verificacio = llista_participacions_suma_participacions(llista)) == false) {
        int i;
        printf("[VERIFICACIO] ");
        if (op == propietat)
            printf("PROPIETAT ");
        else
            printf("TRANSMISSIO ");
        for (i = 0; i < num_identificadors; i++) {
            printf(".%lu", identificadors[i]);
        }
        printf(": la suma de participacions no és vàlida: %lu/%lu\n",
                fraccio_verificacio.numerador, fraccio_verificacio.denominador);
    }
}
