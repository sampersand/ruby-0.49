##
# Runs a webserver on port 1233 (or whatever the first arg is), reads a single
# request, and responds with "Why, hello there!"
##

%PORT = ($ARGV[0] || 1233).to_i
server = TCPserver.open(%PORT)

protect
  conn = select([server])[0][0].accept

  while (line = conn.gets) != "\r\n"
    printf("line: %s\n", line._inspect)
  end while

  greeting = "Why, hello there!\n"

  printf(
    conn,
    "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %d\r\n\r\n%s",
    greeting.length,
    greeting)
  conn.close
ensure
  server.close
end protect
