# Introduzione
In MIPS i registri sono in due formati, `word` o `half`.
* `word` 32bit
* `half` 16bit

Possono essere visti come due gruppi da 16 bit, le due half formano una word
```
[0000000000000000][0000000000000000]
```
# Registri
Gli operatori come addizione etc possono funzionare sia a 2 operandi che 3 operandi.

I register general purpose sono:
```assembly
Registri parametri  -> a0,a1,a2,a3
Registri temporanei -> t0,t1,t2,t3,t4,t5,t6,t7,t8,t9
Registri salvati    -> s0,s1,s2,s3,s4,s5,s6,s7
Registri ritorno    -> v0,v1
Registri speciali   -> sp, ra
```
Possono essere anche usati tramite solo il numero da `1-32`.

I registri vengono usati con il carattere `$s0, $1`

Ci sono poi altri due registri specific purpose, usati nella divisone e moltiplicazione. Per esempio nella moltiplicazione viene usato per rappresentare il numero in 64 bit. Mentre per la divisione per salvare il risultato e il resto
```c
hi //higher
lo //lower
[hi][lo]
```

In tutti i comandi in MIPS, l'operando a sinistra è quello che **riceve** il dato, come in C
```assembly
li $s0, 100
    ;equivalente a: 
    ;s0 = 100
```


Mentre invece i numeri possono essere inseriti direttamente
```assembly
li $s3,826
```
# Metodi di indirizzamento

Si definisce *modo di indirizzamento* (*addressing mode*) una regola che, a partire da alcune informazioni, permette di indirizzare una parola.

Tutti i comandi aritmetici leggono il contenuto dei registri in formato word (32 bit).

In MIPS ci sono vari modi per indirizzare i dati e prenderne i valori. 

## Immediato
`Im` Un numero, non è mai destinazione di un'istruzione
```assembly   
Im -> <numero>
    add	$t0, $t0, 8
```

## Diretto registro
`Reg` Un qualsiasi registro
```
Reg -> <s0/s1/.../s7/t0/t1/.../t7>
    add $s0, $s1, $s2
```

## Indiretto registro 
`(Reg)` Si utilizza un registro come puntatore. Legge la memoria all'indirizzo di Reg. Utilizzato nell'indicizzazione dinamica di un array e stack.
```assembly
    lbu	$t0,($t1)
```

## Implicito
Viene implicitamente utilizzato un registro per eseguire una particolare operazione
```assembly
    mfhi $s0    ; setta nel registro hi il valore del registro
```


# Comandi

## li
*load immediate* -> Mette nel registro destinazione il valore immediato (numero), il primo operando sarà il registro dove mettere il valore, il secondo operando, il numero da mettere.
```assembly
li <Reg>, <Im>

li $s0, 100
    ;s0 = 100
```
## lui
*load upper immediate* -> Mette a 0 tutti i primi 16bit (half) del registro e poi mette nel registro destinazione il valore immediato (numero) nella seconda word.
```assembly
lui <Reg>, <Im>
lui $s0, 0xFFFF
    ;s0 = 0xFFFF 0000
```


## move
Serve a copiare il valore di un registro in un altro registro. Il primo sarà il registro dove verrà copiato il valore, il secondo invece è dove verrà preso il valore. Copia tutto il registro (word)
```assembly
move <Reg>, <Reg>

move $s0, $t0
    ;s0 = t0
```

## add - addu - addi - addiu
Somma il secondo e terzo operando e mette il risultato nel primo

* `add` somma **signed**, se il terzo operando è un numero, lo legge a 16bit
* `addu` somma **unsigned**, se il terzo operando è un numero, lo legge a 32bit
* `addi` somma immediate, il terzo operando è un numero, lo legge a 32 bit
* `addiu` uguale a addiu ma **unsigned**
Solo il terzo operando può essere un numero
```assembly
add <Reg>, <Reg>, <Reg/Im>

add $s0, $t1, 100
    ;setta a s0 la somma di t1 + 100
    ;s0 = t1 + 100

add $s0, $t1, $t2
    ;setta a s0 la somma t1 + t2
    ;s0 = t1 + t2

NON VALIDO:
add $s0, 100, 200
```

