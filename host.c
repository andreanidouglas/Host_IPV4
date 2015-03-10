#include "host.h"

int main(int argc, char** argv)
{
    char* resultado;
    if(argc>3 || argc==1)
    {
        printf("Usage: %s [-n] name|ipaddress\n", argv[0]);
        return (0);
    }
    if (argc==2)
    {
        resultado = getHostAddressByName(argv[1]);
    }
    else
    {
        if (argv[1][0] == '-' && argv[1][1] == 'n')
        {
            resultado = getHostNameByAddress(argv[1]);
        }
        else
        {
            printf("Attribute do not exist: %s\n", argv[1]);
            return (0);
        }
    }
    
    return (0);
}
char* getHostNameByAddress(char* address)
{

    struct hostent* hp;
    char** list;
    int i;
    struct in_addr addr;
    inet_aton(address, &addr);
    in_addr_t s = inet_addr(address);
    

    hp = gethostbyaddr(&addr, sizeof(s), AF_INET);
    if (hp==NULL)
    {
        printf("OLA");
        return NULL;
    }
    else
    {
        list = hp->h_aliases;
        printf("Host: %s\n", hp->h_name);
        printf("Name %s",  list[0]);
        
        for (i=0;list[i]!=NULL;i++)
        {
            printf("Name %d: %s", i, list[0]);
            return "OK";
        }
    }
    return NULL;
}

char* getHostAddressByName(char* name)
{
    struct hostent* hp;
    struct in_addr** list;
    int i;
    hp = gethostbyname("www.uol.com.br");
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

