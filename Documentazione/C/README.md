# Tipi

| Nome          |   Dimensione   |
| ------------- | :------------: |
| **long long** | 64bit (8 byte) |
| **double**    | 64bit (8 byte) |
| **float**     | 32bit (4 byte) |
| **int**       | 32bit (4 byte) |
| **short**     | 16bit (2 byte) |
| **char**      | 8bit (1 byte)  |

# Comandi

## include

Include delle librerie esterne ad esempio <stdio.h>

```c
include <stdio.h>
```

## define

È una macro che permette di definire un "alias" ad un pezzo di codice. Quando il programma viene compilato, il compilatore rimpiazza ogni occorrenza dell'alias con il valore definito

```c
#define <nome> <codice>

#define PI 3.14
```

## printf

| Tipo dato   | Codice |
| ----------  | :----: |
| int signed  | **%d** |
| int unsigned| **%u** |
| float       | **%f** |  
| double      | **%lf**|
| exadecimal  | **%x** |

```c
int n = 10;
printf("numero = %d", n);
// stampa a schermo "numero = 10"
```

Con printf si può anche specificare lo spazio minimo occupato da un numero e la lunghezza della parte dopo la virgola da visualizzare:
```c
int i = 10;
float n = 10.1234;
printf ("numero = |%5d|", i);
// stampa a schermo "numero = |   10|"
//        spazio di 3 caratteri ^

printf ("numero = |%-5d|", i);
// stampa a schermo "numero = |10   |"

printf ("numero = |%.2f|", n);
// stampa a schermo "numero = |10.12|"


```

## scanf

**ATTENZIONE** Lo `scanf` richiede l'inserimento del puntatore `&` prima della variabile in cui si vuole salvare il valore inserito

È molto importante fare attenzione alla specifica del tipo per ogni valore che si prende in input, un tipo sbagliato assegnato ad un valore può formattarlo in modi imprevisti e causare undefined behavior
| Tipo dato                  | Codice  |
| ----------                 | :----:  |
| int signed                 | **%d**  |
| int unsigned               | **%u**  |
| short signed               | **%hd** |
| short unsigned             | **%hu** |
| char signed (come numero)  | **%hhd**|
| char unsigned (come numero)| **%hhu**|
| char                       | **%c**  |
| string (array di char)     | **%s**  |
| float                      | **%f**  |  
| double                     | **%lf** |
| exadecimal                 | **%x**  |

