#include "./parser.c"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    (void)argc;
    if (argv[1]!=NULL) {
        Parser parser=init_parser(argv[1]);
        bool is_ex=(strcmp(get_extension(&parser.fs),"hasm")==0);
        if (!is_ex) {
            fprintf(stderr,"Err: invalid extension\n");
            fprintf(stderr,"allowed extension:hasm\n");
            exit(1);
        }
        parse(&parser);
    }else {
    }
    return 0;
}
