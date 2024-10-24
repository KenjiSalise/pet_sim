#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

const int MAX_HEALTH = 10;
const int MAX_ENERGY = 10;
const int MAX_REST = 10;
const int MAX_HUNGER = 10;
const int MAX_HAPPINESS = 10;
const int REST_THRESHOLD = 10;
const int HUNGER_THRESHOLD = 8;
const int HAPPINESS_THRESHOLD = 3;
const int HEALTH_THRESHOLD = 0;
const int SLEEP_TIME_MS = 1500;
const int ELLIPSIS_TIME_MS = 2500 / 3;

bool isAlive(int& petHealth, int& petHappiness, int& petEnergy, int& petRest, int& petHunger);
string petFace(int& petHealth, int& petHappiness, int& petEnergy, int& petRest, int& petHunger, bool& isPetSleep);
bool isPetSleep(string& petName, bool& isFalcon);
void check_Pet(int& petHealth, int& petHappiness, int& petEnergy, int& petRest, int& petHunger, string& petName, bool& isPetSleep);
void playMode(int& petHealth, int& petHappiness, int& petEnergy, int& petRest, int& petHunger, string& petName, double& moneyBalance);
void arcadePlace(double& moneyBalance, int& petHappiness, int& petEnergy, int& petHunger, string& petName);
void playPlace(double& moneyBalance, int& petHappiness, int& petEnergy, int& petHunger);
void homePlay(int& petHappiness, int& petEnergy, int& petHunger);
void workMode(int& petHealth, int& petHappiness, int& petEnergy, int& petRest, int& petHunger, string& petName, double& moneyBalance);
void feedMode(int& petHealth, int& petHappiness, int& petEnergy, int& petRest, int& petHunger, string& petName, double& moneyBalance);

void ellipsis();


int main() {
    cout.setf(ios::fixed);
    cout.precision(2);

    double moneyBalance = 10000.00;
    string gameName;
    string petName;
    int petHealth = MAX_HEALTH;
    int petHappiness = MAX_HAPPINESS * 0.5;
    int petEnergy = MAX_ENERGY;
    int petRest = MAX_REST - MAX_REST;
    int petHunger = MAX_HUNGER * 0.5;
    string petStatus;
    bool sleep_State = false;
    bool isFalcon = false;
    char choice;
    bool gameSelection = true;
    int gameState;

    
    cout << "[P]et simulator or [A]dopt a child simulator\n> ";
    while (gameSelection) {
        cin >> choice;
        getline(cin, petName);
        switch (choice) {
        case 'P':
        case 'p':
            cout << "Enter pet name: ";
            getline(cin, petName);
            if (petName == "Captain Falcon")
                isFalcon = true;
            gameName = "Tamagotchi";
            gameSelection = false;
            break;
        case 'A':
        case 'a':
            cout << "Enter name of child: ";
            getline(cin, petName);
            if (petName == "Captain Falcon")
                isFalcon = true;
            gameName = "Teaching Feeling";
            gameSelection = false;
            break;
        default:
            cout << "Invalid input, try again \n> ";
         }
    }
    while (isAlive(petHealth, petHappiness, petEnergy, petRest, petHunger)) {
        if (sleep_State == false) {

            cout << "\n\t\t\t "<< gameName <<"\n";
            cout << "==================================================================" << endl;
            cout << "Money: " << moneyBalance << " JPY\n";
            cout << "[C]heck " << petName << "'s status\n";
            cout << "[P]lay with " << petName << endl;
            cout << "Put " << petName << " to [S]leep" << endl;
            cout << "[F]eed " << petName << endl;
            cout << "[W]ork for money\n";
            cout << "==================================================================";
            cout << endl << "> ";
            cin >> choice;
            switch (choice) {
            case 'C':
            case 'c':
                check_Pet(petHealth, petHappiness, petEnergy, petRest, petHunger, petName, sleep_State);
                break;
            case 'P':
            case 'p':
                playMode(petHealth, petHappiness, petEnergy, petRest, petHunger, petName, moneyBalance);
                break;
            case 'S':
            case 's':
                sleep_State = isPetSleep(petName, isFalcon);
                break;
            case 'F':
            case 'f':
                feedMode(petHealth, petHappiness, petEnergy, petRest, petHunger, petName, moneyBalance);

                break;
            case 'W':
            case 'w':
                workMode(petHealth, petHappiness, petEnergy, petRest, petHunger, petName, moneyBalance);
                break;
            default:
                cout << "Invalid input, try again";
                continue;
            }
        }
        else {
            petRest++;
            petEnergy += 2;
            petHunger++;
            petHappiness--;

            cout << endl << "==================================================================" << endl;
            cout << "Money: " << moneyBalance << " JPY\n";
            cout << "[W]ake up " << petName << endl;
            cout << "[L]et " << petName << "sleep\n";
            cout << "==================================================================" << endl;
            cin >> choice;
            switch (choice) {
            case 'W':
            case 'w':
                cout << "==================================================================" << endl;
                cout << "You woke up " << petName << endl;
                cout << "(u.u )..." << endl;
                cout << "==================================================================" << endl;
                Sleep(SLEEP_TIME_MS);
                sleep_State = false;
                break;
            case 'L':
            case 'l':
                sleep_State = true;
                break;
            default:
                cout << "Invalid input, try again";
                continue;
            }
        }

    }
}

