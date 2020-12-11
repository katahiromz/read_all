#! /usr/bin/env ruby

def read_all(filename)
  IO.read(filename)
end

print read_all("read_all.rb")
