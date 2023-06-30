do [1,2,3].each() using i
  print(i)
end
__END__
def doit(*kwargs)
  print(kwargs.assoc(\a1)[1])
end

doit(\a1::1, "a2"::2)

__END__
# for x in Directory.new(".")
#   print($_)
# end

string = "12345"
print(string[1,1])
print(string::class)
# while string =~ /\d\K/
#   print($&)
# end


__END__
/(a)/ =~ "a"
print($1)
do [1,2,3,4].each() using i
print(i)
end
print("\n", "abc".chop(), "\n")
print(chop)
def foo(x, y)
  print(x._inspect(), y)
end

foo([1, 2, 3], 4)


# x = open("|ls -al")
# print(x.read())
# %0 = 34
caawoeifhawoeifhawoefihawoefihawoefihawoeifhawoeifhawoefihaweofih=4
print(caawoeifhawoeifhawoefihawoefihawoefihawoeifhawoeifhawoefihaweofih)
# print(.e34)

__END__
class foo
  def =~(x)
    print("in here")
  end
end

$_ = "a34b"
$. = 12
if 11...34
  print("yes")
end

# class parent
#   def self.static; 12 end

#   def @private;
#     if iterator_p(); yield 34 else 56 end
#   end

#   def public @private
# end

# /a/ =~ "a"
# print($1)

__END__
class child : parent
  def func lol
    do @private using i
      println("i is:", i)
    end
  end
end


parent.static.println()
%CONSTANT = parent.new

def a() 34 end
def b a

print(b())
__END__
def func foo.bar()
end

x = [1,2,3]
a, x[1] = 1, 2
print(a, x._inspect())
exit()
class Foo
  def @bar(x)
    print("<", self, ":", x, ">")
  end

  def lol
    @bar(12)
  end
end

me = Foo.new
me.lol()

# def @foo()
# end
# print(@foo(12));

# def ::(y)
#   print("{", x, ",", y, "}")
# end

# print(self::2)
# # def foo(a+)
# #   print(34)
# # end

# # xc = {"a" => 34}
# # for x in 1..10
# #   if x < 5
# #     continue
# #   end
# #   print(x)
# # end
