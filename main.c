#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 20
#define COLS 50
#define MAX_OBJECTS 100

// Shape types enumeration
typedef enum { LINE, RECTANGLE, TRIANGLE, CIRCLE } ShapeType;

// Structure to track every shape drawn
typedef struct {
    int id;
    ShapeType type;
    int coords[6]; // Stores coordinates: [x1, y1, x2, y2, x3, y3] or [xc, yc, radius]
    int active;    // 1 if object exists, 0 if deleted
} GraphicalObject;

// Global Variables
char canvas[ROWS][COLS];
GraphicalObject objectList[MAX_OBJECTS];
int objectCount = 0;

// Core Engine Functions
void initCanvas();
void printCanvas();
int checkBounds(int x, int y);
void redrawCanvas();

// Shape Logic Modules
void drawLine(int x1, int y1, int x2, int y2);
void drawRectangle(int x1, int y1, int x2, int y2);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void drawCircle(int xc, int yc, int radius);

// Day 2 Features: Management Functions
void addObject(ShapeType type, int c[]);
void deleteObject(int id);
void modifyObject(int id);
void listObjects();

int main() {
    int choice;
    initCanvas();

    while (1) {
        printf("\n=== 2D GRAPHICS EDITOR (Day 2: Object Tracked) ===\n");
        printf("1. Display Canvas\n");
        printf("2. Draw a Shape\n");
        printf("3. List Active Objects\n");
        printf("4. Delete an Object\n");
        printf("5. Modify an Object\n");
        printf("6. Clear/Wipe Canvas\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printCanvas();
                break;
            case 2: {
                int shapeChoice;
                printf("\n--- Select Shape Type ---\n");
                printf("1. Line\n2. Rectangle\n3. Triangle\n4. Circle\n");
                printf("Enter choice: ");
                scanf("%d", &shapeChoice);

                int c[6] = {0};
                if (shapeChoice == 1) {
                    printf("Enter X1 Y1 X2 Y2: ");
                    scanf("%d %d %d %d", &c[0], &c[1], &c[2], &c[3]);
                    addObject(LINE, c);
                } else if (shapeChoice == 2) {
                    printf("Enter Top-Left (X1 Y1) and Bottom-Right (X2 Y2): ");
                    scanf("%d %d %d %d", &c[0], &c[1], &c[2], &c[3]);
                    addObject(RECTANGLE, c);
                } else if (shapeChoice == 3) {
                    printf("Enter X1 Y1 X2 Y2 X3 Y3: ");
                    scanf("%d %d %d %d %d %d", &c[0], &c[1], &c[2], &c[3], &c[4], &c[5]);
                    addObject(TRIANGLE, c);
                } else if (shapeChoice == 4) {
                    printf("Enter Center (Xc Yc) and Radius: ");
                    scanf("%d %d %d", &c[0], &c[1], &c[2]);
                    addObject(CIRCLE, c);
                } else {
                    printf("Invalid shape type.\n");
                }
                break;
            }
            case 3:
                listObjects();
                break;
            case 4: {
                int id;
                listObjects();
                if (objectCount > 0) {
                    printf("Enter Object ID to delete: ");
                    scanf("%d", &id);
                    deleteObject(id);
                }
                break;
            }
            case 5: {
                int id;
                listObjects();
                if (objectCount > 0) {
                    printf("Enter Object ID to modify: ");
                    scanf("%d", &id);
                    modifyObject(id);
                }
                break;
            }
            case 6:
                initCanvas();
                objectCount = 0; // Wipe history
                printf("\nCanvas completely reset.\n");
                break;
            case 7:
                printf("\nExiting program.\n");
                exit(0);
            default:
                printf("\nInvalid option. Try again.\n");
        }
    }
    return 0;
}

void initCanvas() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            canvas[i][j] = '_';
        }
    }
}

void printCanvas() {
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}

int checkBounds(int x, int y) {
    return (x >= 0 && x < COLS && y >= 0 && y < ROWS);
}

// Day 2 Logic: Saves structural parameters to history table, then triggers render
void addObject(ShapeType type, int c[]) {
    if (objectCount >= MAX_OBJECTS) {
        printf("Error: Object storage memory full!\n");
        return;
    }
    objectList[objectCount].id = objectCount + 1;
    objectList[objectCount].type = type;
    objectList[objectCount].active = 1;
    for (int i = 0; i < 6; i++) {
        objectList[objectCount].coords[i] = c[i];
    }
    objectCount++;
    redrawCanvas();
    printf("Object added successfully as ID: %d\n", objectCount);
}

