/*
 *  Author: Ivan Khodyrev
 */
#include "MainInterfaces.h"
#include "StandartCommandInterpreter.h"
#include "ThreadRequestsHandler.h"
#include <cstring>
#include <thread>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <queue>
#include <mutex>
#include <chrono>  

using namespace std;
using namespace P2P_Network;

#define N_SYS_THREADS 2

#ifndef N_THREADS
#define N_THREADS 3
#endif

I_Command_Interpreter *global_cmd_interpeter;
I_Socket_Worker *global_socket_worker;

template <typename Type>
class Q{
private:
	queue<Type> q;
	mutex g_lock;
public:
	Q(){
		q = queue<Type>();
	}

	Type get_Next(){
		Type sock_id;

		lock_guard<mutex> lock(g_lock);
		if (q.empty()) {
			sock_id = -1;
		}else{
			sock_id = q.front();
			q.pop();
		}
		return sock_id;
	}

	void add_New(int sock_id){
		lock_guard<mutex> lock(g_lock);
		q.push(sock_id);
	}
};



void Thread_Answer(bool &is_Workers_Run, Q<int> &q_sockets){
	int sock_id;
	while(is_Workers_Run){
		sock_id = q_sockets.get_Next();
		if (sock_id != -1) {
			global_socket_worker->send_buffer(sock_id, global_cmd_interpeter->do_Command(new Command(global_socket_worker->recieve_buffer(sock_id))));
			global_socket_worker->close_socket(sock_id);
		}else{
			this_thread::sleep_for(chrono::milliseconds(200));
		}
	}
}


void Thread_Handler(Client_Addr	addr, bool &is_Workers_Run, Q<int> &q_sockets){
	int listener_id = global_socket_worker->get_New_Socket_Id();
	int sock_id;
	if(global_socket_worker->bind_socket(listener_id, &addr)) exit(2);
	global_socket_worker->listen_sockets(listener_id, 0);

	while(is_Workers_Run){
		sock_id = global_socket_worker->accept_socket(listener_id);
		if(sock_id < 0){
			continue;
		}
		q_sockets.add_New(sock_id);
	}
	global_socket_worker->close_socket(listener_id);
}

void Check_File(thread &th, bool &is_Workers_Run){
	ifstream file_in;
	string buffer_str = "";
	while(is_Workers_Run){
		this_thread::sleep_for(chrono::seconds(10));
		file_in.open("server_work");
		buffer_str = "";
		if (file_in.is_open()){
			getline(file_in, buffer_str);
			file_in.close();
		}
		if(buffer_str[0]=='0') {	
			is_Workers_Run = false;
			th.~thread();
			continue;
		}
		
	}
	cout<<"i'm done too\n";
}

void Run_Threads(Client_Addr* addr){
	bool is_Workers_Run = true;
	Q<int> q_sockets;

	thread *threads = new thread[N_SYS_THREADS+N_THREADS];
	threads[0] = thread(Thread_Handler, *addr, ref(is_Workers_Run), ref(q_sockets));
	threads[1] = thread(Check_File, ref(threads[0]), ref(is_Workers_Run));
	for(int i=N_SYS_THREADS; i<N_THREADS; i++){
		threads[i] = thread(Thread_Answer, ref(is_Workers_Run), ref(q_sockets));
	}

	ofstream file_out;
	try{
		file_out.open("server_work");
		file_out<<"1";
	}catch(...){
		cout<<"Can't write to server_work";
	}
	if(file_out.is_open()) file_out.close();

	// threads[0].detach();
	for(int i=0; i<N_SYS_THREADS+N_THREADS; i++){
		threads[i].join();
	}
	cout<<"work done"<<endl;
}

void Thread_Requests_Handler::set_Workers(I_Socket_Worker *socket_worker, I_Command_Interpreter *cmd_interpeter){
	global_socket_worker = socket_worker;
	global_cmd_interpeter = cmd_interpeter;
}

void Thread_Requests_Handler::start_Working(Client_Addr* addr){
	Thread_Requests_Handler::is_working = true;
	thread(Run_Threads, addr).detach();
}

int Thread_Requests_Handler::get_Status(){
	return Thread_Requests_Handler::is_working;
}

void Thread_Requests_Handler::stop_Working(){
	Thread_Requests_Handler::is_working= false;
	ofstream file_out;
	try{
		file_out.open("server_work");
		file_out<<"0";
	}catch(...){
		printf("Can't write to server_work");
	}
	if(file_out.is_open()) file_out.close();
}
