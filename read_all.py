#!/usr/bin/env python

def read_all(filename):
  with open(filename, 'rb') as fp:
      return fp.read()

print(read_all("read_all.py").decode('utf-8'))
