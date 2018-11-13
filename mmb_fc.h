#ifndef MMB_FC_H
#define MMB_FC_H

#define TRUE            1
#define FALSE           0

#define RECORD_AUDIO    0x01            /* This says to record audio           */
#define RECORD_VIDEO    0x02            /* This says to record video           */
#define FRAME_CLEANU    0x04            /* This says to cleanup after (delete) */

#define FM_STAT_INV     0x00            /* Frame inactive (just created)       */
#define FM_STAT_REC     0x01            /* Frame was recorded                  */
#define FM_STAT_SNT     0x02            /* Frame was sent                      */
#define FM_STAT_STD     0x04            /* Frame was stopped                   */
#define FM_STAT_CLD     0x08            /* Frame was close                     */
#define FM_STAT_ERR     0x10            /* Frame has error                     */

#define MCI_AUD_ALI     "mmb_aud_ali"   /* Alias for audio recording           */
#define MCI_VID_ALI     "mmb_vid_ali"   /* Alias for video recording           */
#define DEF_AUD_PRE     "mmb_aud"       /* Default audio filename              */
#define DEF_VID_PRE     "mmb_vid"       /* Default video filename              */

#define FM_AUD_INDX     0               /* Frame array index for audio         */
#define FM_VID_INDX     1               /* Frame array index for video         */

#define FM_DEF_LNTH     100             /* Default frame length in ms          */
#define FM_DEF_OPTS     RECORD_AUDIO    /* Default frame is record audio       */

/* Frame types */
typedef double frame_length_t;
typedef int    frame_status_t;
typedef int    frame_opts_t;
typedef int    tool_opts_t;

/* Structs */
struct mmb_frame
{
    char           alias[2][20];    /* aliases for aud, vid   */
    char           filename[2][50]; /* filenames for aud, vid */
    frame_length_t length;          /* in ms                  */
    frame_status_t status;          /* frame status           */
    frame_opts_t   opts;            /* frame options          */
    
};

enum mmb_type {
    audio, video
};

#endif /* MMB_FC_H */
