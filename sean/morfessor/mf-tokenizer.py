import morfessor
import sys

io = morfessor.MorfessorIO()
model = io.read_binary_model_file(sys.argv[1])

for line in sys.stdin:
    output = ""
    for word in line.split():
        output += " ".join(model.viterbi_segment(word)[0]) + " "
    print output
