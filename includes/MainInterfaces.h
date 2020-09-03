/*
 *  Author: Ivan Khodyrev
 */
struct ClientAddr{
	ClientAddr();
	ClientAddr(const char* ip, int port){
		ClientAddr::ip = ip;
		ClientAddr::port = port;
	}

	bool operator==(const ClientAddr& addr) {
	    return ip == addr.ip && port == addr.port;
	}

	const char* ip;
	int port;
};

class ISocketWorker{
public:
	virtual int GetNewSocketId() =0;

	virtual int Recieve(int socket_id, char* buff, int size)=0;
	virtual void Send(int socket_id, const char* buff, int size)=0;

	virtual bool Bind(int socket_id, ClientAddr* addr)=0;
	virtual void Listen(int socket_id, int count)=0;
	virtual int Accept(int socket_id)=0;
	virtual int ConnectTo(int socket_id, ClientAddr* addr)=0;
	virtual void Close(int socket_id)=0;
};

class IDataWorker{
public:
	virtual char* GetFile(const char* hash)=0;
	virtual char* GetFileByName(const char* name)=0;
	virtual void AppendToFileByName(const char* name, const char* text)=0;
	virtual unsigned long int GetHash(const char* path)=0;
	virtual char* AddFile(const char* path)=0;
};

class IRequestsHandler{
public:
	virtual void StartWorking(ClientAddr* addr)=0;
	virtual int GetStatus()=0;
	virtual void StopWorking()=0;
};
