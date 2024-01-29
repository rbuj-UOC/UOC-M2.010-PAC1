/* 
 * File:   propietat_llista.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "propietat_llista.h"
#include "propietari_llista.h"

void llista_propietats_crear_llista(llista_propietats_t *llista) {
    (*llista).punter = NULL;
    (*llista).numelem = 0;
    ((*llista).node_fantasma_esquerra) = (node_propietat_t *) malloc(sizeof (node_propietat_t));
    ((*llista).node_fantasma_esquerra)->idPropietat = 0;
    ((*llista).node_fantasma_esquerra)->nom = NULL;
    ((*llista).node_fantasma_esquerra)->participacio_general.denominador = 0;
    ((*llista).node_fantasma_esquerra)->participacio_general.numerador = 0;
    ((*llista).node_fantasma_esquerra)->llista_participacions.numelem = 0;
    ((*llista).node_fantasma_esquerra)->llista_participacions.ptr_node_participacio = NULL;
    ((*llista).node_fantasma_esquerra)->llista_participacions.node_fantasma_dreta = NULL;
    ((*llista).node_fantasma_esquerra)->llista_participacions.node_fantasma_esquerra = NULL;
    ((*llista).node_fantasma_dreta) = (node_propietat_t *) malloc(sizeof (node_propietat_t));
    ((*llista).node_fantasma_dreta)->idPropietat = 0;
    ((*llista).node_fantasma_dreta)->nom = NULL;
    ((*llista).node_fantasma_dreta)->participacio_general.denominador = 0;
    ((*llista).node_fantasma_dreta)->participacio_general.numerador = 0;
    ((*llista).node_fantasma_dreta)->llista_participacions.numelem = 0;
    ((*llista).node_fantasma_dreta)->llista_participacions.numelem = 0;
    ((*llista).node_fantasma_dreta)->llista_participacions.ptr_node_participacio = NULL;
    ((*llista).node_fantasma_dreta)->llista_participacions.node_fantasma_dreta = NULL;
    ((*llista).node_fantasma_dreta)->llista_participacions.node_fantasma_esquerra = NULL;
    ((*llista).node_fantasma_esquerra)->anterior = NULL;
    ((*llista).node_fantasma_esquerra)->seguent = ((*llista).node_fantasma_dreta);
    ((*llista).node_fantasma_dreta)->anterior = ((*llista).node_fantasma_esquerra);
    ((*llista).node_fantasma_dreta)->seguent = NULL;
}

/* la funció llista_propietats_netejar_llista elimina tots els nodes de la llista
 */
void llista_propietats_netejar_llista(llista_propietats_t *llista) {
    while (llista_propietats_esta_buida(*llista) == false) {
        node_propietat_t *node = (*llista).punter;
        llista_propietats_eliminar_node(llista, node);
    }
}

void llista_propietats_destrueix_llista(llista_propietats_t *llista) {
    llista_propietats_netejar_llista(llista);
    ((*llista).node_fantasma_esquerra)->seguent = NULL;
    ((*llista).node_fantasma_dreta)->anterior = NULL;
    free((node_propietat_t *) (*llista).node_fantasma_dreta);
    free((node_propietat_t *) (*llista).node_fantasma_esquerra);
    (*llista).node_fantasma_dreta = NULL;
    (*llista).node_fantasma_esquerra = NULL;
}

/* la funció llista_propietats_esta_buida retorna cert si la llista està buida,
 * és a dir, no conté elements, altrament retorna fals.
 */
bool llista_propietats_esta_buida(llista_propietats_t llista) {
    return (llista.numelem == 0) ? true : false;
}

