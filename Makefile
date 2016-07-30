##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   
## License:     GPLv3+
##---------------------------------------------------------------------------

all: yamlgenerator nautical-15.yaml nautical-16.yaml nautical-17.yaml imagery-18.yaml config.yaml

clean:
	rm -f *yaml yamlgenerator

yamlgenerator: yamlgenerator.c
	gcc -o yamlgenerator yamlgenerator.c -g

config.yaml: config.yaml.in
	cp -f config.yaml.in config.yaml

#%.yaml: boxes/% yamlgenerator
#	./yamlgenerator 15 < $<  > $@

nautical-15.yaml: boxes/nautical-15 yamlgenerator
	./yamlgenerator 15 < $< > $@

nautical-16.yaml: boxes/nautical-16 yamlgenerator
	./yamlgenerator 16 < $< > $@

nautical-17.yaml: boxes/nautical-17 yamlgenerator
	./yamlgenerator 17 < $< > $@

imagery-18.yaml: boxes/imagery-18 yamlgenerator
	./yamlgenerator 18 < $< > $@
