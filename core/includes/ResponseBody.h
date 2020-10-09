
#ifndef Response_Body_H
#define Response_Body_H

namespace P2P_Network{

	enum Response_Codes
	{
		OK, Connection_Error, Socket_Error, Unknown_Error
	};

	struct Response_Body{
		Response_Codes code;
		string response_text;

		Response_Body(Response_Codes code, string response_text){
			Response_Body::code = code;
			Response_Body::response_text = response_text;
		}

		bool operator==(const Response_Codes& response_code){
			return response_code == code;
		}

		bool operator!=(const Response_Codes& response_code){
			return response_code != code;
		}

	};

}

#endif