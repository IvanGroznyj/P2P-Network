//#include "StandartCommandInterpreter.h"
#include "MainInterfaces.h"

#include "ClientP2P.h"

#include "StandartCommandInterpreter.h"
#include "NetSocketWorker.h"
#include "ThreadRequestsHandler.h"
#include "StandartDataWorker.h"

#include "StandartBuilder.h"


void StandartBuilder::BuildRequestsHandler(){
	ThreadRequestsHandler *thrh = new ThreadRequestsHandler();
	StandartBuilder::cmdinter = new StadnartCommandInterpreter();
	StandartBuilder::cmdinter->SetDataWorker(StandartBuilder::dw);
	thrh->SetWorkers(StandartBuilder::sw, StandartBuilder::cmdinter);
	StandartBuilder::rh = thrh;
}

void StandartBuilder::BuildSocketWorker(){
	StandartBuilder::sw = new NetSocketWorker();
}

void StandartBuilder::BuildDataWorker(){
	StandartDataWorker *tmpdw = new StandartDataWorker();
	tmpdw->LoadHashTable();
	StandartBuilder::dw = tmpdw;

}

P2PClient* StandartBuilder::GetClient(){
	P2PClient* curClient = new P2PClient();
	curClient->SetDataWorker(StandartBuilder::dw);
	curClient->SetSocketWorker(StandartBuilder::sw);
	curClient->SetRequestsHandler(StandartBuilder::rh);
	return curClient;
}
