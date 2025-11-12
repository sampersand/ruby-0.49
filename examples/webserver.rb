server = TCPserver.open(1233)

protect
  conn = select([server])[0][0].accept

  while (line = conn.gets) != "\r\n"
    printf("line: %s\n", line._inspect)
  end while

  greeting = "Why hello there!\n"
  conn.write(
"HTTP/1.1 200 OK\r
Content-Type: text/plain\r
Content-Length: " + greeting.length + "\r\n\r\n" + greeting)
  conn.close
ensure
  server.close
end protect
