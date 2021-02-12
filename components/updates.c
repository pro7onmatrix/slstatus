#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util.h"

const char *
available_updates(void)
{
  static int updates;
  static unsigned int elapsed_milliseconds;
  extern const unsigned int interval;
  extern const unsigned int checkupdates_interval;

  // make sure the update interval is an integer multiple
  // of 'interval'
  const unsigned int update_interval = checkupdates_interval * 1000 - (checkupdates_interval * 1000) % interval;
  if (!(elapsed_milliseconds % update_interval)) {
    char *p;
    FILE *fp;

    if (!(fp = popen("checkupdates | wc -l", "r"))) {
      warn("popen 'checkupdates | wc -l':");
      return NULL;
    }
    // load output into buffer
    p = fgets(buf, sizeof(buf) - 1, fp);
    if (pclose(fp) < 0) {
      warn("pclose 'checkupdates | wc -l':");
      return NULL;
    }
    // catch NULL
    if (!p)
      return NULL;
    // replace trailing newline by NULL terminator
    if ((p = strrchr(buf, '\n')))
      p[0] = '\0';

    if (!buf[0])
      return NULL;

    updates = atoi(buf);
  }

  elapsed_milliseconds += interval;
  return updates ? bprintf(" %d | ", updates) : "";
}

