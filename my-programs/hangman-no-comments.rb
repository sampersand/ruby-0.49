#ruby -s

srand()

%words_file =
  if defined("$words")
    $words
  elsif (q = getenv("WORDS_FILE"))
    q
  else
    "/usr/share/dict/words"
  end if

def func words_from_file(file)
  f = open(file)

  protect
    words = f.to_a
  resque
    fail(sprintf("unable to read file %s: %s", file, $!))
  ensure
    f.close
  end protect

  for word in words
    word =~ /\n$/ && word.chop
  end

  words
end def

module loopable
  def loop
    iterator_p() || fail("must pass an iterator to `loop`")

    while %TRUE
      yield nil
    end
  end
end

class game
  include loopable

  def play
    do loop()
      reset()

      until has_won() || has_lost()
        take_turn()
      end

      print("New game? y/N\n")
      $stdin.gets.chop.lc != 'y' && break
    end
  end
end

class hangman : game
  def hangman.from_file(file, *opts)
    new(words_from_file(file), *opts)
  end

  def hangman.new(*args)
    super.init(*args)
  end

  attr("secret")

  def init(words, *options)
    @words = words

    if (guesses = options.assoc(\guesses))
      @extra_guesses = guesses[1]
    end

    reset()
    self
  end

  def reset
    @secret = @words[rand(@words.length)].split("")
    @guesses = []
  end def

  def @word_string
    str = ''

    for letter in @secret
      str.concat(if @guesses.includes(letter) then letter else '_' end)
    end for

    str
  end

  def @incorrect_guesses
    incorrect = []

    for c in @guesses
      unless @secret.includes(c)
        incorrect << c
      end unless
    end

    incorrect
  end

  def has_won
    # There was no `String#includes?`.
    @word_string() !~ /_/
  end

  def take_turn
    do loop()
      print()
      $stdout.flush

      until (letter = gets().chop.lc) =~ /[a-z]/
        # do nothing
      end

      unless guess(letter)
        $stderr.print(sprintf("Character '%s' isn't was already guessed; try again\n", letter))
        next
      end

      break
    end
  end

  def guess(letter)
    if @guesses.includes(letter)
      return %FALSE
    end

    @guesses << letter
  end

  def to_s
    incorrect = @incorrect_guesses()
    args = [? ] * 9
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

  def _inspect to_s
end

def gets()
  # (('a'..'z').to_a + ["9"])[rand(26)] + "\n"
  "0"
end

hm = hangman.from_file(%words_file, \guesses::10)
# $stdin = $stdin
hm.play()
