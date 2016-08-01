##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   
## License:     GPLv3+
##---------------------------------------------------------------------------

all: yamlgenerator nautical-7.yaml nautical-9.yaml nautical-11.yaml nautical-13.yaml nautical-15.yaml nautical-16.yaml nautical-17.yaml imagery-18.yaml config.yaml

clean:
	rm -f *yaml yamlgenerator

yamlgenerator: yamlgenerator.c
	gcc -o yamlgenerator yamlgenerator.c -g

config.yaml: config.yaml.in
	cp -f config.yaml.in config.yaml

#%.yaml: boxes/% yamlgenerator
#	./yamlgenerator 15 < $<  > $@

nautical-7.yaml: boxes/nautical-7 yamlgenerator
	./yamlgenerator 7 < $< > $@

nautical-9.yaml: boxes/nautical-9 yamlgenerator
	./yamlgenerator 9 < $< > $@

nautical-11.yaml: boxes/nautical-11 yamlgenerator
	./yamlgenerator 11 < $< > $@

nautical-13.yaml: boxes/nautical-13 yamlgenerator
	./yamlgenerator 13 < $< > $@

nautical-15.yaml: boxes/nautical-15 yamlgenerator
	./yamlgenerator 15 < $< > $@

nautical-16.yaml: boxes/nautical-16 yamlgenerator
	./yamlgenerator 16 < $< > $@

nautical-17.yaml: boxes/nautical-17 yamlgenerator
	./yamlgenerator 17 < $< > $@

imagery-18.yaml: boxes/imagery-18 yamlgenerator
	./yamlgenerator 18 < $< > $@