void llista_propietats_afegir_node(llista_propietats_t *llista, char **nom, fraccio_t participacio_general, unsigned long idPropietat) {
    node_propietat_t *nou_node;
    ptr_node_propietat_t iterador;
    if (llista_propietats_esta_buida(*llista) == true) {
        nou_node = node_propietat_crear(nom, participacio_general, idPropietat);
        nou_node->anterior = (*llista).node_fantasma_esquerra;
        nou_node->seguent = (*llista).node_fantasma_dreta;
        ((*llista).node_fantasma_dreta)->anterior = nou_node;
        ((*llista).node_fantasma_esquerra)->seguent = nou_node;
        (*llista).punter = nou_node;
    } else {
        if (llista_propietats_existeix_idPropietat((*llista), idPropietat) == false) {
            llista_propietats_cercar_idPropietat((*llista), idPropietat, &iterador);
            nou_node = node_propietat_crear(nom, participacio_general, idPropietat);
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

void llista_propietats_eliminar_id(llista_propietats_t *llista, unsigned long idPropietat){
    ptr_node_propietat_t iterador;
    if (llista_propietats_troba_idPropietat(*llista, idPropietat, &iterador) == true) {
        llista_propietats_eliminar_node(llista, iterador);
    }
}

/* Elimina un node de la llista i allibera la memoria assignada
 */
void llista_propietats_eliminar_node(llista_propietats_t *llista, node_propietat_t *node) {
    if ((node->anterior)->anterior == NULL) {
        (*llista).punter = node->seguent;
    }
    (node->anterior)->seguent = node->seguent;
    (node->seguent)->anterior = node->anterior;
    (node)->anterior = NULL;
    (node)->seguent = NULL;
    (*llista).numelem = (*llista).numelem - 1;
    node_propietat_alliberar_node(node);
}

/* la funció llista_propietari_cerca_idPropietari retorna cert si existeix un node
 * amb un identificador superior a la llista. Modifica el valor passat per refe-
 * rència iterador, amb l'iterador que compleix la condició, o el darrer si no
 * fos així, retornant fals.
 */
void llista_propietats_cercar_idPropietat(llista_propietats_t llista, unsigned long idPropietat, ptr_node_propietat_t *iterador) {
    (*iterador) = NULL;

    if (llista_propietats_esta_buida(llista) == false) {
        node_propietat_t *node = llista.punter;
        bool trobat = false;
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->idPropietat > idPropietat) ? true : false;
            if (trobat == false) {
                node = node_propietat_seguent(*node);
            }
        }
        node = node_propietat_anterior(*node);
        (*iterador) = node;
    }
}

bool llista_propietats_troba_idPropietat(llista_propietats_t llista, unsigned long idPropietat, ptr_node_propietat_t *iterador) {
    node_propietat_t *node = llista.punter;
    (*iterador) = NULL;
    bool trobat = false;

    if (llista_propietats_esta_buida(llista) == false) {
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->idPropietat == idPropietat) ? true : false;
            (*iterador) = node;
            node = node_propietat_seguent(*node);
        }
    }
    return trobat;
}

/* comprova si ja existeix a la llista l'identificador
 */
bool llista_propietats_existeix_idPropietat(llista_propietats_t llista, unsigned long idPropietat) {
    node_propietat_t *node = llista.punter;
    bool trobat = false;

    if (llista_propietats_esta_buida(llista) == false) {
        while ((node->seguent != NULL) && (trobat == false)) {
            trobat = (node->idPropietat == idPropietat) ? true : false;
            node = node_propietat_seguent(*node);
        }
    }
    return trobat;
}

/*
 * Participacions
 */

void llista_propietats_afegir_particio_node(llista_propietats_t llista, unsigned long idPropietat, unsigned long idPropietari, fraccio_t fraccio) {
    ptr_node_propietat_t iterador_llista_propietats;
    if (llista_propietats_troba_idPropietat(llista, idPropietat, &iterador_llista_propietats) == true) {
        node_propietat_afegir_participacio(iterador_llista_propietats, fraccio, idPropietari);
    }
}

void llista_propietats_eliminar_particio_node(llista_propietats_t llista, unsigned long idPropietat, unsigned long idPropietari) {
    ptr_node_propietat_t iterador_llista_propietats;
    if (llista_propietats_troba_idPropietat(llista, idPropietat, &iterador_llista_propietats) == true) {
        node_propietat_eliminar_participacio(iterador_llista_propietats, idPropietari);
    }
}
fraccio_t llista_propietats_suma_participacions_generals(llista_propietats_t llista) {
    fraccio_t participacio;
    node_propietat_t *node = llista.punter;
    ptr_node_propietat_t iterador = node;
    fraccio_assigna(&participacio, 1, 1);
    if (llista_propietats_esta_buida(llista) == false) {
        fraccio_copia(&participacio, node->participacio_general);
        node = node_propietat_seguent(*iterador);
        while (node_propietat_ultim(*iterador) == false) {
            fraccio_suma(&participacio, participacio, node->participacio_general);
            node = node_propietat_seguent(*iterador);
            iterador = node;
        }
    }
    return participacio;
}

void llista_propietats_verifica(llista_propietats_t llista) {
    fraccio_t fraccio_verificacio;
    node_propietat_t *node = llista.punter;
    ptr_node_propietat_t iterador = node;
    /* Participacions generals
     */
    if (fraccio_unitat(fraccio_verificacio = llista_propietats_suma_participacions_generals(llista)) == false) {
        printf("VERIFICACIO: la suma de participacions generals no és vàlida: %lu/%lu\n",
                fraccio_verificacio.numerador, fraccio_verificacio.denominador);
    }
    /* participacions x propietats
     */
    if (llista_propietats_esta_buida(llista) == false) {
        while (node_propietat_ultim(*iterador) == false) {
            node_propietat_verifica(node);
            iterador = node;
            node = node_propietat_seguent(*iterador);
        }
    }
}
