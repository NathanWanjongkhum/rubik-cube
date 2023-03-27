#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <cstdint>

#include "solver.h"

using namespace std;

enum CubeInfo
{
    STICKERS = 54,
    FACES = 6,
    FACE_STICKERS = 9,
    ROW_LENGTH = 3,
    COL_LENGTH = 3,
};

/**
 * @brief For the move order instead of using primes to define counter-clockwise turns
 * it will just be capatalized.
 *
 * CW  = u, d, r, l, f, b
 * CCW = U, D, R, L, F, B
 */

static char cube[STICKERS];

const char faces[FACES] = {'u', 'd', 'r', 'l', 'f', 'b'};

vector<char> solveOrder;

void display()
{
    cout << "Cube: " << endl;
    for (size_t row = 0; row < ROW_LENGTH; row++)
    {
        for (size_t k = 0; k < FACES * COL_LENGTH; k++)
        {
            // FaceStart + RowStart + RowIndex
            cout << cube[((k / 3) * FACE_STICKERS) + (row * ROW_LENGTH) + (k % ROW_LENGTH)];

            if (k % ROW_LENGTH == 2)
                cout << " ";
        }

        cout << endl;
    }
}

void rotate_face(int faceBeginIndex, bool isClockwise)
{
    char rotatedFace[FACE_STICKERS];

    int row, col, rotatedIndex;
    for (int i = 0; i < FACE_STICKERS; i++)
    {
        row = i / ROW_LENGTH;
        col = i % COL_LENGTH;
        rotatedIndex = isClockwise ? (col * COL_LENGTH + (2 - row)) : ((2 - col) * ROW_LENGTH + row);
        rotatedFace[rotatedIndex] = cube[faceBeginIndex + i];
    }

    // Cant figure out how to memcopy in this case
    for (size_t i = 0; i < FACE_STICKERS; i++)
    {
        cube[faceBeginIndex + i] = rotatedFace[i];
    }
}

void turn_adjacent(int faceBeginIndex, bool isClockwise)
{
    // Turning Face is already solved so it can be skipped over
    // Opposite Face won't rotate so it can be skipped
    // Turning Face and Opposite face are next to each in sort so skip 2

    // the Adjacent Faces move into neighbor which is 2 away in sort

    // Skip over Turning and Opposite face then swap Adjacent Faces

    int skipBeginIndex = faceBeginIndex;
    skipBeginIndex /= FACE_STICKERS;
    skipBeginIndex -= (skipBeginIndex % 2);

    // Since only two swaps are needed no need to reach end
    for (size_t i = 0; i < FACES - 2; i++)
    {
        // Skips over the completed faces
        if (i == skipBeginIndex)
        {
            i++;
            continue;
        }

        // Get faces to swap
        int currentFaceBeginIndex = cube[FACE_STICKERS * i];
        int nextFaceBeginIndex = cube[FACE_STICKERS * (i + 2)];

        // The Rotating Face already defines what part of Adjacent Face is swapping
        // Only 4 rotations, left row-wise, right row-wise, top col-wise, bottem col-wise
    }
}

void turn(char move)
{
    solveOrder.push_back(move);

    // The Turning Face rotates
    // the 4 Adjecent Faces swap stickers

    bool isClockwise = islower(move);
    char face = tolower(move);

    int faceBeginIndex;
    for (int i = 0; i < FACES; i++)
    {
        if (face == faces[i])
        {
            faceBeginIndex = i * FACE_STICKERS;
            break;
        }
    }

    rotate_face(faceBeginIndex, isClockwise);
    turn_adjacent(faceBeginIndex, isClockwise);
}

void verifySolve()
{
    int face, sticker;
    for (size_t i = 0; i < STICKERS; i++)
    {
        // Calculate the face index and sticker index based on the array index
        face = i / FACE_STICKERS;
        sticker = i % FACE_STICKERS;

        // Set the initial color of the sticker based on the face and sticker index
        if (cube[i] != faces[face])
        {
            cout << "Failed Solve!" << endl;
        }
    }
}

int main()
{
    int face, sticker;
    for (size_t i = 0; i < STICKERS; i++)
    {
        // Calculate the face index and sticker index based on the array index
        face = i / FACE_STICKERS;
        sticker = i % FACE_STICKERS;

        // Set the initial color of the sticker based on the face and sticker index
        cube[i] = faces[face];
    }

    display();
    turn('U');
    display();
}
