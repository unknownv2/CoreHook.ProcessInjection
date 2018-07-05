#include "utils.h"



void ptrace_attach(int pid)
{
    if ((ptrace(PTRACE_ATTACH, pid, NULL, NULL)) < 0)
    {
		perror("ptrace_attach");
		exit(-1);
    }

    waitpid(pid, NULL, WUNTRACED);
}

void ptrace_detach(int pid)
{
    if (ptrace(PTRACE_DETACH, pid, NULL, NULL) < 0)
    {
	perror("ptrace_detach");
	exit(-1);
    }
}
void ptrace_read(int pid, unsigned long addr, void *data, int len)
{
	//printf("ptrace_read called pid % dat %d, len %d\n", pid, addr, len);	
	int bytesRead = 0;
	int i = 0;
	long word = 0;
	long *ptr = (long *) data;
	//printf("ptrace_read looping\n");
	if(bytesRead < len) {
	while (bytesRead < len)
	{
		word = ptrace(PTRACE_PEEKTEXT, pid, addr + bytesRead, NULL);
		if(word == -1)
		{
			//fprintf(stderr, "ptrace(PTRACE_PEEKTEXT) failed\n");
			exit(1);
		}
		bytesRead += sizeof(word);
		printf("ptrace_read %u\n", word);
		ptr[i++] = word;
	}
	}
	else {
		printf("INVALID: ptrace_read called at %d, len %d\n", addr, len);
	}
}

long
ptrace_memory_search(int pid, long start, long end, void *data, long len)
{
    long addr = start;
    char *buf = (char *)malloc(len);
    while(addr < end)
    {
        if(ptrace_read2(pid, addr, buf, len))
            if(!memcmp(buf, data, len))
                return addr;
        addr += len;
    }
    return 0;
}

char *
ptrace_read_string(int pid, unsigned long start)
{
    char x = '\0';
    long end;
    char *str = NULL;
    end = ptrace_memory_search(pid, start, start+0x1000, &x, 1);
    if(!end)
        return NULL;
		
	//fprintf(stderr, "ptrace_read_string len = %d\n", end-start);
		
    str = (char *)malloc(end-start + 1);
	memset(str, 0, (unsigned int)(end-start) + 1);
    if(ptrace_read2(pid, start, str, end-start))
        return str;
    return NULL;
}
bool ptrace_read2(int pid, unsigned long addr, void *data, unsigned int len)
{
    int bytesRead = 0;
    int i = 0;
    long word = 0;
    unsigned long *ptr = (unsigned long *)data;

    while (bytesRead < len)
    {
		word = ptrace(PTRACE_PEEKTEXT, pid, addr + bytesRead, NULL);
		if (word == -1)
		{
			//fprintf(stderr, "ptrace(PTRACE_PEEKTEXT) failed\n");
			return false;
		}
		bytesRead += sizeof(long);
		if (bytesRead > len)
		{
			//fprintf(stderr, "ptrace_read2 bytesRead = %d, remainder = %d, rd2 = %d\n", bytesRead,
			//sizeof(long) - (bytesRead - len), (bytesRead - len));
			unsigned int final = sizeof(long) - (bytesRead - len);
			memcpy(ptr + i, &word, final);
			break;
		}
		ptr[i++] = word;
    }
    return true;
}

void ptrace_write(int pid, unsigned long addr, void *data, int len)
{
    int byteCount = 0;
    long word = 0;

    while (byteCount < len)
    {
	memcpy(&word, data + byteCount, sizeof(word));
	word = ptrace(PTRACE_POKETEXT, pid, addr + byteCount, word);
	if (word == -1)
	{
	    fprintf(stderr, "ptrace(PTRACE_POKETEXT) failed\n");
	    exit(1);
	}
	byteCount += sizeof(word);
    }
}