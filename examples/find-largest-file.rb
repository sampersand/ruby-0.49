##
# Finds the largest file in a directory, and all its children.
# If `-print` is supplied, also prints out sizes of the files
##

dir = Dir.pwd
# $LOAD_PATH.unshift(Dir.pwd + '/examples/libs') # No way to get the current file
# $LOAD_PATH.unshift( Dir.pwd + '/libs')

require('find')
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
