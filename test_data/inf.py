with open("word_set.txt", "r") as file:
    print(max([len(list(x)) for x in file]))

