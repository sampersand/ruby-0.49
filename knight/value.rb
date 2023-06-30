instance_exec()
x = Class.new.new
def x.foo
  34
end

print(x.foo)
# class value
#   def value.new(*a)
#     x = super
#     x.initialize(*a)
#     x
#   end
# end

# class integer:value
#   def initialize(num)
#     @num = num
#   end
#   def coerce
#     3
#   end
# end
# print(3 + integer.new(1))
# # class boolean
# #   def boolean.true
# #     new(1)
# #   end
# #   %true = new(1)
# #   def boolean._true
# #     # new().%true
# #   end
# # end

# # # print(boolean._true)
# # print(boolean._true)

