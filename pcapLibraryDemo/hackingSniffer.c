#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

#define MAXBYTES2CAPTURE 2048

void processPacket(u_char *arg, const struct pcap_pkthdr* pkthdr, const u_char *packet){
	int i=0, *counter = (int *)arg;

	printf("Packet Count: %d\n", ++(*counter));
	printf("Received packet size: %d\n", pkthdr->len);
	printf("Payload: \n");

	for(i; i<pkthdr->len; i++){
		if(isprint(packet[i])){
			printf("%c", packet[i]);
		}else{
			printf(". ");
		}

		if((i%16 == 0 && i!=0) || (i == pkthdr->len -1)){
			printf("\n");
		}
	}

	return;
}

int main(){
	int i = 0, count = 0;
	pcap_t *desc = NULL;
	char errbuf[PCAP_ERRBUF_SIZE], *device=NULL;
	memset(errbuf,0,PCAP_ERRBUF_SIZE);

	//Get the name of the first device suitable for the capture
	device = pcap_lookupdev(errbuf);

	printf("Opening device: %s\n", device);

	//Open device in promiscous mode
	desc = pcap_open_live(device, MAXBYTES2CAPTURE, 1, 0, errbuf);

	//Loop forever & call processPacket() for every received package
	pcap_loop(desc, -1, processPacket, (u_char *)&count);

	return 0;
}