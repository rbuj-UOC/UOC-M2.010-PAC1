/* 
 * File:   lines.c
 * Author: Robert Buj Gelonch (rbuj@uoc.edu)
 *
 * Introducció al desenvolupament de programari
 * Master programari lliure - UOC - PAC1
 */

#include "linies.h"

/* elimina un caracter d'una linia (byref) donada la seva posició, retorna la
 * longitud de la linia un cop eliminat el caràcter. posi[0,N]
 */
size_t elimina_caracter_linia(char **linia, size_t posi) {
    size_t longitut = strlen(*linia);
    char *temp2, *temp;

    temp = (char*) alloca(longitut * sizeof (char));
    if (posi == longitut - 1) {
        // eliminar l'últim caràcter de la línia
        strncpy(temp, *linia, longitut - 1);
        temp[longitut] = '\0';
    } else {
        if (posi == 0) {
            // eliminar el primer caràcter de la línia
            strcpy(temp, *linia + 1);
        } else {
            //eliminar un caràcter del mig
            temp2 = (char*) alloca((posi + 1) * sizeof (char));
            strncpy(temp2, *linia, posi);
            temp2[posi] = '\0';
            strcpy(temp, temp2);
            strcat(temp, *linia + posi + 1);
        }
    }
    strcpy(*linia, temp);
    return strlen(*linia);
}

/* formateja una línia (byref) i retorna la seva longitud
 */
size_t formateja_linia(char **linia_ori) {
    bool modificat = false;
    char *linia = (char *) alloca((strlen(*linia_ori) + 1) * sizeof (char));
    strcpy(linia, *linia_ori);
    if (formateja_linia_tabuladors(&linia) == true) {
        modificat = true;
    }
    if (formateja_linia_inici(&linia) == true) {
        modificat = true;
    }
    if (formateja_linia_espais(&linia) == true) {
        modificat = true;
    }
    if (modificat == true) {
        strcpy(*linia_ori, linia);
    }
    return strlen(*linia_ori);
}

/* converteix els tabuladors d'una linia (byref) en espais
 */
bool formateja_linia_tabuladors(char **linia) {
    size_t longitut = strlen(*linia);
    bool modificat = false;
    if (longitut > 0) {
        size_t i;
        char* ptr = *linia;
        for (i = 0; i < longitut; i++) {
            if (*ptr == '\t') {
                *ptr = ' ';
                modificat = true;
            }
            ptr++;
        }
        ptr = NULL;
    }
    return modificat;
}

/* elimina els espais en blanc inicials d'una línia (byref).
 * retorna la longitud de la nova línia.
 */
bool formateja_linia_inici(char **linia_ori) {
    size_t longitut = strlen(*linia_ori);
    bool modificat = false;
    if (longitut > 0) {
        char *linia = (char *) alloca(sizeof (char) * (longitut + 1));
        strcpy(linia, *linia_ori);
        char* ptr = linia;
        while ((*ptr == ' ') && (longitut > 0)) {
            ptr = NULL;
            elimina_caracter_linia(&linia, 0);
            longitut--;
            ptr = linia;
            modificat = true;
        }
        if (modificat == true) {
            strcpy(*linia_ori, linia);
        }
        ptr = NULL;
    }
    return modificat;
}

/* elimina els espais en blanc innecesaris d'una línia (byref).
 * retorna la longitud de la nova línia.
 */
