#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  double b = -1.0;  // Current bankroll
  double pw = -1.0; // Probability of winning
  double ow = -1.0; // Odds of winning
  double pb = -1.0; // Implied probability given by bet
  double ob = -1.0; // Implied odds given by bet
  double bb = -1.0; // Proportion of bet you end with on win
  double gb = -1.0; // Proprtion of bet you gain on win

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-b") == 0) {
      b = atof(argv[i + 1]);
      if (b < 0) {
        printf("Bankroll must be greater than or equal to 0\n");
        return 1;
      }
    } else if (strcmp(argv[i], "-pw") == 0) {
      pw = atof(argv[i + 1]);
      if (!(pw >= 0 && pw <= 1)) {
        printf("Probability of winning must be between 0 and 1\n");
        return 1;
      }
    } else if (strcmp(argv[i], "-ow") == 0) {
      ow = atof(argv[i + 1]);
      if (ow < 0) {
        printf("Odds of winning must be greater than 0\n");
        return 1;
      }
    } else if (strcmp(argv[i], "-pb") == 0) {
      pb = atof(argv[i + 1]);
      if (!(pb > 0 && pb <= 1)) {
        printf("Implied probability must be between 0 and 1\n");
        return 1;
      }
    } else if (strcmp(argv[i], "-ob") == 0) {
      ob = atof(argv[i + 1]);
      if (ob <= 0) {
        printf("Bet odds must be greater than 0\n");
        return 1;
      }
    } else if (strcmp(argv[i], "-bb") == 0) {
      bb = atof(argv[i + 1]);
      if (bb <= 1) {
        printf("Bet back must be greater than 1\n");
        return 1;
      }
    } else if (strcmp(argv[i], "-gb") == 0) {
      gb = atof(argv[i + 1]);
      if (gb <= 0) {
        printf("Bet gained must be greater than 0\n");
        return 1;
      }
    }
  }
  if (b == -1.0 && pw == -1.0 && ow == -1.0 && pb == -1.0 && ob == -1.0 &&
      bb == -1.0 && gb == -1.0) {
    printf("Usage: kelly -b <bankroll> -pw <probability of winning> OR -ow "
           "<odds of winning> -pb <implied probability> OR -ob <implied odds "
           "of bet> "
           "OR -bb <proportion of bet you end with on win> OR -gb <proportion "
           "of bet gained on win>\n");
    return 1;
  }

  int count = 0;
  if (pb != -1.0)
    count++;
  if (ob != -1.0)
    count++;
  if (bb != -1.0)
    count++;
  if (gb != -1.0)
    count++;

  if (count > 1) {
    printf("You can only provide one of -pb or -ob or -bb or -gb\n");
    return 1;
  } else if (count == 0) {
    printf("You must provide one of -pb or -ob or -bb or -gb\n");
    return 1;
  }
  if (pw != -1.0 && ow != -1.0) {
    printf("You can only provide one of -pw or -ow\n");
    return 1;
  }
  if (pw == -1.0 && ow == -1.0) {
    printf("You must provide one of -pw or -ow\n");
    return 1;
  }
  if (ow != -1.0) {
    pw = ow / (1.0 + ow);
  }
  if (pb != -1.0) {
    gb = 1.0 / pb - 1.0;
  } else if (ob != -1.0) {
    gb = 1.0 / ob;
  } else if (bb != -1.0) {
    gb = bb - 1.0;
  }
  double f = pw - ((1 - pw) / gb);
  if (b == -1.0) {
    printf("Optimal bet fraction: %.4f\n", f);
  } else {
    printf("Optimal bet amount: %.4f\n", f * b);
  }
  return 0;
}
