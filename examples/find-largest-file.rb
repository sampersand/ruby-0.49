#!ruby -s
dir = Dir.pwd
$LOAD_PATH.unshift( Dir.pwd + '/libs')

require('find.rb')
__r49_dump("A")
require("print.rb")
__r49_dump("A")
include Find

$, = ' '
$\ = "\n"

files = {}

do find('.') using x
  if File.d(x) then continue end

  files[x] = File.s(x)
  $print && print(x, File.s(x))
end

max = files.max
do files.each_pair using x
  unless x[1] == max then continue end
  print(x[0])
  break
end
