#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <cstdint>

#include "solver.h"

using namespace std;

/**
 * @brief For the move order instead of using primes to define counter-clockwise turns
 * it will just be capatalized.
 *
 * CW  = u, d, r, l, f, b
 * CCW = U, D, R, L, F, B
 */

const static uint8_t NUM_STICKERS = 54; // 6 faces * 9 stickers
static char cube[NUM_STICKERS];

const char faces[6] = {'u', 'd', 'r', 'l', 'f', 'b'};

vector<char> solveOrder;

void display()
{
    for (size_t i = 0; i < 3; i++)
    {

        for (uint8_t k = 0; k < (6 * 3); k++)
        {

            // FaceStart + RowStart + RowIndex
            cout << cube[((k / 3) * 9) + (i * 3) + (k % 3)];

            if (k % 3 == 2)
                cout << " ";
        }
        cout << endl;
    }
}

void rotate_face(uint8_t faceBeginIndex, bool isClockwise)
{
    char rotatedFace[9];

    uint8_t row, col, rotatedIndex;
    for (uint8_t i = 0; i < 9; i++)
    {
        row = i / 3;
        col = i % 3;
        rotatedIndex = isClockwise ? (col * 3 + (2 - row)) : ((2 - col) * 3 + row);
        rotatedFace[rotatedIndex] = cube[faceBeginIndex + i];
    }

    cout << "Face: " << rotatedFace[0] << endl;
    // for (size_t i = 0; i < 9; i++)
    // {
    //     cout << rotatedFace[i];
    // }

    // Cant figure out how to memcopy in this case
    for (uint8_t i = 0; i < 9; i++)
    {
        cube[faceBeginIndex + i] = rotatedFace[i];
    }
}

void turn_adjacent(int face, bool isClockwise)
{
}

void turn(char move)
{
    solveOrder.push_back(move);

    /*
        The turning face rotates
        the 4 adjecent faces swap stickers nearest to face
        the faces swap 3 stickers
    */

    bool isClockwise = islower(move);
    char face = tolower(move);

    uint8_t faceBeginIndex;
    for (uint8_t i = 0; i < 6; i++)
    {
        if (face == faces[i])
        {
            faceBeginIndex = i * 9 - 1;
            break;
        }
    }

    rotate_face(faceBeginIndex, isClockwise);
    turn_adjacent(faceBeginIndex, isClockwise);
}

void verifySolve()
{
    uint8_t face, sticker;
    for (uint8_t i = 0; i < NUM_STICKERS; i++)
    {
        // Calculate the face index and sticker index based on the array index
        face = i / 9;
        sticker = i % 9;

        // Set the initial color of the sticker based on the face and sticker index
        if (cube[i] != faces[face])
        {
            cout << "Failed Solve!" << endl;
        }
    }
}

int main()
{
    uint8_t face, sticker;
    for (uint8_t i = 0; i < NUM_STICKERS; i++)
    {
        // Calculate the face index and sticker index based on the array index
        face = i / 9;
        sticker = i % 9;

        // Set the initial color of the sticker based on the face and sticker index
        cube[i] = faces[face];
    }

    display();
    turn('U');
    display();
}
