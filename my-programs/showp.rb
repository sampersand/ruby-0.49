##
# Prints out all executable files in `$PATH`
##

for dir in $ENV['PATH'].split(':')
  unless File.d(dir) && File.x(dir)
    continue
  end

  diro = Dir.open(dir)

  for path in diro
    path = dir + '/' + path
    if File.x(path) && File.f(path)
      print(path, "\n")
    end
  end

  diro.close
end
