#include "board.h"
#include "constants.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

Board* Board::instance = nullptr;

std::map<FieldName, std::vector<std::vector<FieldName>>> Board::fieldNamesByMills;
std::vector<std::shared_ptr<Field>> Board::fieldsToPrint;
std::vector<std::shared_ptr<Field>> Board::emptyFields;
std::map<FieldName, std::shared_ptr<Field>> Board::fieldsMap;

Board& Board::getInstance() {
    if (!instance) {
        instance = new Board();
    }
    return *instance;
}

// Private constructor initializing the board state
Board::Board() {
    initFieldNamesByMills();
    initFields();
}

void Board::initFields() {
    fieldsToPrint = {};
    emptyFields = {};
    fieldsMap = {};
    for (const auto& fieldName : FieldNames) {
        std::shared_ptr<Field> fieldPtr = std::make_shared<Field>(fieldName);
        fieldsToPrint.push_back(fieldPtr);
        int index = static_cast<int>(fieldPtr->getName());
        emptyFields.insert(emptyFields.begin() + index, fieldPtr);
        fieldsMap[fieldName] = fieldPtr;
    }
}


/* Used to determine which fields to look up when a player makes a move */
void Board::initFieldNamesByMills(){
    fieldNamesByMills = {
   {FieldName::A1, {
        {FieldName::A1, FieldName::D1, FieldName::G1},
        {FieldName::A1, FieldName::A4, FieldName::A7}
        }
    },
    {FieldName::A4, {
        {FieldName::A1, FieldName::A4, FieldName::A7},
        {FieldName::A4,FieldName::B4,FieldName::C4}
        }
    },
    {FieldName::A7, {
        {FieldName::A1,FieldName::A4,FieldName::A7},
        {FieldName::A7, FieldName::D7, FieldName::G7}
        }
    },
    {FieldName::B2, {
        {FieldName::B2, FieldName::B4, FieldName::B6},
        {FieldName::B2, FieldName::D2, FieldName::F2}
        }
    },
    {FieldName::B4, {
        {FieldName::B2, FieldName::B4, FieldName::B6},
        {FieldName::A4, FieldName::B4, FieldName::C4}
        }
    },
    {FieldName::B6, {
        {FieldName::B2, FieldName::B4, FieldName::B6},
        {FieldName::B6, FieldName::D6, FieldName::F6}
        }
    },
    {FieldName::C3, {
        {FieldName::C3, FieldName::C4, FieldName::C5},
        {FieldName::C3, FieldName::D3, FieldName::E3}
        }
    },
    {FieldName::C4, {
        {FieldName::C3, FieldName::C4, FieldName::C5},
        {FieldName::A4, FieldName::B4, FieldName::C4}
        }
    },
    {FieldName::C5, {
        {FieldName::C3, FieldName::C4, FieldName::C5},
        {FieldName::C5, FieldName::D5, FieldName::E5}
        }
    },
    {FieldName::D1, {
        {FieldName::D1, FieldName::D2, FieldName::D3},
        {FieldName::A1, FieldName::D1, FieldName::G1}
        }
    },
    {FieldName::D2, {
        {FieldName::D1, FieldName::D2, FieldName::D3},
        {FieldName::B2, FieldName::D2, FieldName::F2}
        }
    },
    {FieldName::D3, {
        {FieldName::D1, FieldName::D2, FieldName::D3},
        {FieldName::C3, FieldName::D3, FieldName::E3}
        }
    },
    {FieldName::D5, {
        {FieldName::D5, FieldName::D6, FieldName::D7},
        {FieldName::C5, FieldName::D5, FieldName::E5}
        }
    },
    {FieldName::D6, {
        {FieldName::D5, FieldName::D6, FieldName::D7},
        {FieldName::B6, FieldName::D6, FieldName::F6}
        }
    },
    {FieldName::D7, {
        {FieldName::D5, FieldName::D6, FieldName::D7},
        {FieldName::A7, FieldName::D7, FieldName::G7}
        }
    },
    {FieldName::E3, {
        {FieldName::E3, FieldName::E4, FieldName::E5},
        {FieldName::C3, FieldName::D3, FieldName::E3}
        }
    },
    {FieldName::E4, {
        {FieldName::E3, FieldName::E4, FieldName::E5},
        {FieldName::E4, FieldName::F4, FieldName::G4}
        }
    },
    {FieldName::E5, {
        {FieldName::E3, FieldName::E4, FieldName::E5},
        {FieldName::C5, FieldName::D5, FieldName::E5}
        }
    },
    {FieldName::F2, {
        {FieldName::F2, FieldName::F4, FieldName::F6},
        {FieldName::B2, FieldName::D2, FieldName::F2}
        }
    },
    {FieldName::F4, {
        {FieldName::F2, FieldName::F4, FieldName::F6},
        {FieldName::E4, FieldName::F4, FieldName::G4}
        }
    },
    {FieldName::F6, {
        {FieldName::F2, FieldName::F4, FieldName::F6},
        {FieldName::B6, FieldName::D6, FieldName::F6}
        }
    },
    {FieldName::G1, {
        {FieldName::G1, FieldName::G4, FieldName::G7},
        {FieldName::A1, FieldName::D1, FieldName::G1}
        }
    },
    {FieldName::G4, {
        {FieldName::G1, FieldName::G4, FieldName::G7},
        {FieldName::E4, FieldName::F4, FieldName::G4}
        }
    },
    {FieldName::G7, {
        {FieldName::G1, FieldName::G4, FieldName::G7},
        {FieldName::A7, FieldName::D7, FieldName::G7}
        }
    } 
};
}

