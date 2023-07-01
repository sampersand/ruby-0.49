def a b
a()
# def __old_open open2
# def open2(*x)
#   value = __old_open(*x)
#   if iterator_p() then
#     protect
#       yield 2
#     ensure
#       value.close
#     end
#   end if
#   3
# end def

# do open2("example.rb", "r") using i
#   print(i)
# end

__END__
def a b
def b; 34 end
print(a())
rb_eval
def __old_open open2

# def open2(*x)
#   value = __old_open(*x)
#   if iterator_p() then
#     yield 2
#   end if
#   3
# end def

# do open2("example.rb", "r") using i
#   print(i)
# end
