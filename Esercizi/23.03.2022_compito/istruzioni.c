/*
A >> analisi statica del programma 
      >> VIOLAZIONE o CONTSRAINT ==> descrizione regola violata
            >> rimozione delle istruzioni contenenti violazioni
    >> continuare l'analisi

B >> analisi dinamica del programma
      >> per ogni costrutto descrivere quello che succede quando viene eseguito

      >> per ogni operatore che genera SIDE EFFECT:
            >>  se genera un undefined behaviour
                 ==> individuarlo e spiegare la causa
                 ==> rimuovere l'istruzione
                 ==> continuare l'analisi
            >> se NON genera undefined behaviour
                 >> descrivere come viene modificata la memoria 
                        ==> variabile modificata e valore nuovo  (in caso di portable behavior)
                        ==> quali sono i possibili nuovi valori (in caso di non-portable behavior)
      
      >> ulteriori undefined behaviour
            ==> individuarli e spiegare da cosa vengono causati 
            ==> rimuovere l'istruzione
            ==> continuare l'analisi 
*/