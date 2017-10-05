# proj1_5510
A finger client and server for CPSC 5510

Usage: Run 'make' on the command line to compile. Machines tested must be within same firewall; eg, no testing a server running at SU from home.  Launch server on desired machine.  Now send a finger request to the server thusly:
	fingerclient mouse@cs1.seattleu.edu:10240

The response should be either the finger information OR a message that the attempt was unsuccessful if username was misspelled, does not exist, etc. 
