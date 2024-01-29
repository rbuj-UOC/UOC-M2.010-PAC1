# Enunciat
Desenvolupar una aplicació, que anomenarem “g_compropietaris”, que gestiona informació relativa a una petita comunitat de propietaris.

Aquesta comunitat gestiona diverses finques, on cada finca pot tenir diversos propietaris de forma indivisa (és a dir, la propietat es compartida i no es pot dividir en finques més petites) i cada finca, a més, té un grau de participació als ingressos i despeses generals de la comunitat.

La informació de la comunitat es troba dins un fitxer text anomenat “(any)-propietats.txt”, on (any) es refereix a l'any de referència i que conté la llista de propietaris (amb id, nom i email) i la llista de propietats (amb numfinca, nom finca, grau de participacio general dins la comunitat, i llista de propietaris amb el seu grau de participacio dins la finca) .

No obstant, la informació dels propietaris va canviant amb el pas del temps degut a transmissions patrimonials (per herència, compravenda, donació, ...). Les operacions de canvis de titularitat que s'han realitzat durant tot l'any es troben recollides dins el fitxer “(any)-transmissions.txt” .

A partir d'aquest document i de l'anterior comentat de propietats, es genera el fitxer de propietats i propietaris de l'any següent:

```
2010-propietats.txt + 2011-transmissions.txt ---> 2011-propietats.txt
```

detall fitxer (any)-propietats:
```
.Comentari: Fitxer de propietats i propietaris de l'any 2010
#propietaris
idPropietari; nom i cognoms; email
...
#propietats
numfinca; nom finca;participacio general; propietari: participacio & propietari: participacio ...
```
on:
- es fa servir el caràcter “;” (punt i coma) com a separador de camps.
- el grau de participació s'expressa en forma de fracció (“1” o “1/2” o “1/3”).
Aquest punt és important, doncs en aquest cas fer arrodoniment no són correctes (un 0,01% d'un valor de milions d'euros, pot ser una quantitat significativa).
- a la llista de propietaris cada un dels propietaris s'expressa amb la parella de valors propietari : participacio. Si hi ha diversos propietaris, les dades de cadascun d'ells està separat per un símbol d'ampersand ( & ).

detall fitxer (any)-transmissions:

```
.Comentari: Fitxer de transmissions de l'any 2011 #nous propietaris
idNouPropietari; nom i cognoms; email idNouPropietari; nom i cognoms; email
...
#transmissions
>idPropietariAnterior; data; motiu
numFinca; idNouPropietari: participacio & idNouPropietari: participacio numFinca; idNouPropietari: participacio & idNouPropietari: participacio >idPropietariAnterior; data; motiu
numFinca; idNouPropietari: participacio & idNouPropietari: participacio >idPropietariAnterior; data; motiu
numFinca; idNouPropietari: participacio & idNouPropietari: participacio
```

on:
- la data es troba en format aaaa-mm-dd, i
- els motius habituals de transmissions són herència, compravenda o donació.
- si numFinca = 0, implica que l'operació s'aplica a TOTES les seves finques.
- la llista de Nous Propietaris només es refereix a propietaris que no pertanyien a la comunitat. Si ja ho eren, s'ha d'utilitzar el seu codi corresponent.

Com es pot observar a la descripció dels fitxers anteriors,
a) el símbol # a principi de línia serveix per a identificar una secció
b) el símbol . a principi de línia serveix per a identificar un comentari (la línia s' ignora)
c) les línies en blanc també s'han d'ignorar
d) el símbol > al fitxer de transmissions indica que comença una nova transmissió. Aquesta transmissió pot afectar a 1 o a diverses finques (són les línies següents).

L'aplicació g_compropietaris es cridada amb els següents paràmetres:

```
g_compropietaris any_referencia
```

Exemple:

```
g_compropietaris 2011
```

on l'any de referència és l'any que es vol generar (es genera el fitxer de propietats abans de la reunió anual de la comunitat).


