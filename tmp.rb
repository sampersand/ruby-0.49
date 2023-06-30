x = "abc"
print($; = "")
print(x.split._inspect)
__END__
def one_upto(max)
  for x in 1..max
    yield(x)
  end for
end def

do one_upto(10) using i
  print("in here: ", i, "\n")
end do
  
__END__
$\="\n"
protect
  fail("oops")
resque
  print($!)
ensure
  print("always run")
end
__END__
def foo
  begin
  yield(1)
  protect 
  print(34)
end
end

do foo() using i
  # if i == 3; break end
  # println("ttt: ", i);
end
#exit()

__END__
$\="\n"
class Foo
  FOO = 34
  FOO = 45
  @BAR = 34
  print(@BAR)
  print(Foo._inspect())
  print(Foo.responds_to("bar"))
  print(%TRUE, %FALSE)
end

if 1 then
end if
def is_a(x)
end def

/a/ =~ 'a'
print($_)
