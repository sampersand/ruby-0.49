def p(*a)
  for arg in a
    print(arg._inspect, "\n")
  end
end

def puts(*a)
  1
end
