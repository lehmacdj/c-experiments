#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
   if (argc != 3) {
       printf("Usage: %s <destination> <file>", argv[0]);
       return 1;
   }
   int ret = link(argv[1], argv[2]);
   if (ret != 0)
       perror("link");
   return ret;
}
