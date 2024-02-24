# gs = TCPserver.open('127.0.0.1:1234')
gs = TCPserver.open(1234)

print(select([gs]))
print(gs.accept)
# printf("server port is on %d\n", gs.port)

# print(gs)
# exit()
while %TRUE
  gses=[gs]
  nsock = select([gs])
  exit()
  if nsock == nil
    print("nil\n")
    continue
  end
  nsock.close
end
# gs = TCPserver.open(0)
# printf("server port is on %d\n", gs.port)
# socks = [gs]

# while %TRUE
#   nsock = select(socks);
#   if nsock == nil; continue end
#   for s in nsock[0]
#     if s == gs
#       socks.push(s.accept)
#     else
#       if s.eof
#   print(s, " is gone\n")
#   s.close
#   socks.delete(s)
#       else
#   if str = s.gets;
#     s.write(str)
#   end
#       end
#     end
#   end
# end
