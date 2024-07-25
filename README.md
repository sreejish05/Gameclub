# Gameclub: Tic Tac Toe and Hangman

This project features two engaging console games: **Tic Tac Toe** and **Hangman**. The program allows you to choose between these games and provides a simple, text-based interface to play them.

## Games

### Tic Tac Toe
- A classic 3x3 grid game where players alternate placing their markers ('X' and 'O').
- The game checks for a winner or a draw after each move.
- Play with another player and see who wins!

### Hangman
- A word guessing game where you guess a randomly selected word from a predefined list, with each word up to 5 letters long.
- Dynamic memory allocation is used for managing the word and display string.
- Try to guess the word within a limited number of attempts and see if you can figure it out!

## How to Play

1. Clone this repository to your local machine:

    ```bash
    git clone https://github.com/yourusername/mini_gamezone.git
    ```

2. Navigate to the project directory:

    ```bash
    cd mini_gamezone
    ```

3. Compile the program using a C compiler, for example, `gcc`:

    ```bash
    gcc -o gamezone gamezone.c
    ```

4. Run the compiled program:

    ```bash
    ./gamezone
    ```

5. Follow the on-screen instructions to choose and play a game.

## Code Structure

- **gameclub.c**: Contains the code for both Tic Tac Toe and Hangman games, as well as the main menu to select which game to play.

## Contributing

If you would like to add more features or games to this project, please fork the repository and submit a pull request. You can also report issues or request features by opening an issue.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