void ellipsis() {
    for (int i = 0; i < 3; i++) {
        cout << '.' << flush;
        Sleep(ELLIPSIS_TIME_MS);
    }
    cout << endl;
}

string petFace(int& petHealth, int& petHappiness, int& petEnergy, int& petRest, int& petHunger, bool& isPetSleep) {
    int petState;
    if (petHappiness >= 6 && petHappiness <= 8 && petHunger <= 5 && isPetSleep == false && petHealth >= 5 && petEnergy >= 5) {
        petState = 1;
    }
    else if (petHappiness >= 8 && petHunger <= 5 && isPetSleep == false && petHealth >= 5 && petEnergy >= 5) {
        petState = 2;
    }
    else if (petHappiness <= 4 && petHunger <= 5 && isPetSleep == false && petHealth >= 5) {
        petState = 3;
    }
    else if (petHappiness <= 1 && petHappiness <= 2 && petHunger <= 5 && isPetSleep == false && petHealth >= 5 && petEnergy >= 5) {
        petState = 4;
    }
    else if (petHunger >= 6 && petHunger <= 7 && isPetSleep == false && petHealth >= 5 && petEnergy >= 5) {
        petState = 5;
    }
    else if (petHunger >= 8 && petHealth >= 5 && isPetSleep == false && petEnergy >= 5) {
        petState = 6;
    }
    else if (petEnergy <= 4 && petEnergy >= 3 && isPetSleep == false && petHealth >= 5) {
        petState = 7;
    }
    else if (petEnergy <= 2 && isPetSleep == false) {
        petState = 8;
    }
    else if (isPetSleep == true) {
        petState = 9;
    }
    else if (petHealth <= 4 && isPetSleep == false) {
        petState = 10;
    }
    else {
        petState = 0;
    }

    switch (petState) {
    case 0:
        return "(*^▽^*)　";
        break;
    case 1:
        return "（。＾▽＾）";
        break;
    case 2:
        return  "ヾ(≧ ▽ ≦)ゝ";
        break;
    case 3:
        return  "（＞人＜；）";
        break;
    case 4:
        return  "(≧﹏ ≦)";
        break;
    case 5:
        return  "(。__ 。*)";
        break;
    case 6:
        return "~(>_<。)＼";
        break;
    case 7:
        return "(u.u )...";
        break;
    case 8:
        return "(￣o￣) . z Z";
        break;
    case 9:
        return "(_　_)。゜zｚＺ";
        break;
    case 10:
        return "o(TヘTo)";
        break;
    }

}
bool isAlive(int& petHealth, int& petHappiness, int& petEnergy, int& petRest, int& petHunger) {
    if (petHappiness > MAX_HAPPINESS) {
        petHappiness = MAX_HAPPINESS;
    }
    if (petEnergy > MAX_ENERGY) {
        petEnergy = MAX_ENERGY;
    }
    if (petHealth > MAX_HEALTH) {
        petHealth = MAX_HEALTH;
    }
    if (petRest > MAX_REST) {
        petRest = MAX_REST;
    }
    if (petHunger > MAX_HUNGER) {
        petHunger = MAX_HUNGER;
    }
    if (petHappiness <= HAPPINESS_THRESHOLD) {
        petHealth -= 1;
    }
    if (petHunger >= HUNGER_THRESHOLD) {
        petHealth -= 1;
    }
    if (petRest >= REST_THRESHOLD) {
        petHealth -= 1;
    }
    return petHealth > HEALTH_THRESHOLD;
}
void check_Pet(int& petHealth, int& petHappiness, int& petEnergy, int& petRest, int& petHunger, string& petName, bool& isPetSleep) {
    string petStatus = petFace(petHealth, petHappiness, petEnergy, petRest, petHunger, isPetSleep);
    cout << "==================================================================" << endl;
    cout << petName << endl;
    cout << "Pet HP: " << petHealth << "/" << MAX_HEALTH << "\n";
    cout << "Pet Energy: " << petEnergy << "/" << MAX_ENERGY << "\n";
    cout << "Pet Rest: " << petRest << "/" << MAX_REST << "\t\t\t" << petStatus << "\n";
    cout << "Pet Hunger: " << petHunger << "/" << MAX_HUNGER << "\n";
    cout << "Pet Happiness: " << petHappiness << "/" << MAX_HAPPINESS << "\n";
    cout << "==================================================================" << endl << endl;
}
bool isPetSleep(string& petName, bool& isFalcon) {
    cout << "==================================================================" << endl;
    cout << petName << " is now sleeping \n";
    cout << "(_　_)。゜zｚＺ\n";
    if (isFalcon) {
        cout << "SHOW ME YA MOVES!\n";
    }
    cout << "==================================================================" << endl << endl;
    return true;
}
void playMode(int& petHealth, int& petHappiness, int& petEnergy, int& petRest, int& petHunger, string& petName, double& moneyBalance) {
    char choice;
    while (true) {
        cout << endl << "==================================================================" << endl;
        cout << "Where do you want to play with " << petName << "?\n";
        cout << "[G]ame center \n";
        cout << "[P]lay Place\n";
        cout << "[H]ome\n";
        cout << "[B]ack\n";
        cout << "==================================================================" << endl << "> ";
        cin >> choice;
        switch (choice) {
        case 'G':
        case 'g':
            arcadePlace(moneyBalance, petHappiness, petEnergy, petHunger, petName);
            break;
        case 'P':
        case 'p':
            playPlace(moneyBalance, petHappiness, petEnergy, petHunger);
            break;
        case 'H':
        case 'h':
            homePlay(petHappiness, petEnergy, petHunger);
            break;
        case 'B':
        case 'b':
            return;
            break;
        default:
            cout << "Invalid input, try again";
            Sleep(SLEEP_TIME_MS);
            continue;

        }

    }
}
void arcadePlace(double& moneyBalance, int& petHappiness, int& petEnergy, int& petHunger, string& petName) {
    bool stillPlaying = true;
    char choice;
    int homeEnergy = petEnergy * 0.9;
    int id;
    const int KONBINI_FOOD_COST = 500;
    const int GAME_COUNT = 9;
    const string GAME_NAMES[] = {
        "Kirby Air Ride",
        "Mario Kart",
        "Densha de Go Go Go",
        "Taiko no Tatsujin",
        "Pac-Man",
        "Mai Mai",
        "Tekken",
        "Street Fighter 7",
        "Time Crisis",
    };
    const string GAME_OPTIONS[] = {
        "[K]irby Air Ride",
        "Mario Kart [A]rcade",
        "[D]ensha de Go Go Go",
        "[T]aiko no Tatsujin",
        "[P]ac-Man",
        "[M]ai Mai",
        "T[e]kken",
        "[S]treet Fighter 7",
        "Time [C]risis",
    };
    const int GAME_HAPPINESS_VALUES[] = {
        4,
        3,
        10,
        10,
        5,
        8,
        3,
        2,
        10
    };
    const int GAME_COSTS[] = {
        400,
        200,
        500,
        200,
        200,
        200,
        200,
        200,
        200
    };

    while (stillPlaying) {
        cout << endl << "==================================================================" << endl;
        cout << "Money: " << moneyBalance << " JPY\n";
        cout << "What game should " << petName << " play?\n";
        for (int i = 0; i < GAME_COUNT; i++) {
            cout << GAME_OPTIONS[i] << " (" << GAME_COSTS[i] << " JPY)" << endl;
        }
        cout << "Go [H]ome";
        cout << endl << "==================================================================" << endl << "> ";
        cin >> choice;
        switch (choice) {
        case 'K':
        case 'k':
            id = 0;
            break;
        case 'A':
        case 'a':
            id = 1;
            break;
        case 'D':
        case 'd':
            id = 2;
            break;
        case 'T':
        case 't':
            id = 3;
            break;
        case 'P':
        case 'p':
            id = 4;
            break;
        case 'M':
        case 'm':
            id = 5;
            break;
        case 'E':
        case 'e':
            id = 6;
            break;
        case 'S':
        case 's':
            id = 7;
            break;
        case 'C':
        case 'c':
            id = 8;
            break;
        case 'H':
        case 'h':
            stillPlaying = false;
            break;
        default:
            cout << "Invalid input, try again";
            ellipsis();
            continue;
        }
        if (!stillPlaying) {
            break;
        }
        if (GAME_COSTS[id] > moneyBalance) {
            cout << endl << "==================================================================" << endl;
            cout << "Insufficient money balance, " << petName << " cannot play " << GAME_NAMES[id] << ", please try again\n";
            cout << endl << "==================================================================" << endl;
        }
        else {
            cout << endl << "==================================================================" << endl;
            cout << petName << " enjoyed playing " << GAME_NAMES[id] << endl;
            petHappiness += GAME_HAPPINESS_VALUES[id];
            moneyBalance -= GAME_COSTS[id];
            cout << endl << "==================================================================" << endl;
        }
    }
    cout << "Walking home";
    ellipsis();
    petEnergy -= homeEnergy;
    petHunger = HUNGER_THRESHOLD - 1;
    while (true) {
        cout << endl << "==================================================================" << endl;
        cout << petName << " is very tired and hungry\n";
        cout << petName << "'s energy -" << homeEnergy << endl;
        cout << petName << "'s hunger +" << petHunger << endl;
        cout << "Go to the nearest konbini to replenish some energy and hunger? (" << KONBINI_FOOD_COST << " JPY)\n";
        cout << "[Y]/[N]\n";
        cout << endl << "==================================================================" << endl << "> ";
        cin >> choice;
        switch (choice) {
        case 'Y':
        case 'y':
            if (KONBINI_FOOD_COST < moneyBalance) {
                petHunger -= 2;
                cout << endl << "==================================================================" << endl;
                cout << "You bought " << petName << " some food\n";
                homeEnergy = MAX_ENERGY * 0.4;
                petEnergy += homeEnergy;
                cout << petName << "'s energy +" << homeEnergy;
                cout << petName << "'s hunger +" << petHunger << endl;
                cout << "Money balance -" << KONBINI_FOOD_COST << " JPY";
                cout << endl << "==================================================================" << endl;
                return;
            }
            else {
                cout << endl << "==================================================================" << endl;
                cout << "You cannot afford that\n";
                cout << endl << "==================================================================" << endl;
                return;
            }
            Sleep(SLEEP_TIME_MS);
            break;
        case 'N':
        case 'n':
            cout << endl << "==================================================================" << endl;
            cout << "You go home with " << petName << " after a fun day at the arcade";
            cout << endl << "==================================================================" << endl;
            return;
            Sleep(SLEEP_TIME_MS);
        default:
            cout << "Invalid input, try again";
            continue;
        }
        return;
    }
}
void playPlace(double& moneyBalance, int& petHappiness, int& petEnergy, int& petHunger) {

}
void homePlay(int& petHappiness, int& petEnergy, int& petHunger) {

}
void workMode(int& petHealth, int& petHappiness, int& petEnergy, int& petRest, int& petHunger, string& petName, double& moneyBalance) {
    cout << endl << "==================================================================" << endl;
    cout << "You worked for 1 hour, you get 10000 JPY\n";
    moneyBalance += 10000;
    petHappiness--;
    petHunger++;
    cout << "==================================================================" << endl;
}
void feedMode(int& petHealth, int& petHappiness, int& petEnergy, int& petRest, int& petHunger, string& petName, double& moneyBalance) {
    cout << endl << "==================================================================" << endl;
    cout << "You took " << petName << " to a restaurant\n";
    cout << "Money balance -2000 JPY\n";
    cout << petName << " hunger -5\n";
    moneyBalance -= 2000;
    petHunger -= 5;
    cout << "==================================================================" << endl;
}
