/* 
 * File:   g_compropietaris.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include <stdio.h>
#include <stdlib.h>

#include "lectura_propietats.h"
#include "lectura_transmissions.h"
#include "verificacio_participacions.h"
#include "fusio.h"
#include "llistat.h"

int main(int argc, char** argv) {
    llista_propietaris_t llista_propietaris;
    llista_propietaris_t llista_propietaris_nous;
    llista_propietats_t llista_propietats;
    llista_transmissions_t llista_transmissions;

    if (argc != 2) {
        printf("USAGE:\n\t%s any\n\n", argv[0]);
        return (EXIT_FAILURE);
    }

    llista_propietaris_crear_llista(&llista_propietaris);
    llista_propietaris_crear_llista(&llista_propietaris_nous);
    llista_propietats_crear_llista(&llista_propietats);
    llista_transmissions_crear_llista(&llista_transmissions);

    printf("Processant any: %s...\n", argv[1]);
    printf("Registres llegits:\n");

    /* Exercici 1
     */
    lectura_propietats(&llista_propietaris, &llista_propietats, argv[1]);
    lectura_transmissions(&llista_propietaris_nous, &llista_transmissions, argv[1]);

    /* Exercici 2
     */
    verificacio_participacions(llista_propietats, llista_transmissions);

    /* Exercici 3
     */
    fusio(argv[1], &llista_propietaris, &llista_propietaris_nous, &llista_propietats, &llista_transmissions);

    /*
     * Exercixi 4
     */
    llistat(argv[1], llista_propietaris, llista_propietats);

    llista_propietaris_destrueix_llista(&llista_propietaris_nous);
    llista_propietaris_destrueix_llista(&llista_propietaris);
    llista_propietats_destrueix_llista(&llista_propietats);
    llista_transmissions_destrueix_llista(&llista_transmissions);

    return (EXIT_SUCCESS);
}
