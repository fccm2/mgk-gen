all:
	$(MAKE) -C src
test:
	$(MAKE) -C test
clean:
	$(MAKE) -C src clean
man:
	$(MAKE) -C src man
opt:
	$(MAKE) -C src opt
