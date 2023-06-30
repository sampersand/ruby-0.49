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
