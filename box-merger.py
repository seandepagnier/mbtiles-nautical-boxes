#!/usr/bin/python
#
##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   
## License:     GPLv3+
##---------------------------------------------------------------------------
#
# merge adjacent bounding boxes
# the algorithm is between O(n^2) and O(n^3) so it can be very slow for many boxes
# even still, it must be re-run repeatedly until the output matches the input

import sys

lines = sys.stdin.readlines()

# ensure all longitudes are within bounds
def longitude(lon):
    return min(max(lon, -180), 180)

def eq(a, b):
    return abs(a - b) < 1e-5  #  within 10 meters

input = []
for l in lines:
    r = l.rstrip().split(' ')
    input.append((r[0], int(r[1]), float(r[2]), float(r[3]), float(r[4]), float(r[5])))

while len(input):
    l = input.pop(0)
    lname, lzoom, llat0, llon0, llat1, llon1 = l
    merged = False
    rejected = []
    while len(input):
        m = input.pop(0)
        mname, mzoom, mlat0, mlon0, mlat1, mlon1 = m

        # if zoom doesn't match we can't work with these 2 boxes
        if lzoom != mzoom:
            rejected.append(m)
            continue

        # are boxes side by side
        if eq(llat0, mlat0) and eq(llat1, mlat1):
            if eq(llon0, mlon1):
                merged = lname, lzoom, llat0, mlon0, llat1, llon1
            elif eq(llon1, mlon0):
                merged = lname, lzoom, llat0, llon0, llat1, mlon1

        # are boxes above and below
        elif eq(llon0, mlon0) and eq(llon1, mlon1):
            if eq(llat0, mlat1):
                merged = lname, lzoom, mlat0, llon0, llat1, llon1
            elif eq(llat1, mlat0):
                merged = lname, lzoom, llat0, llon0, mlat1, mlon1

        # is m inside l?
        elif llat0 <= mlat0 and llat1 >= mlat1 and \
             llon0 <= mlon0 and llon1 >= mlon1:
            continue

        # is l inside m?
        elif llat0 >= mlat0 and llat1 <= mlat1 and \
             llon0 >= mlon0 and llon1 <= mlon1:
            merged = m

        if merged:
            break
                        
        rejected.append(m)

    input.extend(rejected)

    if merged:
        input.insert(0, merged)
    else:
        print "%s %s %s %s %s %s" % (lname, lzoom, llat0, longitude(llon0), llat1, longitude(llon1))
