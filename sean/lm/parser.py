import re
import sys
import gzip

infile = sys.argv[1]
outfile = re.sub('\.gz$', ".paragraphs", infile)

print "Parsing " + infile

filetext = gzip.open(infile, 'r').read()
output = open(outfile, 'w')
for paragraph in re.finditer('<P>([^<]*)</P>', filetext):
    lines = paragraph.group(1)
    output.write(re.sub('\n', " ", lines) + "\n")
