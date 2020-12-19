#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
static int maxRow = 7;
std::string sixTimesSpaces = "      ";

void exitFunction(std::ofstream& outputFile){
    outputFile << "\nexit" << endl;
    outputFile << "\n****************************************" << endl;
    outputFile << "\nGame Over!\n";
}

void changeMaxRow(string tableauArea[52][7]){
    bool check = false;
    bool checkRow_1 = false;
    bool checkRow_2 = false;
    bool checkRow_3 = false;
    bool checkRow_4 = false;
    bool checkRow_5 = false;
    bool checkRow_6 = false;
    bool checkRow_7 = false;
    int i = 18;

    while(!check){
        for (int j = 0; j < 7; j++){
            if(j == 0){
                if(tableauArea[i][j].empty()) {
                    checkRow_1 = true;
                }
            }else if(j == 1){
                if(tableauArea[i][j].empty()) {
                    checkRow_2 = true;
                }
            }else if(j == 2){
                if(tableauArea[i][j].empty()) {
                    checkRow_3 = true;
                }
            }else if(j == 3){
                if(tableauArea[i][j].empty()) {
                    checkRow_4 = true;
                }
            }else if(j == 4){
                if(tableauArea[i][j].empty()) {
                    checkRow_5 = true;
                }
            }else if(j == 5){
                if(tableauArea[i][j].empty()) {
                    checkRow_6 = true;
                }
            }else if(j == 6){
                if(tableauArea[i][j].empty()) {
                    checkRow_7 = true;
                }
            }
        }

        if(checkRow_1 and checkRow_2 and checkRow_3 and checkRow_4 and checkRow_5 and checkRow_6 and checkRow_7) {
            i--;
            checkRow_1 = false;
            checkRow_2 = false;
            checkRow_3 = false;
            checkRow_4 = false;
            checkRow_5 = false;
            checkRow_6 = false;
            checkRow_7 = false;
        }else{
            maxRow = i + 1;
            check = true;
        }
    }
}

void checkIfNeedPreviousWaste(string waste[24]){
    int remaining = 1;
    int repeat = 1;
    if(waste[0].empty() and waste[1].empty() and waste[2].empty()){
        if(!waste[3].empty()){
            int l = 24;
            while(waste[l-1].empty()){
                l--;
            }
            for (int o = 3; o < l; o++) {
                waste[o-1] = waste[o];
            }
            waste[l-1].clear();
        }

    }

}

void checkIfInvalidMove(string tableauArea[52][7], string foundationArray[13], int row, int column, std::ofstream& outputFile){
    if(foundationArray[12].empty()){
        int tempNext = stoi(tableauArea[row][column].substr(1,2));
        if(tempNext == 01){
            foundationArray[12] = tableauArea[row][column];
            tableauArea[row][column].clear();

        }else{
            outputFile << "\nInvalid Move!\n";
        }
    }else{
        for(int i = 11; i >= 0; i--) {
            if (foundationArray[i].empty()) {
                int tempFoundation = stoi(foundationArray[i+1].substr(1, 2));
                int tempNext = stoi(tableauArea[row][column].substr(1, 2));
                if ((tempFoundation + 1) == tempNext) {
                    foundationArray[i] = tableauArea[row][column];
                    tableauArea[row][column].clear();
                    break;
                }else{
                    outputFile << "\nInvalid Move!\n";
                    break;
                }
            }
        }
    }
}

void checkIfInvalidMove(string tableauArea[52][7], string foundationArray[13], int indexOfWaste, string waste[24], std::ofstream& outputFile){
    if(foundationArray[12].empty()){
        int tempNext = stoi(waste[indexOfWaste].substr(1,2));
        if(tempNext == 01){
            foundationArray[12] = waste[indexOfWaste];
            waste[indexOfWaste].clear();
        }else{
            outputFile << "\nInvalid Move!\n";
        }
    }else{
        for(int i = 11; i >= 0; i--) {
            if (foundationArray[i].empty()) {
                int tempFoundation = stoi(foundationArray[i+1].substr(1, 2));
                int tempNext = stoi(waste[indexOfWaste].substr(1, 2));
                if ((tempFoundation + 1) == tempNext) {
                    foundationArray[i] = waste[indexOfWaste];
                    waste[indexOfWaste].clear();
                    break;
                }else{
                    outputFile << "\nInvalid Move!\n";
                    break;
                }
            }
        }
    }
}

