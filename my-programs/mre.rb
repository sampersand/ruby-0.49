class Value
end

for i in 0..1000
  x=("
class Bool"+i+": Value
  def _inspect; sprintf('Bool"+i+"(%s)', self) end
  $t = new()
  $f = new()
  # def Bool"+i+".new(value) fail('"+i+"') end
  def Bool"+i+".new(value) if value then $t else $f end end
end
  def $t.a; "+i+" end
  def $f.a; 0 end

  printf('["+i+"] %s-%s-%s\n', $t.id, $f.id, Bool"+i+".new(1).id)
")
  if i == 203
    print(x)
    # exit()
  end
  eval(x)
# printf("%s\n%s\n", $t.id, $f.id)
# Bool1.new(1).a
end
