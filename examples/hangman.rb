#ruby -s
# ^ `-s` is identical to modern ruby

# When calling a method without using `.` notation you must supply the 
# parens to distinguish it from an instance variable (which, if undefined, defaulted to `nil`). 
srand()

# In ruby 0.49, constants were denoted via the `%` sigil (just like how in modern ruby, `@` is 
# used for instance variables). They didn't need to be upper case either (in fact, `%1` is a valid
# constant name).
%words_file =
  if defined("$words") # instead of `defined?($words)`, a function called `defined` was used.
    $words
  elsif !(words = $ENV["WORDS_FILE"]).is_nil # `$ENV` was a global! Also, `xxx?` was `is_xxx`
    words
  else
    "/usr/share/dict/words"
  end if # <-- old ruby let you optionally "tag" `end`s, such as this `end if`.

# Removed in the next version, Ruby 0.50, `def func` was syntax that made the defined method unable
# to be called via `.` notation.
def func words_from_file(file)
  f = open(file)

  # The exception keywords were slightly different: `protect ... [resque ...] [ensure ...] end`.
  protect
    # Parenthesis after a method call was required always except when the method came after a `.`,
    # and took no arguments.
    words = f.to_a # Fun fact, this sets `$_` to the last value in `f`!
  resque
    # The current exception was only found in the special variable `$!`; Also, `fail` was the only
    # way to raise exceptions (`raise` didn't exist), and only took an optional string argument.
    fail(sprintf("unable to read file %s: %s", file, $!))
  ensure
    f.close
  end protect # again, entirely optional "tags" could be added after `end`.

  # `for` was the main way to iterate over things. (Later on there's an example of using blocks)
  for word in words
    word =~ /\n$/ && word.chop # there was no `chomp`, modifier `if`, or even `and`.
  end

  words
end def

# Let's make a mixin!---module (and class) names could be lowercase!
module loopable
  def loop
    # Instead of `block_given?` we use `iterator_p()` lol
    unless iterator_p()
      fail("must pass an iterator to `loop`")
    end

    # true and false were actually constants--`%TRUE` and `%FALSE`. Because `nil` was _the_ only
    # falsey thing in ruby 0.49, `%FALSE` was actually an alias for it, and `%TRUE` was simply `1`.
    while %TRUE
      yield nil # You _need_ to yield something, even if you're not going to use it.
    end
  end
end

# Let's make an abstract class
class game
  include loopable # includes act like they do in modern ruby

  def play
    do loop()
      # You need to use `()` here, as `reset` on its own is taken as an uninitialized
      # variable (which default to `nil`, not `NameError`s!)
      reset()

      # `until` has always existed!
      until has_won() || has_lost()
        take_turn()
      end

      # There's no `puts`; you gotta use `print`
      print("New game? y/N\n")

      # Instead of `downcase`, we got `lc`. Also, no `and` or modifier `if`, just `&&`.
      gets().chop.lc != 'y' && break
    end
  end
end

# Inheritance was done via `:` (maybe inspired from C++??) instead of `<`.
class Hangman : game
  # It was convention to do instance methods on the class name itself.
  # Also, keyword args were passed as tuples, hence the `*opts`.
  def Hangman.from_file(file, *opts)
    new(words_from_file(file), *opts)
  end

  # Object#new didn't automatically call `initialize` (which was called `init` back then).
  # Also, the convention was to have `init` return `self`.
  def Hangman.new(*args)
    super.init(*args)
  end

  # Equivalent to modern-day `attr_reader :secret`. The `attr` function still exists but is
  # deprecated.
  attr("secret")

  # Instead of `initialize`, Ruby 0.49 used `init` by convention. However, you'd need to make
  # a custom `new` function that'd call `init` (which then would also have to return `self`)
  def init(words, *options)
    @words = words

    # Keyword arguments were passed in as tuples of `[key, value]`. So, to get the value of it,
    # you'd need to use the `Array#assoc` function (which still exists today!). Also, `\foo` is the
    # old syntax for creating symbols!
    if (guesses = options.assoc(\guesses))
      @extra_guesses = guesses[1]
    end

    self # You need to return `self` from `init`s by convention.
  end

  def reset
    @secret = @words[rand(@words.length)].split("")
    @guesses = []
  end

  # Private functions started with an `@` sign, just like instance variables. (Fun fact: You could
  # do `@1` for varialbe names if you wanted)
  def @word_string
    str = ''

    for letter in @secret
      # No ternary operators, so you just use `if` expressions
      str.concat(if @guesses.includes(letter) then letter else '_' end)
    end for

    str
  end

  def @incorrect_guesses
    bad = []

    # There's no `.select`, `.reject`, or anything, so you gotta do it manually
    for c in @guesses
      if !@secret.includes(c) then bad << c end
    end

    bad
  end

  def has_won
    # There was no `String#includes?`. Gotta use regex!
    @word_string() !~ /_/
  end

  def take_turn
    while 1 # Instead of `loop()` for shiggles
      print() # I totally forgot why this was needed, but without it breaks lol
      $stdout.flush # make sure whatever was printed earlier is out

      # No `next`, ruby 0.49 used `continue`!
      (letter = gets().chop.lc) =~ /[a-z]/ || continue

      # Alas, no `and` :-(
      if guess(letter) then return end

      # Just like modern Ruby, you can `printf` to streams
      printf($stderr, "Character '%s' isn't was already guessed; try again\n", letter)
    end
  end

  # Unfortunately, you must use parens for arguments; you can't `def guess letter`
  def guess(letter)
    if @guesses.includes(letter)
      return %FALSE
    end

    @guesses << letter
  end

  def to_s
    incorrect = @incorrect_guesses()
    args = [? ] * 9 # There was no escape for spaces (modern ruby has `?\s`), so this is just awkward.
    incorrect.length >= 1 && args[0] = ?o
    args[1] = incorrect[0, 5].join(' ')
    incorrect.length >= 2 && args[3] = ?|
    incorrect.length >= 3 && args[2] = ?/
    incorrect.length >= 4 && args[4] = ?\\
    args[5] = if incorrect.length >= 5 then incorrect[5, 5].join(' ') else ' ' end
    incorrect.length >= 5 && args[6] = ?/
    incorrect.length >= 6 && args[7] = ?\\
    args[8] = if incorrect.length >= 10 then incorrect[10, incorrect.length-10].join(' ') else ' ' end
    args << @word_string()
    sprintf("  .--.\n  |  %c   %s\n  | %c%c%c  %s\n  | %c %c  %s\n -+------\n\n  %s\n", *args)
  end

  # This is how aliases worked! Instead of `alias a b` you just `def a b`
  def _inspect to_s
end

# The `::` operator actually just creates a tuple: `a::b` is just `[a, b]`.
hm = Hangman.from_file(%words_file, \guesses::10)
hm.play()
