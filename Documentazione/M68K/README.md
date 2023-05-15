# Introduzione
In m68k i registri sono formati da 3 tipi diversi:
* `long` 32 bit
* `word` 16 bit
* `byte` 8 bit

Possono essere visti come 2 gruppi da 16 bit, le due word formano una long
```
[00000000 00000000][00000000 00000000]
```


**ATTENZIONE** Gli operatori come addizione etc funzionano solo a 2 registri. Il secondo operando sarà quello destinazione dove viene salvato il dato.

Ha 18 registri utilizzabili, 8 data e 8 address
```assembly
d0,d1,d2,d3,d4,d5,d6,d7
a0,a1,a2,a3,a4,a5,a6,a7
```
gli altri sono speciali, come registro 0 dove sono contenuti solo zeri, il registro 1 e 31 etc...
**ATTENZIONE**, i registri a, sono di tipo address, non supportano le operazioni aritmetiche


# Struttura di un programma
Un programma base in M68K è strutturato:
```
ORG $2000

START:

END
```
Dove ORG è l'indirizzo di partenza, START è dove il programma inizierà l'esecuzione, e END è dove terminerà l'esecuzione.


# Utilizzo valori numerici ed esadecimali

I valori numerici in formato **decimale** sono rappresentati aggiungendo un `#` prima del numero, mentre il registro è scritto direttamente
```assembly
add #22,d6
```

per rappresentare valori in formato esadecimale si mette il prefisso `#$`, mentre per il formato binario `#%`
```assembly
move #$16, d0 
    ;copia il numero 22 in formato esadecimale nel registro d0

move #%10110, d0
    ;copia il numero 22 in formato binario nel registro d0
```

# Metodi di indirizzamento

***ATTENZIONE*** Nella documentazione utilizzeremo questi nomi per specificare quali tipi di operandi sono supportati dalle istruzioni. 
Si definisce *modo di indirizzamento* (*addressing mode*) una regola che, a partire da alcune informazioni, permette di indirizzare una parola.

In m68K ci sono vari modi per indirizzare i dati e prenderne i valori. 

## Immediato
`Im` Un numero, non è mai destinazione di un'istruzione
```assembly   
Im -> #<numero>
    move #10, d0
```

## Diretto di registro (dati)
`Dn` Registro dati, può essere usato in tutte le istruzioni che accettano registri, specialmente quelli aritmetici
```
Dn -> <d1/d2/d3/d4/d5/d6/d7>
    move d0, d1
```
## Diretto di registro (indirizzi)
`An` Registro indirizzi, **NON** può essere usato in tutte le istruzioni, per esempio **NON** può essere usato per la moltiplicazione e divisone.
```
An -> <a1/a2/a3/a4/a5/a6/a7>
    move a0, a1
```


## Indiretto registro 
`(An)` Si utilizza un registro indirizzi come puntatore. Legge la memoria all'indirizzo di An. Utilizzato nell'indicizzazione dinamica di un array.
```assembly
    move.l (a0), d0
```
Utile anche sapere il `base indicizzato`, che usa due registri, uno che specifica l'inizio nella memoria, e uno che specifica l'offset.
```assembly
    move.l #1000, a0
    move.l $5, d0
; setta 10 ad indirizzo 1005
    move.l #10, (a0, d0)
```
## Implicito
In questa documentazione non trattiamo casi di indirizzamento implicito.

## Diretto Indirizzo
`Ea` Indirizzo di memoria, valido sia come label che come indirizzo di memoria.
```
Ea -> <label/$indirizzo>

    move.l $0x2000, d0
    move.l unaLabel, d0
```
# Comandi

**ATTENZIONE** In alcuni dei comandi possiamo scegliere quale parte dei registri utilizzare, se solo i primi 8 bit, i primi 16 bit o tutti e 32 bit, facciamo ciò aggiungendo una di queste 3 estensioni dopo il comando:

# Estensioni

`.l` indica il formato long (32 bit)

`.w` indica il formato word (16 bit)

`.b` indica il formato byte (8 bit)

Esempio:
```assembly
move.l d7, d0
    ;copia tutti 32 bit di d7 in d0
move.w d7, d0
    ;copia i primi 16bit di d7 in d0
move.b d7, d0
    ;copia i primi 8bit di d7 in d0
```
### ***ATTENZIONE***

In questa documentazione metteremo fra [ ] e { } le estensioni disponibili. 

Se le parentesi [ ] non sono presenti, vuol dire che non abbiamo informazioni su quel comando, se abbiamo le parentesi vuote [ ] allora il comando non ha estensioni.

In { } è specificata l'estensione di default

## move [l w b] {w}

