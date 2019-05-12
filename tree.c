#include "definitions.c"

void terminate(){
	printf("Gerenciadores terminando...\n");
	fflush(stdout);
	exit(0);
}

int main(){
	signal(SIGTERM, terminate);
	
	int qid = msgget(KEY, IPC_CREAT | 0777);
	if(qid == -1){
		printf("Problema ao criar fila errno: %d\n", errno);
		exit(0);
	}
	
	while(TRUE){
		
		MessageEscalonador msge;
		msgrcv(qid, &msge, sizeof(msge)-sizeof(long int), ESCGER_MSG_TYPE, 0);
		
		sleep(5);
		
		MessageGerente msg;
		msg.status = CONTROL;
		msg.msg_type = ESCGER_MSG_TYPE;
		msgsnd(qid, &msg, sizeof(msg)-sizeof(long int), 0);
	}
	
	return 0;
}

