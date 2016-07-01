#ifndef FONCTIONSTCP_H
#define FONCTIONSTCP_H

#include <stdio.h>
#include <signal.h>

int socketServeur(int port);

int socketClient(char *nomMachine, int port);



#endif
