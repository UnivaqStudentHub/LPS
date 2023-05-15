int x = -1, y = 3, z = -5;
int main(void)
{
      z = x++ * 3 - (x = 6);

      return 0;
}

/*
 analisi statica del programma: non ci sono violazioni di regole sintattiche o di contiguità
 analisi dinamica del programma:
      - undefined behavior alla riga 4, non sappiamo se viene eseguito prima x++ o prima x = 6
 */

// RISCRIVO IN UNSTRUCTURED C
int x = -1, y = 3, z = -5;
int main(void)
{
      // z = x++ * 3 - (x = 6);
      x = 6;
      int t;
      t = x * 3;
      x = x + 1;
      z = t - x;

      return 0;
}
/*
 analisi statica del programma: non ci sono violazioni di regole sintattiche o di contiguità
 analisi dinamica del programma:
      - riga 20 : x = 6
      - riga 22 : t = 18
      - riga 23 : x = 7
      - riga 24 : z = 11
 */