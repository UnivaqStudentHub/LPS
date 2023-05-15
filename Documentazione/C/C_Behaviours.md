# Tipologie di behavior
C Standard individua 5 diverse tipologie di 
behavior:
1. [well-defined behavior](#well-defined-behavior)
2. [locale-specific behavior](#locale-specific-behavior)
3. [unspecified behavior](#unspecified-behavior)
4. [implementation-defined behavior](#implementation-defined-behavior)
5. [undefined behavior](#undefined-behavior)

## Well-defined Behavior
Un `well-defined behavior` è un comportamento completamente definito da C Standard.

Tutti i costrutti del seguente programma, ad esempio, hanno `well-defined behavior`

```C
#include <stdio.h>

int main(void) {
    int x, y = 42;

    x = y;
    return 0;
}
```

## Locale-specific Behavior
Il `locale` è un insieme di parametri, modificabili anche durante l’esecuzione di un programma, che 
supportano l’internazionalizzazione dei programmi in C permettendo di adattare alcuni aspetti del
linguaggio alle convenzioni di uno specifico gruppo di utenti.

Esempi degli aspetti che possono dipendere dal locale sono l’insieme di caratteri usato per l’input-output e il formato di numeri, date e quantità monetarie.

Un `locale-specific behavior` è un comportamento che dipende dalla configurazione del locale.

Ad esempio, il fatto che la funzione *islower* della libreria Standard restituisca 1 per qualche valore del 
parametro diverso da uno dei 26 caratteri minuscoli dell’alfabeto latino, è un locale-specific behavior.

## Unspecified Behavior
Un `unspecified behavior` è l’uso di un valore non specificato o un altro comportamento per il quale C 
Standard presenta due o più possibilità e nessun vincolo su quale di essa debba, ad ogni occasione, 
essere scelta dall’implementazione.

Uno dei casi più comuni di `unspecified behavior` è relativo all’ordine di valutazione delle sotto-espressioni di una stessa espressione, che usiamo come esempio per chiarire il concetto.


Un modo efficace di descrivere l’ordine in cui vengono valutate le sotto-espressioni di una espressione, è
mostrare la traduzione dell’istruzione in una sequenza equivalente di istruzioni `unstructured C`.

Le regole di C 
Standard stabiliscono che per tutti gli **operatori binari**, ad eccezione dell’operatore di concatenazione `,` 
e degli operatori logici `&&` e `||`, l’ordine di valutazione delle due espressioni che costituiscono gli 
operandi è non specificato; ovvero le implementazioni possono valutare i due operandi in un qualunque 
ordine.

Ad esempio, l'istruzione
```C
    x = y * 4 + z % 3;
```
Ha due traduzioni in stile `unstructured C` **ugualmente** corrette.
```C
// Traduzione 1
    int t1, t2;
    t1 = y * 4;
    t2 = z % 3;
    x = t1 + t2;
```
```C
// Traduzione 2
    int t1, t2;
    t2 = z % 3;
    t1 = y * 4;
    x = t1 + t2;
```
Nella maggioranza dei casi la cosa è irrilevante in quanto il risultato è comunque lo stesso. Ma non sempre è così, ad esempio, il codice
```C
    int i = 2, j;

    int g(int x){
        i += x;
        return 3*i;
    }

    int main(void){
        j = i + g(5);
        return 0;
    }
```
un compilatore potrebbe tradurlo come
```C
    int i = 2, j;

    int g(int x){
        int t1;
        i = i + x;
        t1 = 3*i;
        return t1;
    }

    int main(void){
        int t;
        j = i;
        t =  g(5);
        j = j + t;
        return 0;
    }
```
un’altro compilatore, invece potrebbe tradurlo come
```c
    int i = 2, j;

    int g(int x){
        int t1;
        i = i + x;
        t1 = 3*i;
        return t1;
    }

    int main(void){
        int t;
        t =  g(5);
        j = i + t;
        return 0;
    }
```
È quindi possibile che due diversi compilatori producano risultati diversi.

L’ordine di valutazione delle sotto-espressioni è solo un esempio di unspecified behavior: ve ne sono 
molti altri in C Standard.
### Portable e Non-Portable unspecified behavior
Definiamo `portable` un programma C che produce gli stessi risultati su tutte le 
implementazioni.

Tra gli esempi di *unspecified behavior* precedenti, alcuni sono `portable` e alcuni invece sono `non-portable`, proprio a causa dei loro 
*unspecified behavior*.

Definiamo:
* `portable unspecified behavior` gli *unspecified behavior* che non pregiudicano la portabilità
* `non-portable unspecified behavior` gli *unspecified behavior* che rendono non portabile un programma

## Implementation-defined Behavior
Un `implementation-defined behavior` è un *unspecified behavior* ma con un vincolo in più per le implementazioni: documentare quale, tra le possibilità permesse da C Standard, viene scelta.

Anche nel caso di un `implementation-defined behavior` C Standard presenta due o più possibilità e le implementazioni possono scegliere liberamente quale di esse realizzare.

### Portable e Non-Portable  implementation-defined behavior
* `portable implementation-defined behavior`: *implementation-defined behavior* che non pregiudicano la portabilità
* `non-portable implementation-defined behavior`: *implementation-defined behavior* che rendono non portabile un programma

## Undefined Behavior
Un `undefined behavior` è un comportamento che C Standard non definisce, nel modo più assoluto.

Ciò significa che un’implementazione lo può realizzare in qualunque modo preferisca, senza alcun vincolo da parte di C Standard.

Un esempio tipico di undefined behavior è la divisione per 0.

In C esistono degli operatori che hanno un effetto collaterale (in inglese 
`side effect`), ovvero oltre a calcolare un valore, modificano uno dei loro operandi, tali operatori sono:
* operatori di assegnamento `=`, semplice o composti
* operatori di incremento `++` e decremento `--`, prefissi o postfissi.

Diversamente dagli `unspecified e implementation-defined behavior`, per definizione tutti
gli `undefined behavior` rendono `non-portable` un programma.

### Regola Un-D-SE
> Se un'espressione che produce un side effect su una variabile V non è vincolata ad essere eseguita **interamente prima** dell'inizio o dopo del termine dell'esecuzione di altre espressioni che producono side effect su V, oppure calcolano dei valori leggendo V, allora si ha un `undefined behavior`

Ad esempio, nel caso
```C
    z = ( ++x - b ) * ( x -= 3);
```
la regola `Un-D-SE` si applica perché vi sono due operatori che producono un side effect su **𝑥** e non vi è alcun vincolo che imponga che l’esecuzione di uno dei due avvenga interamente prima di quella dell’altro.

Pertando si ha `undefined behavior` e dunque un’implementazione ha licenza di tradurre l'istruzione in un codice 
eseguibile che fa qualunque cosa.

### Regola Comp-SE-E
> Nella valutazione di un'espressione E che non è sotto-espressione di un'espressione più grande, tutti side effect generati dalle sotto-espressioni, terminano prima che termini la valutazione di E

Ad esempio, nel caso
```C
    z = ( ++x - b ) * ( a -= 3);
```
non è contenuta in espressioni più grandi, quindi i `side effect` generati in essa, tra cui la modifica di **x** 
generata da `++x`, terminano prima che termini l’esecuzione della riga.

Poiché il `side effect` generato da `++x` avviene prima che inizi la valutazione di una possibile riga successiva, non si applica `Un-D-SE` e il codice non ha `undefined behavior`.

### Regola Comp-SE-F1
> Tutti side effect generati dalla valutazione degli argomenti in una chiamata di funzione, terminano prima che inizi la chiamata di funzione

Ad esempio, nel codice
```C
    int x = 1, y;

    int f(int a) {
        x *= 5;
        return x-a;
    }

    int main(void){
        y = f(++x);
        return 0;
    }
```
`Comp-SE-F1` garantisce che non abbia `undefined behavior`, e che quando inizia l’esecuzione di `𝑓` il parametro abbia valore pari a `2`.

### Regola Comp-SE-F2
> Sia f1 una funzione nel cui corpo compare una chiamata ad un'altra funzione 12. Tutti i side effect eseguiti in f1 e tutte le valutazioni di espressioni eseguite in f1, diverse dalla chiamata di f2, vengono eseguiti interamente prima dell'inizio o dopo del termine dell'esecuzione del corpo di f2

Ad esempio, nel codice
```C
    int x = 1, y;

    int f(int a) {
        x *= 2;
        return x-a;
    }

    int main(void){
        y = ++x * f(4);
        return 0;
    }
```
`Comp-SE-F2` garantisce che non abbia `undefined behavior` ma “solo” un `non-portable unspecified behavior`.

### Regola Comp-SE-F3
> Tutti i side effect generati da espressioni contenute in una funzione, terminano prima che termini l'esecuzione della funzione

Ad esempio, nel codice
```C
    int x, y = 3;

    int f(int a) {
        return (x=2)*a;
    }

    int main(void){
        x += f(2);
        return 0;
    }
```
`Comp-SE-F3` garantisce che non abbia `undefined behavior` e che al termine dell’esecuzione `𝑥` contenga il valore `6`.

# Esempi undefined behavior
* Esempio 1
```C
/*
- La sotto-espressione 𝑥 ∗= 𝑎 è
contenuta in una funzione.
- L’esecuzione di 𝑓, rispetto
al calcolo di 8 ∗ 𝑥, termina prima o
inizia dopo.
- Il side effect che modifica 𝑥
inizia dopo l’inizio di 𝑓 e termina
prima che termini 𝑓, quindi, il side
effect che modifica 𝑥 termina prima
oppure inizia dopo, rispetto al calcolo
di 8 ∗ 𝑥.

Dunque Un-D-SE non si applica e il codice
ha “solo” un non-portable unspecified
behavior
*/

    int x = 3, y;
    
    int f(int a){
        return (x*=a)%2;
    }

    int main(void){
        y = 8 * x - f(3);
        return 0;
    }
```
* Esempio 2
```C
/*
- La variabile 𝑥 viene letta per calcolare
il valore di 8 ∗ 𝑥 e inoltre viene letta
e modificata in 𝑥 ∗= 3.
- Il side effect che modifica 𝑥 non
è vincolato a terminare prima o a
iniziare dopo rispetto al calcolo
di 8 ∗ 𝑥.

Quindi si applica Un-D-SE, e dunque
il codice ha undefined behavior.
*/

    y = 8 * x - (x *= 3) % 2;
```
## Array
* Calcolo degli indici
```C
/*
Il calcolo degli indici e side effect
nell'espressione * non* sono vincolati a
essere eseguite in tempi distinti
quindi c'è possibilità di
undefined behavior
*/

    int dati1[10];
    dati1[h] = 2 * dati1[h++];  //undefined behavior
    dati1[h] = 3 + h++;  //undefined behavior
    dati1[h++] = 3 + h;  //undefined behavior
```
* Accesso con indice illegale
```C
    int dati1[10];
    dati1[20] = 34;  //undefined behavior
```
## Puntatori
* applicare `*` a puntatori
```C
/*
- Applicare * a null pointer causa
un undefined behavior
- Applicare * ad una variabile puntatore
non inizializzata causa undefined
behavior
- Applicare * ad una variabile di tipo
puntatore a void causa undefined behavior
*/

    short int *p1 = 0, *p2, x;
    void *p3 = &x;
    x = *p1;    //undefined behavior
    *p2 = 2;    //undefined behavior
    *p3 = 3;    //undefined behavior
```
* `cast` tra puntatori
```C
/*
In generale, conversioni tra puntatori
di tipo diverso potrebbero produrre
puntatori non validi (per violazioni di
vincoli di allineamenti) e di
conseguenza causare un undefined
behavior
*/

    int *p1, x = 3;
    char *p3;
    p1 = &x;
    p3 = (char *) p1;    //undefined behavior
```
## Array e Puntatori
* accesso all'elemento OPLE
```C
/*
L'elemento OPLE non esiste, dunque è
undefined behavior accedere a esso
*/

    int a[10], x, *p, *q;

    p = &a[10];
    *p = 2; // undefined behavior
    a[0] = *p   // undefined behavior
```
* aritmetica di puntatori
```C
    int a [10] , *p , *q , *r , *s;
    int x = 3;

    p = &a[5];
    q = &a[10];
    r = &a[11]; // undefined behavior
    r = p + 6; /* undefined behavior:
             p+6 è maggiore di POPLEL */

    s = p + 5; // OK: s è il POPLEL
    r = s - 2; // OK: r punta a[8]
    a[0] = *r ;

    a[1] = *s ; /* undefined behavior:
                s è il POPLEL */

    s = &a[10] - 0; /* OK: s è
                    il POPLEL */

    q = &a[11] - 3; /* undefined behavior:
                    calcola &a[11] */

    q = &a[8] + x - 2; /* undefined
            behavior, calcola & a [11]
            (come passo intermedio ) */
    q = &a[8] + ( x - 2 ); /* OK:
                        q punta a [9] */
```
* regola CIAPE
```C
/*
È undefined behavior deferenziare (ovvero
accedere al valore) il POPLEL di un array
*/

    unsigned long a[8] = { 1, 2, 3, 4, 5};
    unsigned long *p;

    p = a + 2;  // p punta a[2]
    a[6] = p[2];    // copia a[4] in a[6]
    p[1] += p[-1]; // somma a[1] a a[3]
    p[-2] = 0; //scrive 0 in a[0]

    p[-3] = 0; /* undefined behavior:
            scrive fuori dell ’ array */
    
    p[5] = -1; // scrive -1 in a[7]

    p[6] = 1; /* undefined behavior:
            scrive 1 nell’elemento OPLE 
            (deferenzia il POPLEL) */
```
## Conversioni
* conversioni dirette da un tipo intero a un tipo intero con segno
```C
/*
È undefined behavior se il valore da
convertire non è rappresentabile mediante
il tipo intero con segno
*/

    unsigned long long x = 11111987654321;
    signed int y;

    y = x;  // undefined behavior
```
* conversioni dirette da un tipo float a un tipo intero diverso da `_Bool`
```C
/*
È undefined behavior se il valore (privo
della parte frazionaria) da convertire
non è rappresentabile mediante
il tipo intero
*/

    float x = 1111198.32;
    short int y;

    y = x;  // undefined behavior
```
* conversioni dirette da un tipo aritmetico a un tipo float
```C
/*
È undefined behavior se il valore da convertire non è rappresentabile mediante
il tipo float
*/

    float x = 1111198.32 / 3213123072; // undefined behavior
    //valore che dovrebbe risultare 0,034583
    //valore effettivo in c 0.000346
```
# Esempi implementation defined behavior
## Puntatori
* conversione tra puntatori e valori interi
```C
/*
Il risultato di una conversione tra
un puntatore e un valore intero è un
implementation defined behavior
*/

    int *p;

    p = (int *) 0x1000; // implementation defined behavior
```
* conversione tra puntatori e oggetti
```C
/*
Il risultato di una conversione tra
un puntatore e un oggetto è un
implementation defined behavior
*/

    float *p1;
    unsigned long long w;

    p1 = (float *) 0x1000; // implementation defined behavior
    w = (unsigned long long) p1;    // implementation defined behavior
```