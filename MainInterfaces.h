struct ClientAddr{
	ClientAddr();
	ClientAddr(char* ip, int port){
		ClientAddr::ip = ip;
		ClientAddr::port = port;
	}
	const char* ip;
	int port;
};

class ISocketWorker{
public:
	virtual int GetNewSocketId() =0;

	virtual int Recieve(int socket_id, char* buff, int size)=0;
	virtual void Send(int socket_id, char* buff, int size)=0;

	virtual bool Bind(int socket_id, ClientAddr* addr)=0;
	virtual void Listen(int socket_id, int count)=0;
	virtual int Accept(int socket_id)=0;
	virtual int ConnectTo(int socket_id, ClientAddr* addr)=0;
	virtual void Close(int socket_id)=0;
};

class IDataWorker{
public:
	virtual char* GetFile(char* hash)=0;
	virtual char* GetFileByName(char* name)=0;
	virtual void AppendToFileByName(char* name, char* text)=0;
	virtual unsigned long int GetHash(char* path)=0;
	virtual char* AddFile(char* path)=0;
};

class IRequestsHandler{
public:
	virtual void StartWorking(ClientAddr* addr)=0;
	virtual int GetStatus()=0;
	virtual void StopWorking()=0;
};
