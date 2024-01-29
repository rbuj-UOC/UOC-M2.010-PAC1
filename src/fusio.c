#include "fusio.h"

/*
 * Exercici 3
 */
void fusio(char *any, llista_propietaris_t *llista_propietaris, llista_propietaris_t *llista_propietaris_nous, llista_propietats_t *llista_propietats, llista_transmissions_t *llista_transmissions) {
    fusio_propietaris(llista_propietaris, llista_propietaris_nous);
    fusio_participacions(llista_propietats, *llista_transmissions);
    fusio_propietaris_propietats(llista_propietaris, *llista_propietats);
    fusio_fitxer(any, *llista_propietaris, *llista_propietats);
}

void fusio_fitxer(char *any, llista_propietaris_t llista_propietaris, llista_propietats_t llista_propietats) {
    char any_seguent[12];
    sprintf(any_seguent, "%i", atoi(any) + 1);
    FILE *fp = crear_fitxer(any_seguent, "-propietats.txt");
    if (fp == NULL) {
        printf("No es pot crear el fitxer %s-propietats.txt\n", any_seguent);
        exit(EXIT_FAILURE);
    }
    fusio_fitxer_propietaris(fp, llista_propietaris);
    fusio_fitxer_propietats(fp, llista_propietats);
    fclose(fp);
}

/*
 * Fusiona dos llistes de propietaris, afegint els propietaris nous als ja existents,
 * eliminant els tractats de la llista de propietaris nous.
 */
void fusio_propietaris(llista_propietaris_t *llista_propietaris, llista_propietaris_t *llista_propietaris_nous) {
    llista_propietaris_fusiona(llista_propietaris, llista_propietaris_nous);
}

/*
 * Per a cada transaccio aplicar-la a la llista de propietats:
 * 1-Agafar l'identificador de l'antic propietari i de la propietat de la transaccio
 * 2-trobar el node de la llista de propietats amb l'idenificador de l'antic propietari i la propietat
 *
 * Si idPropietat <> 0
 * 3-Agafar la participacio de l'antic propietari/propietat de la llista de propietats
 * 4-Eliminar de la llista de propietats el propietari/propitat antic
 * 5-Afegir el nou propietari, multiplicant el valor de la participacio de l'antic propietari amb la del nou
 *
 * Si idPropietat == 0 (Totes les propietats)
 * 6-Recorrer tots el nodes de la llista de propietats
 * 7-per a cada node de propietats cercar si existeix el propietari a modificar totes les seves propietats
 * 8-Agafar la participacio i propietat de l'antic propietari de la llista de propietats
 * 9-Eliminar de la llista de propietats el propietari/propitat antic
 * 10-Afegir el nou propietari, multiplicant el valor de la participacio de l'antic propietari amb la del nou
 */
void fusio_participacions(llista_propietats_t *llista_propietats, llista_transmissions_t llista_transmissions) {
    long unsigned int i, j, k, l;

    node_registre_t *node_registre_transmissio;
    node_participacio_t *node_participacio_registre_transmissio;
    node_propietat_t node_propietat;

    ptr_node_transmissio_t iterador_llista_transmissions;
    ptr_node_registre_t iterador_llista_registres;
    ptr_node_propietat_t iterador_llista_propietats;
    ptr_node_participacio_t iterador_llista_participacions, iterador_participacio_registre_transmissio;

    unsigned long idPropietat, idNouPropietari;
    fraccio_t participacio_anterior, participacio_de_participacio, participacio;

    iterador_llista_transmissions = llista_transmissions.punter;
    for (i = 0; i < llista_transmissions.numelem; i++) {
        node_transmissio_t *node_transmissio;
        unsigned long idPropietariAntic;

        /* 1.1/2 */
        idPropietariAntic = (*iterador_llista_transmissions).idPropietariAnterior;
        iterador_llista_registres = (*iterador_llista_transmissions).llista_registres.punter;
        for (j = 0; j < (*iterador_llista_transmissions).llista_registres.numelem; j++) {
            /* 1.2/2 */
            idPropietat = (*iterador_llista_registres).idPropietat;
            if (idPropietat != 0) {
                /* 2.1/2 */
                if (llista_propietats_troba_idPropietat(*(llista_propietats), idPropietat, &iterador_llista_propietats) == true) {
                    /* 2.1/2 */
                    if (llista_participacions_troba_id((iterador_llista_propietats->llista_participacions), idPropietariAntic, &iterador_llista_participacions) == true) {
                        /* 3 */
                        fraccio_copia(&participacio_anterior, (*iterador_llista_participacions).participacio);
                        /* 4 */
                        llista_participacions_eliminar_id(&(iterador_llista_propietats->llista_participacions), idPropietariAntic);
                        /* 5 */
                        iterador_participacio_registre_transmissio = (*iterador_llista_registres).llista_participacions.ptr_node_participacio;
                        for (k = 0; k < (*iterador_llista_registres).llista_participacions.numelem; k++) {
                            idNouPropietari = (*iterador_participacio_registre_transmissio).id;
                            fraccio_copia(&participacio, (*iterador_participacio_registre_transmissio).participacio);
                            fraccio_multiplica(&participacio_de_participacio, participacio_anterior, participacio);
                            llista_propietats_afegir_particio_node(*llista_propietats, idPropietat, idNouPropietari, participacio_de_participacio);

                            node_participacio_registre_transmissio = iterador_participacio_registre_transmissio;
                            iterador_participacio_registre_transmissio = node_participacio_seguent(*node_participacio_registre_transmissio);
                        }
                    }
                }
            } else {
                /* 6 */
                iterador_llista_propietats = llista_propietats->punter;
                for (k = 0; k < llista_propietats->numelem; k++) {
                    /* 7 */
                    if (llista_participacions_troba_id((iterador_llista_propietats->llista_participacions), idPropietariAntic, &iterador_llista_participacions) == true) {
                        /* 8 */
                        idPropietat = (*iterador_llista_propietats).idPropietat;
                        fraccio_copia(&participacio_anterior, (*iterador_llista_participacions).participacio);
                        /* 9 */
                        llista_participacions_eliminar_id(&(iterador_llista_propietats->llista_participacions), idPropietariAntic);
                        /* 10 */
                        iterador_participacio_registre_transmissio = (*iterador_llista_registres).llista_participacions.ptr_node_participacio;
                        for (l = 0; l < (*iterador_llista_registres).llista_participacions.numelem; l++) {
                            idNouPropietari = (*iterador_participacio_registre_transmissio).id;
                            fraccio_copia(&participacio, (*iterador_participacio_registre_transmissio).participacio);
                            fraccio_multiplica(&participacio_de_participacio, participacio_anterior, participacio);
                            llista_propietats_afegir_particio_node(*llista_propietats, idPropietat, idNouPropietari, participacio_de_participacio);

                            node_participacio_registre_transmissio = iterador_participacio_registre_transmissio;
                            iterador_participacio_registre_transmissio = node_participacio_seguent(*node_participacio_registre_transmissio);
                        }
                    }
                    node_propietat = *iterador_llista_propietats;
                    iterador_llista_propietats = node_propietat_seguent(node_propietat);
                }
            }
            node_registre_transmissio = iterador_llista_registres;
            iterador_llista_registres = node_registre_seguent(*node_registre_transmissio);
        }
        node_transmissio = iterador_llista_transmissions;
        iterador_llista_transmissions = node_transmissio_seguent(*node_transmissio);
    }
}

