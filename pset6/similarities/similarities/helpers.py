import io
from nltk.tokenize import sent_tokenize


def lines(a, b):

    set1 = set()
    set2 = set()
    # library to work with strings
    s = io.StringIO(a)
    t = io.StringIO(b)

    for line in s:
        set1.add(line.rstrip())

    for line in t:
        set2.add(line.rstrip())

    list1 = list(set1.intersection(set2))
    # debugging output
    print(list1)

    return list1


def sentences(a, b):
    """Return sentences in both a and b"""

    list1 = sent_tokenize(a, language='english')
    print(list1)
    set1 = set(list1)

    list2 = sent_tokenize(b, language='english')
    print(list2)
    set2 = set(list2)

    list3 = list(set1.intersection(set2))

    print(list3)

    return list3


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    set1 = set()
    set2 = set()
    length = int(n)

    s = io.StringIO(a)
    t = io.StringIO(b)

    print(a)
    print(b)
    for i in range(0, len(a)-length+1, 1):
        print(a[i:i + length])
        set1.add(a[i:i + length])

    for j in range(0, len(b)-length+1, 1):
        print(b[j:j + length])
        set2.add(b[j:j + length])

    list3 = list(set1.intersection(set2))

    print(list3)

    return list3
