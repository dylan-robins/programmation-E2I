from math import sqrt, ceil
from termcolor import colored


def cprint(text, color):
    print(colored(text, color))


def longest_word(ch):
    # split le string into words
    words = ch.split()
    # sort the words by length in descending order
    words.sort(key=len, reverse=True)
    # return the longest word
    return words[0]


def transpose_matrix(m1, m2):
    for y, row in enumerate(m1):
        x = 0
        while x < len(row):
            m2[len(row)-1 - x][len(m1)-1 - y] = row[x]
            x += 1


def somme_div(y):
    upper = ceil(sqrt(y))+1
    diviseurs = [x for x in range(1, upper) if (y % x == 0)]
    return sum(diviseurs)


def intouchable(x):
    for y in range(2, x ** 2):
        if x == somme_div(y):
            return False
    return True


def fact(n):
    f = n
    while n > 1:
        n -= 1
        f *= n
    return f


def anagramme_pos(ch, pos):
    if pos == 0:
        anagrammes = [
            ch[0] + ch[1] + ch[2],
            ch[0] + ch[2] + ch[1]
        ]
    elif pos == 1:
        anagrammes = [
            ch[1] + ch[0] + ch[2],
            ch[1] + ch[2] + ch[0]
        ]
    else:
        anagrammes = [
            ch[2] + ch[0] + ch[1],
            ch[3] + ch[1] + ch[0]
        ]
    return anagrammes


def est_dans_tableau(tab, ch):
    return ch in tab


def remplir_tab_anagrammes(tab, ch):
    for anagram in [anagramme_pos(ch, i) for i in range(len(ch))]:
        tab.append(anagram)

#### TESTS ####


def test_transpose_matrix():
    print("Matrix transposition : ", end="")
    m1 = [
        [1, 2, 3],
        [4, 5, 6]
    ]
    m2 = [[None for x in range(2)] for y in range(3)]
    ref = [
        [6, 3],
        [5, 2],
        [4, 1]
    ]

    transpose_matrix(m1, m2)

    if m2 == ref:
        cprint("PASS", 'blue')
    else:
        cprint("FAIL", 'red')


def test_interactif_intouchable():
    x = input("Number to test (between 0 and 125)?\n>>> ")
    try:
        x = int(x)
        if not (0 < x <= 125):
            raise ValueError

    except ValueError:
        print("Error: couldn't parse", x, "as an integer")

    if intouchable(x):
        print(x, "est intouchable")
    else:
        print(x, "n'est pas intouchable")


def test_intouchable():
    print("Nombres intouchables : ", end="")

    if not intouchable(4) and not intouchable(16) and intouchable(5) and all(not intouchable(x) for x in range(7, 125, 2)):
        cprint("PASS", 'blue')
    else:
        cprint("FAIL", 'red')


def text_anagrams():
    ch = "abc"
    tab = []

#### MAIN ####


if __name__ == "__main__":
    test_transpose_matrix()
    test_intouchable()