/*
 * Elimina els propietaris de la llista de propietaris que actualment no tenen propietats
 */
void fusio_propietaris_propietats(llista_propietaris_t *llista_propietaris,
        llista_propietats_t llista_propietats) {
    long unsigned int i;

    ptr_node_propietari_t iterador_llista_propietaris = llista_propietaris->punter;
    for (i = 0; i < llista_propietaris->numelem; i++) {
        node_propietari_t * node_propietari;
        unsigned long int idPropietari;
        ptr_node_propietat_t iterador_llista_propietats;
        bool trobat;
        long unsigned int j;

        node_propietari = iterador_llista_propietaris;
        idPropietari = node_propietari->idPropietari;
        iterador_llista_propietats = llista_propietats.punter;
        trobat = false;

        for (j = 0; ((j < llista_propietats.numelem) && (trobat == false)); j++) {
            node_propietat_t *node_propietat;

            node_propietat = iterador_llista_propietats;
            trobat = llista_participacions_existeix_id(node_propietat->llista_participacions, idPropietari);
            iterador_llista_propietats = node_propietat_seguent(*node_propietat);
        }
        iterador_llista_propietaris = node_propietari_seguent(*node_propietari);
        if (trobat == false) {
            llista_propietaris_eliminar_id(llista_propietaris, idPropietari);
        }
    }
}

void fusio_fitxer_propietats(FILE *fp, llista_propietats_t llista) {
    ptr_node_propietat_t iterador_llista_propietats;
    ptr_node_participacio_t iterador_llista_participacions;
    node_participacio_t *node_participacio;
    long unsigned int i;

    fprintf(fp, "\n#propietats\n");
    iterador_llista_propietats = llista.punter;
    for (i = 0; i < llista.numelem; i++) {
        node_propietat_t *node_propietat;
        long unsigned int j;

        fprintf(fp, "%lu; %s; %lu/%lu;", (*iterador_llista_propietats).idPropietat,
                (*iterador_llista_propietats).nom,
                (*iterador_llista_propietats).participacio_general.numerador,
                (*iterador_llista_propietats).participacio_general.denominador);
        iterador_llista_participacions = (*iterador_llista_propietats).llista_participacions.ptr_node_participacio;
        for (j = 0; j < (*iterador_llista_propietats).llista_participacions.numelem; j++) {
            fprintf(fp, " %lu : %lu/%lu", (*iterador_llista_participacions).id,
                    (*iterador_llista_participacions).participacio.numerador,
                    (*iterador_llista_participacions).participacio.denominador);

            if (j < ((*iterador_llista_propietats).llista_participacions.numelem) - 1) {
                fprintf(fp, " &");
            }
            node_participacio = iterador_llista_participacions;
            iterador_llista_participacions = node_participacio_seguent(*node_participacio);
        }
        fprintf(fp, "\n");
        node_propietat = iterador_llista_propietats;
        iterador_llista_propietats = node_propietat_seguent(*node_propietat);
    }
}

void fusio_fitxer_propietaris(FILE *fp, llista_propietaris_t llista) {
    ptr_node_propietari_t iterador_llista_propietaris;
    long unsigned int i;

    fprintf(fp, "#propietaris\n");
    iterador_llista_propietaris = llista.punter;
    for (i = 0; i < llista.numelem; i++) {
        node_propietari_t *node_propietari;

        fprintf(fp, "%lu; %s; %s\n", (*iterador_llista_propietaris).idPropietari,
                (*iterador_llista_propietaris).nom,
                (*iterador_llista_propietaris).email);
        node_propietari = iterador_llista_propietaris;
        iterador_llista_propietaris = node_propietari_seguent(*node_propietari);
    }
}
