#LIB_DIR = $(shell ocamlfind query magick)
#LIB_DIR = +magick
LIB_DIR = ../src

test: rose.png
	ocaml -I $(LIB_DIR) magick.cma test_01.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_02.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_03.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_04.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_05.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_06.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_07.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_08.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_09.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_10.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_11.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_12.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_13.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_14.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_15.ml || :
	ocaml -I $(LIB_DIR) magick.cma test_16.ml || :

test_opt: rose.png
	ocamlopt -o test_01.opt -I $(LIB_DIR) magick.cmxa test_01.ml && ./test_01.opt || :
	ocamlopt -o test_02.opt -I $(LIB_DIR) magick.cmxa test_02.ml && ./test_02.opt || :
	ocamlopt -o test_03.opt -I $(LIB_DIR) magick.cmxa test_03.ml && ./test_03.opt || :
	ocamlopt -o test_04.opt -I $(LIB_DIR) magick.cmxa test_04.ml && ./test_04.opt || :
	ocamlopt -o test_05.opt -I $(LIB_DIR) magick.cmxa test_05.ml && ./test_05.opt || :
	ocamlopt -o test_06.opt -I $(LIB_DIR) magick.cmxa test_06.ml && ./test_06.opt || :
	ocamlopt -o test_07.opt -I $(LIB_DIR) magick.cmxa test_07.ml && ./test_07.opt || :
	ocamlopt -o test_08.opt -I $(LIB_DIR) magick.cmxa test_08.ml && ./test_08.opt || :
	ocamlopt -o test_09.opt -I $(LIB_DIR) magick.cmxa test_09.ml && ./test_09.opt || :
	ocamlopt -o test_10.opt -I $(LIB_DIR) magick.cmxa test_10.ml && ./test_10.opt || :
	ocamlopt -o test_11.opt -I $(LIB_DIR) magick.cmxa test_11.ml && ./test_11.opt || :
	ocamlopt -o test_11.opt -I $(LIB_DIR) magick.cmxa test_12.ml && ./test_12.opt || :
	ocamlopt -o test_13.opt -I $(LIB_DIR) magick.cmxa test_13.ml && ./test_13.opt || :
	ocamlopt -o test_14.opt -I $(LIB_DIR) magick.cmxa test_14.ml && ./test_14.opt || :
	ocamlopt -o test_15.opt -I $(LIB_DIR) magick.cmxa test_15.ml && ./test_15.opt || :
	ocamlopt -o test_16.opt -I $(LIB_DIR) magick.cmxa test_16.ml && ./test_16.opt || :

rose.png:
	convert rose: $@
clean:
	$(RM) rose.png
	$(RM) test_01.opt test_01.o test_01.cmi test_01.cmx
	$(RM) test_02.opt test_02.o test_02.cmi test_02.cmx
	$(RM) test_03.opt test_03.o test_03.cmi test_03.cmx
	$(RM) test_04.opt test_04.o test_04.cmi test_04.cmx
	$(RM) test_05.opt test_05.o test_05.cmi test_05.cmx
	$(RM) test_06.opt test_06.o test_06.cmi test_06.cmx
	$(RM) test_07.opt test_07.o test_07.cmi test_07.cmx
	$(RM) test_08.opt test_08.o test_08.cmi test_08.cmx
	$(RM) test_09.opt test_09.o test_09.cmi test_09.cmx
	$(RM) test_10.opt test_10.o test_10.cmi test_10.cmx
	$(RM) test_11.opt test_11.o test_11.cmi test_11.cmx
	$(RM) test_12.opt test_12.o test_12.cmi test_12.cmx
	$(RM) test_13.opt test_13.o test_13.cmi test_13.cmx
	$(RM) test_14.opt test_14.o test_14.cmi test_14.cmx
	$(RM) test_15.opt test_15.o test_15.cmi test_15.cmx
	$(RM) test_16.opt test_16.o test_16.cmi test_16.cmx
