class ISocketWorker{
public:
	virtual int GetNewSocketId() =0;

	virtual int Recieve(int socketId, char* buff, int size)=0;
	virtual void Send(int socketId, char* buff, int size)=0;

	virtual bool Bind(int socketId, char *ip, int port)=0;
	virtual void Listen(int socketId, int count)=0;
	virtual int Accept(int socketId)=0;
	virtual int ConnectTo(int socketId, char *ip, int port)=0;
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
	virtual void StartWorking(char* ip, int port)=0;
	virtual int GetStatus()=0;
	virtual void StopWorking()=0;
};
