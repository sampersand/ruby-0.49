class WebServer
  def WebServer.new(port)
    super.init(TCPserver.open(port))
  end

  def WebServer.accept(port)
    server = new(port)
    # protect
    #   while %TRUE
    #     conn = select([server])[0][0].accept
    #     yield 
  end

  def init(server)
    @server = server
  end

  def close
    @server.close
  end

  def accept
    select([@conn])[0][0]

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
