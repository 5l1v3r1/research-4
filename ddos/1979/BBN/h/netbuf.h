#define net_b_per_k_b	8	/* number of netbuf to one kernel buf */
#define b_freect	b_wcount /*a word in a buf. see buf.h */

#ifndef BUFMOD
#define b_overhead	4	/*bytes of overhead in a netbuf*/
#define	B_OVERHEAD	4	/*bytes of overhead in a netbuf*/
#define net_b_size	60	/*bytes of data in a netbuf*/
#define NET_B_SIZE	60	/*for completeness*/
#endif BUFMOD

#ifdef BUFMOD
#define net_b_size      64      /*bytes of data in a netbuf*/
#define NET_B_SIZE      64      /*for completeness*/
#endif


 struct netbuf		/*network buffer data structure*/
 {
	struct netbuf *b_qlink;		/*q link for msgs. must be first*/
	char	b_len;			/*amount of data in b_data*/
	char	b_resv;			/*reserved. see defines below*/
#ifndef BUFMOD
	char	b_data[net_b_size];	/*data space*/
 };
#endif BUFMOD
#ifdef BUFMOD
	int	b_loc;			/*location of data space*/
} bufhead[kb_hiwat][net_b_per_k_b];
#endif BUFMOD

/* bits defined within the b_resv field of a message buffer*/
#define b_eom		0200	/*end of message. no used by primitives*/
#define b_memberof	017	/*index of kbuf that netbuf is in. used by*/
				/*primitives but not by users*/
#ifdef RMI
#define b_raw           0100    /* this buf used for raw message */
				/* rbuf_max (max useable by rmi): netparam.h*/
int rbuf_count;                 /* number currently in use */
#endif



 /*buffer system state vector*/

 struct
 {
	int	b_hyster;		/* hysteresis before releaseing buffers */
	int	b_alloc;		/*current # of kbufs allocated*/
	struct buf *kb_[kb_hiwat];	/*pointers to allocated kbufs or 0*/
	int	b_cntfree;		/* number of buffers in free list */
	char	*b_freel;		/*free list of netbuffers. looks like a message*/
	int	b_need;			/*non-zero if space needed. see flags below*/
#ifdef BUFMOD
	char    emerbuf[64];
#endif BUFMOD
#ifndef BUFMOD
	struct netbuf	emerbuf;	/* the emergency buffer */
#endif BUFMOD
 } net_b;

/*defines on b_need*/
#define proc_need	01	/*buffer needed by process, so do wakeup*/
#define int_need	02	/*buffer needed by interrupt. wakeup superfluous*/

/**/
