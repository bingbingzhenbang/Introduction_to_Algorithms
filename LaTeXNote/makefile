all: Introduction_to_Algorithms.pdf

Introduction_to_Algorithms.pdf: Introduction_to_Algorithms.tex	
	docker run -v  $(CURDIR):/doc thomasweise/texlive xelatex.sh Introduction_to_Algorithms.tex