*move* -> Copia il contenuto del primo operando nel secondo. Se la destinazione è un registro indirizzi (a), di default usa formato long
```assembly
move <Im/Dn/An/(An)/Ea>, <Dn/An/(An)/Ea>

move #100, d0
    ;d0 = 100
move d7, d0
    ;d0 = d7
move.w  $2082,$208c     ; copia la word dell'address di memoria $2082 nell'address di memoria $208c
```
È inoltre possibile utilizzare operazioni di somma per indicare address, queste operazioni vengono fatte dal traduttore e non al momento dell'esecuzione

```assembly
move.b  $00002080+1,d1     ; copia il valore del byte dell'address di memoria $2081 in d1
```
## add - adda [l w b]
*addition* -> Effettua la somma di due valori e salva il risultato nel secondo. `adda` non cambia il CCR
```assembly
add <Im/Dn/An/(An)/Ea>, <Dn/An/(An)/Ea>
adda <Im/Dn/An/(An)/Ea> , <An>

add #100, d0
    ;d7 = d7 + 100
add d7, d0
    ;d0 = d0 + d7
add.b   #3,$0000208c    ; somma 3 al byte dell'address di memoria $208c
``` 

## sub [l w b]
*subtract* -> Effettua la sottrazione del secondo valore meno il primo e salva il risultato nel secondo 
```assembly
sub <Im/Dn/An/(An)/Ea>, <Dn/An/(An)/Ea>

sub d7, d0
    ;d0 = d0 - d7
sub #100, d0
    ;d0 = d0 - 100
sub.b   #3,$0000208c    ; sottrare 3 al byte dell'address di memoria $208c
```
**ATTENZIONE**, il secondo parametro deve sempre essere un registro, se vogliamo fare `100 - d0` dobbiamo caricare il `100` dentro un registro, poi fare la sottrazione
```assembly
move #100, d7
sub d7, d0
```

## divs - divu [ ]
* `divs` divisione **signed**
* `divu` divisione **unsigned**

Divide il secondo registro per il primo num/reg, salva il risultato nel secondo registro. Il primo operando viene letto con formato `word`, il secondo con formato `long`. 

