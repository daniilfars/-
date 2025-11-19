#include <iostream>
#include <cstdlib>
#include <ctime>

/*Суть игры: генерируется поле 5 х 5 с пятью минами. Игрок вводит координаты клетки, которую хочет открыть.
Если клетка не была заминирована(0), то выводится количество мин вокруг этой клетки. А если же была заминирована(-1),
То он проиграл, и выводится начальное поле с минами.
Игрок выиграет, если откроет все не заминированные клетки.
*/

enum {max_size = 5, mina = -1};

void print_pole(int (&pole)[max_size][max_size])
{
    //вывод поля
    for(int i=0; i < max_size; ++i) {
        for(int j=0; j < max_size; ++j) {
            std::cout << pole[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int get_count(int (&ar)[max_size][max_size], int x, int y)
{
    int count = 0;

    if(x-1 >= 0 && y-1 >= 0 && ar[x-1][y-1] == mina)
        count++;
    if(x-1 >= 0 && y+1 <= 4 && ar[x-1][y+1] == mina)
        count++;
    if(x+1 <= 4 && y-1 >= 0 && ar[x+1][y-1] == mina)
        count++;
    if(x+1 <= 4 && y+1 <= 4 && ar[x+1][y+1] == mina)
        count++;
    if(x-1 >= 0 && ar[x-1][y] == mina)
        count++;
    if(x+1 <= 4 && ar[x+1][y] == mina)
        count++;
    if(y-1 >= 0 && ar[x][y-1] == mina)
        count++;
    if(y+1 <= 4 && ar[x][y+1] == mina)
        count++;

    return count;
}

int main()
{
    std::srand(std::time(nullptr));

    int ar[max_size][max_size] = {0};
    int pole[max_size][max_size] = {0};
    bool flag = 0;

    //генерация мин
    for(int i=0; i < max_size; ++i) {
        int x_rand = rand() % max_size;
        int y_rand = rand() % max_size;
        if(ar[x_rand][y_rand] == mina) {
            i--;
            continue;
        }
        else {
            ar[x_rand][y_rand] = mina;
        }
    }

    std::cout << "The game's gist: we have generated field 5 x 5 with five mines. The player enters the coordinates of the cell they want to open. If the cell is unmined (0), the number of mines surrounding that cell is displayed. If it is mined (-1), then the player loses, and the initial field with mines is displayed. The player wins if they open all unmined cells." << std::endl << std::endl;

    for(int i=0; i < max_size * max_size - 5 && flag == 0; ++i) {
        int x, y, count_min;
        std::cout << "Write cell coordinates(x y): ";
        std::cin >> x >> y;
        std::cout << std::endl;
        x--;
        y--;

        while(ar[x][y] == 1) {
            std::cout << "This coordinates was open, write cell coordinates(x y): ";
            std::cin >> x >> y;
            std::cout << std::endl;
            x--;
            y--;
        }

        if(ar[x][y] == mina) {
            print_pole(ar);
            std::cout << "You lost";
            flag = 1;
        }
        else {
            count_min = get_count(ar, x, y);
            ar[x][y] = 1;
            pole[x][y] = count_min;
            print_pole(pole);
        }
    }

    return 0;
}