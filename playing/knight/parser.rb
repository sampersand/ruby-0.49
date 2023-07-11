class parser
  def parser.new(source)
    super.init(source)
  end

  def init(source)
    @source = source
    self
  end

  def each
    yield 3
  end
end

for x in parser.new("A")
  print(x)
end