## sub - subu

* `sub` sottrae **signed**, se il terzo operando è un numero, lo legge a 16bit
* `subu` sottrae **unsigned**, se il terzo operando è un numero, lo legge a 32bit

Fa la sottrazione
 tra secondo e terzo operando, mettendo il risultato nel primo

```assembly
sub <Reg>, <Reg>, <Reg/Im> 

sub $s0, $t1, $t2
    ;s0 = t1 - t2

sub $s0, $t1, 100
    ;s0 = t1 - 100
```
**ATTENZIONE**
Il secondo operando deve **sempre** essere un registro, non può essere un numero:
```assembly
    ;NON VALIDO
sub $s1, 100, $t2
    ;s1 = 100 - $t2
```
Se si vuole sottrarre un numero, dovremmo caricare il `100` in un registro
```assembly
li $t1, 100
sub $s1, $t1, $t2
    ;t1 = 100
    ;s1 = t1 - t2
```

## div - divu (tre operandi)

* `div` divide **signed**, se il terzo operando è un numero, lo legge a 32bit se positivo, 16bit se negativo
* `divu` divide **unsigned**, se il terzo operando è un numero, lo legge a 32bit se positivo, 16bit se negativo

Effettua la divisione intera tra secondo operando (dividendo) e terzo operando (divisore) mettendo il risultato nel primo operando


