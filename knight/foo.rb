def fuinc rand1
  3
end

print(do rand1(0, 2, 3); end, "\n")
print(rand1(0, 2, 3), "\n")

__END__
def __old_open open

def open(*x)
  file = __old_open(*x)

  if !iterator_p() then
    return file
  end if

  protect
    yield file
  ensure
    file.close
  end
end def

print(open("example.rb", "r"))
print(do open("example.rb", "r") using i
  print(i)
end)
