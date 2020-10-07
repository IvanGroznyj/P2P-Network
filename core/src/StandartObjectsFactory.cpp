#include "StandartObjectsFactory.h"

#include "StandartCommandInterpreter.h"
#include "NetSocketWorker.h"
#include "ThreadRequestsHandler.h"
#include "StandartDataWorker.h"

using namespace P2P_Network;

I_Socket_Worker* Standart_Objects_Factory::get_Socket_Worker(){
	return new Net_Socket_Worker();
};

I_Requests_Handler* Standart_Objects_Factory::get_Requests_Handler(){
	Thread_Requests_Handler *thread_req_handler = new Thread_Requests_Handler();
	thread_req_handler->set_Workers(Standart_Objects_Factory::get_Socket_Worker(), Standart_Objects_Factory::get_Command_Interpreter());
	return thread_req_handler;
};

I_Data_Worker* Standart_Objects_Factory::get_Data_Worker(){
	Standart_Data_Worker *dworker = new Standart_Data_Worker();
	dworker->load_Hash_Table();
	return dworker;
};

Client* Standart_Objects_Factory::get_Client(){
	Client* cur_Client = new Client();
	cur_Client->set_Data_Worker(Standart_Objects_Factory::get_Data_Worker());
	cur_Client->set_Socket_Worker(Standart_Objects_Factory::get_Socket_Worker());
	cur_Client->set_Requests_Handler(Standart_Objects_Factory::get_Requests_Handler());
	return cur_Client;
};

I_Command_Interpreter* Standart_Objects_Factory::get_Command_Interpreter(){
	Stadnart_Command_Interpreter *cmd_interpeter = new Stadnart_Command_Interpreter();
	cmd_interpeter->set_Data_Worker(Standart_Objects_Factory::get_Data_Worker());
	return cmd_interpeter;
}
