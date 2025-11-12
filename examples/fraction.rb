class fraction
  include Comparable

  attr('numer')
  attr('denom')

  def fraction.new(*args)
    # Default second argument to `1`
    if args.length == 1
      args << 1
    end

    super.init(*args)
  end

  def init(numer, denom)
    @numer, @denom = numer, denom
    self
  end

  def coerce(other)
    if other.is_kind_of(fraction) then
      other
    else
      fraction.new(other.to_i)
    end if
  end

  def is_int
    @denom == 1
  end

  def to_s
    if self.is_int then
      @numer.to_s
    else
      sprintf("%d/%d", @numer, @denom)
    end if
  end

  def +(other)
    other = coerce(other)
    fraction.new(@numer*other.denom + @denom*other.numer, @denom*other.denom)
  end

  def -(other)
    other = coerce(other)
    fraction.new(@numer*other.denom - @denom*other.numer, @denom*other.denom)
  end

  def *(other)
    other = coerce(other)
    fraction.new(@numer*other.numer, @denom*other.denom)
  end

  def /(other)
    other = coerce(other)
    fraction.new(@numer*other.denom, @denom*other.numer)
  end

  def <=>(other)
    other = coerce(other)
    (@numer*@denom) <=> (other.numer*other.denom)
  end
end

$\="\n"
print( (3 + fraction.new(2, 10)) )
print( fraction.new(3, 4) / fraction.new(2, 5) )
print( fraction.new(3, 4) < fraction.new(2, 5) )