bool formateja_linia_espais(char **linia_ori) {
    bool modificat = false;
    size_t longitut = strlen(*linia_ori);
    char *linia = alloca(sizeof (char) *(longitut + 1));
    char *ptr = NULL;
    size_t posi;

    // eliminar dos espais consecutius
    if (longitut > 0) {
        strcpy(linia, *linia_ori);
        ptr = strstr(linia, "  ");
        while ((ptr != NULL) && (longitut > 0)) {
            posi = longitut - strlen(ptr);
            longitut = elimina_caracter_linia(&linia, posi);
            ptr = strstr(linia, "  ");
            modificat = true;
        }
        ptr = NULL;
    }
    // eliminar espai abans del separador ;
    if (longitut > 0) {
        ptr = strstr(linia, " ;");
        while ((ptr != NULL) && (longitut > 0)) {
            posi = longitut - strlen(ptr);
            longitut = elimina_caracter_linia(&linia, posi);
            ptr = strstr(linia, " ;");
            modificat = true;
        }
        ptr = NULL;
    }
    // eliminar espai després del separador ;
    if (longitut > 0) {
        ptr = strstr(linia, "; ");
        while ((ptr != NULL) && (longitut > 0)) {
            posi = longitut - strlen(ptr) + 1;
            longitut = elimina_caracter_linia(&linia, posi);
            ptr = strstr(linia, "; ");
            modificat = true;
        }
        ptr = NULL;
    }
    // eliminar espai abans del separador :
    if (longitut > 0) {
        ptr = strstr(linia, " :");
        while ((ptr != NULL) && (longitut > 0)) {
            posi = longitut - strlen(ptr);
            longitut = elimina_caracter_linia(&linia, posi);
            ptr = strstr(linia, " :");
            modificat = true;
        }
        ptr = NULL;
    }
    // eliminar espai després del separador :
    if (longitut > 0) {
        ptr = strstr(linia, ": ");
        while ((ptr != NULL) && (longitut > 0)) {
            posi = longitut - strlen(ptr) + 1;
            longitut = elimina_caracter_linia(&linia, posi);
            ptr = strstr(linia, ": ");
            modificat = true;
        }
        ptr = NULL;
    }
    // eliminar espai abans del separador &
    if (longitut > 0) {
        ptr = strstr(linia, " &");
        while ((ptr != NULL) && (longitut > 0)) {
            posi = longitut - strlen(ptr);
            longitut = elimina_caracter_linia(&linia, posi);
            ptr = strstr(linia, " &");
            modificat = true;
        }
        ptr = NULL;
    }
    // eliminar espai després del separador &
    if (longitut > 0) {
        ptr = strstr(linia, "& ");
        while ((ptr != NULL) && (longitut > 0)) {
            posi = longitut - strlen(ptr) + 1;
            longitut = elimina_caracter_linia(&linia, posi);
            ptr = strstr(linia, "& ");
            modificat = true;
        }
        ptr = NULL;
    }
    // eliminar espai abans del separador /
    if (longitut > 0) {
        ptr = strstr(linia, " /");
        while ((ptr != NULL) && (longitut > 0)) {
            posi = longitut - strlen(ptr);
            longitut = elimina_caracter_linia(&linia, posi);
            ptr = strstr(linia, " /");
            modificat = true;
        }
        ptr = NULL;
    }
    // eliminar espai després del separador /
    if (longitut > 0) {
        ptr = strstr(linia, "/ ");
        while ((ptr != NULL) && (longitut > 0)) {
            posi = longitut - strlen(ptr) + 1;
            longitut = elimina_caracter_linia(&linia, posi);
            ptr = strstr(linia, "/ ");
            modificat = true;
        }
        ptr = NULL;
    }
    // eliminar espai abans del separador >
    if (longitut > 0) {
        ptr = strstr(linia, " >");
        while ((ptr != NULL) && (longitut > 0)) {
            posi = longitut - strlen(ptr);
            longitut = elimina_caracter_linia(&linia, posi);
            ptr = strstr(linia, " >");
            modificat = true;
        }
        ptr = NULL;
    }
    // eliminar espai després del separador >
    if (longitut > 0) {
        ptr = strstr(linia, "> ");
        while ((ptr != NULL) && (longitut > 0)) {
            posi = longitut - strlen(ptr) + 1;
            longitut = elimina_caracter_linia(&linia, posi);
            ptr = strstr(linia, "> ");
            modificat = true;
        }
        ptr = NULL;
    }

    if (modificat == true) {
        strcpy(*linia_ori, linia);
    }
    return modificat;
}

bool linia_igual(char *linia, const char* cadena) {
    return (strcmp(linia, cadena) == 0) ? true : false;
}
