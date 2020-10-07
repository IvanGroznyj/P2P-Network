/*
 *  Author: Ivan Khodyrev
 */
#ifndef NatPMP_H
#define NatPMP_H

namespace P2P_Network{

	class Nat_PMP {
	public:
		const static int UDP_CODE = 1;
		const static int TCP_CODE = 2;
		static void port_Forwarding(int code, int internal_port, int external_port, int life_time = 3600);
	};

}

#endif