# on considère un LFSR de 4 bits de polynôme X4 + X + 1

etat = [1, 0, 1, 0]  # état initial

def etat_suivant(e):
    etat_final = [0, 0, 0, 0]
    etat_final[0] = e[1]
    etat_final[1] = e[2]
    etat_final[2] = e[3]
    etat_final[3] = (e[0] + e[1]) % 2
    return etat_final

def netats_suivants(e,n):
    etats = []
    for i in range(n):
        e = etat_suivant(e)
        etats.append(e)
    return etats

print(netats_suivants(etat, 5))

# matrice de transition :
# | 0 0 0 1
# | 1 0 0 1 
# | 0 1 0 0
# | 0 0 1 0
