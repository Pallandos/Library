.section .minirisc_init,"ax"
.global _minirisc_init
.type   _minirisc_init, @function

_minirisc_init:
	li t0,0x10000000 	# écrit l'adresse de charout dans le registre t0

	la t1, my_str

	loop_start:
		lb a0, 0(t1)            # Charger le caractère courant
		beq a0, x0, loop_end    # Si caractère = 0, sortir de la boucle
		sb a0, 0(t0)            # Affichage
		addi t1, t1, 1          # Passer au caractère suivant
		j loop_start

	loop_end:
		li t3, 0x220a0000       # Adresse de la mémoire de l'extinction
		li t2, 0xdeadbeef       # Extinction
		sw t2, 0(t3)
	
	my_str:
		.string "Hello World!!\n\0"

