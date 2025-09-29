
case "lol"
when "lol"
  print("34!\n")
  redo
when "?"
  print("yes!\n")
end
__END__
if
  print(1)
elsif
  print("2")
elsif
  print(3)
end
__END__
class fraction
  attr('numer')
  attr('denom')

  def fraction.new(numer, denom)
    super.init(numer, denom)
  end

  def init(numer, denom)
    @numer, @denom = numer, denom
    self
  end

  def is_int; @denom == 1 end
  def to_s
    if self.is_int then
      @numer.to_s
    else
      sprintf("%d/%d", @numer, @denom)
    end if
  end
end

$\="\n"
print(fraction.new(2, 1))
