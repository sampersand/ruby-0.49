#!ruby -s
$* << '.'
dir = $*[0] || Dir.pwd

$LOAD_PATH << './libs'
require('find.rb')
include Find

$, = ' '
$\ = "\n"

files = {}

do find('.') using x
  if File.d(x) then continue end

  files[x] = File.s(x)
  $print && print(x, File.s(x))
end

print(files._inspect)
print(files.max)
