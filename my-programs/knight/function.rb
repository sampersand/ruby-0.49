unless defined("kn") then module kn end end


%FUNCTIONS = {
  '+' => [2, \+],
  'D' => [1, \D] }

def kn.+(lhs, rhs) lhs.run + rhs.run end

def kn.P
  g = gets
  g != "" && g[g.length - 1] == ?\n && g.chop
  g != "" && g[g.length - 1] == ?\r && g.chop
  Str.new(g)
end

srand()
def kn.R
  Int.new(rand(0xffffffff))
end

def kn.B(block)
  block
end

def kn.C(block)
  block.run.run
end

def kn.Q(code)
  exit(code.to_i)
end

def kn.O(val)
  v = val.to_s

  if v[v.length - 1] == ?\\
    print(v.clone.chop)
  else
    print(v, "\n")
  end

  %null
end

def kn.L(val)
  Int.new(val.run.length)
end

def kn.!(val)
  Bool.new(!val.is_truthy)
end

def kn.~(val)
  Int.new(-val.to_i)
end

def kn.A(val)
  val.run.ascii
end

def kn.comma(val)
  Ary.new(val)
end

def kn.head(val)
  val.run.to_a[0]
end

__END__

    register '[' do
      _1.run[0]
    end

    register ']' do
      _1.run[1..]
    end

    register '+' do
      _1.run + _2.run
    end

    register '-' do
      _1.run - _2.run
    end

    register '*' do
      _1.run * _2.run
    end

    register '/' do
      _1.run / _2.run
    end

    register '%' do
      _1.run % _2.run
    end

    register '^' do
      _1.run ** _2.run
    end

    register '<' do
      _1.run < _2.run
    end

    register '>' do
      _1.run > _2.run
    end

    register '?' do
      _1.run == _2.run
    end

    register ';' do
      _1.run
      _2.run
    end

    register '&' do
      !(lhs = _1.run) ? lhs : _2.run
    end

    register '|' do
      !(lhs = _1.run) ? _2.run : lhs
    end

    register '=' do
      _2.run.tap &_1.method(:assign)
    end

    register 'W' do
      _2.run until _1.falsey?
    end

    register 'I' do
      (_1.falsey? ? _3 : _2).run
    end

    register 'G' do
      _1.run[_2.to_i, _3.to_i]
    end

    register 'S' do
      (x = _1.run.dup)[_2.to_i, _3.to_i] = _4.run
    end

  end
end
