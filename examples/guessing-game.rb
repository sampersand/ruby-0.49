%MAX = ($ARGV[0] || 100).to_i

srand()
secret = 1 + rand(%MAX)
guesses = 0
printf("Guessing game! Guess a number from 1-%d!\n", %MAX)

until (guess = gets().to_i) == secret
  print("Too ", if guess < secret then "small" else "large" end, "!\n")
  guesses += 1
end until;

printf("Correct! It took you %d guesses!\n", guesses)
