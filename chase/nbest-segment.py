#!/bin/env python
import morfessor
import sys

io = morfessor.MorfessorIO()

if len(sys.argv) < 3:
  print "Usage: %s model_file sentence_file" % (sys.argv[0],)
  sys.exit(1)

model_file = sys.argv[1]
sentence_file = sys.argv[2]

model = io.read_binary_model_file(model_file)

with open(sentence_file, "r") as f:
  for line in f:
    sys.stdout.write("(")
    for word in line.split():
      nodes = {} # nodes indexed by the partial word so far
      nodes[""] = {}

      best = model.viterbi_nbest(word, 5)
      # best is an array of tuples, each of which is:
      # - (segmentation, -log prob), where segmentation is an array of strings

      # build the graph out by walking each path that we were given, adding
      # edges to the graph if they aren't there, or increasing their weight
      # if they are
      for scored_seg in best:
        seg = scored_seg[0]
        logprob = -scored_seg[1]

        curword = ""
        for word in seg:
          if word not in nodes[curword]:
            nodes[curword][word] = [logprob]
          else:
            nodes[curword][word].append(logprob)
          curword += word
          if curword not in nodes:
            nodes[curword] = {}

      # do a topological sort of the nodes to assign ids for output
      topo_id = {}
      topo_sorted = []
      visited = set()

      def visit_node(word):
        global topo_id
        global topo_sorted
        if word in visited:
          return

        visited.add(word)
        for edge in nodes[word]:
          visit_node(word + edge)
        nid = len(nodes) - 1 - len(topo_id)
        topo_id[word] = nid
        topo_sorted = [word] + topo_sorted

      visit_node("")

      # append this word to our lattice in PLF format
      for word in topo_sorted:
        # no edges for last node
        if len(nodes[word]) == 0:
          continue

        sys.stdout.write("(")
        log_max = max(logprob for edge in nodes[word]
                              for logprob in nodes[word][edge])

        denom = sum(pow(2, logprob - log_max) for edge in nodes[word]
                                              for logprob in nodes[word][edge])
        for edge in nodes[word]:
          num = sum(pow(2, logprob - log_max) for logprob in nodes[word][edge])
          dist = topo_id[word + edge] - topo_id[word]
          sys.stdout.write("('%s', %f, %d)," % (edge, num / denom, dist))
        sys.stdout.write("),")

    sys.stdout.write(")\n")
