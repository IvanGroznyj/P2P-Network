class NatPMP {
public:
	const static int UDP_CODE = 1;
	const static int TCP_CODE = 2;
	static void PortForwarding(int code, int internal_port, int external_port, int life_time = 3600);
};