**ATTENZIONE** salva il quoziente della divisone nei primi 16 bit del secondo registro, il resto negli ultimi 16 bit. Se si vuole accedere al resto, usare il comando [swap](#swap)
```assembly
divs <Im/Dn/(An)/Ea>, <Dn>
divu <Im/Dn/(An)/Ea>, <Dn>

move #100, d0
    ;d0 = 100
divs #11, d0
    ;d0 = d0/11, cioé 100/11 
divs    $00002810,d0    ; divide d0 per il valore dell'address $2810
```
al termine dell'esecuzione del codice il registro `d0` sarà composto dai seguenti bit (in formato esadecimale):
>[`00010009`]

dove `0001` è il resto, mentre `0009` è il risultato

per ottenere il quoziente serve copiare il registro in formato word, copiandone solo i **primi 16 bit**

per ottenere il resto serve eseguire `swap` sul registro, e poi ripetere quanto detto sopra:
```assembly
move.w d0, d1
    ;d1 = d0/11

swap d0
move.w d0, d2
    ;d2 = d0 % 11
```


## muls - mulu [ ]

* `muls` moltiplicazione **signed**
* `mulu` moltiplicazione **unsigned**

Moltiplica il secondo registro per il primo valore/registro e salva il risultato nel secondo registro. Il primo operando viene letto con formato `word`, il secondo con formato `long`. 
```assembly
muls <Im/Dn/(An)/Ea>, <Dn>
mulu <Im/Dn/(An)/Ea>, <Dn>

muls #10,d1
    ;d1 = d1 * 10

muls d1,d2
    ;d2 = d2 * d1
muls    $00002810,d0    ; moltiplica d0 per il valore dell'address $2810

```


## swap [ ]
*swap* -> Inverte le due word all'interno dello stesso registro, se guardiamo il registro come se fosse `[a,b]`, diventerà `[b,a]`, utile per la divisione
```assembly
swap <Dn>

    ;prima: d0 = 0x0000FFFF
swap d0
    ;dopo:  d0 = 0xFFFF0000
```

## clr [l w b]
*clear* -> Azzera il contenuto del registro messo dopo il comando
```assembly
clr <Dn/(An)>

    ;prima: d0 = 0x01495840
clr d0
    ;dopo:  d0 = 0x00000000

;oppure

;prima: d0 = 0x01495840
clr.w d0
;dopo:  d0 = 0x01490000 
```


## exg 
*exchange* -> Scambia il contenuto di due registri, **ATTENZIONE**, funziona solo con 32 bit
```assembly
exg <Dn/An>, <Dn/An>
----------------------------
    ;prima: d0 = 0x12940000
    ;prima: d1 = 0x00000010
exg d0,d1
    ;dopo:  d0 = 0x00000010
    ;dopo:  d1 = 0x12940000
```
## neg [l w b] {w}
*negate* -> Cambia il segno al valore del registro messo dopo l'operando
```assembly
neg <Dn/(An)/Ea>
----------------------------
    ;prima: d0 = 100 
neg d0
    ;dopo:  d0 = -100 
```
## ext [l w]
*extend* -> Estende un registro al formato specificato, usato per convertire un registro da byte a word (.w), o da word a long (.l). **ATTENZIONE**, il funzionamento del comando è prendere l'ultimo bit del tipo di formato che volete convertire e sostituirlo a tutti i restanti bit del nuovo formato, per esempio da byte a word, copia l'ultimo bit del byte e lo mette in tutti i restanti bit della word. 

```assembly
ext.w <Dn> ;converte la parte byte nella word
ext.l <Dn> ;converte la parte word nella long

----------------------------

    ;prima: d0 = 0xFF -> 1111 1111 (negativo, quindi copia l'1)
ext.w d0
    ;dopo: d0 = 0xFFFF -> 1111 1111 1111 1111

    ;prima: d1 = 0x1234 -> 0001 0010 0011 0100  (positivo, quindi copia lo 0)
ext.l d1
    ;dopo: d1 = 0x00001234

    ;prima d2 = 0xFF00 -> 1111 1111 0000 0000
ext.w d2
    ;dopo: d2 = 0x0000 -> 0000 0000 0000 0000
```

# Comandi branch e comparazione
Questi comandi vengono usati per mettere a confronto un registro con un altro registro, o con un numero immediato, per poi andare nella label se la condizione è vera.

In m68k, comparazione e branch vengono effettuati in comandi separati. Il primo ,`cmp`, mette a confronto due valori, poi con i vari comandi di branch, si decide a quale label andare. 

Ci sono due comandi di comparazione, quello rispetto due valori `cmp`, e quello rispetto allo zero `tst`. Questi comandi accettano l'utilizzo di `.l` `.w` `.b`

Entrambi i comandi `cmp` e `tst` salvano il risultato del confronto nel `CCR`, che poi verrà utilizzato nei comandi di branch scritti sotto.

## tst [l w b] {w}
*test* -> Comparazione con lo 0
```assembly
tst <An/Dn/(An)/Ea>
    ; comparazione con 0
```

## cmp [l w b] {w}
*compare* -> Se il secondo operando è un registro indirizzi (a) allora ha formato `long`. 

***ATTENZIONE*** In m68K viene confrontato il secondo operando con il primo. Se facciamo 
```
cmp #3,d1
bgt daQualcheParte
``` 
verrà confrontato d1 con 3.
```assembly
cmp <Im/Dn/(An)/Ea>, <Dn>
    ; comparazione di due valori 

cmp #10,d1
```
## Comandi di branch
Una volta settati i valori da comparare, possiamo fare il confronto vero e proprio con i comandi di branch, questi andranno a controllare i dati del CCR e "salteranno" alla label data se la comparazione è vera. Tutti hanno sintassi:
```assembly
comando <label>
```

tutti gli esempi qui sotto hanno il cmp come:
```
cmp a, b
```
## Signed
Comando             |  Logicamente        | Acronimo
:------------------:|:-------------------:|:------------------------
beq                 |      b == a         | *Branch equal*   
bne                 |      b != a         | *Branch not equal*
blt                 |      b < a          | *Branch less than*
ble                 |      b <= a         | *Branch less or equal*
bgt                 |      b > a          | *Branch greater than*
bge                 |      b >= a         | *Branch greater or equal*  
## Unsigned
Comando             |  Logicamente        | Acronimo
:------------------:|:-------------------:|:------------------------
beq                 |      b == a         | *Branch equal*   
bne                 |      b != a         | *Branch not equal*
blo                 |      b < a          | *Branch lower than*
bls                 |      b <= a         | *Branch lower than or same*
bhi                 |      b > a          | *Branch higher than*
bhs                 |      b >= a         | *Branch than or same* 
## Comandi di branch speciali (CCR)
Esistono dei comandi di branch "speciali": molti comandi in m68k, una volta eseguiti, comparano il registro destinazione con lo 0, inoltre tengono conto anche del segno del numero, se c'è stato un overflow, etc... Queste informazioni vengono salvate nel CCR. Come i precedenti comandi di branch, hanno sintassi: 
```assembly
comando <label>
```
e sono:
* `bmi` se un valore è negativo
* `bpl` se un valore è positivo
* `bcs` (Branch Carry Set) se dopo aver fatto un'operazione aritmetica su numeri unsigned, c'è stato riporto nella cifra più a sinistra (più significativa), per esempio, prendendo un byte per numero, si fa `255 + 9`, il risultato sarà `8`, perchè `264` è più grande del numero massimo rappresentabile da un byte, che è 255, se ciò è accaduto, allora si dice che c'è stato **riporto**. Vale anche se un numero va da positivo a negativo, es: 1-3 sarà 254. 
* `bcc` (Branch Carry Clear) come `bcs`, ma se **NON** c'è stato riporto
* `bvs` (Branch oVerflow Set) se dopo aver fatto una operazione aritmetica, viene causato un overflow (per esempio: se venissero sommati 2 numeri positivi signed, e ne uscisse come risultato un numero negativo, è Overflow)
* `bvc` (Branch oVerflow Clear) come `bvs`, ma **NON** c'è stato Overflow


## Branch incondizionato
Va direttamente alla label.
```assembly
bra <label>
jmp <label>
```
## Lettura degli elementi del CCR
Come visto prima nei branch, nel CCR troviamo varie informazioni durante l'esecuzione del codice, come per esempio se c'è stato un overflow, se un numero è maggiore, se è minore, etc... Possiamo leggere queste informazioni tramite questi comandi, se una condizione è vera, allora tutti i bit saranno settati a 1, altrimenti saranno settati a 0. Hanno tutti sintassi:
```assembly
comando <destinazione>
```
* `scc` se non c'è stato riporto (Carry Clear)
* `scs` se c'è stato riporto (Carry Set)
* `seq` se è uguale (EQual)
* `sne` se non è uguale (Not Equal)
* `sge` se è maggiore uguale (Greater or Equal) **SIGNED**
* `sgt` se è maggiore (Greater) **SIGNED**
* `sle` se è minore uguale (Less or Equal) **SIGNED**
* `sls` se è più piccolo o uguale (LOwer) **UNSIGNED**
* `slt` se è minore (Less Than) **SIGNED**
* `shi` se è più grande (HIgher) **UNSIGNED**
* `smi` se è negativo (MInus)
* `spl` se è positivo (Positive)
* `svc` se non c'è stato overflow (oVerflow Clear)
* `svs` se c'è stato overflow (oVerflow Set)
* `sf`  se è falso (false)
* `st`  se è vero (true)


# Operazioni sui bit e logici
Le operazioni sui bit ci permettono di effettuare modifiche ai singoli bit di un registro, come spostarli a sinistra/destra, invertirli, etc...

## not, or, and, eor
Effettua le operazioni not, or, and, xor, tra un registro e una maschera. La maschera è una sequenza di bit che specificano su quali posizioni si deve effettuare l'operazione logica. I vari operatori hanno funzioni equiparabili a:
* `NOT` Inverso di tutti i bit (1 diventa 0, 0 diventa 1), non usa una maschera
* `OR`  Setta ad 1 i bit alle posizioni della maschera, senza modificare gli altri
* `AND` Prelevare i bit alle posizioni della maschera, oppure controllare se un bit è segnato ad 1 nella posizione segnata nella maschera
* `EOR` Inverso dei bit alle posizioni della maschera.

il primo elemento del comando sarà la maschera, (tranne nel not), il secondo elemento sarà il registro dove effettuare l'operazione, e dove verrà salvata
```assembly
not <reg>

or <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>
and <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>
eor <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>
```
esempi:
```assembly
    ; per semplicità di scrittura, sono rappresentati solo 8 dei 32 bit
    ; d0 = 01100111
    ; in realtà sarebbe
    ; d0 = 00000000000000000000000001100111

    ; d0 = 01100111 (maschera)
    ; d1 = 11001100 
    ; d2 = 11001100 
    ; d3 = 11001100 
    ; d4 = 11001100 

not d1
    ; d1 = 00110011

or d0, d2
    ; d2 = 11101111

and d0, d3
    ; d3 = 01000100

eor d0, d4
    ; d4 = 10101011
```

## lsl [l w b] {w}
*logical shift left* -> Sposta tutti i bit di di un registro di tot posizioni a sinistra, le cifre aggiunte saranno uguali a 0.

Uguale al comando `<<` in C




```assembly
lsl <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>

    ;d0 = 01011101 (in binario)
    ;d2 = 3 (in decimale)
lsl d2, d0
    ;d0 = 11101000

;più un grande:

    ;d0 = 87658765 (in esadecimale) 
lsl #4, d0
    ;d0 = 87657650 (la word a sinistra non è stata shiftata) 

lsl.l #5, d0
    ;d0 = ECAECA00 (stavolta con .l l'intero valore è stato shiftato)
```

Lo `shift sinistro` logico ha lo scopo aritmetico di effettuare `(N * 2^k) mod 2^l` dove N = numero dove effettuare lo shift, k è il numero di bit da spostare a sinistra, e l è il numero di bit nel formato usato.


## lsr [l w b] {w}
*logical shift right* -> Sposta tutti i bit di di un registro di tot posizioni a destra, le cifre aggiunte saranno uguali a 0. Ignora il segno del numero, quindi un numero negativo verrà trattato ugualmente ad uno positivo. 
 
Uguale al comando `>>` in C

```assembly
lsr <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>

    ;d0 = 11011101 (in binario)
    ;d2 = 3 (in decimale)
lsr d2, d0
    ;d0 = 00011011

;più un grande:

    ;d0 = 87658765 (in esadecimale) = 10000111011001011000011101100101
lsr #4, d0
    ;d0 = 87650876 (la word a sinistra non è stata shiftata)

lsr.l #5, d0
    ;d0 = 043B2843 (stavolta con .l l'intero valore è stato shiftato)
```

Lo `shift destro` logico equivale a calcolare `N/2^k` dove N è il numero dove effettuare lo shift e `k` è la quantità dello shift, oppure semplicemente, ogni volta che spostiamo di una posizione, il numero viene diviso per 2.


## asr / asl [l w b] {w}
*arithmetical shift right/left* -> Sposta tutti i bit di di un registro di tot posizioni a destra/sinistra. Tiene conto del segno del numero. Se verso destra, i numeri aggiunti saranno uguali al numero più a sinistra, se verso sinistra, il segno verrà ignorato, ma se c'è un cambio di segno, verrà segnato sul CCR

```assembly
asr <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>

asl <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>

    ;d0 = 10010111 (in binario)
    ;d2 = 2 (in decimale)
    
asr d2, d0

    ;d0 = 11100101

;più in grande:

    ;d0 = 87658765 (in esadecimale)
asr #4, d0
    ;d0 = 8765F876 (la word a sinistra non è stata shiftata)

asr.l #5, d0
    ;d0 = FC3B2FC3 (stavolta con .l l'intero valore è stato shiftato)
```

Aritmeticamente, lo  `shift sinistro` aritmetico è uguale a calcolare `N*2^k`, dove N è il numero dove effettuare lo shift e `k` è la quantità dello shift, oppure semplicemente, ogni volta che spostiamo di una posizione, il numero viene moltiplicato per 2. 

Mentre per lo `shift destro` aritmetico è uguale a calcolare `N/2^k`, dove N è il numero dove effettuare lo shift e `k` è la quantità dello shift, oppure semplicemente, ogni volta che spostiamo di una posizione, il numero viene diviso per 2.


Bisogna fare attenzione nel caso in cui il numero sia negativo, o se il numero è grande, visto che potrebbe verificarsi un overflow.

## rol / ror [l w b] {w}
*rotate left / rotate right* -> Prendendo per esempio la rotazione a destra, il comando sposterà a destra di un tot numero di bit, e li posizionerà a sinistra (al posto dei bit da aggiungere). Lo stesso vale per rol, ma verso sinistra
```assembly
rol <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>
ror <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>

    ;d0 = 01000011
rol #2, d0
    ;d0 = 11010000

;più in grande:

    ;d0 = 87658765 (in esadecimale)
rol #4, d0
    ;d0 = 87657658 (la word a sinistra non è stata ruotata)

rol.l #5, d0
    ;d0 = ECAECB10 (stavolta con .l l'intero valore è stato ruotato)
```

# Operazioni sui singoli bit
Servono per effettuare operazioni sui singoli bit. Tutti i comandi seguenti, prima di modificare un bit, settano il CCR `equal` al valore del bit da cambiare, e poi modificano il bit. Se il secondo operando è un registro viene letto tutto il registro, se non lo è, vengono letti solo i primi 8 bit.

Il primo operando è il bit da leggere, il secondo sarà dove effettuare e salvare l'operazione. 
## btst
*Bit test* -> Testa il bit a posizione specificata del registro, setta la condizione del CCR `equal` al valore del bit a quella posizione, poi possiamo usare il comando `beq` per il branch. Non modifica la destinazione

```assembly
btst <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>
```
## bclr 
*Bit clear* -> Setta a 0 il bit a posizione specificata del registro.
```assembly
bclr <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>
```

## bchg
*Bit change* -> Inverte il bit a posizione specificata del registro.
```assembly
bchg <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>
```

## bset
*Bit set* -> Setta ad 1 il bit a posizione specificata del registro.
```assembly
bset <Im/Dn/(An)/Ea>, <Dn/(An)/Ea>
```

# La memoria in M68K
La memoria in M68K può essere vista come una lista di byte, dove ogni byte nella lista ha una posizione chiamata "address". La gestione dei dati salvati all'interno della memoria è completamente lasciata allo sviluppatore che scrive il programma, quindi andrà tenuta in considerazione la lunghezza in byte dei vari formati di dato che andremo a salvare. 


**ATTENZIONE**, quando andiamo a leggere e scrivere negli address, in base alla grandezza del formato che vogliamo usare, l'indirizzo scelto dovrà essere un multiplo del formato scelto. Per esempio, non possiamo salvare una word (4 byte) all'indirizzo 2021, perchè non è modulo di 4, ma possiamo salvarlo in 2024

## Formati di dato e allineamento
Ogni formato di dato ha la propria lunghezza, dovremo tenerne conto quando salviamo e leggiamo dalla memoria. I dati letti/scritti verranno letti dall'indirizzo specificato, fino all'`indirizzo + lunghezza`.

Alcuni formati standard, diversi dal formato **byte**, definiscono una restrizione agli indirizzi validi per le 
parole standard di tale formato, chiamata `vincolo di allineamento`.

* `byte` : ha lunghezza 8 bit (1 parola)
* `word` : ha lunghezza 16 bit (2 parole), fattore di allineamento 2
* `long` : ha lunghezza 32 bit (4 parole), fattore di allineamento 2

Ad esempio, per salvare una **word** all'address $2000, il dato verrà salvato agli indirizzi $2000 e $2001 e, dunque, la successiva **word** o **long**, non potrà essere salvata a partire dall'address $2001, bensì dovrà essere salvata a partire dall'address $2002.

Importante è sapere il modo in cui i dati in memoria vengono letti/scritti. Esistono due tipologie chiamate `little endian` e `big endian`. 

In m68k, per la lettura/scrittura in memoria viene usato il [Big endian](#Big-endian).

### Little endian
Little endian è quando i byte sono salvati da destra verso sinistra, partendo dal più significativo. Per esempio il numero esadecimale `#$1234` viene salvato in memoria come `#$34 #$12`.

### Big endian
Big endian è quando i byte sono salvati da sinistra verso destra, partendo dal più significativo. Per esempio il numero esadecimale `#$1234` viene salvato in memoria come `#$12 #$34`.

## Utilizzo della memoria
Per utilizzare la memoria all'interno del programma, ci basterà specificare il numero dell'indirizzo della memoria come operando, scrivendolo in maniera `$numero_indirizzo`, esempio `$2000`. Alternativamente, possiamo creare una `variabile` alias all'inizio del programma che indica a quale indirizzo fa riferimento l'alias. Facciamo ciò tramite il comando [equ](#equ)

```assembly
unaVariabile equ $3000

move.w #1234, $00002000
    ; la word 1234 viene salvata in memoria all'indirizzo $2000
    ; quindi viene salvato 12 all'indirizzo $2000 e 34 all'indirizzo $2001
move.w #1234, unaVariabile
```
Naturalmente la lettura e scrittura dipendono dal formato di dato utilizzato.

## equ
*equals* -> La direttiva `equ` è un alias. Ricorda che l'assembler poi sostituirà il nome di questo nome con il valore indicato.

Deve essere messo prima di `ORG $2000` e senza indentazione. Verrà convertito dall'assembler e sostituito con l'indirizzo di memoria.

```assembly
<nome_variabile>:  equ  <adr/Im> 

unaVariabile: equ 5020
unaVariabile: equ #$FF0022

```
Esempio:
```assembly
unaVariabile: equ 5020

    ORG $1000
    move.l  #unaVariabile,d0    
;assemblato in -> move.l  #5020,d0
```

# Indirizzi di Memoria e Label
Gli indirizzi possono essere scritti in forme più comode utilizzando `label`. 
Ogni label è legata ad un indirizzo di memoria, ovvero rappresenta tale indirizzo. In fase di traduzione l'assembler trasforma ogni label nell'indirizzo ad essa legato. Hanno quindi senso operazioni come
```assembly
; se pippo è una label, l'indirizzo successivo sarà l'indirizzo pippo+1, quello dopo ancora pippo+2, e così via..-

        move.b  d4,d6
pippo:  cmp #256,d0 
        clr d6              ;pippo+1
        move.w  d0,d2       ;pippo+2
```
Quando il programma viene assemblato, ogni istruzione è convertita in un numero a 32 bit (4 byte). Quando il programma viene eseguito, questi numeri sono caricati nella memoria ed eseguiti. Le label sono solo un "alias" all'indirizzo di memoria dove è salvata l'istruzione. Quando per esempio facciamo un branch ad una label, quello che in realtà sta succedendo, è che il programma continua l'esecuzione all'indirizzo di memoria dove è salvata la label.

# Allocazione statica della memoria
L’allocazione della memoria statica viene fatta mediante le `sezioni`; ogni sezione ha un `indirizzo di inizio sezione`.

Si può allocare la memoria in maniera "statica" (cioè non si può espandere).

Una direttiva di definizione dati:
* indica quanti byte devono essere allocati e se necessario, i valori da memorizzare.
* non indica l’indirizzo di memoria dei byte da allocare: tale indirizzo è determinato automaticamente dall'assembler.

## org
Per allocare la memoria viene utilizzata la direttiva 𝒐𝒓𝒈 seguita dall’indirizzo di inizio 
sezione. Tale direttiva imposta infatti l’indirizzo di memoria iniziale per i successivi che seguiranno.
```assembly
org     $1100
move.l  #$12,d0
tst d1
```
Indirizzo           |  Comando        
:------------------:|:-------------------
1100    |    org     $1100
1100    |   move.l  #$12,d0
1104    |   tst d1

## dc [l w b]
**define constant** -> La direttiva `dc` è usata per definire costanti.

Se non è specificata una estensione di lunghezza (b,w,l), per le stringhe è utilizzato il formato *byte*, mentre per i valori numerici il formato *word*.
``` assembly
<label>: dc <valore>

x: dc.b 10
v:  dc.l    1,3,4
    ; alloca 3 long, la prima con valore 1, la seconda con valore 3 e la terza con valore 4
    ; "v" è l'indirizzo della prima long
-----------------------------------------
    org $2800
v:  dc.l    0       ; v ha indirizzo 2800
w:  dc.l    220200  ; w ha indirizzo 2804 
    ; ovvero 2800 (org) + 4 byte (long v)
```
Possiamo usare `dc` per definire array e stringhe (di lunghezza fissa).


Per esempio per definire un array di 5 elementi tutti a valore 1:
```assembly
    ; long unArray[ 5 ] = { 1, 1, 1, 1, 1 };
    org $4000
unArray: dc.l 1,1,1,1,1
```
Potremo poi accedere ai valori dell'array usando il nome della label. Se volessimo iterare gli elementi dell'array, dovremo leggere l'indirizzo dell'array, e poi incrementarlo in base alla grandezza degli elementi. Oppure se dobbiamo leggere un elemento specifico, possiamo usare `label+posizione`
```assembly
; STATICO
    ; copia elemento a posizione 3
move.l unArray+2, d0

; DINAMICO
    ; prende l'indirizzo di "unArray"
move.l #unArray, a0
    ; incrementa l'indirizzo di 4 byte
    ; perchè il tipo degli elementi di "unArray" è long
add.l #4, a0
    ; copia elemento a posizione 1
move.l (a0), d0

```
C'è un altro tipo di rappresentazione per gli array, che per una serie di problemi è consigliabile ***non*** *utilizzare*.
```assembly
    move.w   el3,d0
    add.w    el0,d0
; fine codice

; int x[ 4 ] = { 7, 0, 3, 8 };
    org $4000
el0: dc.w     7
el1: dc.w     0
el2: dc.w     3
el3: dc.w     8
```
## ds [l w b]
Simile a dc, ma dichiara uno spazio di memoria di grandezza fissa data dal numero di elementi moltiplicato dal tipo di selettore [l w b] che scegliamo. Molto utile per creare array di N elementi. Il contenuto di questo spazio di memoria non è definito.
```
<label>: ds <numero_elementi>

;esempio, array di 10 elementi long
array: ds.l 10
```
## dcb [l w b]
Simile a `ds` ma ci permette di mettere un valore di default in ogni segmento della memoria.
```
<label>: dcb <numero_elementi>,<valore_iniziale>

;esempio, array di 10 elementi long con valore di default 0
array: dcb.l 10, 0
```

# Stack e funzioni
Nei linguaggi assembly, per implementare le funzioni, si deve usare e gestire lo stack. Lo stack è una pila di frame che contengono i vari dati necessari per l'esecuzione di una funzione. 

In M68K quando una funzione viene chiamata, viene aggiunto automaticamente un frame allo stack che contiene l'indirizzo successivo a quello della riga di chiamata di funzione, in questo modo è facile implementare sia funzioni che non chiamano altre funzioni, che funzioni ricorsive.

## Lettura e scrittura dello stack
Il registro speciale `sp` tiene conto della posizione della cima dello stack. Quando dobbiamo aggiungere informazioni, dobbiamo decrementare il registro `sp` per poi salvare nell'indirizzo puntato da `sp`, il dato da memorizzare. Quando invece dobbiamo prelevare un dato o rimuovere un frame, dobbiamo fare l'incremento dello stack pointer.

M68K ci permette facilmente di aggiungere e rimuovere tramite la sintassi `(sp)` (indirizzamento indiretto-registro) che permette anche di modificare il valore di `sp`.

## Lettura dello stack, pre decremento, post incremento
Usa la stessa sintassi della lettura in memoria. ***ATTENZIONE*** Il post/pre incremento/decremento usano il [.l, .w, .b] come quantità di bit da incrementare/decrementare.

Comando  |  Funzione        
:-------:|:-------------------
(sp)     |  Seleziona elemento alla cima dello stack
-(sp)    |  Decrementa sp prima di eseguire l'istruzione, usato per aggiungere un dato allo stack
(sp)+    |  Incrementa sp dopo l'esecuzione dell'istruzione, usato per prelevare un dato dallo stack
N(sp)    | N un numero, legge a posizione sp + N, usato per prelevare i parametri da una funzione

```assembly
; sp = $1000
; prima decrementa sp di 4 (l)
; poi salva il valore 10 nell'indirizzo puntato da sp (cima dello stack)
    move.l #10, -(sp)
; sp = $996

; prima decrementa sp di 2 (w)
; poi salva il valore 20 nell'indirizzo puntato da sp (cima dello stack)
    move.w #20, -(sp)
; sp = $994

; preleva l'elemento nell'indirizzo puntato da sp (cima dello stack), e poi incrementa sp di 2 (w)
    move.w (sp)+, d0
; d0 = 20
; sp = $996

; preleva l'elemento nell'indirizzo puntato da sp (cima dello stack), poi incrementa sp di 4 (l)
    move.l (sp)+, d1
; d1 = 10
; sp = $1000

; salva il valore 1000 nell'indirizzo sp + 4, non modifica sp
    move.l #1000, 4(sp)
```
L'offset può anche essere un alias dato da `equ`, per esempio si può usare 
```assembly
parametro_1: equ 0
parametro_2: equ 4

move.l parametro_1(sp), d0  ; move.l 0($sp), d0
move.l parametro_2(sp), d1  ; move.l 4($sp), d1
```
## bsr - Chiamata a funzione

Il comando `bsr` decrementa lo `sp` di 4 byte (gli indirizzi in M68K hanno dimensione long) per poi aggiungere l'indirizzo di ritorno nello spazio liberato. In seguito effettua il salto alla label specificata. 
```assembly
bsr <label>

; esempio
    bsr una_funzione
```
## rts - Ritorno da funzione
Il comando `rts` utilizza l'elemento dello stack puntato da `sp` come indirizzo di ritorno alla funzione chiamante. Una volta eseguito il pop, incrementa `sp` di 4 byte (gli indirizzi in M68K hanno dimensione long).
```
rts
```
Esempio di bsr e rts
```assembly
; i parametri vengono scritti al contrario, quindi primo è num_2, poi num_1
    ORG $1000
    move.l #3, -(sp) ; push di num_2 
    move.w #2, -(sp) ; push di num_1
    sub.l #4, sp     ; riserva spazio per il risultato
    bsr somma
    move.l (sp)+, d0 ; preleva il risultato
    add.l #6, sp     ;pop dei parametri
    bra end


* Routine somma
; Input
;	Word in stack frame - parametro num_1
;	Long in stack frame - parametro num_2
; Output
;	Long in stack frame - risultato
; Registri modificati
;	d0 (word), d1 (long)
; Stack frame
; Offset | Contenuto    | Note
; ----------------------------------------------
;        |              |
;        |              |
;   0    | pc di ritorno| allocato da chiamante
;        |              |
;   4    | risultato    | allocato da chiamante
;        |              |
;   8    | num_1        | allocato da chiamante
;        |              |
;  10    | num_2        | allocato da chiamante
;        |              |
; ----------------------------------------------
; dimensione stack frame: 14

risultato: equ 4
num_1: equ 8
num_2: equ 10

somma:
    move.w num_1(sp), d1 ; d1 = num_1
    move.l num_2(sp), d0 ; d0 = num_2
    add.l d1, d0         ; d0 = num_2 + num_1
    move.l d0, risultato(sp) ; salva risultato
    rts
```
