# TP et TD 3

## Exo 1

En pseudo code on aurait : 

```c

P1(){
    // ------
    reception(P2, "rdv1");
    envoi(P2, "rdv1");

    RDV()
    // ------
}

P2(){
    // -----
    envoi(P1, "rdv2");
    reception(P1, "rdv2");

    RDV()
    // -----
}

```

## Exo 2

La généralisation donne : 

```c

PN(){
    for (int j, j<N j++){
        P(Pj,"rdv");
    }
    for (int j, j<N, j++){
        V(Pj,"rdv");
    }

    RDV()
}

Pi(){
    V(Pi,"rdv");
    P(Pj,"rdv");

    RDV()
}

```

## 2.8

Le père lit ce que le user écrit dans le terminal, le met dans le tube et le fis lit le tube.

> `wait(NULL)` : attente de la fin du fils mais sans tenir compte du message de terminaison

## 2.9
