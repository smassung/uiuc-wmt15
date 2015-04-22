writeup.pdf: $(wildcard *.tex)
	latexmk writeup.tex --shell-escape -pdf -dvi- -ps-

clean:
	latexmk -c
	latexmk -CA
	rm writeup.bbl
