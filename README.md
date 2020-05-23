# P2P-Network
My P2P-network. Chat and file transfer.

## Start & Build
- Clone git: <br />
`git clone https://github.com/IvanGroznyj/P2P-Network.git`
- Clear build dir: <br />
`$ cd P2P-Network/Debug/` <br />
`$ make clean`
- After that, if you want to run unit tests: <br />
`$ make unittests` <br />
`$ cd ..` <br />
`$ ./Debug/runner`
- Or if you want to make the simple p2p-chat:  <br />
`$ make all` <br />
`$ cd ..` <br />
`$ ./Debug/runner <your local ip addres> <port>`
