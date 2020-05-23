/*
 *  Author: Ivan Khodyrev
 */
#ifdef __linux__
    #include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
#elif _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
#endif

class NetSocketWorker: public ISocketWorker{
private:
	void ConvertAddr(sockaddr_in &addr, ClientAddr* client_addr);
public:
	int GetNewSocketId();
	
	int Recieve(int socket_id, char* buff, int size);
	void Send(int socket_id, const char* buff, int size);
	
	
	bool Bind(int socket_id,  ClientAddr* addr);
	void Listen(int socket_id, int count);
	int Accept(int socket_id);
	int ConnectTo(int socket_id,  ClientAddr* addr);
	void Close(int socket_id);
};
