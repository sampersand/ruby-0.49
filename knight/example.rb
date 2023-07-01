def __old_open open
def open(*x)
  value = __old_open(*x)
  if iterator_p() then
    protect
      yield value
    ensure
      value.close
    end
  end if
  value
end def

do open("example.rb", "r") using i
  print(i)
end
