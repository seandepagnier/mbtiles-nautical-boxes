##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   
## License:     GPLv3+
##---------------------------------------------------------------------------

all: seed-F.yaml config.yaml

yamlgenerator: yamlgenerator.c
	gcc -o yamlgenerator yamlgenerator.c -g

seed-F.yaml: yamlgenerator cm93boxes-F
	./yamlgenerator 15 < cm93boxes-F > seed-F.yaml

seed-G.yaml: yamlgenerator cm93boxes-G
	./yamlgenerator 16 < cm93boxes-G > seed-G.yaml

clean:
	rm -f seed.yaml yamlgenerator
