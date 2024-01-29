/* 
 * File:   lectura_propietats.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "lectura_propietats.h"

/* llegeix els fitxers any-propietats.txt i ant-
 * i carrega les seves dades a les llistes de propietaris i propietats
 * byval any
 * byref llista_propietaris
 */
void lectura_propietats(llista_propietaris_t *llista_propietaris, llista_propietats_t *llista_propietats, char* any) {
    FILE *fp;
    char *linia = NULL;
    bool tractament_propietaris = false, tractament_propietats = false;
    int longitut = 0;

    fp = obrir_fitxer(any, "-propietats.txt");
    if (fp == NULL) {
        printf("No es pot llegir el fitxer %s-propietats.txt\n", any);
        exit(EXIT_FAILURE);
    }
    while (llegir_linia(fp, &linia, &longitut) != EOF) {
        if (longitut > 0) {
            if (formateja_linia(&linia) != 0) {
                if (tractament_propietaris == true) {
                    tractar_propietari_linia_propietats(llista_propietaris, linia, &tractament_propietaris, &tractament_propietats);
                } else {
                    if (tractament_propietats == true) {
                        tractar_propietat_linia_propietats(llista_propietats, linia, &tractament_propietaris, &tractament_propietats);
                    } else {
                        if (*linia == '#') {
                            tractament_propietaris = linia_igual(linia, "#propietaris");
                            tractament_propietats = linia_igual(linia, "#propietats");
                            if ((tractament_propietats != true) && (tractament_propietaris != true)) {
                                printf("ERROR: Format de fitxer incorrecte\n");
                                exit(EXIT_FAILURE);
                            }
                        } else {
                            if (*linia != '.') {
                                printf("ERROR: format de fitxer incorrecte\n");
                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                }
            }
        }
        if (linia != NULL) {
            free((char *) linia);
            linia = NULL;
        }
    }
    fclose(fp);
    printf("propietaris %s\t: %lu\n", any, (*llista_propietaris).numelem);
    printf("propietats \t\t: %lu\n", (*llista_propietats).numelem);
}

/* actualment s'estan tractant les propietats
 * byval linia
 * byref tractament_propietaris
 * byref tractament_propietats
 * byref llista_propietaris
 */
void tractar_propietat_linia_propietats(llista_propietats_t *llista, char *linia, bool *tractament_propietaris, bool *tractament_propietats) {
    unsigned long idPropietat, idPropietari;
    size_t start, end, width;
    char *p_start = NULL, *p_end = NULL;
    char *temp, *nom;
    fraccio_t participacio_general, fraccio_participacio;
    if (*linia != '.') {
        if (*linia == '#') {
            *tractament_propietaris = linia_igual(linia, "#propietaris");
            if (*tractament_propietaris != true) {
                printf("ERROR: Format de fitxer incorrecte\n");
                exit(EXIT_FAILURE);
            }
            *tractament_propietats = false;
        } else {
            /*
             * idPropietat
             */
            p_start = linia;
            p_end = strstr(p_start, ";");
            start = strlen(p_start);
            end = strlen(p_end);
            width = start - end;
            temp = (char *) malloc(sizeof (char) * (width + 1));
            strncpy(temp, p_start, width);
            temp[width]= '\0';
            idPropietat = (unsigned long) atol(temp);
            free((char *) temp);
            temp = NULL;
            /*
             * nom
             */
            p_start = p_end + 1;
            p_end = strstr(p_start, ";");
            start = strlen(p_start);
            end = strlen(p_end);
            width = start - end;
            nom = (char *) malloc(sizeof (char) * (width + 1));
            strncpy(nom, p_start, width);
            nom[width]= '\0';
            /*
             * participació general
             */
            p_start = p_end + 1;
            p_end = strstr(p_start, ";");
            start = strlen(p_start);
            end = strlen(p_end);
            width = start - end;
            temp = (char *) malloc(sizeof (char) * (width + 1));
            strncpy(temp, p_start, width);
            temp[width]= '\0';
            text2fraccio(temp, &participacio_general);
            free((char *) temp);
            /* introduir a la llista */
            llista_propietats_afegir_node(llista, &nom, participacio_general, idPropietat);
            /*
             * participacions
             */
            p_start = p_end + 1;
            p_end = strstr(p_start, ":");
            while (p_end != NULL) {
                /*
                 * idPropietari
                 */
                start = strlen(p_start);
                end = strlen(p_end);
                width = start - end;
                temp = (char *) malloc(sizeof (char) * (width + 1));
                strncpy(temp, p_start, width);
                temp[width]= '\0';
                idPropietari = (unsigned long) atol(temp);
                free((char *) temp);
                temp = NULL;
                /*
                 * fraccio_participacio
                 */
                p_start = p_end + 1;
                p_end = strstr(p_start, "&");
                if (p_end == NULL) {
                	width = strlen(p_start);
                    temp = (char *) malloc(sizeof (char) * (width + 1));
                    strncpy(temp, p_start, width);
                } else {
                    start = strlen(p_start);
                    end = strlen(p_end);
                    width = start - end;
                    temp = (char *) malloc(sizeof (char) * (width + 1));
                    strncpy(temp, p_start, width);
                    p_start = p_end + 1;
                    p_end = strstr(p_start, ":");
                }
                temp[width]= '\0';
                text2fraccio(temp, &fraccio_participacio);
                free((char *) temp);
                /* introduir a la llista */
                llista_propietats_afegir_particio_node(*llista, idPropietat, idPropietari, fraccio_participacio);
            }

            p_start = NULL;
            p_end = NULL;
        }
    }
}

/* actualment s'estan tractan els propietaris
 * byval linia
 * byref tractament_propietaris
 * byref tractament_propietats
 * byref llista_propietaris
 */
void tractar_propietari_linia_propietats(llista_propietaris_t *llista, char *linia, bool *tractament_propietaris, bool *tractament_propietats) {
    unsigned long idPropietari;
    size_t start, end, width;
    char *p_start = NULL, *p_end = NULL;
    char *temp, *email, *nom;
    if (*linia != '.') {
        if (*linia == '#') {
            *tractament_propietats = linia_igual(linia, "#propietats");
            if (*tractament_propietats != true) {
                printf("ERROR: Format de fitxer incorrecte\n");
                exit(EXIT_FAILURE);
            }
            *tractament_propietaris = false;
        } else {
            /*
             * idPropietari
             */
            p_start = linia;
            p_end = strstr(p_start, ";");
            start = strlen(p_start);
            end = strlen(p_end);
            width = start - end;
            temp = (char *) malloc(sizeof (char) * (width + 1));
            strncpy(temp, p_start, width);
            temp[width]= '\0';
            idPropietari = (unsigned long) atol(temp);
            free((char *) temp);
            /*
             * nom
             */
            p_start = p_end + 1;
            p_end = strstr(p_start, ";");
            start = strlen(p_start);
            end = strlen(p_end);
            width = start - end;
            nom = (char *) malloc(sizeof (char) * (width + 1));
            strncpy(nom, p_start, width);
            nom[width]= '\0';
            /*
             * email
             */
            p_start = p_end + 1;
            width = strlen(p_start);
            email = (char *) malloc(sizeof (char) * (width + 1));
            strncpy(email, p_start, width);
            email[width]= '\0';

            llista_propietaris_afegir_node(llista, &nom, &email, idPropietari);
        }
    }
}
