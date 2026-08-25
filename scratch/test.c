#include<stdio.h>
int main () {
char *file_path = "../data/test.pdf";
FILE *f = fopen(file_path, "rb");
char *jump = "";
fseek(f, 0, SEEK_END);
fgets(jump, 6, f);
printf("EOF is: %s\n", jump);
}