void checkIfInvalidMove(string tableauArea[52][7], int column1, int column2, int numberOfPile, std::ofstream& outputFile){
    int tempo = numberOfPile;
    if(tableauArea[0][column2].empty()){
        if(tableauArea[0][column1].empty()){
            outputFile << "\nInvalid Move!\n";
        }else {
            int i = 0;
            int j = 0;

            while (!tableauArea[i+1][column1].empty()) {
                i++;
            }
            if(numberOfPile != 0){
                if(tableauArea[i][column1].substr(1,2) == "13"){
                    while(tempo >= 0){
                        tableauArea[j][column2] = tableauArea[i - numberOfPile][column1];
                        tableauArea[i - numberOfPile][column1].clear();
                        j++;
                        i++;
                        tempo--;
                    }
                }else {
                    outputFile << "\nInvalid Move!\n";
                }

            }
            if(tableauArea[i][column1].substr(1,2) == "13" && numberOfPile == 0){
                tableauArea[0][column2] = tableauArea[i][column1];
                tableauArea[i][column1].clear();
            }else{
                outputFile << "\nInvalid Move!\n";
            }
        }
    }else if(!tableauArea[0][column2].empty()){
        if(numberOfPile != 0){
            int j = 0;
            int i = 0;
            while (!tableauArea[i+1][column1].empty()) {
                i++;
            }
            while(!tableauArea[j+1][column2].empty()){
                j++;
            }
            if(tableauArea[j][column2].substr(0,1) == "H" or tableauArea[j][column2].substr(0,1) == "D"){
                if( ((stoi(tableauArea[j][column2].substr(1,2))-1) == stoi(tableauArea[i-numberOfPile][column1].substr(1,2))) and (tableauArea[i-numberOfPile][column1].substr(0,1) == "S" or tableauArea[i-numberOfPile][column1].substr(0,1) == "C") ){
                    while(tempo >= 0){
                        tableauArea[j+1][column2] = tableauArea[i - numberOfPile][column1];
                        tableauArea[i - numberOfPile][column1].clear();
                        j++;
                        i++;
                        tempo--;
                    }
                }else {
                    outputFile << "\nInvalid Move!\n";
                }
            }else if(tableauArea[j][column2].substr(0,1) == "S" or tableauArea[j][column2].substr(0,1) == "C"){
                if( ((stoi(tableauArea[j][column2].substr(1,2))-1) == stoi(tableauArea[i-numberOfPile][column1].substr(1,2))) and (tableauArea[i-numberOfPile][column1].substr(0,1) == "D" or tableauArea[i-numberOfPile][column1].substr(0,1) == "H") ){
                    while(tempo >= 0){
                        tableauArea[j+1][column2] = tableauArea[i - numberOfPile][column1];
                        tableauArea[i - numberOfPile][column1].clear();
                        j++;
                        i++;
                        tempo--;
                    }
                }else {
                    outputFile << "\nInvalid Move!\n";
                }
            }else {
                outputFile << "\nInvalid Move!\n";
            }
        }else if(numberOfPile == 0) {
            int i = 0;
            int j = 0;
            while (!tableauArea[i + 1][column1].empty()) {
                i++;
            }
            while (!tableauArea[j + 1][column2].empty()) {
                j++;
            }
            if (tableauArea[j][column2].substr(0, 1) == "H" or tableauArea[j][column2].substr(0, 1) == "D") {
                if (((stoi(tableauArea[j][column2].substr(1, 2)) - 1) == stoi(tableauArea[i][column1].substr(1, 2))) and
                    (tableauArea[i][column1].substr(0, 1) == "S" or tableauArea[i][column1].substr(0, 1) == "C")) {
                    tableauArea[j + 1][column2] = tableauArea[i][column1];
                    tableauArea[i][column1].clear();
                }else {
                    outputFile << "\nInvalid Move!\n";
                }
            } else if (tableauArea[j][column2].substr(0, 1) == "S" or tableauArea[j][column2].substr(0, 1) == "C") {
                if (((stoi(tableauArea[j][column2].substr(1, 2)) - 1) == stoi(tableauArea[i][column1].substr(1, 2))) and
                    (tableauArea[i][column1].substr(0, 1) == "D" or tableauArea[i][column1].substr(0, 1) == "H")) {
                    tableauArea[j + 1][column2] = tableauArea[i][column1];
                    tableauArea[i][column1].clear();
                }else {
                    outputFile << "\nInvalid Move!\n";
                }
            } else {
                outputFile << "\nInvalid Move!\n";
            }
        }else{
            outputFile << "\nInvalid Move!\n";
        }
    }
}

