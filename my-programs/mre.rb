print("ABCDEF".split("")[7,4]._inspect)

__END__
#ruby -s

class hangman
  def hangman.new(words, *opts)
    super.init("paniconograph", *opts)
  end

  attr("secret")

  def init(secret, *options)
    @secret = secret
    @guesses = []
    self
  end


  def guess(letter)
    # if @guesses.includes(letter)
    #   return %FALSE
    # end
    @guesses << letter
  end

  def word_string
    str = []

    do @secret.each_byte using letter
      print(letter.a)
      # str << if @guesses.includes(letter) then letter.chr else '_' end
    end
    
    # print(str._inspect)
  end
end

srand(0)
hm = hangman.new("paniconograph")
print(hm.secret, "\n")
hm.guess(?p)
print(hm.word_string, "\n")
print(hm)
