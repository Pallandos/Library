"""
Module cryptographie symétrique

Ce module contient de nombreux outils utiles en cryptographie symétrique.

Contient : 
    dictionnaire de l'alphabet/entier, SBOX de l'AES
    chiffrement / déchiffrement de Hill, substitution affine

Auteur : Pallandos
"""

import sympy as sp
from typing import List

# HELP : 
# pour convertir du décimal en binaire  : utiliser la fonction hex()

LETTERS = {
    'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7, 'I': 8, 'J': 9,
    'K': 10, 'L': 11, 'M': 12, 'N': 13, 'O': 14, 'P': 15, 'Q': 16, 'R': 17, 'S': 18,
    'T': 19, 'U': 20, 'V': 21, 'W': 22, 'X': 23, 'Y': 24, 'Z': 25
}

AES_SBOX = [
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
]

def inverse_mod(a : int, m : int):
    """
    Calcule le modulo inverse de a modulo m en utilisant l'algorithme d'Euclide étendu.
    """
    m0, x0, x1 = m, 0, 1
    if m == 1:
        return 0
    while a > 1:
        # q is quotient
        q = a // m
        m, a = a % m, m
        x0, x1 = x1 - q * x0, x0
    if x1 < 0:
        x1 += m0
    return x1

def decrypt_affine(cypher : str, a : int, b : int) -> str:
    """Déchiffre un message chiffré avec le chiffrement affine selon les paramètres a et b.

    Args:
        cypher (str): chiffré à déchiffrer
        a (int): paramètre multiplicatif du chiffrement affine
        b (int): paramètre additif du chiffrement affine

    Returns:
        str: clair déchiffré
    """

    ainv = inverse_mod(a, 26)
    decrypted_message = ""
    for char in cypher:
        if char.isalpha():
            num = LETTERS[char]
            decrypted_num = (ainv * (num - b)) % 26
            decrypted_message += list(LETTERS.keys())[decrypted_num]
        else:
            decrypted_message += char
    return decrypted_message

def hill_encrypt(key: List[List[int]], plaintext: List[List[int]], modulus: int = 26) -> List[List[int]]:
    """Encrypte le plaintext selon le chiffrement de Hill.

    Args:
        key (List[List[int]]): clé de chiffrement
        plaintext (List[List[int]]): texte à chiffrer (CONVERTIR LES LETTRES EN ENTIERS)
        modulus (int, optional): Module contexte. Défaut à 26 pour l'alphabet.

    Returns:
        List[List[int]]: texte chiffré
    """
    K = sp.Matrix(key)
    P = sp.Matrix(plaintext)
    # Vérification de l'inversibilité de la clé modulo
    if int(K.det()) % modulus == 0:
        raise ValueError(f"La matrice clé n'est pas inversible modulo {modulus}.")
    # Chiffrement par produit matriciel
    C = (K * P) % modulus
    # Conversion en liste de listes
    return [[int(C[i, j]) for j in range(C.cols)] for i in range(C.rows)]

def hill_decrypt(key: List[List[int]], ciphertext: List[List[int]], modulus: int = 26) -> List[List[int]]:
    """Déchiffre le ciphertext selon le chiffrement de Hill.

    Args:
        key (List[List[int]]): clé de chiffrement
        ciphertext (List[List[int]]): texte à déchiffrer
        modulus (int, optional): Module contexte. Défaut à 26 pour l'alphabet.

    Returns:
        List[List[int]]: texte déchiffré
    """
    K = sp.Matrix(key)
    C = sp.Matrix(ciphertext)
    # Vérification
    det = int(K.det()) % modulus
    if det == 0:
        raise ValueError(f"La matrice clé n'est pas inversible modulo {modulus}.")
    # Calcul de l'inverse modulaire de la matrice
    inv_det = pow(det, -1, modulus)
    adj = K.adjugate()
    K_inv = (inv_det * adj) % modulus
    # Déchiffrement par produit matriciel
    P = (K_inv * C) % modulus
    return [[int(P[i, j]) for j in range(P.cols)] for i in range(P.rows)]


if __name__ == "__main__":
    print("======= EXEMPLES D'UTILISATIONS =======")

    print("==== Chiffrement de Hill ====")
    key_matrix = [[5, 12], [1, 3]]
    plaintext_blocks = [[10], [21]]  # exemple de l'exercice 3

    cipher_blocks = hill_encrypt(key_matrix, plaintext_blocks)
    print("Ciphertext blocks:", cipher_blocks)

    recovered = hill_decrypt(key_matrix, cipher_blocks)
    print("Recovered plaintext blocks:", recovered)