std::map<FieldName, std::vector<std::vector<FieldName>>>& Board::getFieldNamesByMills(){
    return fieldNamesByMills;
}

std::vector<std::shared_ptr<Field>>& Board::getFields(){
    return fieldsToPrint;
}

std::vector<std::shared_ptr<Field>>& Board::getEmptyFields() {
    return emptyFields;
}

std::map<FieldName, std::shared_ptr<Field>>& Board::getFieldsMap(){
    return fieldsMap;
}

/* Prints the board to the console from the top to the last row. The board's fields 
vector contains the fields in the order they need to be printed to the console. 
Fields are displayed via the piece on the field. All pieces are represented by a "O" string with a colour depending on 
whether they are a default piece or belong to a player. The piece's display method
prints the "O" string with the appropriate colour to the console.
 */
void Board::display(){

/* COLUMN IDENTIFIERS */
    std::cout << "   A    B    C      D      E   F     G" << std::endl;

/* 1st ROW (FIELD ROW 1) */
    std::cout << "1  ";
    fieldsToPrint[0]->getPiece()->display(); // A1
    std::cout  << "----------------";
    fieldsToPrint[1]->getPiece()->display(); // D1
    std::cout << "----------------";
    fieldsToPrint[2]->getPiece()->display(); // G1
    std::cout << std::endl;

/* 2nd ROW (FIELD ROW 2) */
    std::cout << "   |                |                |" << std::endl;

/* 3rd ROW*/
    std::cout << "2  |    ";
    fieldsToPrint[3]->getPiece()->display(); // B2
    std::cout <<"-----------";
    fieldsToPrint[4]->getPiece()->display(); // D2
    std::cout<<"-----------";
    fieldsToPrint[5]->getPiece()->display(); // F2
    std::cout<<"    |" << std::endl;

/* 4th ROW */
    std::cout << "   |    |           |           |    |" << std::endl;

/* 5th ROW (FIELD ROW 3) */
    std::cout << "3  |    |    ";
    fieldsToPrint[6]->getPiece()->display(); // C3
    std::cout<<"------";
    fieldsToPrint[7]->getPiece()->display(); // D3
    std::cout<<"------";
    fieldsToPrint[8]->getPiece()->display(); // E3
    std::cout<<"    |    |" << std::endl;

/* 6th ROW */
    std::cout << "   |    |    |             |    |    |" << std::endl;

/* 7th ROW */
    std::cout << "   |    |    |             |    |    |" << std::endl;


/* 8th ROW (FIELD ROW 4) */
    std::cout << "4  ";
    fieldsToPrint[9]->getPiece()->display(); // A4
    std::cout << "----";
    fieldsToPrint[10]->getPiece()->display(); // B4
    std::cout<<"----";
    fieldsToPrint[11]->getPiece()->display(); // C4
    std::cout<<"             "; // middle of the board
    fieldsToPrint[12]->getPiece()->display(); // E4
    std::cout<<"----";
    fieldsToPrint[13]->getPiece()->display(); // F4
    std::cout<<"----";
    fieldsToPrint[14]->getPiece()->display(); // G4
    std::cout << std::endl;

/* 9th ROW */
    std::cout << "   |    |    |             |    |    |" << std::endl;

/* 10th ROW */
    std::cout << "   |    |    |             |    |    |" << std::endl;

/* 11th ROW (FIELD ROW 5) */
    std::cout << "5  |    |    ";
    fieldsToPrint[15]->getPiece()->display(); // C5
    std::cout<<"------";
    fieldsToPrint[16]->getPiece()->display(); // D5
    std::cout<<"------";
    fieldsToPrint[17]->getPiece()->display(); // E5
    std::cout<<"    |    |" << std::endl;

/* 12th ROW */
    std::cout << "   |    |           |           |    |" << std::endl;

/* 13th ROW (FIELD ROW 6) */
    std::cout << "6  |    ";
    fieldsToPrint[18]->getPiece()->display(); // B6
    std::cout<<"-----------";
    fieldsToPrint[19]->getPiece()->display(); // D6
    std::cout<<"-----------";
    fieldsToPrint[20]->getPiece()->display(); // F6
    std::cout<<"    |" << std::endl;

/* 14th ROW */
    std::cout << "   |                |                |" << std::endl;

/* 15th (LAST) ROW (FIELD ROW 7) */
    std::cout << "7  ";
    fieldsToPrint[21]->getPiece()->display(); // A7
    std::cout << "----------------";
    fieldsToPrint[22]->getPiece()->display(); // D7
    std::cout<<"----------------";
    fieldsToPrint[23]->getPiece()->display(); // F7
    std::cout << std::endl;
}

Board::~Board(){};