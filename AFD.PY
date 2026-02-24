import re

def afd_tokenizar(texto):
    tokens = []
    i = 0
    n = len(texto)

    while i < n:
        c = texto[i]

        # Ignorar espacios
        if c.isspace():
            i += 1
            continue

        # Estado inicial → "+"
        if c == '+':
            if i + 1 < n and texto[i + 1] == '+':
                tokens.append(('INCR', '++'))
                i += 2
            else:
                tokens.append(('SUMA', '+'))
                i += 1

        # Estado inicial → "ID"
        elif re.match(r'[A-Z]', c):
            j = i + 1
            while j < n and re.match(r'[a-z0-9]', texto[j]):
                j += 1
            tokens.append(('ID', texto[i:j]))
            i = j

        # El NO
        else:
            tokens.append(('NO ACEPTA', c))
            i += 1

    return tokens


# Leer
try:
    with open('texto.txt', 'r') as archivo:
        for num, linea in enumerate(archivo, 1):
            print(f"\nLínea {num}: {linea.rstrip()}")
            for tipo, valor in afd_tokenizar(linea):
                print(f"  {tipo}: {valor}")

except FileNotFoundError:
    print("Error: no se encontró 'texto.txt'")