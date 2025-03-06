from http.server import HTTPServer, SimpleHTTPRequestHandler

class CrossOriginHTTPRequestHandler(SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header("Cross-Origin-Opener-Policy", "same-origin")
        self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
        SimpleHTTPRequestHandler.end_headers(self)

if __name__ == '__main__':
    server_address = ('', 8000)
    httpd = HTTPServer(server_address, CrossOriginHTTPRequestHandler)
    print("Serving on http://localhost:8000")
    httpd.serve_forever()