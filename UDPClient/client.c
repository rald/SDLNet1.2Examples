#include <SDL/SDL.h>
#include <SDL/SDL_net.h>

int main(int argc,char *argv[]) {

	UDPsocket udpSocket;
	UDPpacket *udpPacket;

	IPaddress ipAddress;

	int quit=0;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s host port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if(SDLNet_Init()==-1) {
		printf("SDLNet_Init: %s\n",SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!(udpSocket = SDLNet_UDP_Open(0))) {
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (SDLNet_ResolveHost(&ipAddress, argv[1], atoi(argv[2]))) {
		fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", argv[1], atoi(argv[2]), SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!(udpPacket = SDLNet_AllocPacket(512))) {
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	while (!quit) {
		printf("Fill the buffer\n>");
		scanf("%s", (char *)udpPacket->data);

		udpPacket->address.host = ipAddress.host;
		udpPacket->address.port = ipAddress.port;

		udpPacket->len = strlen((char *)udpPacket->data) + 1;

		SDLNet_UDP_Send(udpSocket, -1, udpPacket);

		if (!strcmp((char *)udpPacket->data, "quit")) quit = 1;
	}

	SDLNet_FreePacket(udpPacket);

	SDLNet_Quit();

	return EXIT_SUCCESS;
}
