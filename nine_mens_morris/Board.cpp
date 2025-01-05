#include "board.h"
#include "constants.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

Board* Board::instance = nullptr;

std::map<FieldName, std::vector<std::vector<FieldName>>> Board::fieldNamesByMills;
std::vector<std::shared_ptr<Field>> Board::fields;
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
    fields = {};
    fieldsMap = {};
    for (const auto& fieldName : FieldNames) {
        std::shared_ptr<Field> fieldPtr = std::make_shared<Field>(fieldName);
        fields.push_back(fieldPtr);
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

std::map<FieldName, std::vector<std::vector<FieldName>>> Board::getFieldNamesByMills(){
    return fieldNamesByMills;
}

std::vector<std::shared_ptr<Field>> Board::getFields(){
    return fields;
}

std::map<FieldName, std::shared_ptr<Field>> Board::getFieldsMap(){
    return fieldsMap;
}

/* Prints the board to the console from the top to the last row. The board's fields 
vector contains the fields in the order they need to be printed to the console. 
Fields are displayed via the piece on the field. All pieces are represented by a "O" string with a colour depending on 
whether they are a default piece or belong to a player. The piece's display method
prints the "O" string with the appropriate colour to the console.
 */
void Board::display(){
/* 1st ROW */
    fields[0]->getPiece()->display(); // A1
    std::cout  << "----------------";
    fields[1]->getPiece()->display(); // D1
    std::cout << "----------------";
    fields[2]->getPiece()->display(); // G1
    std::cout << std::endl;

/* 2nd ROW*/
    std::cout << "|                |                |" << std::endl;

/* 3rd ROW*/
    std::cout << "|    ";
    fields[3]->getPiece()->display(); // B2
    std::cout <<"-----------";
    fields[4]->getPiece()->display(); // D2
    std::cout<<"-----------";
    fields[5]->getPiece()->display(); // F2
    std::cout<<"    |" << std::endl;

/* 4th ROW */
    std::cout << "|    |           |           |    |" << std::endl;

/* 5th ROW */
    std::cout << "|    |    ";
    fields[6]->getPiece()->display(); // C3
    std::cout<<"------";
    fields[7]->getPiece()->display(); // D3
    std::cout<<"------";
    fields[8]->getPiece()->display(); // E3
    std::cout<<"    |    |" << std::endl;

/* 6th ROW */
    std::cout << "|    |    |             |    |    |" << std::endl;

/* 7th ROW */
    std::cout << "|    |    |             |    |    |" << std::endl;

/* 8th ROW */
    std::cout << "|    |    |             |    |    |" << std::endl;


/* 9th ROW */
    fields[9]->getPiece()->display(); // A4
    std::cout << "----";
    fields[10]->getPiece()->display(); // B4
    std::cout<<"----";
    fields[11]->getPiece()->display(); // C4
    std::cout<<"             "; // middle of the board
    fields[12]->getPiece()->display(); // E4
    std::cout<<"----";
    fields[13]->getPiece()->display(); // F4
    std::cout<<"----";
    fields[14]->getPiece()->display(); // G4
    std::cout << std::endl;

/* 10th ROW */
    std::cout << "|    |    |             |    |    |" << std::endl;

/* 11th ROW */
    std::cout << "|    |    |             |    |    |" << std::endl;

/* 12th ROW */
    std::cout << "|    |    |             |    |    |" << std::endl;

/* 13th ROW */
    std::cout << "|    |    ";
    fields[15]->getPiece()->display(); // C5
    std::cout<<"------";
    fields[16]->getPiece()->display(); // D5
    std::cout<<"------";
    fields[17]->getPiece()->display(); // E5
    std::cout<<"    |    |" << std::endl;

/* 14th ROW */
    std::cout << "|    |           |           |    |" << std::endl;

/* 15th ROW */
    std::cout << "|    ";
    fields[18]->getPiece()->display(); // B6
    std::cout<<"-----------";
    fields[19]->getPiece()->display(); // D6
    std::cout<<"-----------";
    fields[20]->getPiece()->display(); // F6
    std::cout<<"    |" << std::endl;

/* 16th ROW */
    std::cout << "|                |                |" << std::endl;

/* 17th (LAST) ROW */
    fields[21]->getPiece()->display(); // A7
    std::cout << "----------------";
    fields[22]->getPiece()->display(); // D7
    std::cout<<"----------------";
    fields[23]->getPiece()->display(); // F7
    std::cout << std::endl;
}

Board::~Board(){};