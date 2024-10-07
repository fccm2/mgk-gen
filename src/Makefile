# Makefile to compile the Magick-Interface!
# authors: Monnier Florent (2024)
# To the extent permitted by law, you can use, modify, and redistribute
# this file.

MAGICK_CORE_CFLAGS = $(shell pkg-config --cflags MagickCore)
MAGICK_CORE_CLIBS = $(shell pkg-config --libs MagickCore)

OCAMLC_WHERE = $(shell ocamlc -where)
OCAML_MAGICK_DIR = magick

OCAMLMKLIB = ocamlmklib
OCAMLOPT = ocamlopt
OCAMLC = ocamlc

OCAMLFIND = ocamlfind
INSTALL = install
MKDIR = mkdir
SUDO = sudo
CP = cp

all: lib
lib: dllmagick_stubs.so magick.cma
opt: dllmagick_stubs.so magick.cmxa

magick_stubs.o: magick_stubs.c
	$(OCAMLOPT) -fPIC -c -ccopt "$(MAGICK_CORE_CFLAGS)" $<

magick.cmi: magick.mli
	$(OCAMLC) -c $<

magick.cmo: magick.ml magick.cmi
	$(OCAMLC) -c $<

magick.cmx: magick.ml magick.cmi
	$(OCAMLOPT) -c $<

magick.cma: magick.cmo dllmagick_stubs.so
	$(OCAMLC) -a -o $@ $< -dllib dllmagick_stubs.so

magick.cmxa: magick.cmx dllmagick_stubs.so
	$(OCAMLOPT) -a -o $@ $< -cclib -lmagick_stubs -cclib "$(MAGICK_CORE_CLIBS)"

dllmagick_stubs.so: magick_stubs.o
	$(OCAMLMKLIB) -o magick_stubs -ldopt "$(MAGICK_CORE_CLIBS)" $<

install:
	$(MKDIR) -p $(OCAML_MAGICK_DIR)
	$(CP) \
	  dllmagick_stubs.so  \
	  libmagick_stubs.a   \
	  magick.mli          \
	  magick.cmi          \
	  magick.cmo          \
	  magick.cmx          \
	  magick.cma          \
	  magick.cmxa         \
	  $(OCAML_MAGICK_DIR)
	$(SUDO) $(MKDIR) -p \
	  $(OCAMLC_WHERE)/$(OCAML_MAGICK_DIR)/
	$(SUDO) $(CP) $(OCAML_MAGICK_DIR)/* \
	  $(OCAMLC_WHERE)/$(OCAML_MAGICK_DIR)/

find_install:
	$(OCAMLFIND) install magick META \
	  dllmagick_stubs.so  \
	  libmagick_stubs.a   \
	  magick.mli          \
	  magick.cmi          \
	  magick.cmo          \
	  magick.cmx          \
	  magick.cma          \
	  magick.cmxa         \
	  #Eol

doc:
	mkdir -p doc
	ocamldoc -d doc -html magick.mli

clean:
	$(RM) *.[oa] *.cm[ioxa] *.cmx[as] *.so
