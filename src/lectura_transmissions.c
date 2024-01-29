/* 
 * File:   lectura_transmissions.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "lectura_transmissions.h"

void lectura_transmissions(llista_propietaris_t *llista_propietaris, llista_transmissions_t *llista_transmissions, char* any) {
    FILE *fp;
    char *linia = NULL;
    bool tractament_propietaris = false, tractament_transmissions = false;
    unsigned long idPropietariAnterior;
    dia_t data_transmissio;
    int longitut = 0;

    fp = obrir_fitxer(any, "-transmissions.txt");
    if (fp == NULL) {
        printf("No es pot llegir el fitxer %s-transmissions.txt\n", any);
        exit(EXIT_FAILURE);
    }
    while (llegir_linia(fp, &linia, &longitut) != EOF) {
        if (longitut > 0) {
            if (formateja_linia(&linia) != 0) {
                if (tractament_propietaris == true) {
                    tractar_propietari_linia_transmissions(llista_propietaris, linia, &tractament_propietaris, &tractament_transmissions);
                } else {
                    if (tractament_transmissions == true) {
                        tractar_transmissio_linia_transmissions(llista_transmissions, linia, &tractament_propietaris, &tractament_transmissions, &idPropietariAnterior, &data_transmissio);
                    } else {
                        if (*linia == '#') {
                            tractament_propietaris = linia_igual(linia, "#nous propietaris");
                            tractament_transmissions = linia_igual(linia, "#transmissions");
                            if ((tractament_transmissions != true) && (tractament_propietaris != true)) {
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
    printf("propietaris nous\t: %lu\n", (*llista_propietaris).numelem);
    printf("transmissions\t\t: %lu\n", (*llista_transmissions).numelem);
}

void tractar_propietari_linia_transmissions(llista_propietaris_t *llista, char *linia, bool *tractament_propietaris, bool *tractament_transmissions) {
    unsigned long idPropietari;
    size_t start, end, width;
    char *p_start = NULL, *p_end = NULL;
    char *temp, *email, *nom;
    if (*linia != '.') {
        if (*linia == '#') {
            *tractament_transmissions = linia_igual(linia, "#transmissions");
            if (*tractament_transmissions != true) {
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
            nom = (char *) malloc(sizeof(char) * (width + 1));
            strncpy(nom, p_start, width);
            nom[width]= '\0';
            /*
             * email
             */
            p_start = p_end + 1;
            width = strlen(p_start);
            email = (char *) malloc(sizeof(char) * (width + 1));
            strncpy(email, p_start, width);
            email[width]= '\0';
            /*
             * Introduir a la llista
             */
            llista_propietaris_afegir_node(llista, &nom, &email, idPropietari);
        }
    }
}

void tractar_transmissio_linia_transmissions(llista_transmissions_t *llista, char *linia,
        bool *tractament_propietaris, bool *tractament_transmissions,
        unsigned long *idPropietariAnterior, dia_t *data_transmissio) {
    size_t start, end, width;
    char *p_start = NULL, *p_end = NULL;
    char *motiu, *temp;
    unsigned long idPropietat;
    fraccio_t fraccio_participacio;
    (void) tractament_transmissions;

    if (*linia != '.') {
        if (*linia == '#') {
            *tractament_propietaris = linia_igual(linia, "#nous propietaris");
            if (*tractament_propietaris != true) {
                printf("ERROR: Format de fitxer incorrecte\n");
                exit(EXIT_FAILURE);
            }
            *tractament_propietaris = false;
        } else {
            if (*linia == '>') {
                // Antic Propietari
                /*
                 * idPropietari
                 */
                p_start = linia + 1;
                p_end = strstr(p_start, ";");
                start = strlen(p_start);
                end = strlen(p_end);
                width = start - end;
                temp = (char *) malloc(sizeof (char) * (width + 1));
                strncpy(temp, p_start, width);
                temp[width] = '\0';
                *idPropietariAnterior = (unsigned long) atol(temp);
                free((char *) temp);
                /*
                 * data
                 */
                p_start = p_end + 1;
                p_end = strstr(p_start, ";");
                start = strlen(p_start);
                end = strlen(p_end);
                width = start - end;
                temp = (char *) malloc(sizeof (char) * (width + 1));
                strncpy(temp, p_start, width);
                temp[width] = '\0';
                text2dia(temp, data_transmissio);
                free((char *) temp);
                /*
                 * motiu
                 */
                p_start = p_end + 1;
                width = strlen(p_start);
                motiu = (char *) malloc(sizeof (char) * (width+ 1));
                strcpy(motiu, p_start);
                motiu[width] = '\0';
                /*
                 * Introduir antic propietari a la llista
                 */
                llista_transmissions_afegir_node(llista, *idPropietariAnterior, *data_transmissio, &motiu);
            } else {
                // Finca
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
                temp[width] = '\0';
                idPropietat = (unsigned long) atol(temp);
                free((char *) temp);
                /* Introduir Finca de l'Antic propietari a la llista */
                llista_transmissions_afegir_registre_node(*llista, *idPropietariAnterior, *data_transmissio, idPropietat);
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
                    temp[width] = '\0';
                    unsigned long idNouPropietari = (unsigned long) atol(temp);
                    free((char *) temp);
                    /*
                     * fraccio_participacio
                     */
                    p_start = p_end + 1;
                    p_end = strstr(p_start, "&");
                    if (p_end == NULL) {
                        width = strlen(p_start);
                        temp = (char *) malloc(sizeof (char) * (width + 1));
                        strcpy(temp, p_start);
                    } else {
                        start = strlen(p_start);
                        end = strlen(p_end);
                        width = start - end;
                        temp = (char *) malloc(sizeof (char) * (width + 1));
                        strncpy(temp, p_start, width);
                        p_start = p_end + 1;
                        p_end = strstr(p_start, ":");
                    }
                    temp[width] = '\0';
                    text2fraccio(temp, &fraccio_participacio);
                    free((char *) temp);
                    /* introduir a la llista */
                    llista_transmissions_afegir_particio_registre_node(*llista, *idPropietariAnterior, *data_transmissio, idPropietat, idNouPropietari, fraccio_participacio);
                }
            }
        }
    }
}
