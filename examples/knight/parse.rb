unless defined("kn") then module kn end end

def kn.@first_line()
  do $source.each using line
    return line
  end
end

def kn.@strip_whitespace()
  while $source != ""
    if $source[0].chr =~ /\s/
      $source.sub(/^\s+/, '')
      continue
    end

    if $source[0] == ?#
      $source.sub(/^.*\n/, '') # delete comment
      continue
    end

    return
  end
end

def kn.@del_prefix()
  $source[0, $&.length] = ''
  return $&
end

def kn.parse(source)
  old_under = $source

  protect
    $source = source
    @parse_one()
  ensure
    $source = old_under
  end protect
end

%EOF_PREMATURELY_REACHED = "End of file prematurely reached\n"

def kn.@parse_one()
  @strip_whitespace()

  # Ruby 0.49's regex was super limited---it had `^` and `$` with their weird
  # "beginning or end of line" semantics like modern Ruby has, but it doesn't
  # have modern Ruby's `\A` or `\z`... So, we have to get the first line out
  # and then match against that.
  val = case @first_line()
  when /^\d+/
    Int.new($&)

  when /^[a-z_][a-z_\d]*/
    Var.new($&)

  when /^"/, /^'/
    # There's somethin weird with the regex /^('([^']*?)'|"([^"]*?)")/ and idk what it is
    $source =~ /^"([^"]*?)"/ || $source =~ /^'([^']*?)'/
    Str.new($1)

  when /^[TF][A-Z_]*/
    if $&[0] == ?T then %true else %false end

  when /^N[A-Z_]*/
    %null

  when /^@/
    %EMPTY_ARY

  when /^[A-Z][A-Z_]*/, /^\W/
    arity, fn = %FUNCTIONS[@del_prefix()]
    if arity.is_nil
      fail("Unknown function " + $&)
    end

    args = []

    for i in 0..arity - 1
      protect
        args << @parse_one()
      resque
        if ($!.to_s == %EOF_PREMATURELY_REACHED)
          fail("missing argument #" + i + " for function " + fn.id2name)
        else
          fail()
        end
      end
    end

    return Ast.new(fn, args)
  else
    if $source == ""
      fail(%EOF_PREMATURELY_REACHED)
    end

    fail("unknown token start: " + $source[0].chr._inspect)
  end

  @del_prefix()
  val
end
