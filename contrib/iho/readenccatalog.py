#!/usr/bin/env python

import json
import simplejson
import xmltodict
import sys
import pprint


def getScale(scale):
# http://wiki.openstreetmap.org/wiki/DE:Zoom_levels
  s = int(scale)
  if s >= 500000000 : #World
    return 0
  elif s >= 250000000 :
    return 1
  elif s >= 150000000 :
    return 2
  elif s >= 70000000 :
    return 3
  elif s >= 35000000 :
    return 4
  elif s >= 15000000 :
    return 5
  elif s >= 81920000 :
    return 6
  elif s >= 4096000 :
    return 7
  elif s >= 2048000 :
    return 8
  elif s >= 1024000 : # grosses Gebiet
    return 9
  elif s >= 512000 :
    return 10
  elif s >= 256000 :  # Gebiet
    return 11
  elif s >= 128000 :
    return 12   
  elif s >= 64000 :  # Stadt
    return 13
  elif s >= 32000 :
    return 14
  elif s >= 16000 :
    return 15
  elif s >= 8000 :  # kleine Strasse
    return 16
  elif s >= 4000 :
    return 17
  elif s >= 2000:
    return 18
  else:
    return 19

with open('catalogue.xml') as fd:
    doc = simplejson.loads(simplejson.dumps(xmltodict.parse(fd.read(),xml_attribs=True)))
    for cat in doc.keys():
       for enc in doc[cat]:
         if enc == "enc":
           for cells in doc[cat][enc]:
             for cell in doc[cat][enc][cells]:
               print "%s %d %s %s %s %s" % ( cell['dsnm'],getScale(cell['cscl']),
                                             cell['slat'],cell['wlon'],
                                             cell['nlat'],cell['elon'])