sono stati omessi tipi che vengono usati raramente, per saperne di più consultare le tabelle [qui](https://cplusplus.com/reference/cstdio/scanf/)
```c
int s;
scanf("%d", &s);
// inserisce un valore intero in s
```
## sizeof
Ritorna la grandezza dell'elemento passato in input
```c
char n = sizeof(int); // 4
int n2 = sizeof(n); // 1
```
## if

```c
if (condizione) {
    // codice se vero
} else{
    // codice se falso
}

//unstructured

if(!condizione) goto if_false;
    //codice se vero
    goto if_end;
if_false:
    //codice se falso
if_end:
```

## Operatore ternario

```c
condizione ? seVero : seFalso;

//esempio
int unaVariabile = numero > 0 ? 1 : 0;
```

## >> e <<

Operano direttamente sui bit delle variabili

`>>` sposta i bit a destra di un numero di bit specificato
`<<` sposta i bit a sinistra di un numero di bit specificato

```c
int a = 2;  // a = 0000 0010
a >> 1; // a = 0000 0001

--------------------------------

int a = 4;  // a = 0000 0100
a << 1; // a = 0000 1000
```

# Cicli

## for

```c
for (variabili; condizioni; incrementi) {
    // codice
}


//unstructured
int i;
for_start:
    if(i < 5) goto for_end;
        //codice del for
    i++;
    goto for_start
for_end:

//esempio
for(int i = 0, j = 0; i < 5; i++){

}

```

## while

Esegue il ciclo finchè la condizione è vera

```c
while(condizione){
   //codice
}

//unstructured
while_true:
    if(!condizione) goto while_end
    //codice
    goto while_true
while_end:
```

## do-while

Esegue il ciclo finchè la condizione è vera, ma esegue almeno una volta.

```c
do{
   //codice
} while(condizione);

//unstructured
while_true:
    //codice
    if(condizione) goto while_true;
```

# Tipi enumerativi

Sono utilizzati per creare degli alias a valori, sono utili per gestire le "tipologie" di cose all'interno del programma. Possiamo anche dare valori di default, oppure mischiare i due

```c
typedef enum {
    GATTO = 3,
    CANE, //implicitamente sarà 4
} Animale;

```

# struct

Usato per raggruppare più valori in una singola variabile, "simile" agli oggetti in Java, ma senza metodi. Naturalmente I tipi possono essere diversi. Da ricordare che a meno che si usi la malloc, il dato creato si troverà nello stack
**_Dichiarazione_**

```c
struct nome{
    //parametri
}
typedef struct {
    //parametri
} nome


//esempio
struct Point{
    int x;
    int y;
}
typedef struct {
    int start;
    int end;
} Line;
```

**_Utilizzo_**, I parametri sono passati in ordine

```c
struct Point punto = {
    1, //x
    2 //y
};
Line linea = {
    0, //start
    1   //end
};
```

# Union

Le union sono simili agli struct, ma hanno la differenza che, al suo interno, è possibile leggere un dato usando diverse interpretazioni. é usato spesso all'interno di struct con una variabile enumerativa che indica il tipo all'interno dell'union. La grandezza della union sarà quella del parametro con grandezza più alta.

````c
union nome{
    //parametri
}
//Esempio:

typedef union {
    char bytes[4];
    int numero;
} Numero;

Numero numero = { 1024 };
// numero.intero (letto come intero)
// numero.bytes[0] (letto come char array)

````

Si possono anche usare le union anonime per creare una struttura che contenga una variabile di un tipo specifico.

```c
typedef enum{
    intero = 0,
    reale = 1,
    carattere = 2,
} Tipo;

typedef struct {
    Tipo tipo;
    union {
        int intero;
        double reale;
        char carattere;
    };
} Numero;

Numero num = { intero, 10 };

```

# Puntatori

I puntatori hanno lo scopo di permettere il passaggio per "reference" di un informazione. Quando per esempio chiamiamo un metodo, possiamo passare come parametro una variabile tramite reference, poi la funzione modificherà ciò che gli è stato passato.

I puntatori vengono usati con 2 caratteri speciali

- `&` per prendere il puntatore di una variabile
- `*` per accedere ad un puntatore


## Dichiarazione puntatore
Possiamo settare una variabile come puntatore ad un altra variabile, oppure ad un blocco di memoria. Quando usiamo `*`, stiamo "referenziando".
```c
int nome;
int *puntatore;
puntatore = &nome;

//esempio
int x = 10;
int *p = &x; 
//p punta alla variabile x
```

## Utilizzo puntatore

Possiamo risalire a cosa punta il puntatore mettendo `*` prima del puntatore, in questo modo, scrivere/leggere il puntatore ha lo stesso effetto di scrivere/leggere cosa punta il puntatore. Viene chiamato "dereferenziazione"

```c
int x = 10;
int *p = &x;
// p contiene l'indirizzo di x

*p = 20;
//ora x è uguale a 20
```

## operatore freccia
Quando abbiamo, per esempio, un puntatore ad uno struct e dobbiamo settarne un campo, possiamo usare l'operatore `->`
```c
typedef struct {
    int x;
} Punto;

int x = 2;
Punto p = { x };
Punto *puntatore = &p;

(*puntatore).x = 10;
```
c'è un modo più veloce di scrivere ciò ed è quello di usare l'operatore freccia. `->`
```c
puntatore->x = 15;
printf("%d", puntatore->x);
```
## NULL pointer
Il null pointer è un puntatore speciale che viene tipicamente usato per specificare che un puntatore non punta ancora a nulla. Dobbiamo fare attenzione a non deferenziare un puntatore nullo, in quanto questo può causare errori.

```c
int *p = NULL;

int x = *p; //ERRORE
```
## void pointer
Un void pointer è un puntatore ad un tipo non specificato. è utile per creare cose "generiche", un esempio in seguito sarà la `malloc`.
***ATTENZIONE*** NON è possibile fare aritmetica dei puntatori con i void pointer. è una constraint violation di C.

## Aritmetica dei puntatori
I puntatori possono essere incrementati, decrementati etc. è molto utile per gestire gli array. Per esempio, se vogliamo passare ad una funzione una parte di un array, possiamo passargli il puntatore dell'array incrementato dalla posizione iniziale dell'array.
Il C gestisce in automatico la grandezza dell'incremento di un puntatore, in assembly quando dobbiamo spostarci all'elemento successivo, dobbiamo incrementare il puntatore rispetto alla dimensione degli elementi. Mentre in C, ci basta incrementare di 1.
```c
int sommaArray(int dim, int *array){
    int i;
    int somma = 0;
    for(i = 0; i < dim; i++){
        somma += array[i];
    }
    return somma;
}

int array[10] = {1,2,3,4,5,6,7,8,9,10};
int *p = array;
//somma gli ultimi 5 elementi dell'array
int risultato = sommaArray(5, p + 5); 
printf("%d", risultato); //40
```
## Puntatore a funzione
Si può prendere il puntatore ad una funzione, si usa:
```c
<tipo ritorno> (* nomeVariabile)(<tipo parametro>);


int somma(int a, int b){
    return a + b;
}

int (*pf)(int a, int b); //pf è il nome della variabile
pf = &somma;
(*pf)(1, 2); //somma(1, 2)
```
# Array

Gli array possono essere considerati come un puntatore a una lista di elementi, che ha una lunghezza fissa.
Quando facciamo `array[posizione]`, si sta facendo puntatore dell'array + posizione.
**_ATTENZIONE_** Gli array scritti successivamente sono salvati sullo stack. Dobbiamo fare attenzione quando vengono passati risultati da funzione, perchè in automatico, C pulisce la memoria usata dalla funzione una volta che si ritorna. Il c "clonerà" l'array se è ritornato direttamente dalla funzione, ma se fa parte di una struct, oppure array bidimensionale, il contenuto dell'array non sarà valido.

Ci sono due nozioni da ricordare, quello dei  `OPLE` e`POPLEL`. 
Rispettivamente `Element One-Past-Last-Element` e `Pointer One-Past-Last-Element`. 

Quello importante è il `POPLEL`, esso indica il puntatore dell'elemento successivo all'ultimo elemento dell'array. In pratica la fine dell'array. 
## Monodimensionali

```c
int name[length];
//esempio
int array[4] = {2,1,3,4}; //valori iniziali
```

```c
/*
 * array1 = { 10, 12, -4, 0, 0, 0, 9 } di dimensione 7
 * [ 6 ] = 9  mette 9 nella posizione di indice 6
 * dell'array
*/
int array1[ ] = { 10, 12, -4, [ 6 ] = 9 };
```

```c
// 	array2 = { 2.5, 5.0, 1.2, 0.0, 0.0 } di dimensione 5
float array2[ 5 ] = { 2.5f, 5.0f, 1.2f }
// array3 = { 0.7, 0.0, 0.0, 3.4, -1.1, 0.0, 0.0, 0.0 } di dimensione 8
float array3[ 8 ] = { 0.7f, [ 3 ] = 3.4f, -1.1f };
```

## Bidimensionali

```c
array2 = array3  //ERRORE: gli array non possono essere assegnati
int array4[ ][ 6 ] = { { 100 }, { 10, 20, 30, 40, 50, 60 }, { 1, 2, 3 } };
//definizione di array bidimensionale (multidimensionale)
```

**_ATTENZIONE_** In un array bidimensionale, o in generale multidimensionale, la prima dimensione può essere omessa, mentre tutte le altre vanno per forza specificate

```c
int array5[ 4 ][ ] = { { 100, 101, 102 }, { 10, 20, 30 }};      //ERRORE: seconda dimensione non specificata
int array6[  ][ 4 ] = { { 100, 101, 102 }, { 10, 20, 30 }};     //OK
```

Per utilizzare dinamicamente un array

```c
int array7[2][4] = {{1, 2, 3, 4},{2,3,4,5}};
    for(int i=0;i<2;i++){
        printf("\n");
        for(int j=0;j<4;j++){
            printf("%d ",array7[i][j]);
        }
    }
```
## Array di puntatori ad array
```c
    int array1[2] = {1,2};
    int array2[2] = {3,4};
    int array3[2] = {5,6};
    int *array[] = {array1, array2, array3};
```
## Array di funzioni
```c
int somma(int a, int b){
    return a + b;
}
int prodotto(int a, int b){
    return a * b;
}
int (*aritmetica[])(int a, int b) = {somma, prodotto};

printf("%d", (*aritmetica[0])(1,2)); //3
```

## Switch
Lo switch ha una funzione simile all'if else, ma permette di gestire più facilmente e velocemente una serie di condizioni. Ogni blocco è chiamato `case`, una volta entrato nel blocco, dobbiamo ricordare di uscirne, a meno che non ci serva continuare al blocco successivo.
```c
switch(elemento){
    case q1: {
        //codice
        break;
    }
    case q2:
    case q3: {
        //se l'elemento è uguale a q2 o q3
        break;
    }
    case q4:{
        //codice
        //non metto il break, continua l'esecuzione al case successivo
    }
    case q5: {
        //viene eseguito se è uguale a q5, ma anche se è uguale a q4, dato che in q4 NON è stato specificato il break
        break;
    }
    default: {
        //se non si è ancora usciti dai blocchi precedenti
    }
}
//esempio
int qualcosa(int a){
    int risultato = a;
    switch(a){
        case 1: {
            risultato = a * 2;
            break;
        }
        case 2:
        case 3: {
            risultato = a * 5;
            break;
        }
        case 4:{
            risultato = a * 10;
        }
        case 5:{
            risultato++;
            break;
        }
        default: {
            risultato = -1;
        }
    return risultato;
}

qualcosa(1); //2
qualcosa(2); //10
qualcosa(3); //15
qualcosa(4); //41
qualcosa(5); //6
qualcosa(6); //-1
```

# malloc, realloc, dealloc, free
Prendiamo questo esempio:
```c
typedef struct {
    int *voti;
    int id;
} Studente;
Studente creaStudente(int id) {
    int voti[3] = { 0,0,0 };
    Studente studente = { voti, id };
    return studente;
}
```
è parzialmente corretto. Logicamente va bene, ma quando la funzione termina di eseguire, C clona il valore di ritorno e dealloca tutta la memoria che è stata utilizzata all'interno della funzione. Questo vuol dire che il puntatore all'array dei voti non sarà più valido.
Per questo motivo dobbiamo utilizzare l'allocazione di memoria dinamica.
## malloc
Ritorna un puntatore ad un blocco di memoria di dimensione uguale al parametro passato. Si usa spesso insieme a `sizeof` che ci dice la dimensione dell'elemento. Si deve anche fare il Type casting del puntatore dell'array.
```c
   Tipo *puntatore = (tipo *) malloc(dimensione);

    // alloca un blocco di memoria che riesce a contenere un array di 3 elementi di tipo int
   int *voti = (int*) malloc(sizeof(int) * 3);
```
***ATTENZIONE*** Utilizzando malloc, il valore degli elementi all'interno non è azzerato.
***ATTENZIONEV2*** Potrebbe accadere che la memoria non sia sufficiente per allocare l'array. In questo caso, la funzione restituisce NULL.
## free
La funzione `free` ha l'effetto contrario, libera la sezione di memoria allocato con malloc. è MOLTO importante ricordarsi di liberare la memoria allocata quando non ci serve più, perchè se non si fa, ci sarà memory leak.
```c
    int *voti[] = (int *) malloc(sizeof(int) * 3); 
    free(voti);
```
## calloc
La funzione `calloc` accetta due parametri, il numero di elementi e la grandezza di ogni elemento. in oltre, azzera la memoria allocata.
```c
    Tipo *puntatore = (Tipo *) calloc(numeroElementi, dimensioneElemento);

    int *voti = (int *) calloc(3, sizeof(int));
    int *studente = (studente *) calloc(1, sizeof(studente));
```
## realloc 
Incrementa la dimensione di un certo blocco di memoria, usato spesso per gli array. Come parametri ha il puntatore al blocco di memoria da ingrandire e la nuova dimensione. Il vecchio puntatore viene deallocato (non piu valido) e ritorna un nuovo puntatore alla nuova memoria.
```c
    Tipo *nuovoPuntatore = (tipo *) realloc(vecchioPuntatore, nuovaDimensione);

    //array di 3 elementi
    int *voti = (int *) malloc(sizeof(int) * 3);
    //array di 5 elementi 
    voti = (int *) realloc(voti, sizeof(int) * 5);
```
