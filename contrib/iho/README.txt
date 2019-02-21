* Requirements

- wget
- unzip
- python-simplejson, python-xmltodict

* Processing

$ wget http://primar.ecc.no/primar/catalogue.ctl
$ file catalogue.ctl
catalogue.ctl: Zip archive data, at least v2.0 to extract
$ unzip catalogue.ctl 
$ ./readenccatalog.py

* Wish
In the case of huge bbox (> 2048 tiles?) split bbox or reduce zoom

