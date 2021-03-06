#include "util.h"
#include "args.h"

#include "node.h"
#include "tokenizer.h"
#include "parser.h"
#include "assemble.h"
#include "vm.h"

int main(int argc, char **argv)
{
    char *m_file_path = argparse(argc, argv);

    StreamObject *streamObject = open_stream(m_file_path, "r");
    if (streamObject == NULL)
        exit(EXIT_FAILURE);

    char *f_source = read_stream(streamObject);

    TokenNode *tk = tokenize(f_source);

    if (tk == NULL)
        perror("error: tokenize failed");
    else
    {
        TokenNode *tk_iter = tk;

        printf("\n");
        parse(tk_iter, f_source);
        char *executable_file = assemble(tk_iter);

        if (executable_file)
        {
            printf("\nPress enter to run the code...");
            getc(stdin);
            load_program(executable_file);
            printf("Done");
        }
    }

    free(tk);
    free(m_file_path);
    free(f_source);
    close_stream(streamObject);
	
#ifdef _WIN32
	printf("\nPress enter to exit...");
	getc(stdin);
#endif

    return 0;
}
