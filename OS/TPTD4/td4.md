# TDTP POSIX

## TD : 

L'ordonnanceur lance les *threads* à un moment non certain, donc fiare attention en cas d'accès par référence. 

> Un `exit()` touchera TOUS les threads avec le même PID, donc tous les threads de la famille 

> Un `malloc()` alloue de la mémoire sur le tas et pas sur la pile. Cela perme td'avoir des données persistantes. 
