#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "hyphen.h"
#include "csutil.h"


int 
main(int argc, char** argv)
{

    HyphenDict *dict;
    char * df;
    char * wtc;
    FILE* wtclst;
    int k, n, i, j, c;
    char buf[101];
    int  nHyphCount;
    char *hyphens;
    char *lcword;
    char *hyphword;

  /* first parse the command line options */
  /* arg1 - hyphen dictionary file, arg2 - file of words to check */

  if (argv[1]) {
       df = mystrdup(argv[1]);
  } else {
    fprintf(stderr,"correct syntax is:\n"); 
    fprintf(stderr,"example hyphen_dictionary_file file_of_words_to_check\n");
    exit(1);
  }

  if (argv[2]) {
       wtc = mystrdup(argv[2]);
  } else {
    fprintf(stderr,"correct syntax is:\n"); 
    fprintf(stderr,"example hyphen_dictionary_file file_of_words_to_check\n");
    exit(1);
  }

  /* load the hyphenation dictionary */  
  if ((dict = hnj_hyphen_load(df)) == NULL) {
       fprintf(stderr, "Couldn't find file %s\n", df);
       fflush(stderr);
       exit(1);
  }

  /* open the words to check list */
  wtclst = fopen(wtc,"r");
  if (!wtclst) {
    fprintf(stderr,"Error - could not open file of words to check\n");
    exit(1);
  }

    
  /* now read each word from the wtc file */
    while(fgets(buf,100,wtclst)) {
       k = strlen(buf);
       *(buf + k - 1) = '\0';

       /* set aside some buffers to hold lower cased */
       /* and hyphen information */
       lcword = (char *) malloc(k+1);
       hyphens = (char *)malloc(k+5);
       enmkallsmall(lcword,buf,dict->cset);

       /* first remove any trailing periods */
       n = k-1;
       while((n >=0) && (lcword[n] == '.')) n--;
       n++;

       /* now actually try to hyphenate the word */
       if (n > 0) {
	 if (hnj_hyphen_hyphenate(dict, lcword, n-1, hyphens))
         {
             free(hyphens);
             free(lcword);
             fprintf(stderr, "hyphenation error\n");
             exit(1);
         }
       }

       /* now backfill hyphens[] for any removed periods */
       for (c = n; c < k; c++) hyphens[c] = '0';
       hyphens[k] = '\0';

       /* now create a new char string showing hyphenation positions */
       /* count the hyphens and allocate space for the new hypehanted string */
       nHyphCount = 0;
       for (i = 0; i < n; i++)
          if (hyphens[i]&1)
             nHyphCount++;
       hyphword = (char *) malloc(k+1+nHyphCount);
       j = 0;
       for (i = 0; i < n; i++) {
	  hyphword[j++] = buf[i];
          if (hyphens[i]&1)
	  {
	      hyphword[j++] = '-';
	  }
       }
       hyphword[j] = '\0';
       fprintf(stdout,"%s\n",hyphword);
       fflush(stdout);

       free(hyphens);
       free(lcword);
       free(hyphword);

    }

    return 0;
}


  

          
  
