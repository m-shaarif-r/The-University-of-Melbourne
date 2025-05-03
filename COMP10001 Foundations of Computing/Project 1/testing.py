LIKELY_WORDS = ["Frenchy", "INTENSE", "ComputerScienceFTW", "HelloMrGumby"]
MIDDLE = "Horse20"
CREME_PUFF = 38
import itertools
possible_pws = []

def hack_it(start=LIKELY_WORDS, middle=MIDDLE, end=CREME_PUFF):
    # your code here
    start = sorted(start, key=lambda i: i[0])
    for i in itertools.permutations(start,2):
        first_part = ''.join(list(i))
        for end_num in range(end + 1):
            possible_pws.append(first_part + middle + str(end_num).zfill(2))
    print(possible_pws)

hack_it()