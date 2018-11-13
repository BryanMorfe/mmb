#ifndef MMB_ARGV_H
#define MMB_ARGV_H

#define TOOL_VERB_MD    0x01    /* Verbose mode activated  */
#define TOOL_HELP_AC    0x02    /* Help mode activated     */
#define TOOL_EN_BCNG    0x04    /* Enable broadcasting     */
#define TOOL_IVAL_OT    0x08    /* Invalid option detected */

struct mmb_opts
{
    char opt[5];
    char arg[100];
};

struct mm_server
{
    char hostname[100];
    int port;
};

int tool_opts;
int fm_opts;

void map_argv(int argc, char **argv);

void parse_inp(struct mm_server *serv, char prefixes[2][40]);

#endif /* MMB_ARGV_H */
