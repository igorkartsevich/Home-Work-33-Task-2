#include <iostream>
#include <exception>

enum GAMEELEMENT {
    EMPTY,
    BOOT,
    FISH
};

class FishException : public std::exception {
public:
    const char* what() const noexcept override {
        return "You WON! The FISH was caught!";
    }
};

class BootException : public std::exception {
public:
    const char* what() const noexcept override {
        return "You LOST! The BOOT was caught!";
    }
};

class OutOfFieldException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Out of Field's borders! Repeat!";
    }
};

class Game {
public:
    void setGameField() {
        std::srand(time(NULL));
        gameField[std::rand() % 3][std::rand() % 3] = FISH;

        int bootsCounter = 3;
        while (bootsCounter != 0) {
            int x = std::rand() % 3;
            int y = std::rand() % 3;
            if (gameField[x][y] == EMPTY) {
                gameField[x][y] = BOOT;
                --bootsCounter;
            }
        }
    }

    void getGameField() { // for control
        std::cout << "Game field!\n0 - EMPTY, 1 - BOOTS, 2 - FISH\n\n";
        
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                std::cout << gameField[x][y] << "   ";
            }
            std::cout << std::endl;
        }
        
        std::cout << "\nFishing started!\n\n";
    }

    void makeAttempt() {
        int x, y;
        std::cout << "Make next step (x (1-3), y (1-3)): ";
        std::cin >> x >> y;

        if (x > 3 || y > 3) throw OutOfFieldException();

        --x; --y;
        if (gameField[x][y] == FISH) throw FishException();
        if (gameField[x][y] == BOOT) throw BootException();
    }

private:
    int gameField[3][3] = { 0 };

};

int main()
{
    Game game;
    game.setGameField();
    game.getGameField(); // for control

    int attemptsCounter = 0;
    while (true) {
        try {
            ++attemptsCounter;
            game.makeAttempt();
            std::cout << "Without result! The game continues!\n\n";
        }
        catch (const OutOfFieldException& exc) {
            std::cerr << exc.what() << std::endl << std::endl;
        }
        catch (const FishException& exc) {
            std::cerr << exc.what() << " Attempts: " << attemptsCounter << std::endl;
            return 0;
        }
        catch (const BootException& exc) {
            std::cerr << exc.what() << std::endl;
            return 0;
        }
    }
}