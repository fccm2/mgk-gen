all:
	$(MAKE) -C src
test:
	$(MAKE) -C test
clean:
	$(MAKE) -C src clean
doc:
	$(MAKE) -C src doc
opt:
	$(MAKE) -C src opt
