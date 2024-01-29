#include "llistat.h"

void llistat(char *any, llista_propietaris_t llista_propietaris, llista_propietats_t llista_propietats) {
    ptr_node_propietari_t iterador_llista_propietaris;
    ptr_node_propietat_t iterador_llista_propietats;
    ptr_node_participacio_t iterador_llista_participacions;
    node_propietari_t *node_propietari;
    node_propietat_t *node_propietat;
    node_participacio_t *node_participacio;
    fraccio_t participacio, fraccio_temporal, fraccio_acomulador;
    bool start = false;
    char str_participacio[6];
    double float_fraccio_acomulador = 0, float_participacio;
    long unsigned int i;

    FILE *fp = crear_fitxer(any, "-participacions.txt");
    if (fp == NULL) {
        printf("No es pot crear el fitxer %s-propietats.txt\n", any);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%-6s  %-35s %s %30s%10s\n", "idProp", "Nom", "Email", "Part(fracc)", "Part(%)");
    fprintf(fp, "-------------------------------------------------------------------------------------------------\n");
    iterador_llista_propietaris = llista_propietaris.punter;
    for (i = 0; i < llista_propietaris.numelem; i++) {
        bool trobat = false;
        node_propietari = iterador_llista_propietaris;
        unsigned long idPropietari = node_propietari->idPropietari;
        iterador_llista_propietats = llista_propietats.punter;
        long unsigned int j;
        for (j = 0; j < llista_propietats.numelem; j++) {
            node_propietat = iterador_llista_propietats;
            if (llista_participacions_troba_id(node_propietat->llista_participacions, idPropietari, &iterador_llista_participacions) == true) {
                node_participacio = iterador_llista_participacions;
                if (trobat == false) {
                    fraccio_multiplica(&participacio, node_participacio->participacio, node_propietat->participacio_general);
                    trobat = true;
                } else {
                    fraccio_multiplica(&fraccio_temporal, node_participacio->participacio, node_propietat->participacio_general);
                    fraccio_suma(&participacio, fraccio_temporal, participacio);
                }
            }
            iterador_llista_propietats = node_propietat_seguent(*node_propietat);
        }
        if (trobat == true) {
            if (start == false) {
                fraccio_copia(&fraccio_acomulador, participacio);
                start = true;
            } else {
                fraccio_suma(&fraccio_acomulador, participacio, fraccio_acomulador);
            }
            sprintf(str_participacio, "%3.2f", ((double) 100 * participacio.numerador) / ((double) participacio.denominador));
            float_participacio = atof(str_participacio);
            float_fraccio_acomulador += float_participacio;
            fprintf(fp, "%6lu  %-35s %-25s %3lu/%-3lu %10s%c\n", idPropietari, (*iterador_llista_propietaris).nom, (*iterador_llista_propietaris).email,
                    participacio.numerador, participacio.denominador, str_participacio, '%');
        }
        iterador_llista_propietaris = node_propietari_seguent(*node_propietari);
    }
    fprintf(fp, "-------------------------------------------------------------------------------------------------\n");
    fprintf(fp, "%6lu propietaris %50s %3lu/%-3lu %10.2f%c\n", llista_propietaris.numelem, "TOTAL", fraccio_acomulador.numerador, fraccio_acomulador.denominador, float_fraccio_acomulador, '%');
    fclose(fp);
}
