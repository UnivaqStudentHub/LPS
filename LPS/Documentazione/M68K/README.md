# Introduzione
In m68k i registri sono formati in 3 tipi diversi:
* `long` 32 bit
* `word` 16 bit
* `byte` 8 bit

Possono essere visti come 2 gruppi da 16 bit, le due word formano una long
```
[00000000 00000000][00000000 00000000]
```
In questa documentazione utilizzeremo questi nomi per i vari tipi di indirizzamento.
* `reg`: registro
* `adr`: indirizzo di memoria
* `num`: numero

**ATTENZIONE** A differenza di MIPS, gli operatori come addizione etc funzionano solo a 2 registri, con il secondo operando, quello che riceve il dato.

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
move #$00000016, d0 
; copia il numero 22 in formato esadecimale nel registro d0

move #%10110, d0
; copia il numero 22 in formato binario nel registro d0
```

# Comandi

**ATTENZIONE** In alcuni dei comandi possiamo scegliere quale parte dei registri utilizzare, se solo i primi 8 bit, i primi 16 bit o tutti e 32 bit, facciamo ciò aggiungendo uno di questi 3 dopo il comando:

`.l` indica il formato long (32 bit)

`.w` indica il formato word (16 bit)

`.b` indica il formato byte (8 bit)

Esempio:
```assembly
move.l d7, d0
; copia tutti 32 bit di d7 in d0
move.w d7, d0
; copia i primi 16bit di d7 in d0
move.b d7, d0
; copia i primi 8bit di d7 in d0
```

### ***ATTENZIONE***

In questa documentazione metteremo fra [ ] e { } le estensioni disponibili. 

Se le parentesi [ ] non sono presenti, vuol dire che non abbiamo informazioni su quel comando, se abbiamo le parentesi vuote [ ] allora il comando non ha estensioni.

In { } è specificata l'estensione di default

## move [l w b] {w}

Copia il contenuto del primo nel secondo. Se la destinazione è un registro indirizzi (a), di default usa formato long
```assembly
move <num/reg>, <destinazione>

move #100, d0
; d0 = 100
move d7, d0
; d0 = d7
```
## add [l w b]
Effettua la somma di due valori e salva il risultato nel secondo
```assembly
add <num/reg>, <destinazione>

add #100, d0
; d7 = d7 + 100
add d7, d0
; d0 = d0 + d7
```

## sub [l w b]
Effettua la sottrazione del secondo valore meno il primo e salva il risultato nel secondo 
```assembly
sub <num/reg>, <destinazione>

sub d7, d0
; d0 = d0 - d7
sub #100, d0
; d0 = d0 - 100
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

