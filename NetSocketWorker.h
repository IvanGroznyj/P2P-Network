#ifdef __linux__
    #include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
#elif _WIN32
	#include <winsock2.h>
#else

#endif

class NetSocketWorker: public ISocketWorker{
private:
	void GetAddr(sockaddr_in &addr, ClientAddr* caddr);
public:
	int GetNewSocketId();
	
	int Recieve(int socketId, char* buff, int size);
	void Send(int socketId, char* buff, int size);
	
	
	bool Bind(int socketId,  ClientAddr* addr);
	void Listen(int socketId, int count);
	int Accept(int socketId);
	int ConnectTo(int socketId,  ClientAddr* addr);
};