// Day 2 Logic: Deactivates an item and re-renders the survivors
void deleteObject(int id) {
    for (int i = 0; i < objectCount; i++) {
        if (objectList[i].id == id && objectList[i].active == 1) {
            objectList[i].active = 0;
            redrawCanvas();
            printf("Object ID %d deleted successfully.\n", id);
            return;
        }
    }
    printf("Object ID not found.\n");
}

// Day 2 Logic: Updates targeted metrics in place
void modifyObject(int id) {
    for (int i = 0; i < objectCount; i++) {
        if (objectList[i].id == id && objectList[i].active == 1) {
            printf("Enter new coordinates for this object:\n");
            if (objectList[i].type == LINE || objectList[i].type == RECTANGLE) {
                printf("Enter 4 values (X1 Y1 X2 Y2): ");
                scanf("%d %d %d %d", &objectList[i].coords[0], &objectList[i].coords[1], &objectList[i].coords[2], &objectList[i].coords[3]);
            } else if (objectList[i].type == TRIANGLE) {
                printf("Enter 6 values (X1 Y1 X2 Y2 X3 Y3): ");
                scanf("%d %d %d %d %d %d", &objectList[i].coords[0], &objectList[i].coords[1], &objectList[i].coords[2], &objectList[i].coords[3], &objectList[i].coords[4], &objectList[i].coords[5]);
            } else if (objectList[i].type == CIRCLE) {
                printf("Enter 3 values (Xc Yc Radius): ");
                scanf("%d %d %d", &objectList[i].coords[0], &objectList[i].coords[1], &objectList[i].coords[2]);
            }
            redrawCanvas();
            printf("Object ID %d modified successfully.\n", id);
            return;
        }
    }
    printf("Object ID not found.\n");
}

// Day 2 Logic: Displays current working vector objects list
void listObjects() {
    int count = 0;
    printf("\n--- Active Geometric Objects ---\n");
    for (int i = 0; i < objectCount; i++) {
        if (objectList[i].active) {
            count++;
            printf("ID: %d | Type: ", objectList[i].id);
            if (objectList[i].type == LINE) printf("Line");
            else if (objectList[i].type == RECTANGLE) printf("Rectangle");
            else if (objectList[i].type == TRIANGLE) printf("Triangle");
            else if (objectList[i].type == CIRCLE) printf("Circle");
            printf("\n");
        }
    }
    if (count == 0) printf("(No shapes drawn yet)\n");
}

// Day 2 Logic: Clears the matrix, cycles the structural objects log, and outputs them safely
void redrawCanvas() {
    initCanvas(); // Clear background grid completely
    for (int i = 0; i < objectCount; i++) {
        if (objectList[i].active) {
            int *c = objectList[i].coords;
            if (objectList[i].type == LINE) drawLine(c[0], c[1], c[2], c[3]);
            else if (objectList[i].type == RECTANGLE) drawRectangle(c[0], c[1], c[2], c[3]);
            else if (objectList[i].type == TRIANGLE) drawTriangle(c[0], c[1], c[2], c[3], c[4], c[5]);
            else if (objectList[i].type == CIRCLE) drawCircle(c[0], c[1], c[2]);
        }
    }
}

/* Math Drawing Implementations */
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1, dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    if (steps == 0) {
        if (checkBounds(x1, y1)) canvas[y1][x1] = '*';
        return;
    }
    float xInc = (float)dx / steps, yInc = (float)dy / steps;
    float x = x1, y = y1;
    for (int i = 0; i <= steps; i++) {
        int cx = (int)(x + 0.5), cy = (int)(y + 0.5);
        if (checkBounds(cx, cy)) canvas[cy][cx] = '*';
        x += xInc; y += yInc;
    }
}

void drawRectangle(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y1); drawLine(x1, y2, x2, y2);
    drawLine(x1, y1, x1, y2); drawLine(x2, y1, x2, y2);
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2); drawLine(x2, y2, x3, y3); drawLine(x3, y3, x1, y1);
}

void drawCircle(int xc, int yc, int radius) {
    for (int y = yc - radius; y <= yc + radius; y++) {
        for (int x = xc - radius; x <= xc + radius; x++) {
            if (checkBounds(x, y)) {
                int dx = x - xc, dy = y - yc;
                double dist = sqrt(dx*dx + dy*dy);
                if (dist >= radius - 0.5 && dist <= radius + 0.5) {
                    canvas[y][x] = '*';
                }
            }
        }
    }
}