**NOTA**: Il risultato viene calcolato esclusivamente in formato intero (NON ARROTONDATO), il resto viene perduto, per avere il resto usare `div` [due operandi](#div-due-operandi) 

```assembly
div <Reg>, <Reg>, <Reg/Im>

div $a1, $t1, $t2
    ;a1 = t1 / t2

div $a1, $t1, 10
    ;a1 = t1 / 10
```


## div - divu (due operandi)
Effettua la divisione intera tra il valore del primo operando (dividendo) e il valore del secondo (divisore), mettendo il risultato nei registri `hi` e `lo`.

* `div` divide **signed**
* `divu` divide **unsigned**

Viene salvato in `lo` il quoziente ed in `hi` il resto.

I registro `lo` e `hi` non possono essere letti direttamente ma vanno usati con i comandi [mflo](#mflo) e [mfhi](#mfhi)
    
**ATTENZIONE**
Il dividendo e divisore **DEVONO** essere dei registri
```assembly
div <dividendo>, <divisore>
    
div $s0, $t1 
    ;lo = s0 / t0
    ;hi = s0 % t0

mflo $s1 
    ;s1 = lo

mfhi $t1
    ;t1 = hi
```

## mul - mulu
Effettua la moltiplicazione. Il risultato sarà salvato nel registro destinazione. 
I registri LO e HI assumono un contenuto indefinito


* `mul` moltiplica **signed**, se il terzo operando è un numero, se positivo lo legge a 32bit, 16bit se negativo
* `mulu` moltiplica **unsigned**, se il terzo operando è un numero, se positivo lo legge a 32bit, 16bit se negativo


**ATTENZIONE** Il risultato sarà espresso massimo in 32 bit, per la versione a 64 bit guarda [mult](#mult)

```assembly
mul <Reg>, <Reg>, <Reg/Im>

mul $s0, $t0, $t1
    ;s0 = t0 * t1
mul $s0, $to, 100
    ;s0 = t0 * 100
```

## mult - multu

* `mult` moltiplica **signed**, lo legge a 32bit
* `multu` moltiplica **unsigned**, lo legge a 32bit

Effettua la moltiplicazione tra due registri, salva le prime 32 cifre in `lo`, e le restanti 32 in `hi`
```assembly
mult <Reg>,<Reg>

mult $s0, $t0
    ;lo = primi 32 bit
    ;hi = ultimi 32 bit
```

## mfhi
*Move From hi* -> Estrae il valore di `hi` e lo inserisce nel registro
```assembly
mfhi <Reg>
mfhi $s0
    ;s0 = hi
```


## mflo
*Move From lo* -> Estrae il valore di `lo` e lo inserisce nel registro
```assembly
mflo <Reg>

mflo $s0
    ;s0 = lo
```


## mthi
*Move To hi* -> Setta nel registro `hi` il valore del registro
```assembly
mthi <Reg/Im>

mthi $s0
    ;hi = s0
mthi 50
    ;hi = 50
```

## mtlo
*Move To lo* -> Setta nel registro `lo` il valore del registro
```assembly
mtlo <Reg/Im>

mtlo $s0
    ;lo = s0
mtlo 50
    ;lo = 50
```

# Comandi branch e comparazione
Questi comandi vengono usati per mettere a confronto un registro con un altro, o ad un numero immediato, per poi andare nella label se la condizione è vera.

## Branch incondizionato
Utilizzato molto nei loop, il branch incondizionato esegue il salto alla label ogni volta.

Le istruzioni di salto incondizionato sono `b` e `j`
```
b <label>
j <label>
```
Esempio:
```assembly
b for_start
```

## Comparazione con lo 0
hanno sintassi del tipo:
```
comando <Reg>, <label>
```

Comando             |  Logicamente         
:------------------:|:-------------------:
beqz                 |      a == b            
bnez                 |      a != b       
bltz                 |      a < b
blez                 |      a <= b
bgtz                 |      a > b
bgez                 |      a >= b   

Esempio:
```assembly
bgtz $s0, maggiore_zero
```
## Comparazione tra valori signed
Comparano due registri tra di loro e vanno alla label se la condizione è vera.
Hanno sintassi del tipo:
```
comando <Reg>, <Reg/Im>, <label>
```

Comando             |  Logicamente         
:------------------:|:-------------------:
beq                 |      a == b            
bne                 |      a != b       
blt                 |      a < b
ble                 |      a <= b
bgt                 |      a > b
bge                 |      a >= b     

Esempio:
```assembly
beq $s1, $s2, label_uguali
```
## Comparazione tra valori unsigned
```
comando <Reg>, <Reg/Im>, <label>
```


Comando              |  Logicamente         
:-------------------:|:-------------------:     
bltu                 |      a < b
bleu                 |      a <= b
bgtu                 |      a > b
bgeu                 |      a >= b   

Esempio:
```assembly
bltu $s1, $s2, label
```

# Operazioni sui bit e logici
Le operazioni sui bit ci permettono di effettuare modifiche ai singoli bit di un registro, come spostarli a sinistra/destra, invertirli, etc...

## not, or, and, xor
Effettua le operazioni not, or, and, zor, tra un registro e una maschera. La maschera è una sequenza di bit che specificano a quali posizioni si deve effettuare l'operazione logica. I vari operatori hanno funzioni equiparabili a:
* AND: Prelevare i bit alle posizioni della maschera, oppure controllare se un bit è segnato ad 1 nella posizione segnata nella maschera
* OR: Setta ad 1 i bit alle posizioni della maschera, senza modificare gli altri
* NOT: Inverso di tutti i bit (1 diventa 0, 0 diventa 1), non usa una maschera
* XOR: Inverso dei bit alle posizioni della maschera.

l'ultimo elemento del comando sarà la maschera, (tranne nel not), il secondo elemento sarà il registro dove effettuare l'operazione
```assembly
not <Reg>, <Reg>

or <Reg>, <Reg>, <Reg/Im> 
or <Reg>, <Im>

and <Reg>, <Reg>, <Reg/Im> 
and <Reg>, <Im>

xor <Reg>, <Reg>, <Reg/Im> 
xor <Reg>, <Im>
```
esempi: 
```assembly
    ;per semplicità di scrittura, sono rappresentati solo 8 dei 32 bit
    ;s0 = 01100111
    ;in realtà sarebbe
    ;s0 = 00000000000000000000000001100111

    ;s0 = 01100111 (maschera)
    ;s1 = 11001100 
    ;s2 = 11001100 
    ;s3 = 11001100 
    ;s4 = 11001100 

not $s1, $s1
    ;s1 = 00110011

or $s2, $s2, $s0
    ;s2 = 11101111

and $s3, $s3, $s0
    ;s3 = 01000100

xor $s4, $s4, $s0
    ;s4 = 10101011
```

-----------------------------------

## sll 
*Shift left logical* -> Sposta tutti i bit di di un registro di tot posizioni a sinistra, le cifre aggiunte saranno uguali a 0.
Uguale al comando << in C
```assembly
sll <Reg>, <Reg>, <Im>

    ;s0 = 01011101 (in binario)
sll $s0, $s0, 3
    ;s0 = 11101000
```

## srl 
*Shift right logical* -> Sposta tutti i bit di di un registro di tot posizioni a destra, le cifre aggiunte saranno uguali a 0. Ignora il segno del numero, quindi un numero negativo verrà trattato ugualmente ad uno positivo. 
Uguale al comando >> in C (undefined behaviour)
```assembly
srl <Reg>, <Reg>, <Im>

    ;s0 = 11011101 (in binario)
srl $s0, $s0, 3
    ;s0 = 00011011
```

## sra
*Shift right arithmetical* -> Sposta tutti i bit di di un registro di tot posizioni a destra. Tiene conto del segno del numero. i valori aggiunti a sinistra saranno uguali al valore del bit più significativo (quello più a sinistra)
Uguale al comando >> in C (undefined behaviour) 
```assembly
sra <Reg>, <Reg>, <Im>

    ;s0 = 10010111 (in binario)
    ;s2 = 2 (in decimale)
sra $s0, $s0, $s2
    ;s0 = 11100101
```
## rol / ror
*Rotate left / right* -> Prendendo per esempio la rotazione a destra, il comando sposterà a destra di un tot numero di bit, e li posizionerà a sinitra (al posto dei bit da aggiungere). Lo stesso vale per rol, ma verso sinistra
```assembly
rol <Reg>, <Reg>, <Reg/Im>
ror <Reg>, <Reg>, <Reg/Im>

    ;s0 = 01000011
rol $s0, $s0, 2
    ;s0 = 11010000
```


# Input e output (syscall)
Le syscall ci permettono di comunicare con le api del sistema operativo. Un esempio sono quelle di lettura e scrittura del terminale.
Il funzionamento generale è quello di inserire il tipo di comando che vogliamo effettuare nel registro `$v0`, ed eseguire la `syscall`.

## Input numero intero
Per effettuare l'input di un numero intero (leggere da terminale), si deve settare il registro `$v0` a `5`, effettuare la syscall, e poi leggere il risultato in `$v0`

```assembly
li $v0, 5
syscall
move $s1, $v0
```

## Output numero intero
Per effettuare l'output di un numero intero, si setta il registro di `$v0` a `1`, e il numero da stampare all'interno del registro `$a0`

```assembly
li $a0, 20
li $v0, 1
syscall     
    ;stampa 20
```
# La memoria in MIPS
La memoria in MIPS può essere vista come una lista di byte, dove ogni byte nella lista ha una posizione chiamata "address". La gestione dei dati salvati all'interno della memoria è completamente lasciata allo sviluppatore che scrive il programma, quindi dovrà essere tenuta in considerazione la lunghezza in byte dei vari formati di dato che andremo a salvare. 

**ATTENZIONE**, quando andiamo a leggere e scrivere negli address, in base alla grandezza del formato che vogliamo usare, l'indirizzo scelto dovrà essere un multiplo del formato scelto. Per esempio, non possiamo salvare una word (4 byte) all'indirizzo 2021, perchè non è modulo di 4, ma possiamo salvarlo in 2024

## Formati di dato
Ogni formato di dato ha la propria lunghezza, dovremo tenerne conto quando salviamo e leggiamo dalla memoria. I dati letti/scritti verranno letti dall'indirizzo specificato, fino all'`indirizzo + lunghezza`.

Alcuni formati standard, diversi dal formato **byte**, definiscono una restrizione agli indirizzi validi per le 
parole standard di tale formato, chiamata `vincolo di allineamento`.
* `byte` : ha lunghezza 8 bit (1 parola)
* `word` : ha lunghezza 16 bit (2 parole), fattore di allineamento 2
* `long` : ha lunghezza 32 bit (4 parole), fattore di allineamento 4

Ad esempio, per salvare una **word** all'address 0x2000, il dato verrà salvato negli indirizzi 0x2000 e 0x2001 e, dunque, la successiva **word**, non potrà essere salvata a partire dall'address 0x2001, bensì dovrà essere salvata a partire dall'address 0x2002.

Importante è sapere il modo in cui i dati in memoria vengono letti/scritti. 

Esistono due tipologie chiamate `little endian` e `big endian`. 

In MIPS, per la lettura/scrittura in memoria può essere usato sia il [Big endian](#Big-endian) che il [Little endian](#little-endian).

MIPS32-MARS utilizza il [Little endian](#little-endian).

### Little endian
Little endian è quando i byte sono salvati da destra verso sinistra, partendo dal più significativo. Per esempio il numero `0x1234` viene salvato in memoria come `0x34 0x12`.

### Big endian
Big endian è quando i byte sono salvati da sinistra verso destra, partendo dal più significativo. Per esempio il numero `0x1234` viene salvato in memoria come `0x12 0x34`.

## Utilizzo della memoria
Per utilizzare la memoria all'interno del programma, ci basterà specificare il numero dell'indirizzo della memoria come operando, scrivendolo in maniera `$numero_indirizzo`, esempio `$2000`. Alternativamente, possiamo creare una `variabile` alias all'inizio del programma che indica a quale indirizzo fa riferimento l'alias. Facciamo ciò tramite il comando [.eqv](#.eqv)


In MIPS la memoria viene gestita principalmente dai comandi [lw-lh-lb](#Trasferimento-da-registro-a-memoria) e [sw-sh-sb](#Trasferimento-da-memoria-a-registro), rispettivamente per salvare in e caricare dalla memoria;

## .eqv
*equal variable* -> Crea un alias dell'indirizzo della memoria. 
Deve essere sempre scritto prima del `.text`.

Quando il programma viene assemblato, l'assembler sostituirà l'alias con l'indirizzo della memoria.


```assembly
.eqv <nome_variabile>, <adr/reg>

.eqv var_v, 0x10011000 
    ;var_v è l'address 0x10011000
.eqv var_w, $s0
    ;var_w è il registro s0
```
## Trasferimento da registro a memoria
In MIPS non è possibile utilizzare gli indirizzi di memoria direttamente all'interno delle istruzioni, dovranno per forza essere salvate all'interno di un registro prima di poterle usare.
### sw
*Store word*-> Salva la word contenuta nel registro, nell'indirizzo specificato (32 bit, 4 byte)

```assembly
sw <reg>, <adr>

    ;so = 1234
sw $s0, 2000
    ;salva ad address 2000 la word 1234
```
### sh
*Store half*-> Salva la half contenuta nel registro, nell'indirizzo specificato (16 bit, 2 byte)

```assembly
sh <reg>, <adr>

    ;so = 1234
sh $s0, 2000
    ;salva ad address 2000 la half 1234
```
### sb
*Store byte*-> Salva il byte contenuto nel registro, nell'indirizzo specificato (8 bit, 1 byte)

```assembly
sb <reg>, <adr>

    ;so = 200
sh $s0, 2000
    ;salva ad address 2000 il byte 200
```
le istruzioni store non necessitano di avere la specifica *unsigned*
## Trasferimento da memoria a registro
Per prelevare un dato dalla memoria e salvarlo in un registro.
### lw
*Load word* -> Preleva la word dall'indirizzo specificato e la salva nel registro. (32 bit, 4 byte).
```assembly
lw <Reg>, <adr/(Reg)>

lw $s0, 2000
```

### lh - lhu
*Load half / load half unsigned*  -> Preleva la half dall'indirizzo specificato e la salva nel registro. (16 bit, 2 byte).
* `lh` Setta il CCR in base al segno del numero
* `lhu` Non setta il CCR
```assembly
lh <Reg>, <adr/(Reg)>
lhu <Reg>, <adr/(Reg)>

lh $s0, 2000
lhu $s1, 3000
```
### lb - lbu
*Load byte / load byte unsigned* -> Preleva il byte dall'indirizzo specificato e la salva nel registro. (8 bit, 1 byte).
* `lb` Setta il CCR in base al segno del numero
* `lbu` Non setta il CCR
```assembly
lb <Reg>, <adr/(Reg)>
lbu <Reg>, <adr/(Reg)>

lb $s0, 2000
lbu $s1, 3000
```
### la 
*Load address* -> Copia l'indirizzo della label nel registro

```assembly
la <Reg>, <label/(Reg)>

la $s0, unaLabel
```

# Indirizzi di Memoria e Label
Gli indirizzi possono essere scritti in forme più comode utilizzando `label`. 
Ogni label è legata ad un indirizzo di memoria, ovvero rappresenta tale indirizzo. In fase di traduzione l'assembler trasforma ogni label nell'indirizzo ad essa legato. Hanno quindi senso operazioni come

```assembly
; se pippo è una label, l'indirizzo successivo sarà l'indirizzo pippo+1, quello dopo ancora pippo+2, e così via...

        li  $s0, 100
pippo:  add $s0, $t1, 100 
        div $a1, $t1, 10    ;pippo+1
        mul $s0, $t0, $t1   ;pippo+2
```
Quando il programma viene assemblato, ogni istruzione è convertita in un numero a 32 bit (4 byte). Quando il programma viene eseguito, questi numeri sono caricati nella memoria ed eseguiti. Le label sono solo un "alias" all'indirizzo di memoria dove è salvata l'istruzione. Quando per esempio facciamo un branch ad una label, quello che in realtà sta succedendo, è che il programma continua l'esecuzione all'indirizzo di memoria dove è salvata la label.

# Allocazione statica della memoria
L’allocazione della memoria statica viene fatta mediante le `sezioni`; ogni sezione ha un `indirizzo di inizio sezione`.

Si può allocare la memoria in maniera "statica" (cioè non si può espandere).

Una direttiva di definizione dati:
* indica quanti byte devono essere allocati e se necessario, i valori da memorizzare.
* non indica l’indirizzo di memoria dei byte da allocare: tale indirizzo è determinato automaticamente dall'assembler.

## .data
Per indicare la sezione della memoria in MIPS32-MARS viene utilizzata la direttiva *.data*. Tale direttiva viene seguita dalle dichiarazioni di costanti.
```assembly
    .data
```

## Definizione di costanti
Per definire costanti all'interno di un programma vengono invece utilizzata le direttive:
* ***.byte*** -> definisce una o più costanti di formato *byte*
* ***.half*** -> definisce una o più costanti di formato *half*
* ***.word*** -> definisce una o più costanti di formato *word*

Combinando i meccanismi di direttive e etichette, si ottiene una sintassi simile al C
```assembly
    .data
eta:        .byte   24      ; char eta = 24;
voto:       .half   28      ; int voto = 28;
score:      .word   -170     ; long int score = -170;
```
Nelle direttive ***.byte*** ***.half*** ***.word*** i valori possono essere espressi anche in esadecimale
```assembly
    .data
.byte   0xAF
.half   0xAB13
.word   0xABCD0000
```
***ATTENZIONE*** Si noti che l'assembler MARS scrive valori secondo la endianness [Little endian](#little-endian)
```assembly
    .data
.byte   0xAA 0xBB 0xCC 0xDD
```
è equivalente a
```assembly
    .data
.word   0xDDCCBBAA
```
Possiamo usare i meccanismi di direttive e etichette per definire array e stringhe (di lunghezza fissa).


Per esempio per definire un array di 5 elementi tutti a valore 1:
```assembly
    ; char unArray[ 5 ] = { 1, 1, 1, 1, 1 };
    .data   $10010000
unArray:    .byte   1,1,1,1,1
```
Potremo poi accedere ai valori dell'array usando il nome della label. Se volessimo iterare gli elementi dell'array, dovremo leggere l'indirizzo dell'array, e poi incrementarlo in base alla grandezza degli elementi. Oppure se dobbiamo leggere un elemento specifico, possiamo usare `label+posizione`
```assembly
; STATICO
    .data   $10010000
unArray:    .byte   1,1,1,1,1
    ; unArray[3] += 8
lb      $t0,unArray+3
add     $t0,$t0,8
sb      $t0,unArray+3

; DINAMICO
    .data   $10010000
unArray:    .byte   1,1,1,1,1
id1:	    .word	2

    .text
    ; unArray[5]=3*unArray[id1];
la      $t1,unArray  ; prende l'indirizzo di "unArray"
lw	    $t2,id1      ; copia il valore di id1 in $t2
add	    $t1,$t1,$t2  ; calcola l'indice [id1];
lb	    $t0,($t1)    ; copia in $t0 il valore unArray[id1]
mul	    $t0,$t0,3    ; effettua la moltiplicazione
sb	    $t0,array1+5 ; copia il risultato in unArray[5]
```
## Array di N elementi
Possiamo usare array di N elementi usando la direttiva `.space`
```
<label>: .space <dimensione in byte>

;esempio array di 1000 long
array: .space 4000
```

## Stack e funzioni
Nei linguaggi assembly, per implementare le funzioni, si deve usare e gestire lo stack. Lo stack è una pila di frame che contengono i vari dati necessari per l'esecuzione di una funzione. 

In MIPS, il linguaggio non ci aiuta nella gestione dei frame e indirizzi di ritorno, deve pensare tutto lo sviluppatore. Quando una funzione viene chiamata, il registro `$ra` verrà modificato con l'indirizzo del chiamante, se abbiamo bisogno, all'interno di questa funzione, di chiamarne un altra, oppure fare ricorsione, allora dobbiamo salvare l'indirizzo di ritorno all'interno dello stack, per poi decrementare lo stack pointer.

Quando si chiama una funzione, la funzione chiamata avrà il compito di allineare lo stack pointer in modo da ritornare alla posizione dove era quando la funzione è stata chiamata. Se ha eventuali valori di ritorno, si troveranno dove si trova lo stack pointer.

esempio: (ricorda che è una pila, gli elementi vengono aggiunti dal basso verso l'alto)
```
Chiamata:

| return address | <--- SP
------------------
| parameter 2    |
------------------
| parameter 1    |

Ritorno:
| risultato      | <--- SP
``` 
Naturalmente potrebbe essere non necessario usare lo stack, dipende sempre dall'implementazione dello sviluppatore.
## Lettura e scrittura dello stack
In MIPS non ci sono comandi per gestire lo stack, ma si dovranno usare i `read / store` che si userebbero normalmente per la gestione della memoria. L'unica differenza è che usiamo il registro `$sp` in mezzo parentesi tonde (perché si utilizza l'indirizzamento indiretto-registro).

Possiamo anche aggiungere un offset che andrà a selezionare N + SP. Non modifica `$sp`

```assembly
; lettura
lw	    $t0,($sp)
; scrittura
sw	    $t0,($sp)
; offset, lettura di sp + 4
sw     $t0, 4($sp) 
```

## Chiamata a funzione e ritorno da funzione
In mips troviamo un comando che setta il valore di `$ra` con l'indirizzo successivo a quello della riga di chiamata di funzione, e uno che permette di fare un salto all'indirizzo di ritorno.

## jal
`jump and link` -> Setta il valore di `$ra` con l'indirizzo successivo a quello della riga di chiamata di funzione, e poi fa il salto alla label della funzione.
```assembly
    jal <label>
;esempio
    jal funzione1
```

## jr 
`jump register` -> Fa il salto alla label della funzione, di solito si usa l'indirizzo `$ra`, ma qualsiasi va bene.
```assembly
    jr <registro>
;esempio
    jr $ra
```
## convenzione
La convenzione di MIPS ci dice che i registri temporanei (t) possono essere usati a piacimento, i registri salvati (s) possono essere usati dalla funzione chiamata, ma dovranno essere ripristinati ai valori iniziali prima di ritornare. Si può usare i registri `v` per i valori di ritorno e `a` per i parametri, oppure usare lo stack se non è una funzione che chiama altre funzioni.
Esempio di jal e jr

## Esempio funzione
```assembly
# i parametri vengono scritti al contrario, quindi primo è num_2, poi num_1
	.text
	sub	$sp,$sp,8
	li	$s0,3
	sw	$s0,($sp)
	li	$s0,2
	sh	$s0,4($sp)
	jal	somma
	lw	$s0,($sp)	# preleva il risultato
	add	$sp,$sp,8	# pop dei parametri
	b	end
	

# Routine somma
# Input
#	Half in stack frame - parametro num_1
#	Word in stack frame - parametro num_2
# Output
#	Word in stack frame - risultato
# Registri modificati
#	$t0, $t1
# Stack frame
# Offset | Contenuto    | Note
# ----------------------------------------------
#        |              |
#        |              |
#   0    | num_2 e      | allocato da chiamante
#        | risultato    |
#        |              |
#   4    | num_1        | allocato da chiamante
#        |              |
# ----------------------------------------------
# dimensione stack frame: 6

.eqv	num_1, 4
.eqv	num_2, 0

somma:
	lh	$t1,num_1($sp)
	lw	$t0,num_2($sp)
	add	$t0,$t0,$t1
	sw	$t0,num_2($sp)
	jr	$ra

end:
```
## Esempio funzione ricorsiva
Funzione originale 
```c
int fr(int x) {
    if (x <= 0) return 0;
    if (x == 1) return 3;
    return fr(x / 3) + x;
}
```

```assembly
li $t0, 22
    sub $sp,$sp,4  
    sw $t0, ($sp) #add parameter to function call
    jal fr
    lw $t0, ($sp)
    b end
fr:
    lw $t0, ($sp) #get parameter of function call
    bgt $t0, 0, if_grater_than_zero
    #if (x <= 0) return 0;
    sw $zero, ($sp)
    jr $ra
if_grater_than_zero:
    #if (x == 1) return 3;
    bne $t0, 1, if_not_one
    li $t1, 3
    sw $t1, ($sp)
    jr $ra
if_not_one:
#   add frame for return address and parameter
    sub $sp $sp, 8
    sw $ra, 4($sp) #add return address
#   int par = x;
    move $t1, $t0
#   par /= 3;
    div $t1, $t1, 3
    sw $t1, ($sp)  #add parameter
#   int result = frStack(par);
    jal fr
    lw $t1, ($sp)  #return value
    lw $ra, 4($sp) #return address
    lw $t2, 8($sp) #x
#   x += result;
    add $t2, $t2, $t1
    add $sp, $sp, 8 #pop of the frame
    sw $t2, ($sp)
    jr $ra
#   return x;
end:
```
