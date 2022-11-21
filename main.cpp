#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <cmath>

void clear() {
    std::cin.clear();
    std::cin.ignore(256, '\n');
}

int64_t getValidInput(const std::string& prompt) {
    int64_t input;
    std::cout << prompt << std::endl;
    std::cin >> std::dec >> input;
    if (std::cin.fail()) {
        clear();
        std::cout << "Invalid input." << std::endl;
        return getValidInput(prompt);
    }
    if (input < 0 || input > 31) {
        clear();
        std::cout << "Input out of range." << std::endl;
        return getValidInput(prompt);
    }
    clear();
    return input;
}

struct Stat {
    std::string name;
    int64_t value;
};

void fatalError() {
    std::cout << "An unexpected error has occurred. The program will now shut down in 5 seconds." << std::endl;
    sleep(5);
    exit(2);
}

void error() {
    std::cout << "\nInvalid input! Please try again." << std::endl;
}

bool PIDCheck(int64_t pid) {
    if (pid < 0 || pid > 4294967295) {
        error();
        return false;
    }
    else
        return true;
}

int main() {
    int64_t pid, choice, height, hp = 0, atk = 0, def = 0, spa = 0, spd = 0, spe = 0;
    int64_t x = 0, y = 0, z = 0, key;
    int wurmple = 0;
    double cos = 2.54;
    bool pWrite = false, runtime = true;
    std::cout << "\nInsert your PID:\n";
    std::cin >> std::hex >> pid;
    while (!pWrite) {
        if (!PIDCheck(pid)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin >> pid;
        }
        else
            pWrite = true;
    }

    std::cout << "\nIs your pokemon a Wurmple?\n1) Yes\n2) No\n";
    std::cin >> wurmple;
    while (runtime) {
        switch(wurmple) {
            case 1:
                key = static_cast<int>((pid/65536)%10);
                std::cout << "Your wurmple will evolve into ";
                if (key >= 0 && key <= 4)
                    std::cout << "Silcoon\n";
                else if (key >= 5)
                    std::cout << "Cascoon\n";
                else
                    fatalError();
                system("pause");
                return 0;
            case 2:
                runtime = false;
                break;
            default:
                clear();
                std::cout << "Invalid input.\n";
                std::cin >> wurmple;
                break;
        }
    }

    runtime = true;
    std::vector<Stat> stats = {
            {"HP", hp},
            {"ATTACK", atk},
            {"DEFENSE", def},
            {"SPECIAL ATTACK", spa},
            {"SPECIAL DEFENSE", spd},
            {"SPEED", spe},
    };
    std::cout << "\nInsert your IVs:" << std::endl;
    for (auto& stat : stats) {
        stat.value = getValidInput(stat.name + ": ") % 16;
    }

    std::cout << "\nFor which pokemon you want to calculate the size?\n";
    std::cout << "\n1) Magikarp\n2) Remoraid\n3) Heracross\n4) Seedot/Lotad\n5) Barboach/Shroomish\n\n";
    std::cin >> choice;
    while (runtime) {
        switch(choice) {
            case 1:
                height = 9;
                runtime = false;
                break;
            case 2:
                height = 6;
                runtime = false;
                break;
            case 3:
                height = 15;
                runtime = false;
                break;
            case 4:
                height = 5;
                runtime = false;
                break;
            case 5:
                height = 4;
                runtime = false;
                break;
            default:
                error();
                break;
        }
    }

    unsigned p1 = pid % 256;
    unsigned p2 = (static_cast<int>(pid/256))%256;
    int64_t s = ((((atk^def)*hp)^p1)*256) + (((spa^spd)*spe)^p2);

    runtime = true;
    while (runtime) {
        switch(s) {
            case 0 ... 8:
                x = 290;
                y = 1;
                z = 0;
                runtime = false;
                break;
            case 9 ... 108:
                x = 300;
                y = 1;
                z = 10;
                runtime = false;
                break;
            case 109 ... 308:
                x = 400;
                y = 2;
                z = 110;
                break;
            case 309 ... 708:
                x = 500;
                y = 4;
                z = 310;
                runtime = false;
                break;
            case 709 ... 2708:
                x = 600;
                y = 20;
                z = 710;
                runtime = false;
                break;
            case 2709 ... 7708:
                x = 700;
                y = 50;
                z = 2710;
                runtime = false;
                break;
            case 7709 ... 17708:
                x = 800;
                y = 100;
                z = 7710;
                runtime = false;
                break;
            case 17709 ... 32708:
                x = 900;
                y = 150;
                z = 17710;
                runtime = false;
                break;
            case 32709 ... 47708:
                x = 1000;
                y = 150;
                z = 32710;
                runtime = false;
                break;
            case 47709 ... 57708:
                x = 1100;
                y = 100;
                z = 47710;
                runtime = false;
                break;
            case 57709 ... 62708:
                x = 1200;
                y = 50;
                z = 57710;
                runtime = false;
                break;
            case 62709 ... 64708:
                x = 1300;
                y = 20;
                z = 63710;
                runtime = false;
                break;
            case 64709 ... 65208:
                x = 1400;
                y = 5;
                z = 64710;
                runtime = false;
                break;
            case 65209 ... 65408:
                x = 1500;
                y = 2;
                z = 65210;
                runtime = false;
                break;
            case 65409 ... 65508:
                x = 1600;
                y = 1;
                z = 65410;
                runtime = false;
                break;
            case 65509 ... 65535:
                x = 1700;
                y = 1;
                z = 65510;
                runtime = false;
                break;
            default:
                fatalError();
                break;
        }
    }
    auto final = ((((s - z) / y) + x) * height / 100);
    auto val = static_cast<double>(final)/cos;
    auto iFinal = floorf(static_cast<float>(val)*10)/10;

    std::cout << "\nYour pokemon size is: " << std::dec << final << " cm/" << iFinal << " in\n\n";
    system("pause");
    return 0;
}