void checkIfInvalidMove(string tableauArea[52][7], int wasteIndex, string waste[24], int column2, std::ofstream& outputFile){
    int tempo = 0;
    if(tableauArea[0][column2].empty()){
        int i = 0;
        if(waste[wasteIndex].substr(1,2) == "13"){
            tableauArea[0][column2] = waste[wasteIndex];
            waste[wasteIndex].clear();
        }else{
            outputFile << "\nInvalid Move!\n";
        }

    }else if(!tableauArea[0][column2].empty()){
        int j = 0;
        while (!tableauArea[j + 1][column2].empty()) {
            j++;
        }
        if (tableauArea[j][column2].substr(0, 1) == "H" or tableauArea[j][column2].substr(0, 1) == "D") {
            if (((stoi(tableauArea[j][column2].substr(1, 2)) - 1) == stoi(waste[wasteIndex].substr(1, 2))) and (waste[wasteIndex].substr(0, 1) == "S" or waste[wasteIndex].substr(0, 1) == "C")) {
                tableauArea[j + 1][column2] = waste[wasteIndex];
                waste[wasteIndex].clear();
            }else {
                outputFile << "\nInvalid Move!\n";
            }
        } else if (tableauArea[j][column2].substr(0, 1) == "S" or tableauArea[j][column2].substr(0, 1) == "C") {
            if (((stoi(tableauArea[j][column2].substr(1, 2)) - 1) == stoi(waste[wasteIndex].substr(1, 2))) and (waste[wasteIndex].substr(0, 1) == "D" or waste[wasteIndex].substr(0, 1) == "H")) {
                tableauArea[j + 1][column2] = waste[wasteIndex];
                waste[wasteIndex].clear();
            }else {
                outputFile << "\nInvalid Move!\n";
            }
        } else {
            outputFile << "\nInvalid Move!\n";
        }
    }else{
        outputFile << "\nInvalid Move!\n";
    }
}

void printCommand(string commandString[], int n, std::ofstream& outputFile){
    outputFile << "\n";

    for(int i=0;i<n;i++) {
        outputFile << commandString[i] << " ";
    }
    outputFile << "\n";
}

