/*
5 Diversi tipi di behavior:
    > well-defined
    > locale-specific
    > unspecified
    > implementation-defined
    > undefined

*/

// WELL-DEFINED
/*
    >> E' un comportamento del tutto gestito da C standard
*/
// esempi
int x, y = 42;
x = y;
return x;

// LOCALE-SPECIFIC
/*
    >> I locale-specific sono tutti legati all'esecuzione di funzioni delle librere standard di C

    NON VENGONO TRATTATE NEL CORSO
*/

// UNSPECIFIED
/*
    >> Uso di un valore non specificato o di un altro comportamento per il quale il C standard presenta due o più possibità
            >> non sappiamo quale implementazione viene scelta

    >> Caso più comune : Ordine di valutazione delle sottoespressioni di una stessa espressione
        >> L'ordine di valutazione delle espressioni non è specificato
        >> Le implementazioni possono valutare l'espressione in qualsiasi ordine
            >> E1 + E2, in cui sia E1 ed E2 sono a loro volta altre espressioni
                >> un'implementazione può scegliere se valutare prima E1 o prima E2

    >> Definiamo due tipi di c : 
        >> portable
            >> unspecified behavior che non pregiudicano la portabilità del codice 

        >> non-portable
            >> unspecified behavior che rendono un programma non portabile
    
*/
// esempi  ==> entrambi i modi restituiscono lo stesso risultato
x = y * 4 + z % 3;      //non sappiamo cosa esegue per primo
// riscriviamolo in unstructured (1° modo)
int t1, t2;
t1 = y * 4;
t2 = z % 3;
x = t1 + t2;

// riscriviamolo in unstructured (2° modo)
int t1,t2;
t2 = z % 3;
t1 = y * 4;
x = t1 + t2;



// IMPLEMENTATION-DEFINED
/*
    >> La documentazione dell'implementazione deve dichiarare quale delle possibilità permesse da C standard viene realizzata
    >> Distinguiamo fra due tipi di behavior :
        >> portable implementation-defined behavior
            >> non pregiudicano la portabilità
        
        >> non-portable implementation-defined behavior
            >> rendono non portabile un programma
*/


//UNDEFINED 
/*
    >> Comportamento che C standard non definisce nel modo più assoluto

    >> Quando abbiamo un' Undefined Behavior?
        >> [Regola Un-D-SE] 
            >>se una variabile è affetta da side effect
                >> E non viene eseguita interamente all'inizio o alla fine delle altre espressioni
                >> OPPURE in altre espressioni viene usata questa variabile
            >> esempio che rappresenta entrambi i casi : z = ( ++x - b ) * ( x -= 3 )

    >> Espressioni non contenute in espressioni piu' grandi
        >>[Regola Comp-SE-E]
            >> Nella valutazione di un’espressione E che non e' sotto-espressionedi un’espressione piu' grande, 
               tutti i side effect generati dalle sotto-espressioni, terminano prima che termini la valutazione di E
    
    >> Side effects all'interno di argomenti di una funzione
        >>[Regola Comp-SE-F1]
            >> Tutti i side effect generati dalla valutazione degli argomenti in una chiamata di funzione,
               terminano prima che inizi la chiamata di funzione
    
    >> Funzione dentro funzione con side effect 
        >>[Regola Comp-SE-F2]  ==> non-portable unspecified behavior
            >> Sia f1 una funzione nel cui corpo compare una chiamata ad un’altra funzione f2.
               Tutti i side effect eseguiti in f1 e tutte le valutazioni di espressioni eseguite in f1,
               diverse dalla chiamata di f2, vengono eseguiti interamente prima dell’inizio
               o dopo del termine dell’esecuzione del corpo di f2
    
    >> Side effects all'interno delle funzioni
        >>[Regola Comp-SE-F3]
            >> Tutti i side effect generati da espressioni contenute in una funzione, 
               terminano prima che termini l’esecuzione della funzione
            





*/




// OPERATORI CON SIDE-EFFECT
/*
    >> Oltre a calcolare un valore modificano uno dei loro operandi 
        >> Producono un side effect
            >> Esempi :
                >> x++ , ++x
        
        >> x++
            >> prima restituisce il valore della variabile e poi aumenta di 1
        
        >> ++x
            >> prima aumenta di 1 e poi restituisce il valore della variabile
    
    >> Stesse regole valgono per --x e x-- 
    >> Atri tipi di side effect si ottengono nelle assegngazioni all'interno delle espressioni
        ad esempio quando abbiamo x+= <variabile o numero> e operazioni simili
*/
// Esempi:

    y++ + a;
    // Si traduce in :
    a= y+a;
    y = y+1;

    ++y + a;
    // Si traduce in : 
    y=y+1;
    a= y+a;

    // Esempio di portable unsecified behavior
    x = y++ * (z + 5);
    
    // Esempio di non-portable unsecified behavior
    z = (++x - b) * (x -=3);
    /*
        >>Perchè?
            >> La x è presente in entrambe le parentesi
                >> Il risultato può cambiare a differenza dell'ordine di esecuzione
                    delle parantesi 

    */

