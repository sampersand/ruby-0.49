# EMulates ruby's builtin print methods

def p(*a)
  for arg in a
    print(arg._inspect, "\n")
  end
  a
end

def puts(*args)
  for arg in args
    if arg.is_kind_of(Array)
      puts(*arg)
      continue
    end

    arg = sprintf("%s", arg) # convert to string, and clone

    unless arg =~ /\n$/
      arg.concat("\n")
    end

    $stdout.write(arg)
  end
end

puts( [['a', 'b'], 'd', x="q\n"] )
p('<', x, '>')
