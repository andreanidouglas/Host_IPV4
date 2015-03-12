#include "host.h"

int main(int argc, char** argv)
{
    char* resultado;
    if(argc>3 || argc==1)
    {
        printf("Erro\nUso: %s nome\n", argv[0]);
        return (0);
    }
    if (argc==2)
    {
        resultado = getHostAddressByName(argv[1]);
	if (resultado == NULL)
	{
            printf("Nao foi possivel resolver o nome\n");
	}
    }
    else
    {
        if (argv[1][0] == '-' && argv[1][1] == 'r')
        {
            resultado = getHostNameByAddress(argv[2]);
        }
        else
        {
            printf("Erro: Atributo nao existe: %s\n", argv[1]);
	    printf("Uso: %s -r ip_address\n", argv[0]);
            return (0);
        }
	if (resultado == NULL)
	{
	    printf("Endereco IP Invalido\n");
	}
    }
    
    return (0);
}
char* getHostNameByAddress(char* address)
{

    struct hostent* hp;
    struct in_addr addr;

    bzero(&addr, sizeof(struct in_addr));
    inet_aton(address, &addr);
    hp = gethostbyaddr(&addr, sizeof(addr), AF_INET);

    if (hp==NULL)
    {
    	return NULL;
    }
    else
    {
        printf("Host: %s\n", hp->h_name);
	return ("OK");
    }
    return NULL;
}

char* getHostAddressByName(char* name)
{
    struct hostent* hp;
    struct in_addr** list;
    int i;
    hp = gethostbyname(name);
    if (hp == NULL)
    {
        return NULL;
    }
    else
    {
        list = (struct in_addr **)hp->h_addr_list;
        for (i=0; list[i]!=NULL;i++)
        {
            printf("IP %d: %s\n", i, (char*)inet_ntoa(*list[i]));
        }
	return ("OK");
    }
}

