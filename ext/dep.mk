GET=wget
all: 7.1.1-47.tar.gz
7.1.1-47.tar.gz:
	$(GET) https://github.com/ImageMagick/ImageMagick/archive/refs/tags/7.1.1-47.tar.gz
clean:
	$(RM) 7.1.1-47.tar.gz
