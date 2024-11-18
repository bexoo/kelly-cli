# Kelly Criterion Calculator

A command-line utility for calculating optimal bet sizes using the Kelly Criterion.

## Installation

1. First, compile the program:

   ```bash
   gcc kelly.c -o kelly
   ```

2. Make it executable:

   ```bash
   chmod +x kelly
   ```

3. Move it to your system's bin directory:
   ```bash
   sudo mv kelly /usr/local/bin/
   ```

## Usage

The Kelly calculator accepts the following parameters:

```bash
kelly -b <bankroll> (-pw <win probability> | -ow <win odds>) (-pb <implied probability> | -ob <implied odds> | -bb <bet back ratio> | -gb <gain ratio>)
```

### Parameters:

- `-b`: Your current bankroll (optional)
- `-pw`: Probability of winning (0-1)
- `-ow`: Odds of winning (alternative to -pw)
- `-pb`: Implied probability from the bet (0-1)
- `-ob`: Implied odds from the bet (not the payoff odds)
- `-bb`: Proportion you end with on win (>1)
- `-gb`: Proportion gained on win (>0)

### Examples:

1. Calculate optimal bet fraction with 60% probability of winning and 3 to 2 implied bet odds:

   ```bash
   kelly -pw 0.6 -ob 1.5
   ```

2. Calculate optimal bet amount from bankroll with 2 to 1 odds of winning and implied probability:

   ```bash
   kelly -b 1000 -ow 2.0 -pb 0.4
   ```

3. For a bet that doubles your money on win:

   ```bash
   kelly -pw 0.55 -bb 2.0

   ```

4. For a bet that gains 10% of your bet on win:
   ```bash
   kelly -b 500 -pw 0.2 -gb 0.1
   ```
