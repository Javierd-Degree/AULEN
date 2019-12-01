#ifndef MINIMIZE_H
#define MINIMIZE_H


int* estadosAccesibles(AFND* afd);

void *estadosDistinguibles(AFND* afd, int* estadosAccesibles, int numAccesibles);


#endif