void printInstantTableStatue(string tableauArea[52][7], string stock[24], string hearts[13], string diamonds[13], string clubs[13], string spades[13], string waste[24], bool open_1[1], bool open_2[2], bool open_3[3], bool open_4[4], bool open_5[5], bool open_6[6], std::ofstream& outputFile){
    bool isGameOwer = true;
    outputFile << "\n****************************************\n\n";
    if(stock[0].empty()){
        outputFile << "___ ";
    }else{
        outputFile << "@@@ ";
    }
    for(int i = 2; i >= 0; i--){
        if(waste[i].empty()){
            outputFile << "___ ";
        }else {
            outputFile << waste[i] << " ";
        }
    }
    outputFile << sixTimesSpaces;
    if(hearts[12].empty()){
        outputFile << "___ ";
    }else{
        for(int i = 0; i < 13; i++){
            if(!hearts[i].empty()){
                outputFile << hearts[i] << " ";
                break;
            }
        }
    }if(diamonds[12].empty()){
        outputFile << "___ ";
    }else{
        for(int i = 0; i < 13; i++){
            if(!diamonds[i].empty()){
                outputFile << diamonds[i] << " ";
                break;
            }
        }
    }if(spades[12].empty()){
        outputFile << "___ ";
    }else{
        for(int i = 0; i < 13; i++){
            if(!spades[i].empty()){
                outputFile << spades[i] << " ";
                break;
            }
        }
    }if(clubs[12].empty()){
        outputFile << "___\n\n";
    }else{
        for(int i = 0; i < 13; i++){
            if(!clubs[i].empty()){
                outputFile << clubs[i] << "\n\n";
                break;
            }
        }
    }for(int i = 0; i < maxRow; i++){
        for(int j = 0; j < 7; j++) {
            if(tableauArea[i][j].empty()){
                if(j == 6){
                    outputFile << sixTimesSpaces << endl;
                }else {
                    outputFile << sixTimesSpaces;
                }
            }else if (i == 0){
                isGameOwer = false;
                if(j == 0){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 1){
                    if(open_1[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 2){
                    if (open_2[i]) {
                        outputFile << tableauArea[i][j] << "   ";
                    } else {
                        outputFile << "@@@   ";
                    }
                }else if(j == 3){
                    if(open_3[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 4){
                    if(open_4[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 5){
                    if(open_5[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 6){
                    if(open_6[i]){
                        outputFile << tableauArea[i][j] << "\n";
                    }else{
                        outputFile << "@@@\n";
                    }
                }
            }else if(i == 1){
                if(j == 0){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 1){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 2){
                    if (open_2[i]) {
                        outputFile << tableauArea[i][j] << "   ";
                    } else {
                        outputFile << "@@@   ";
                    }
                }else if(j == 3){
                    if(open_3[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 4){
                    if(open_4[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 5){
                    if(open_5[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 6){
                    if(open_6[i]){
                        outputFile << tableauArea[i][j] << "\n";
                    }else{
                        outputFile << "@@@\n";
                    }
                }
            }else if(i == 2){
                if(j == 0){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 1){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 2){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 3){
                    if(open_3[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 4){
                    if(open_4[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 5){
                    if(open_5[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 6){
                    if(open_6[i]){
                        outputFile << tableauArea[i][j] << "\n";
                    }else{
                        outputFile << "@@@\n";
                    }
                }
            }else if(i == 3){
                if(j == 0){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 1){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 2){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 3){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 4){
                    if(open_4[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 5){
                    if(open_5[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 6){
                    if(open_6[i]){
                        outputFile << tableauArea[i][j] << "\n";
                    }else{
                        outputFile << "@@@\n";
                    }
                }
            }else if(i == 4){
                if(j == 0){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 1){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 2){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 3){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 4){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 5){
                    if(open_5[i]){
                        outputFile << tableauArea[i][j] << "   ";
                    }else{
                        outputFile << "@@@   ";
                    }
                }else if(j == 6){
                    if(open_6[i]){
                        outputFile << tableauArea[i][j] << "\n";
                    }else{
                        outputFile << "@@@\n";
                    }
                }
            }else if(i == 5){
                if(j == 0){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 1){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 2){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 3){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 4){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 5){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 6){
                    if(open_6[i]){
                        outputFile << tableauArea[i][j] << "\n";
                    }else{
                        outputFile << "@@@\n";
                    }
                }
            }else if(i >= 6){
                if(j == 0){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 1){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 2){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 3){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 4){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 5){
                    outputFile << tableauArea[i][j] << "   ";
                }else if(j == 6){
                    outputFile << tableauArea[i][j] << "\n";
                }
            }
        }
    }
    if(isGameOwer){
        outputFile << "\n\n****************************************\n\nYou Win!\n\nGame Ower!\n";
    }

}

void moveFunction(string commandString[], string tableauArea[52][7], string stock[24], string hearts[13], string diamonds[13], string clubs[13], string spades[13], string waste[24], bool open_1[1], bool open_2[2], bool open_3[3], bool open_4[4], bool open_5[5], bool open_6[6], std::ofstream& outputFile){
    if(commandString[1] == "to"){
        if(commandString[3] == "pile"){
            int temporary = stoi(commandString[4]);
            for(int i = 0; i < maxRow ; i++){
                if(tableauArea[i][temporary].empty()){
                    printCommand(commandString,commandString->size() + 1, outputFile);
                    outputFile << "\nInvalid Move!\n";
                    printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
                    break;
                }else if(!tableauArea[i+1][temporary].empty()){
                    continue;
                }else{
                    if(tableauArea[i][temporary].substr(0,1) == "H"){
                        printCommand(commandString, commandString->size() + 1, outputFile);
                        checkIfInvalidMove(tableauArea, hearts, i, temporary, outputFile);
                        changeMaxRow(tableauArea);
                        printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
                        break;
                    }else if(tableauArea[i][temporary].substr(0,1) == "D"){
                        printCommand(commandString, commandString->size() + 1, outputFile);
                        checkIfInvalidMove(tableauArea, diamonds, i, temporary, outputFile);
                        changeMaxRow(tableauArea);
                        printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
                        break;
                    }else if(tableauArea[i][temporary].substr(0,1) == "C"){
                        printCommand(commandString, commandString->size() + 1, outputFile);
                        checkIfInvalidMove(tableauArea, clubs, i, temporary, outputFile);
                        changeMaxRow(tableauArea);
                        printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
                        break;
                    }else if(tableauArea[i][temporary].substr(0,1) == "S"){
                        printCommand(commandString, commandString->size() + 1, outputFile);
                        checkIfInvalidMove(tableauArea, spades, i, temporary, outputFile);
                        changeMaxRow(tableauArea);
                        printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
                        break;
                    }
                }
            }
        }else if(commandString[3] == "waste") {
            int i = 0;
            while(waste[i].empty()){
                i++;
            }
            if (waste[i].substr(0, 1) == "H") {
                printCommand(commandString, commandString->size() + 1, outputFile);
                checkIfInvalidMove(tableauArea, hearts, i, waste, outputFile);
                checkIfNeedPreviousWaste(waste);
                changeMaxRow(tableauArea);
                printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
            } else if (waste[i].substr(0, 1) == "D") {
                printCommand(commandString, commandString->size() + 1, outputFile);
                checkIfInvalidMove(tableauArea, diamonds, i, waste, outputFile);
                checkIfNeedPreviousWaste(waste);
                changeMaxRow(tableauArea);
                printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
            } else if (waste[i].substr(0, 1) == "C") {
                printCommand(commandString, commandString->size() + 1, outputFile);
                checkIfInvalidMove(tableauArea, clubs, i, waste, outputFile);
                checkIfNeedPreviousWaste(waste);
                changeMaxRow(tableauArea);
                printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
            } else if (waste[i].substr(0, 1) == "S") {
                printCommand(commandString, commandString->size() + 1, outputFile);
                checkIfInvalidMove(tableauArea, spades, i, waste, outputFile);
                checkIfNeedPreviousWaste(waste);
                changeMaxRow(tableauArea);
                printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
            }
        }else{
            outputFile << "\nInvalid Move!\n";
        }
    }else if(commandString[1] == "waste"){
        printCommand(commandString, commandString->size() + 1, outputFile);
        int i = 0;
        int temporary = stoi(commandString[2]);
        while(waste[i].empty()){
            i++;
            if(i >= 3){
            }
        }
        checkIfInvalidMove(tableauArea, i, waste, temporary, outputFile);
        checkIfNeedPreviousWaste(waste);
        changeMaxRow(tableauArea);
        printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
    }else if(commandString[1] == "pile"){
        int movingPileNum = stoi(commandString[2]);
        int howManyPile = stoi(commandString[3]);
        int toWhere = stoi(commandString[4]);
        printCommand(commandString, commandString->size() + 1, outputFile);
        checkIfInvalidMove(tableauArea, movingPileNum, toWhere, howManyPile, outputFile);
        changeMaxRow(tableauArea);
        printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
    }else if(commandString[1] == "foundation"){
        if(commandString[2] == "0"){
            printCommand(commandString, commandString->size() + 1, outputFile);
            int toWhichColumn = stoi(commandString[3]);
            int i = 0;
            int j = 0;
            while(hearts[i].empty()){
                i++;
                if(i >= 12){break;}
            }
            while(!tableauArea[j][toWhichColumn].empty()){
                j++;
                if(j >= 12){break;}
            }
            if(tableauArea[j-1][toWhichColumn].substr(0,1) == "S" or tableauArea[j-1][toWhichColumn].substr(0,1) == "C"){

                if( (stoi(hearts[i].substr(1,2)) +1) == (stoi(tableauArea[j-1][toWhichColumn].substr(1,2))) ){
                    tableauArea[j][toWhichColumn] = hearts[i];
                    hearts[i].clear();

                }else{
                    outputFile << "\nInvalid Move!\n";
                }
            }else if(tableauArea[j][toWhichColumn].empty() and hearts[i].substr(1,2) == "13"){
                tableauArea[j][toWhichColumn] = hearts[i];
                hearts[i].clear();
            }else{
                outputFile << "\nInvalid Move!\n";
            }
            changeMaxRow(tableauArea);
            printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);

        }else if(commandString[2] == "1"){
            printCommand(commandString, commandString->size() + 1, outputFile);
            int toWhichColumn = stoi(commandString[3]);
            int i = 0;
            int j = 0;
            while(diamonds[i].empty()){
                i++;
                if(i >= 12){break;}
            }
            while(!tableauArea[j][toWhichColumn].empty()){
                j++;
                if(j >= 12){break;}
            }
            if(tableauArea[j-1][toWhichColumn].substr(0,1) == "S" or tableauArea[j-1][toWhichColumn].substr(0,1) == "C"){
                if( (stoi(diamonds[i].substr(1,2)) +1) == (stoi(tableauArea[j-1][toWhichColumn].substr(1,2))) ){
                    tableauArea[j][toWhichColumn] = diamonds[i];
                    diamonds[i].clear();

                }else{
                    outputFile << "\nInvalid Move!\n";
                }
            }else if(tableauArea[j][toWhichColumn].empty() and diamonds[i].substr(1,2) == "13"){
                tableauArea[j][toWhichColumn] = diamonds[i];
                diamonds[i].clear();
            }else{
                outputFile << "\nInvalid Move!\n";
            }
            changeMaxRow(tableauArea);
            printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
        }else if(commandString[2] == "2"){
            printCommand(commandString, commandString->size() + 1, outputFile);
            int toWhichColumn = stoi(commandString[3]);
            int i = 0;
            int j = 0;
            while(spades[i].empty()){
                i++;
                if(i >= 12){break;}
            }
            while(!tableauArea[j][toWhichColumn].empty()){
                j++;
                if(j >= 12){break;}
            }
            if(tableauArea[j-1][toWhichColumn].substr(0,1) == "H" or tableauArea[j-1][toWhichColumn].substr(0,1) == "D"){
                if( (stoi(spades[i].substr(1,2)) +1) == (stoi(tableauArea[j-1][toWhichColumn].substr(1,2))) ){
                    tableauArea[j][toWhichColumn] = spades[i];
                    spades[i].clear();
                }else{
                    outputFile << "\nInvalid Move!\n";
                }
            }else if(tableauArea[j][toWhichColumn].empty() and spades[i].substr(1,2) == "13"){
                tableauArea[j][toWhichColumn] = spades[i];
                spades[i].clear();
            }else{
                outputFile << "\nInvalid Move!\n";
            }
            changeMaxRow(tableauArea);
            printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
        }else if(commandString[2] == "3"){
            printCommand(commandString, commandString->size() + 1, outputFile);
            int toWhichColumn = stoi(commandString[3]);
            int i = 0;
            int j = 0;
            while(clubs[i].empty()){
                i++;
                if(i >= 12){break;}
            }
            while(!tableauArea[j][toWhichColumn].empty()){
                j++;
                if(j >= 12){break;}
            }
            if(tableauArea[j-1][toWhichColumn].substr(0,1) == "H" or tableauArea[j-1][toWhichColumn].substr(0,1) == "D"){
                if( (stoi(clubs[i].substr(1,2)) +1) == (stoi(tableauArea[j-1][toWhichColumn].substr(1,2))) ){
                    tableauArea[j][toWhichColumn] = clubs[i];
                    clubs[i].clear();
                }else{
                    outputFile << "\nInvalid Move!\n";
                }
            }else if(tableauArea[j][toWhichColumn].empty() and clubs[i].substr(1,2) == "13"){
                tableauArea[j][toWhichColumn] = clubs[i];
                clubs[i].clear();
            }else{
                outputFile << "\nInvalid Move!\n";
            }
            changeMaxRow(tableauArea);
            printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
        }else{
            outputFile << "\nInvalid Move!\n";
        }
    }else{
        outputFile << "\nInvalid Move!\n";
    }
}

void openFunction(string commandString[], string tableauArea[52][7], string stock[24], string hearts[13], string diamonds[13], string clubs[13], string spades[13], string waste[24], bool open_1[1], bool open_2[2], bool open_3[3], bool open_4[4], bool open_5[5], bool open_6[6], std::ofstream& outputFile){
    if(commandString[1] == "from"){
        printCommand(commandString, commandString->size() + 1, outputFile);
        bool checkIfWasteEmpty = true;
        if(stock[0].empty()){
            int m = 0;
            int j = 23;
            while(waste[m].empty()){
                m++;
            }
            while(waste[j].empty()){
                j--;
            }
            int constant = j-m+1;
            for(int i = 0; i < constant; i++){
                stock[i] = waste[j];
                waste[j].clear();
                j--;
            }
        }else{
            int i = 0;
            int j = 23;
            while (stock[i].empty()){
                i+=3;
                if(i == 24){
                    break;
                }
            }
            while(j >= 0){
                if (!waste[j].empty()){
                    checkIfWasteEmpty = false;
                }
                j--;
            }
            if(checkIfWasteEmpty){
                waste[2] = stock[i];
                waste[1] = stock[i+1];
                waste[0] = stock[i+2];
                stock[i].clear();
                stock[i+1].clear();
                stock[i+2].clear();

                int m = 0;
                int l = 23;
                while (stock[m].empty()){
                    m++;
                    if(m == 24){
                        break;
                    }
                }
                while(stock[l].empty()){
                    l--;
                    if (l == -1){
                        break;
                    }
                }
                if(m != 24 and l != -1) {
                    for (int o = m; o <= l; o++) {
                        stock[o - m] = stock[o];
                    }
                    while (m > 0) {
                        stock[l--].clear();
                        m--;
                    }
                }
            }else{
                int remaining = 0;
                int repeat = 3;
                if(waste[0].empty() and !waste[1].empty()) {
                    remaining = 1;
                    repeat = 2;
                }else if(waste[0].empty() and waste[1].empty()){
                    remaining = 2;
                    repeat = 1;
                }

                if(repeat >= 2) {
                    for (int a = 0; a < repeat; a++) {
                        int l = 24;
                        while(waste[l-1].empty()){
                            l--;
                        }
                        for (int o = l; o > remaining; o--) {
                            waste[o] = waste[o-1];
                        }
                        remaining++;
                    }
                    waste[2] = stock[0];
                    waste[1] = stock[1];
                    waste[0] = stock[2];
                    stock[0].clear();
                    stock[1].clear();
                    stock[2].clear();
                    int m = 0;
                    int l = 23;
                    while (stock[m].empty()){
                        m++;
                        if(m == 24){
                            break;
                        }
                    }
                    while(stock[l].empty()){
                        l--;
                        if (l == -1){
                            break;
                        }
                    }
                    if(m != 24 and l != -1){
                        for(int o = m; o <= l; o++){
                            stock[o-m] = stock[o];
                        }
                        while (m > 0) {
                            stock[l--].clear();
                            m--;
                        }
                    }
                }else if(repeat == 1){
                    int l = 24;
                    while(waste[l-1].empty()){
                        l--;
                    }
                    for (int o = l; o > remaining; o--) {
                        waste[o] = waste[o-1];
                    }
                    waste[2] = stock[0];
                    waste[1] = stock[1];
                    waste[0] = stock[2];
                    stock[0].clear();
                    stock[1].clear();
                    stock[2].clear();
                    int m = 0;
                    l = 23;
                    while (stock[m].empty()){
                        m++;
                        if(m == 24){
                            break;
                        }
                    }
                    while(stock[l].empty()){
                        l--;
                        if (l == -1){
                            break;
                        }
                    }
                    if(m != 24 and l != -1) {
                        for (int o = m; o <= l; o++) {
                            stock[o - m] = stock[o];
                        }
                        while (m > 0) {
                            stock[l--].clear();
                            m--;
                        }
                    }
                }
            }
        }
        printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
    }else{
        int temporary = stoi(commandString[1]);
        for(int i = 0; i < maxRow; i++){
            if(tableauArea[i][temporary].empty()){
                printCommand(commandString,commandString->size() + 1, outputFile);
                outputFile << "\nInvalid Move!\n";
                printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
            }else if(!tableauArea[i+1][temporary].empty()){
                continue;
            }else{
                if(temporary == 1){
                    open_1[i] = true;
                    printCommand(commandString, commandString->size() + 1, outputFile);
                    printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
                    break;
                }else if(temporary == 2){
                    open_2[i] = true;
                    printCommand(commandString, commandString->size() + 1, outputFile);
                    printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
                    break;
                }else if(temporary == 3){
                    open_3[i] = true;
                    printCommand(commandString, commandString->size() + 1, outputFile);
                    printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
                    break;
                }else if(temporary == 4){
                    open_4[i] = true;
                    printCommand(commandString, commandString->size() + 1, outputFile);
                    printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
                    break;
                }else if(temporary == 5){
                    open_5[i] = true;
                    printCommand(commandString, commandString->size() + 1, outputFile);
                    printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
                    break;
                }else if(temporary == 6){
                    open_6[i] = true;
                    printCommand(commandString, commandString->size() + 1, outputFile);
                    printInstantTableStatue(tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
                    break;
                }
            }
        }
    }
}

void createGameTable(string deckPath, string tableauArea[52][7], string stock[24], std::ofstream& outputFile){
    int counterStock = 23;
    int counterTable = 0;
    int row = 6;
    int column = 6;

    ifstream file(deckPath);
    string str;
    while (getline(file, str)) {
        str = str.substr(0, str.length() - 1);
        if(counterStock >= 0){
            stock[counterStock--] = str;
        }else{
            if (row == 6) {
                tableauArea[row--][column] = str;
            }else if(row == 5){
                tableauArea[row][column--] = str;
                counterTable++;
                if(counterTable == 2){
                    counterTable = 0;
                    column = 6;
                    row--;
                }
            }else if(row == 4){
                tableauArea[row][column--] = str;
                counterTable++;
                if(counterTable == 3){
                    counterTable = 0;
                    column = 6;
                    row--;
                }
            }else if(row == 3){
                tableauArea[row][column--] = str;
                counterTable++;
                if(counterTable == 4){
                    counterTable = 0;
                    column = 6;
                    row--;
                }
            }else if(row == 2){
                tableauArea[row][column--] = str;
                counterTable++;
                if(counterTable == 5){
                    counterTable = 0;
                    column = 6;
                    row--;
                }
            }else if(row == 1){
                tableauArea[row][column--] = str;
                counterTable++;
                if(counterTable == 6){
                    counterTable = 0;
                    column = 6;
                    row--;
                }
            }else{
                tableauArea[row][column--] = str;
                counterTable++;
                if(counterTable == 7){
                    counterTable = 0;
                }
            }
        }
    }

    outputFile << "\n@@@ ___ ___ ___         ___ ___ ___ ___\n\n";

    for(int i = 0; i < 7 ; i++) {
        for (int j = i; j < 7; j++) {
            if(!tableauArea[i+1][j].empty()){
                outputFile << "@@@" << "   ";
            }else {
                tableauArea[i][j] = tableauArea[i][j].substr(0,3);
                outputFile << tableauArea[i][j] << "   ";
            }
        }
        outputFile << "\n";
        for (int z = 0; z < (i+1)*2 ; z++){
            outputFile << "   ";
        }
    }
}

void takeCommands(string commandsPath, string tableauArea[52][7], string stock[24], string hearts[13], string diamonds[13], string clubs[13], string spades[13], string waste[24], bool open_1[1], bool open_2[2], bool open_3[3], bool open_4[4], bool open_5[5], bool open_6[6], std::ofstream& outputFile){
    ifstream file(commandsPath);
    string str;
    while (getline(file, str)){

        string arr[5];
        int i = 0;
        stringstream ssin(str);
        while (ssin.good() && i < 5){
            ssin >> arr[i];
            ++i;
        }

        if(arr[0] == "move"){
            moveFunction(arr, tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
        }else if(arr[0] == "open"){
            openFunction(arr, tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
        }else if(arr[0] == "exit"){
            exitFunction(outputFile);
        }else{
            outputFile << "\nInvalid Move\n";
        }

    }
}

int main(int argc, char** argv) {
    std::string tableauArea[52][7] = {};
    std::string stock[24] = {};
    std::string hearts[13] = {};
    std::string diamonds[13] = {};
    std::string clubs[13] = {};
    std::string spades[13] = {};
    std::string waste[24] = {};

    bool open_1[1] = {false};
    bool open_2[2] = {false, false};
    bool open_3[3] = {false, false, false};
    bool open_4[4] = {false, false, false, false};
    bool open_5[5] = {false, false, false, false, false};
    bool open_6[6] = {false, false, false, false, false, false};


    ofstream outputFile(argv[3]);

    createGameTable(argv[1], tableauArea, stock, outputFile);
    takeCommands(argv[2], tableauArea, stock, hearts, diamonds, clubs, spades, waste, open_1, open_2, open_3, open_4, open_5, open_6, outputFile);
    outputFile.close();
}
