from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # Initialise empty lists
    list_a = a.splitlines()
    list_b = b.splitlines()

    # convert to sets and use intersection to generate common list
    list_common = list(set(list_a).intersection(list_b))

    return list_common


def sentences(a, b):
    """Return sentences in both a and b"""

    # Create lists of sentences
    list_a = sent_tokenize(a)
    list_b = sent_tokenize(b)

    # Convert to sets and use intersection to generate common list
    list_common = list(set(list_a).intersection(list_b))

    return list_common


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # Create empty lists
    sub_a = []
    sub_b = []

    # Calculate all substrings in each list
    for i in range(len(a) - n + 1):
        sub_a.append(a[i:i+n])

    for i in range(len(b) - n + 1):
        sub_b.append(b[i:i+n])

    # Convert to sets and use intersection to generate common list
    list_common = list(set(sub_a).intersection(sub_b))

    return list_common
