/*
 * Multimedia Broadcaster (MMB)
 * Copyright (c) 2018 Bryan Morfe. All rights reserved.
 * This tools allows recording of audio and/or in frames
 * while sending it to a server specified or storing the
 * frames locally.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mmb_argv.h"
#include "mmb_fc.h"
//#include <Windows.h>
//#include <Mmsystem.h>

#define OPT_MAP(opts, opt) ((opts & opt) == opt)
#define VERBOSE(msg) {\
    if (OPT_MAP(tool_opts, TOOL_VERB_MD) == TRUE) {\
        printf(msg); \
        printf("\n"); \
    } \
}

/* Prototypes */
void display_help();
void build_fn(int frame_n, enum mmb_type m_type, char *pre, char *fn);
int rec_frame(struct mmb_frame *fm);
int send_frame(struct mmb_frame *fm);
int stop_frame(struct mmb_frame *fm);
int close_mmb(struct mmb_frame *fm);

/* Main function */
int main(int argc, char **argv)
{
    int frames_rec = 0;
    char def_prefixes[2][40];
    
    struct mmb_frame fm;
    struct mm_server serv;
    
    map_argv(argc, argv);
    
    parse_inp(&serv, def_prefixes);
    
    if (OPT_MAP(tool_opts, TOOL_HELP_AC) == TRUE)
    {
        display_help();
        return 0;
    }
    
    /***** Initialize frame *****/
    
    /* Aliases to refer to the frames of audio and video */
    strcpy(fm.alias[FM_AUD_INDX], MCI_AUD_ALI);
    strcpy(fm.alias[FM_VID_INDX], MCI_VID_ALI);
    
    /* If no filename is provided use default */
    sprintf(def_prefixes[FM_AUD_INDX], "%s", DEF_AUD_PRE);
    sprintf(def_prefixes[FM_VID_INDX], "%s", DEF_VID_PRE);
    
    while (TRUE) {
        
        /* Config frame */
        build_fn(frames_rec, audio, def_prefixes[FM_AUD_INDX], fm.filename[FM_AUD_INDX]);
        build_fn(frames_rec, video, def_prefixes[FM_VID_INDX], fm.filename[FM_VID_INDX]);
        fm.status = FM_STAT_INV;
        fm.length = FM_DEF_LNTH;
        fm.opts = fm_opts;
        
        /* Record frame */
        rec_frame(&fm);
        
        /* Stop frame */
        stop_frame(&fm);
        
        /* Send frame */
        send_frame(&fm);
        
        /* Close mci (and clean up if option used) */
        close_mmb(&fm);
        
        /* Wait for the frame's length (for syncronization) */
        sleep(5);
        
        frames_rec++;
    }
    
    return 0;
}

/* Function definitions */

void display_help()
{
    printf("usage: mmb [options]\n");
    printf("\tCommands:\n");
    printf("\t\t-a\t\tactivate audio recording and broadcasting\n");
    printf("\t\t--apre\t\taudio filename prefix\n");
    printf("\t\t-b\t\tenable broadcasting\n");
    printf("\t\t-c\t\tcleanup: delete each file after it's sent\n");
    printf("\t\t-d\t\tautivate video recording and broadcasting\n");
    printf("\t\t--dpre\t\tvideo filename prefix\n");
    printf("\t\t-h\t\tdisplay help menu\n");
    printf("\t\t-l\t\tframe length in milliseconds\n");
    printf("\t\t-p\t\tserver port\n");
    printf("\t\t-s\t\tserver ip address where content will be broadcasted to.\n");
    printf("\t\t-v\t\tactivate verbose mode\n");
}

void build_fn(int frame_n, enum mmb_type m_type, char *pre, char *fn)
{
    switch (m_type)
    {
        case audio:
            sprintf(fn, "%s-%5d.wav", pre, frame_n);
            break;
        case video:
            sprintf(fn, "%s-%5d.avi", pre, frame_n);
            break;
    }
}

int rec_frame(struct mmb_frame *fm)
{
    
    int err;
    
    /* Audio */
    if (OPT_MAP(fm_opts, RECORD_AUDIO))
    {
        VERBOSE("Recording audio...");
    }
    
    /* Video */
    if (OPT_MAP(fm_opts, RECORD_VIDEO))
    {
        VERBOSE("Recording video...");
    }
    
    if (err == 0) {
        fm->status = FM_STAT_REC;
    } else {
        fm->status = FM_STAT_ERR;
    }
    
    return err;
    
}

int send_frame(struct mmb_frame *fm)
{
    int err;
    
    /* Audio */
    if (OPT_MAP(fm_opts, RECORD_AUDIO))
    {
        VERBOSE("sending audio...");
    }
    
    /* Video */
    if (OPT_MAP(fm_opts, RECORD_VIDEO))
    {
        VERBOSE("sending video...");
    }
    
    return err;
}

int stop_frame(struct mmb_frame *fm)
{
    int err;
    
    /* Audio */
    if (OPT_MAP(fm_opts, RECORD_AUDIO))
    {
        VERBOSE("stopping audio...");
    }
    
    /* Video */
    if (OPT_MAP(fm_opts, RECORD_VIDEO))
    {
        VERBOSE("stopping video...");
    }
    
    return err;
}

int close_mmb(struct mmb_frame *fm)
{
    int err;
    
    /* Audio */
    if (OPT_MAP(fm_opts, RECORD_AUDIO))
    {
        VERBOSE("closing audio...");
    }
    
    /* Video */
    if (OPT_MAP(fm_opts, RECORD_VIDEO))
    {
        VERBOSE("closing video...");
    }
    
    return err;
}
