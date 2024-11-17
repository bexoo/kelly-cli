#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  double bankroll;
  double win_prob;
  double gain_ratio;
} KellyParams;

double parse_double(const char *str, double min, double max) {
  double val = atof(str);
  return (val >= min && (max < 0 || val <= max)) ? val : -1.0;
}

double calc_gain_ratio(double pb, double ob, double bb, double gb) {
  if (pb > 0)
    return 1.0 / pb - 1.0;
  if (ob > 0)
    return 1.0 / ob;
  if (bb > 1)
    return bb - 1.0;
  return gb;
}

KellyParams parse_args(int argc, char *argv[]) {
  KellyParams params = {-1.0, -1.0, -1.0};
  double pb = -1.0, ob = -1.0, bb = -1.0, gb = -1.0, odds = -1.0;

  for (int i = 1; i < argc; i += 2) {
    if (i + 1 >= argc)
      break;

    const char *flag = argv[i];
    const char *value = argv[i + 1];

    if (strcmp(flag, "-b") == 0)
      params.bankroll = parse_double(value, 0, -1);
    else if (strcmp(flag, "-pw") == 0)
      params.win_prob = parse_double(value, 0, 1);
    else if (strcmp(flag, "-ow") == 0)
      odds = parse_double(value, 0, -1);
    else if (strcmp(flag, "-pb") == 0)
      pb = parse_double(value, 0, 1);
    else if (strcmp(flag, "-ob") == 0)
      ob = parse_double(value, 0, -1);
    else if (strcmp(flag, "-bb") == 0)
      bb = parse_double(value, 1, -1);
    else if (strcmp(flag, "-gb") == 0)
      gb = parse_double(value, 0, -1);
  }

  // Convert odds to probability if needed
  if (params.win_prob < 0 && odds > 0)
    params.win_prob = odds / (1.0 + odds);

  // Calculate gain ratio from provided parameters
  int gain_params = (pb > 0) + (ob > 0) + (bb > 0) + (gb > 0);
  if (gain_params == 1)
    params.gain_ratio = calc_gain_ratio(pb, ob, bb, gb);

  return params;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf(
        "Usage: kelly -b <bankroll> (-pw <win probability> | -ow <win odds>) "
        "(-pb <implied probability> | -ob <implied odds> | -bb <winnings to "
        "bet ratio> | -gb <gained to bet ratio>)\n");
    return 1;
  }

  KellyParams params = parse_args(argc, argv);

  if (params.win_prob < 0 || params.gain_ratio < 0) {
    printf("Invalid or missing parameters\n");
    return 1;
  }

  double fraction =
      params.win_prob - ((1.0 - params.win_prob) / params.gain_ratio);

  if (params.bankroll < 0)
    printf("Optimal bet fraction: %.4f\n", fraction);
  else
    printf("Optimal bet amount: %.4f\n", fraction * params.bankroll);

  return 0;
}