Per tant, si l'any de referència és 2011, llavors:

```
2010-propietats.txt + 2011-transmissions.txt ---> 2011-propietats.txt
```

L'aplicació ha de fer els següents processos de forma consecutiva:
1. Llegir dades (any-propietaris.txt i any-transmissions.txt)
2. Verificar dades participacions, si les fraccions sumen 1.
3. Generar llistat de propietaris de l'any a partir d'(any-1)-propietaris.txt i (any)-transmissions.txt
4. Generar llistat de propietaris amb les seves participacions globals dins la comunitat (any-participacions.txt).

## Punt 1 (Llegir dades)

Ha de llegir els fitxers de text d'entrada any-propietaris.txt i any-transmissions.txt i carregar la informació en estructures de memòria de forma organitzada (com no se sap el nombre d'elements, s'haurà de fer servir llistes dinàmiques o d'altres formes).

Ha de mostrar un missatge final en pantalla que doni un resum final dels elements lllegits:

```
Processant any 2011...
Registres llegits:
propietaris 2010 : xxx
propietats       : xxx
propietaris nous : xxx
transmissions    : xxx
```

## Punt 2 (Verificar dades participacions)

Correspon a recorrer les llistes de memòria creades anteriorment, i verificar que les dades de les participacions són correctes. Hi ha dos controls:

a) A nivell de comunitat: La suma de participacions generals de cada finca ha de donar 1.

b) A nivell de finca: La suma de participacions de cada finca per a tots els propietaris d'aquesta també ha de donar 1.

Si algun dels resultats és incorrecte, mostrar en pantalla un missatge d'avís indicant l'error detectat. No obstant, això no impedirà els llistats posteriors.

Recordar que les operacions s'han de fer amb fraccions.

## Punt 3 (Generar fitxer de propietaris de l'any en curs)

Té el mateix format que el fitxer de propietaris original.

Pas previ: En el pas 1 s'ha llegit el fitxer de propietats, creant les llistes de propietaris i de propietats, i el fitxer de transmissions, creant dos llistes noves: nous propietaris i transmissions.

**Procés**

El primer que s'haurà de fer es afegir la llista de nous propietaris a la llista ja existent (s'afegiran al final).

El segon pas és aplicar la llista de transmissions. Per tant, s'ha de recórrer la llista de transmissions que es té a memòria, i per a cada una de les finques d'aquest propietari inclosa s'ha de fer la substitució pel nou propietari. Amb un exemple s'entendrà millor:

A la llista de propietats, tenim:
```
5;Cal Pep;1/10;16:1/2 & 17:1/2
```

La finca 5 (“Cal Pep”) , amb una participació general d'un 1/10 part de la comunitat, pertany a Joan (id=16) i Pere (id=17) a parts iguals (és a dir, participació 1/2 ).

Si en Joan mor, i li deixa a les seves filles Maria (id=27), Marta (id=28) i Montserrat (id=29) la finca 5 a parts iguals, la informació de la finca queda:

```
5;Cal Pep;1/10;26:1/6 & 27:1/6 & 28:1/6 & 17:1/2
```

Si posteriorment, la Maria ven a Marta la seva part, el resultat final és:

```
5;Cal Pep;1/10;27:1/3 & 28:1/6 & 17:1/2
```

## Punt 4 (Generar llistat de propietaris amb les participacions globals dins la comunitat)

El llistat generat tindrà el nom de “(any)-participacions.txt” i serà de la forma:

