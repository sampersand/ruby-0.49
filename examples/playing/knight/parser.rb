a = "123abc"
/^(\d+)/ =~ a
print($~)
exit()

class parser
  def parser.new(source)
    super.init(source)
  end

  def init(source)
    @source = source
    self
  end

  def each
    @source.sub(/\A +/, '')
    case @source
    end

    yield 3
  end
end

$DATA = "
;=x 3
: DUMP *9+2x"
for x in parser.new($DATA)
  print(x)
end
