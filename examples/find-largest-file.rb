##
# Finds the largest file in a directory, and all its children.
# If `-print` is supplied, also prints out sizes of the files
##

# Similar to `$:.unshift(__dir__)` nowadays, but a lot more baroque-ly
$LOAD_PATH.unshift($0[0, $0.rindex('/')] + '/libs')

GC.disable # There's a bug in GC that I haven't solved yet
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

max = files.max
do files.each_pair using x
  unless x[1] == max then continue end
  print(x[0])
  break
end