```
idProp Nom              Email                  Part(fracc)   Part(%)
----------------------------------------------------------------------
 1     Joan Pi Port      jpiport@mail.com        1/25          4,00%
 2     Marta Pi Port     mpiport@mail.com        2/25          8,00%
 3     Francesc Pi Port  fpiport@mail.com        2/25          8,00%
 4     Narcís Mont Prim  nmontprim@mail.com      1/9          11,11%
 5     Sandra Mont Prim  smontprim@mail.com      2/9          22,22%
 6     Rogeli Mont Prim  rmontprim@mail.com      4/9          44,44%
 7     Ricard Pi Mont    rpimont@mail.com        1/45          2,22%
----------------------------------------------------------------------
 7 propietaris                            TOTAL   1           99,99%
```

La participació (en fracció) es calcularà a partir de la suma de la participació de cada propietari a totes les finques que posseeixi.

La participació en % és una representació del càlcul anterior en fracció, arrodonit a 2 decimals. Com s'ha comentat anteriorment, és a efectes de comprensibilitat però sense valor legal.

**Procés**

Una forma fàcil de calcular-ho és anar recorrent la llista de propietaris, i per cada propietari fer una cerca per la llista de finques per anar sumant les seves participacions (en fracció). Un cop calculada aquesta suma, es pot guardar aquest valor dins la mateixa llista de propietaris a memòria.

Un cop finalitzats els càlculs, es pot generar el llistat passant-li només la llista dinàmica de propietaris, que ja conté tota la informació.

Per simplificar es pot considerar que les entrades de dades són sintàcticament correctes.

# Resposta

## Entorn de desenvolupament

- IDE: NetBeans 7.0.1 (C/C++)
- SO: Mac OS X 10.6.8 + Xcode 3.2.6 + JRE 1.6 10M3425 
- SO: Ubuntu 11.10 + gcc 4.6.1 + JRE 1.6.0-23

### Per afegir o modificar els arguments del programa

En propietats del projecte, en la secció "Execució" establir:

```
"${OUTPUT_PATH}" 2010
```

on 2010 és l'any que es passa com paràmetre

### Gestió de tasques amb l'IDE afegint patrons ToDo

per activar-ho: >>Eines-> Opcions C/C++<< Opcions del projecte: Suport per a la indexació de fitxers que no siguin ...
```C
// @todo: explicació
```

## Punts desenvolupats del programa

- Llista propietaris: llista doblement enllaçada amb dos nodes fantasma. Variable amb apuntador al primer element + nombre d'elements. Mètode d'inserció directa, ordenat per idPropietari.
- Llista propietats: llista doblement enllaçada amb dos nodes fantasma. Variable amb apuntador al primer element + nombre d'elements, cada node de la llista conté un punter a una llista de particions. Mètode d'inserció directa, ordenat per idPropietat.
- Llista transmissions: llista doblement enllaçada amb dos nodes fantasma. Variable amb apuntador al primer element + nombre d'elements, cada node de la llista conté un punter a una llista de registres. Mètode d'inserció directa, ordenat per idPropietari.
- Llista registres: llista doblement enllaçada amb dos nodes fantasma. Variable amb apuntador al primer element + nombre d'elements, cada node de la llista conté un punter a una llista de particions. Mètode d'inserció directa, ordenat per idPropietat.
- Llista particions: llista doblement enllaçada amb dos nodes fantasma. Variable amb apuntador al primer element + nombre d'elements. Mètode d'inserció directa, ordenat per id. emmagatzema particions de propietaris o de propietats.

## Decisions preses

- Formatació de les dades d'entrada del fitxer per línies abans de processar-les per facilitar el tractament.
- Funcions pel tractament de cadenes: sempre s'utilitza el pas per referència, còpia a variable local i el valor modificat per referència.
- Llistes doblement encadenades. Variable amb apuntador al primer element + nombre d'elements. Mètode d'inserció directa, ordenat per idPropietari.
- Les cadenes de text en el nodes de les llistes són dinàmiques.
- Per recorrer les llistes s'utilitzen iteradors.
- Definició de booleans en boolean.h
- Definició de fraccions i operacions elementals a fraccio.h
- Carpeta exclusiva per fonts i per capçaleres.
- Formatació del codi K&R
