def estadoQ0(fita, posFita):
    if fita[posFita] == 'B':
        posFita = posFita + 1
        estadoQ1(fita, posFita)

def estadoQ1(fita, posFita):
    if fita[posFita] == '0' or fita[posFita] == '1':
        posFita = posFita + 1
        estadoQ1(fita, posFita)
    else:
        posFita = posFita + 1
        estadoQ2(fita, posFita)

def estadoQ2(fita, posFita):
    if fita[posFita] == '0' or fita[posFita] == '1':
        posFita = posFita + 1
        estadoQ2(fita, posFita)
    else:
        posFita = posFita - 1
        estadoQ3(fita, posFita)

def estadoQ3(fita, posFita):
    if fita[posFita] == '0':
        fita[posFita] = '1'
        posFita = posFita - 1
        estadoQ3(fita, posFita)
    elif fita[posFita] == '1':
        fita[posFita] = '0'
        posFita = posFita - 1
        estadoQ4(fita, posFita)
    else:
        posFita = posFita + 1
        estadoQ6(fita, posFita)

def estadoQ4(fita, posFita):
    if fita[posFita] == '0' or fita[posFita] == '1':
        posFita = posFita - 1
        estadoQ4(fita, posFita)
    else:
        posFita = posFita - 1
        estadoQ5(fita, posFita)

def estadoQ5(fita, posFita):
    if posFita == 0:
        fita.insert(0, 'B')
        posFita = posFita + 1


    if fita[posFita] == '1':
        fita[posFita] = '0'
        posFita = posFita - 1
        estadoQ5(fita, posFita)
    else:
        fita[posFita] = '1'
        posFita = posFita + 1

        estadoQ1(fita, posFita)

def estadoQ6(fita, posFita):
    if fita[posFita] == '1':
        fita[posFita] = 'B'
        posFita = posFita + 1
        estadoQ6(fita, posFita)
    else:
        while('B' in fita):
            fita.remove('B')
        novaFita = ''.join(fita)
        print("Resultado: " + novaFita)


vetorFita = ['B']

primeiroNumero = input("Insira o primeiro numero: ")
segundoNumero = input("Insira o segundo numero: ")

for x in list(primeiroNumero):
    vetorFita.append(x)

vetorFita.append('B')

for x in list(segundoNumero):
    vetorFita.append(x)

vetorFita.append('B')

estadoQ0(vetorFita, 0)