module Find
  def prune() $find_should_prune = 1 end
  def find(root)
    dirs = [root]

    until dirs.length == 0
      diro = Dir.open(dir = dirs.pop())

      protect
        for file in diro
          if file == '.' || file == '..' then
            continue
          end

          $find_should_prune = nil
          yield(file = sprintf("%s/%s", dir, file))

          if !$find_should_prune && File.d(file) then
            dirs << file
          end
        end for
      ensure
        diro.close
      end
    end
  end
end module