**ATTENZIONE** salva il risultato della divisone nei primi 16 bit del secondo registro, il resto negli ultimi 16 bit. Se si vuole accedere al resto, usare il comando [swap](#swap)
```assembly
divs <num/reg>, <destinazione>

move #100, d0
; d0 = 100
divs #11, d0
; d0 = d0/11, cioé 100/11 
```
al termine dell'esecuzione del codice il registro `d0` sarà composto dai seguenti bit (in formato esadecimale):
>[`00010009`]

dove `0001` è il resto, mentre `0009` è il risultato

per ottenere il risultato serve copiare il registro in formato word, copiando solo i **primi 16 bit** di esso

per ottenere il resto serve eseguire `swap` sul registro, e poi ripetere quanto detto sopra:
```assembly
move.w d0, d1
; d1 = d0/11

swap d0
move.w d0, d2
; d2 = d0 % 11
```


## muls - mulu [ ]

* `muls` moltiplicazione **signed**
* `mulu` moltiplicazione **unsigned**

Moltiplica il secondo registro per il primo valore/registro e salva il risultato nel secondo registro. Il primo operando viene letto con formato `word`, il secondo con formato `long`. 
```assembly
muls <num/reg>, <destinazione>

muls #10,d1
; d1 = d1 * 10

muls d1,d2
; d2 = d2 * d1

```


## swap [ ]
Inverte le due word all'interno dello stesso registro, se guardiamo il registro come se fosse `[a,b]`, diventerà `[b,a]`, utile per la divisione
```assembly
swap <reg>

;prima: d0 = 0x0000FFFF
swap d0
;dopo:  d0 = 0xFFFF0000
```

## clr [ ]
Azzera il contenuto del registro messo dopo il comando
```assembly
clr <reg>

;prima: d0 = 0x01495840
clr d0
;dopo:  d0 = 0x00000000
```


## exg 
Scambia il contenuto di due registri, **ATTENZIONE**, funziona solo con 32 bit
```assembly
;prima: d0 = 0x12940000
;prima: d1 = 0x00000010
exg d0,d1
;dopo:  d0 = 0x00000010
;dopo:  d1 = 0x12940000
```
## neg [l w b] {w}
Cambia il segno al valore del registro messo dopo l'operando
```assembly
neg <reg>

;prima: d0 = 100 
neg d0
;dopo:  d0 = -100 
```
## ext [l w]
Estende un registro al formato specificato, usato per convertire un registro da byte a word (.w), o da word a long (.l). **ATTENZIONE**, il funzionamento del comando è prendere l'ultimo bit del tipo di formato che volete convertire e sostituirlo a tutti i restanti bit del nuovo formato, per esempio da byte a word, copia l'ultimo bit del byte e lo mette in tutti i restanti bit della word. 

```assembly
ext.w <reg> ;converte la parte byte nella word
ext.l <reg> ;converte la parte word nella long


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
Questi comandi vengono usati per mettere a confronto un registro ad un altro registro, o ad un numero immediato, per poi andare nella label se la condizione è vera.

In m68k la comparazione e branch vengono effettuati in comandi separati. Il primo ,`cmp`, mette a confronto due valori, poi con i vari comandi di branch, si decide a quale label andare. 

Ci sono due comandi di comparazione, quello rispetto due valori `cmp`, e quello rispetto allo zero `tst`. Questi comandi accettano l'utilizzo di `.l` `.w` `.b`

Entrambi i comandi `cmp` e `tst` salvano il risultato del confronto nel `CCR`, che poi verranno utilizzati nei comandi di branch scritti sotto.

## tst [l w b] {w}
```assembly
tst <reg>
; comparazione con 0
```

## cmp [l w b] {w}
Se il secondo operando è un registro indirizzi (a) allora ha formato `long`.
```assembly
cmp <num/reg>, <reg>
; comparazione di due valori 
```
## Comandi di branch
Una volta settati i valori da comparare, possiamo fare il confronto vero e proprio con i comandi di branch, questi andranno a controllare i dati del CCR e "salteranno" alla label data se la comparazione è vera. Tutti hanno sintassi:
```assembly
comando <label>
```

* `beq` a == b
* `bne` a != b
* `blt` a < b
* `ble` a <= b
* `bgt` a > b
* `bge` a >= b

## Comandi di branch speciali (CCR)
In oltre ci sono altri comandi di branch "speciali", molti comandi in m68k, una volta eseguiti, comparano il registro destinazione con lo 0, in oltre tengono conto anche del segno del numero, se c'è stato un overflow, etc... Queste informazioni vengono salvate nel CCR, ed oltre ai comandi di branch precedenti, come i precedenti comandi di branch, hanno sintassi: 
```assembly
comando <label>
```
e sono:
* `bmi` se un valore è negativo
* `bpl` se un valore è positivo
* `bcs` se dopo aver fatto un operazione aritmetica su numeri unsigned, se c'è stato riporto nella cifra più a sinistra (più significativa), per esempio, prendendo un byte per numero, si fa `255 + 9`, il risultato sarà `8`, perchè `264` è più grande del numero massimo rappresentabile da un byte, che è 255, se ciò è accaduto, allora si dice che c'è stato **riporto**. vale anche se un numero va da positivo a negativo, es: 1-3 sarà 254. 
* `bcc` come bcs, ma se **NON** c'è stato riporto
* `bvc` come bcc, ma con numeri signed
* `bvs` come bcs, ma con numeri signed


## Branch incondizionato
Va direttamente alla label.
```assembly
bra <label>
jmp <label>
```
## Lettura degli elementi del CCR
Come visto prima nei branch, nel CCR troviamo varie informazioni durante l'esecuzione del codice, come per esempio se c'è stato un overflow, se un numero è maggiore, se è minore, etc... Possiamo leggere queste informazioni tramite questi comandi, se una condizione è vera, allora tutti i bit saranno settati a 1, sennò saranno settati a 0. hanno tutti sintassi:
```assembly
comando <destinazione>
```
* `scc` se non c'è stato riporto (carry clear)
* `scs` se c'è stato riporto (carry set)
* `seq` se è uguale
* `sge` se è maggiore uguale (greater or equal) **SIGNED**
* `sgt` se è maggiore (greater) **SIGNED**
* `sle` se è minore uguale (less or equal) **SIGNED**
* `sls` se è più piccolo o uguale (lower) **UNSIGNED**
* `slt` se è minore (less) **SIGNED**
* `shi` se è più grande (higher) **UNSIGNED**
* `smi` se è negativo
* `sne` se non è uguale
* `spl` se è positivo
* `svc` se non c'è stato overflow (overflow clear)
* `svs` se c'è stato overflow (overflow set)
* `sf`  se è falso
* `st`  se è vero


# Operazioni sui bit e logici
Le operazioni sui bit ci permettono di effettuare modifiche ai singoli bit di un registro, come spostarli a sinistra/destra, invertirli, etc...

## not, or, and, xor
Effettua le operazioni not, or, and, xor, tra un registro e una maschera. La maschera è una sequenza di bit che specificano a quali posizioni si deve effettuare l'operazione logica. I vari operatori hanno funzioni equiparabili a:
* `NOT` Inverso di tutti i bit (1 diventa 0, 0 diventa 1), non usa una maschera
* `OR`  Setta ad 1 i bit alle posizioni della maschera, senza modificare gli altri
* `AND` Prelevare i bit alle posizioni della maschera, oppure controllare se un bit è segnato ad 1 nella posizione segnata nella maschera
* `XOR` Inverso dei bit alle posizioni della maschera.

il primo elemento del comando sarà la maschera, (tranne nel not), il secondo elemento sarà il registro dove effettuare l'operazione, e dove verrà salvata
```assembly
not <reg>

or <num/reg>, <destinazione>
and <num/reg>, <destinazione>
eor <num/reg>, <destinazione>
```
esempi:
```assembly
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
-----------------------------------
## lsl 
logical shift left, sposta tutti i bit di di un registro di tot posizioni a sinistra, le cifre aggiunte saranno uguali a 0.
Uguale al comando << in C
```assembly
lsl <reg/num>, <destinazione>

; d0 = 01011101 (in binario)
; d2 = 3 (in decimale)
lsl d2, d0
; d0 = 11101000
```
## lsr 
logical shift right, sposta tutti i bit di di un registro di tot posizioni a destra, le cifre aggiunte saranno uguali a 0. Ignora il segno del numero, quindi un numero negativo verrà trattato ugualmente ad uno positivo. 
Uguale al comando >> in C (undefined behaviour)
```assembly
lsr <reg/num>, <destinazione>

; d0 = 11011101 (in binario)
; d2 = 3 (in decimale)
lsr d2, d0
; d0 = 00011011
```

## asr / asl 
arithmetical shift right/left, sposta tutti i bit di di un registro di tot posizioni a destra/sinistra. Tiene conto del segno del numero. Se verso destra, i numeri aggiunti saranno uguali al numero più a sinistra, se verso sinistra, il segno verrà ignorato, ma se c'è un cambio di segno, verrà segnato sul CCR

```assembly
asr <reg/num>, <destinazione>
asl <reg/num>, <destinazione>
; d0 = 10010111 (in binario)
; d2 = 2 (in decimale)
asr d2, d0
; d0 = 11100101
```
## rol / ror
rotate left / rotate right. Prendendo per esempio la rotazione a destra, il comando sposterà a destra di un tot numero di bit, e li posizionerà a sinistra (al posto dei bit da aggiungere). Lo stesso vale per rol, ma verso sinistra
```assembly
rol <reg/num>, <destinazione>
ror <reg/num>, <destinazione>

; d0 = 01000011
rol #2, d0
; d0 = 11010000
```

# Operazioni sui singoli bit
Servono per effettuare operazioni sui singoli bit. Tutti i comandi seguenti, prima di modificare un bit, settano il CCR `equal` al valore del bit da cambiare, e poi modificano il bit. Se il secondo operando è un registro viene letto tutto il registro, se non lo è, vengono letti solo i primi 8 bit.

Il primo operando è il bit da leggere, il secondo sarà dove effettuare l'operazione e salvarla. 
## btst
Testa il bit a posizione specificata del registro, setta la condizione del CCR `equal` al valore del bit a quella posizione, poi possiamo usare il comando `beq` per i branch. Non modifica la destinazione

```assembly
btst <num/reg>, <reg/adr>
```
## bclr 
Setta a 0 il bit a posizione specificata del registro.
```assembly
bclr <num/reg>, <dest>
```

## bchg
Inverte il bit a posizione specificata del registro.
```assembly
bchg <num/reg>, <dest>
```

## bset
Setta ad 1 il bit a posizione specificata del registro.
```assembly
bset <num/reg>, <dest>
```