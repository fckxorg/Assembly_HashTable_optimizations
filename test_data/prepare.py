import re
data = []

with open("gaijin.txt", "r") as file:
    for line in file:
        raw_tokens = re.sub(r'([^\s\w]|_)+', '', line)
        tokens = raw_tokens.split()
        garbage = ['a', 'the', 'in', 'of', 'and', 'to', 'in', 'is']
        for el in garbage: 
            while el in tokens:
                tokens.remove(el);
        data += tokens


word_count = 0
average_length = 0

data = list(set(data))


with open("word_set.txt", "w") as file:
    for el in data:
        file.write(el + '\n')
        word_count += 1
        average_length += len(el)

average_length /= word_count

with open("prepare.log", "w") as file:
    file.write("AVERAGE WORD LENGTH: " + str(average_length) + "\n")
    file.write("WORD COUNT: " + str(word_count) + "\n")
