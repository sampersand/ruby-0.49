def tap
  yield self
  self
end

def p(*x)
  if x.length == 1 then x = x[0] end
  print(x._inspect, "\n")
  x
end

def puts(*x)
  print(*x)
  print("\n")
end

def evalf(fmt, *x)
  eval(sprintf(fmt, *x))
end
