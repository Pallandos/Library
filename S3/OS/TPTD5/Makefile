default: cpu cpu_affinity produit_threads

cpu: cpu.c
	gcc cpu.c -o cpu

cpu_affinity: cpu_affinity.c
	gcc cpu_affinity.c -o cpu_affinity

produit_threads: produit_threads.c
	gcc -o produit_threads produit_threads.c -lpthread