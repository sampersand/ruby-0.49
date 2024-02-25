class Value
  def Value.new(val)
    super.init(val)
  end

  attr("val")

  def init(val)
    @val = val
    self
  end

  def to_s; run().val.to_s end
  def to_i; run().val.to_i end
  def to_a; run().to_a end
  def is_truthy; run().val end
  def length; to_a().length end

  def run
    self
  end
end

class Null : Value
  def to_s _inspect
  def to_i() 0 end
  def _inspect() 'null' end
  def is_truthy; %FALSE end
end
%null = Null.new(nil)

class Bool : Value
end

%true = Bool.new(%TRUE)
%false = Bool.new(%FALSE)

class Str : Value
  def length; @val.length end
end

class Int : Value
  def init(val)
    super(val.to_i)
  end

  for x in '+ - * / % **'.split
    eval(sprintf("def %s(rhs) Int.new(@val %s rhs.to_i) end", x, x))
  end

  def <(rhs) Bool.new(@val < rhs.to_i) end
  def >(rhs) Bool.new(@val > rhs.to_i) end
end

class Ary : Value
  def Ary.new(*args)
    super(args)
  end
end
%EMPTY_ARY = Ary.new()

class Var : Value
end

class Ast : Value
  def Ast.new(fn, args)
    super([fn, args])
  end

  def init(a)
    @fn = a[0]
    @args = a[1]
    self
  end

  def run
    kn.apply(@fn, *@args)
  end
end
