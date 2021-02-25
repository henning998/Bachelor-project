#include "include.h"
#include "server.h"

int main(int argc, char **argv)
{
    server Serverobj;
    bool drive = true;
    int key;
    Serverobj.connect();

    while (drive)
    {
        system("/bin/stty raw");

        key = getchar();

        

        /* use system call to set terminal behaviour to more normal behaviour */
        system("/bin/stty cooked");
        switch (key)
        {
        case 'w':
            Serverobj.writing("w");
            break;
        case 's':
            Serverobj.writing("s");
            break;
        /*case 'a':
            Serverobj.writing(std::to_string(key));
            break;
        case 'd':
            Serverobj.writing(std::to_string(key));
            break;*/
        case 27:
            drive = false;
            break;
        default:
            Serverobj.writing("NOPE");
            break;
        }
        //Serverobj.writing("0");
        //Serverobj.closing();
        //usleep(1000000);
    }

    return 0;
}
