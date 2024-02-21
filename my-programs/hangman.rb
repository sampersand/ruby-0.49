#ruby -s

srand() # parens are required

class game
  def play
    # TODO
  end
end

%words_file =
  if defined("$words")
    $words
  elsif !(q = getenv("WORDS_FILE")).is_nil
    q
  else
    "/usr/share/dict/words"
  end if

def func word_from_file(file)
  f = open(file)

  protect
    words = f.to_a
  resque
    fail(sprintf("unable to read file %s: %s", file, $!))
  ensure
    f.close
  end protect

  for word in words
    word =~ /\n$/ && $_.chop
  end for

  words
end

class hangman : game
  def hangman.from_file(file, *opts)
    new(word_from_file(file), *opts)
  end

  def hangman.new(words, *opts)
    super.init(words[rand(words.length)], *opts)
  end

  attr("secret")

  def init(secret, *options)
    @secret = secret
    @guesses = []

    unless (guesses = options.assoc(\guesses)).is_nil
      @extra_guesses = guesses[1]
    end

    self
  end

  def @private
    3
  end

  def guess(letter)
    if @guesses.includes(letter)
      return %FALSE
    end

    @guesses << letter
  end

  # def 
end

srand(0)
hm = hangman.from_file(%words_file, \guesses::10)
print(hm.secret, "\n")
hm.guess(?p)
print(hm)
__END__
  def hangman.new()

  def vehicle.new(make, model)
    super.init(make, model)
  end

  def init(make, model)
    @make = make
    @model = model
    self
  end

  def to_s
    sprintf("A %s by %s", @make, @model)
  end def

  def _inspect to_s
end class

class car : vehicle
end class

print(vehicle.new("samp", "ersand"))

__END__
print([1] == [1])
__END__
def self.a 
  3
end

def one_upto(max)
  for x in 1..max
    yield x
  end for
end def

do one_upto(10) using i
  print("in here: ", i, "\n")
end do
print(a())
  
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
