#define OSTD_HEADLESS
#define OSTD_IMPL
#include "../src/ostd.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif

#define PORT 9000

typedef struct Request {
	string method;
	string body;
	string path; // if GET
} Request;

unit_local Request parse_request(u8 *buffer) {
    Request req = {0};
    string request = { c_style_strlen((const char*)buffer), buffer };

    string delim = STR(" ");

    s64 first_space = string_find_index_from_left(request, delim);
    if (first_space < 0) {
        req.method = request;
        req.path = (string){0, 0};
        req.body = (string){0, 0};
        return req;
    }
    req.method = (string){ .count = (u64)first_space, .data = request.data };

    if (req.method.count > 7) {
        req.method.count = 7;
    }

    string after_method = { request.count - (u64)(first_space + 1), request.data + first_space + 1 };

    s64 second_space = string_find_index_from_left(after_method, delim);
    if (second_space < 0) {
        req.path = after_method;
        req.body = (string){0, 0};
        if (req.path.count > 255) {
            req.path.count = 255;
        }
        return req;
    }
    req.path = (string){ .count = (u64)second_space, .data = after_method.data };

    if (req.path.count > 255) {
        req.path.count = 255;
    }

    req.body = (string){ .count = after_method.count - (u64)(second_space + 1), .data = after_method.data + second_space + 1 };

    return req;
}

int main(void) {
	
	Socket listen_socket;
	Socket_Result r;
	r = sys_socket_init(&listen_socket, SOCKET_DOMAIN_IPV4, SOCKET_TYPE_STREAM, SOCKET_PROTOCOL_TCP);
	if (r != SOCKET_OK) {
		print("sys_socket_init error");
		return (int)r;
	}
	
	r = sys_socket_bind(listen_socket, 0, PORT);
	if (r != SOCKET_OK) {
		print("sys_socket_bind error\n");
		return (int)r;
	}
	
	r = sys_socket_listen(listen_socket, 5);
	if (r != SOCKET_OK) {
		print("sys_socket_listen error\n");
		return (int)r;
	}
	print("Listening...\n");
	
	u8 buffer[4096];
	
	while (true) {
		
		Socket client_sock;
		r = sys_socket_accept(listen_socket, &client_sock);
		if (r != SOCKET_OK) {
			print("sys_socket_accept error\n");
			return (int)r;
		}
		
		print("Someone connected\n");
		
		memset(buffer, 0, sizeof(buffer));
		u64 received = 0;
		print("Waiting recv\n");
		r = sys_socket_recv(client_sock, buffer, sizeof(buffer)-1, &received);
		print("recv\n");
		if (r != SOCKET_OK) {
			print("sys_socket_recv error\n");
			return (int)r;
		}
		print("We received something\n");
		
		if (received > 9) {
			Request req = parse_request(buffer);
			
			if (strings_match(req.path, STR("/"))) {
				print("Requested static http: (%s: '%s')\n", req.method, req.path);
				
			    string res_text = STR("Hello there");
			    int status = 200;
			    
			    string res = tprint(
			    	"HTTP/1.1 %d OK\r\n"
		             "Content-Type: %s\r\n"
		             "Content-Length: %i\r\n"
		             "\r\n%s",
		             status, STR("text/html"), res_text.count, res_text);
			    
			    u64 sent;
			    sys_socket_send(client_sock, res.data, res.count, &sent);
			    
			    assert(sent == res.count);
			    
			} else {
				print("Unexpected message: (%s: '%s')\n", req.method, req.path);
			}
		} else {
			string weird = (string) { sizeof(received), buffer };
			print("Received weird stuff: %s\n", weird);
		}
		
		sys_socket_close(client_sock);
	}
	
	return 0;
}

