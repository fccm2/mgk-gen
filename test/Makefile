#LIB_DIR = $(shell ocamlfind query magick)
#LIB_DIR = +magick
LIB_DIR = ../src

test: rose.png
	ocaml -I $(LIB_DIR) magick.cma test_01.ml
	ocaml -I $(LIB_DIR) magick.cma test_02.ml

test_opt: rose.png
	ocamlopt -o test_01.opt -I $(LIB_DIR) magick.cmxa test_01.ml && ./test_01.opt
	ocamlopt -o test_02.opt -I $(LIB_DIR) magick.cmxa test_02.ml && ./test_02.opt

rose.png:
	convert rose: $@
cleap:
	$(RM) *.png
clean:
	$(RM) *.o *.cm[iox] *.opt
