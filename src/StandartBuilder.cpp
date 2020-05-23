/*
 *  Author: Ivan Khodyrev
 */
#include "../includes/MainInterfaces.h"

#include "../includes/ClientP2P.h"

#include "../includes/StandartCommandInterpreter.h"
#include "../includes/NetSocketWorker.h"
#include "../includes/ThreadRequestsHandler.h"
#include "../includes/StandartDataWorker.h"

#include "../includes/StandartBuilder.h"


void StandartBuilder::BuildRequestsHandler(){
	ThreadRequestsHandler *thread_req_handler = new ThreadRequestsHandler();
	StandartBuilder::cmd_interpeter = new StadnartCommandInterpreter();
	StandartBuilder::cmd_interpeter->SetDataWorker(StandartBuilder::data_worker);
	thread_req_handler->SetWorkers(StandartBuilder::socket_worker, StandartBuilder::cmd_interpeter);
	StandartBuilder::request_handler = thread_req_handler;
}

void StandartBuilder::BuildSocketWorker(){
	StandartBuilder::socket_worker = new NetSocketWorker();
}

void StandartBuilder::BuildDataWorker(){
	StandartDataWorker *dworker = new StandartDataWorker();
	dworker->LoadHashTable();
	StandartBuilder::data_worker = dworker;

}

P2PClient* StandartBuilder::GetClient(){
	P2PClient* curClient = new P2PClient();
	curClient->SetDataWorker(StandartBuilder::data_worker);
	curClient->SetSocketWorker(StandartBuilder::socket_worker);
	curClient->SetRequestsHandler(StandartBuilder::request_handler);
	return curClient;
}
