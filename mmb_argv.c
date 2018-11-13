#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mmb_argv.h"
#include "mmb_fc.h"

tool_opts_t tool_opts = 0;
frame_opts_t fm_opts = 0;

static struct mmb_opts opts[100];
int opts_length;

static int is_opt_passed(const char *opt)
{
    
    for (int i = 0; i < opts_length; i++)
        if (strcmp(opt, opts[i].opt) == 0)
            return TRUE;
    
    return FALSE;
}

static void arg_for_opt(const char *opt, char *arg)
{
    int found = FALSE;
    for (int i = 0; i < opts_length && found == FALSE; i++)
        if (strcmp(opt, opts[i].opt))
        {
            strcpy(arg, opts[i].arg);
            found = TRUE;
        }
}

static void debug_display()
{
    int i;
    for (i = 0; i < opts_length; i++)
        printf("%s\t%s\n", opts[i].opt, opts[i].arg);
}

void map_argv(int argc, char **argv)
{
    int i, j = 0;
    for (i = 1; i < argc; i++)
    {
        const char *lopt_beg = "--";
        
        if (strncmp(argv[i], lopt_beg, 2) == 0)
        {
            /* is long option */
            strcpy(opts[j].opt, argv[i]+2);
            
            if (i+1 < argc && argv[i+1][0] == '-')
                j++;
        }
        else if (argv[i][0] == '-')
        {
            /* is short option */
            int ln = strlen(argv[i]);
            if (ln > 2)
            {
                // has more options, ex: -abc
                int k;
                for (k = 1; k < ln; ++k)
                {
                    opts[j].opt[0] = argv[i][k];
                    opts[j++].opt[1] = '\0';
                }
                j--;
                
            }
            else
            {
                opts[j].opt[0] = argv[i][1];
                opts[j].opt[1] = '\0';
            }
            
            if (i+1 < argc && argv[i+1][0] == '-')
                j++;
        }
        else
        {
            /* is arg of option */
            strcpy(opts[j++].arg, argv[i]);
        }
        
    }
    
    opts_length = j + 1;
    // debug_display();
    if (is_opt_passed("h") == TRUE)
    {
        tool_opts |= TOOL_HELP_AC;
        return;
    }
    
    if (is_opt_passed("b\0") == TRUE)
        tool_opts |= TOOL_EN_BCNG;
    
    if (is_opt_passed("v\0") == TRUE)
        tool_opts |= TOOL_VERB_MD;
    
    if (is_opt_passed("a\0") == TRUE)
        fm_opts |= RECORD_AUDIO;
    
    if (is_opt_passed("d\0") == TRUE)
        fm_opts |= RECORD_VIDEO;
    
    if (is_opt_passed("c\0") == TRUE)
        fm_opts |= FRAME_CLEANU;
}

void parse_inp(struct mm_server *serv, char prefixes[2][40])
{
    if (serv != NULL)
    {
        arg_for_opt("s\0", serv->hostname);
        
        char port[6];
        arg_for_opt("p\0", port);
        serv->port = atoi(port);
    }
    
    arg_for_opt("apre", prefixes[FM_AUD_INDX]);
    arg_for_opt("dpre", prefixes[FM_VID_INDX]);
}
