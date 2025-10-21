# TP chiffrement de césar

cypher1 ="MPRVXRHQJUACPRAHURVUPAPRCVPRQPRYQVRFXRPCHWQPRAPQHKXQQPMPFHCLIPPUFPAPFHUAHUGLJFFPUGRPAXGVCXUJXCPUHUTQ"

letters = {
    'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7, 'I': 8, 'J': 9,
    'K': 10, 'L': 11, 'M': 12, 'N': 13, 'O': 14, 'P': 15, 'Q': 16, 'R': 17, 'S': 18,
    'T': 19, 'U': 20, 'V': 21, 'W': 22, 'X': 23, 'Y': 24, 'Z': 25
}

def inverse_mod(a, m):
    """
    Computes the modular inverse of a under modulo m using the Extended Euclidean Algorithm.
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

def decrypt_affine(cypher, a, b):
    """
    Decrypts a message using the affine cipher with the given parameters.
    """

    # Calculate the modular inverse of a under modulo 26
    ainv = inverse_mod(a, 26)
    decrypted_message = ""
    for char in cypher:
        if char.isalpha():
            # Convert letter to number
            num = letters[char]
            # Apply the decryption formula
            decrypted_num = (ainv * (num - b)) % 26
            # Convert number back to letter
            decrypted_message += list(letters.keys())[decrypted_num]
        else:
            decrypted_message += char
    return decrypted_message

print(decrypt_affine(cypher1, 15, 7))