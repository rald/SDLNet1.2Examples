#include <SDL/SDL.h>
#include <SDL/SDL_net.h>

int main(int argc,char *argv[]) {

	UDPsocket udpSocket;
	UDPpacket *udpPacket;

	int quit=0;

	if(SDLNet_Init()==-1) {
		printf("SDLNet_Init: %s\n",SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if(!(udpSocket=SDLNet_UDP_Open(2000))) {
		fprintf(stderr,"SDLNet_UDP_Open: %s\n",SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if(!(udpPacket=SDLNet_AllocPacket(512))) {
		fprintf(stderr,"SDLNet_AllocPacket: %s\n",SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	while(!quit) {
		if(SDLNet_UDP_Recv(udpSocket,udpPacket)) {
			printf("UDP Packet incoming\n");
			printf("\tChan: %d\n", udpPacket->channel);
			printf("\tData: %s\n", (char *)udpPacket->data);
			printf("\tLen: %d\n", udpPacket->len);
			printf("\tMaxlen: %d\n", udpPacket->maxlen);
			printf("\tStatus: %d\n", udpPacket->status);
			printf("\tAddress: %x Port: %x\n", udpPacket->address.host, udpPacket->address.port);

			if (!strcmp((char *)udpPacket->data, "quit")) quit = 1;
		}
	}

	SDLNet_FreePacket(udpPacket);

	SDLNet_Quit();

	return EXIT_SUCCESS;
}
