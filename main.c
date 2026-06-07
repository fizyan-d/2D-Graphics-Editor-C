
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 20
#define COLS 50

// Global matrix for our drawing board
char canvas[ROWS][COLS];

// Function declarations
void initCanvas();
void printCanvas();
int checkBounds(int x, int y);
void drawLine(int x1, int y1, int x2, int y2);
void drawRectangle(int x1, int y1, int x2, int y2);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void drawCircle(int xc, int yc, int radius);

int main() {
    int choice;
    initCanvas();

    while (1) {
        printf("\n--- 2D GRAPHICS EDITOR ---\n");
        printf("1. Display Canvas\n");
        printf("2. Draw Line\n");
        printf("3. Draw Rectangle\n");
        printf("4. Draw Triangle\n");
        printf("5. Draw Circle\n");
        printf("6. Clear Canvas\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printCanvas();
                break;
            case 2: {
                int x1, y1, x2, y2;
                printf("Enter start coordinates (X1 Y1): ");
                scanf("%d %d", &x1, &y1);
                printf("Enter end coordinates (X2 Y2): ");
                scanf("%d %d", &x2, &y2);
                drawLine(x1, y1, x2, y2);
                break;
            }
            case 3: {
                int x1, y1, x2, y2;
                printf("Enter top-left corner (X1 Y1): ");
                scanf("%d %d", &x1, &y1);
                printf("Enter bottom-right corner (X2 Y2): ");
                scanf("%d %d", &x2, &y2);
                drawRectangle(x1, y1, x2, y2);
                break;
            }
            case 4: {
                int x1, y1, x2, y2, x3, y3;
                printf("Enter Point 1 (X1 Y1): ");
                scanf("%d %d", &x1, &y1);
                printf("Enter Point 2 (X2 Y2): ");
                scanf("%d %d", &x2, &y2);
                printf("Enter Point 3 (X3 Y3): ");
                scanf("%d %d", &x3, &y3);
                drawTriangle(x1, y1, x2, y2, x3, y3);
                break;
            }
            case 5: {
                int xc, yc, r;
                printf("Enter center point (Xc Yc): ");
                scanf("%d %d", &xc, &yc);
                printf("Enter radius: ");
                scanf("%d", &r);
                drawCircle(xc, yc, r);
                break;
            }
            case 6:
                initCanvas();
                printf("\nCanvas cleared successfully.\n");
                break;
            case 7:
                printf("\nExiting program.\n");
                exit(0);
            default:
                printf("\nInvalid option, please try again.\n");
        }
    }
    return 0;
}

// Fills the board with blank space slots
void initCanvas() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            canvas[i][j] = '_';
        }
    }
}

// Renders the current grid state on screen
void printCanvas() {
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}

// Make sure we don't try to access coordinates outside our array sizes
int checkBounds(int x, int y) {
    return (x >= 0 && x < COLS && y >= 0 && y < ROWS);
}

// Standard step-based line generation plotting
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    if (steps == 0) {
        if (checkBounds(x1, y1)) canvas[y1][x1] = '*';
        return;
    }

    float xInc = (float)dx / steps;
    float yInc = (float)dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        int currentX = (int)(x + 0.5);
        int currentY = (int)(y + 0.5);

        if (checkBounds(currentX, currentY)) {
            canvas[currentY][currentX] = '*';
        }
        x += xInc;
        y += yInc;
    }
}

// Draws a rectangle by linking four independent lines together
void drawRectangle(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y1); // Top line
    drawLine(x1, y2, x2, y2); // Bottom line
    drawLine(x1, y1, x1, y2); // Left line
    drawLine(x2, y1, x2, y2); // Right line
}

// Connects 3 distinct vertices using the line tool
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

// Plots points that fall closely along the path of a circle radius equation
void drawCircle(int xc, int yc, int radius) {
    for (int y = yc - radius; y <= yc + radius; y++) {
        for (int x = xc - radius; x <= xc + radius; x++) {
            if (checkBounds(x, y)) {
                int dx = x - xc;
                int dy = y - yc;
                double dist = sqrt(dx*dx + dy*dy);
                
                // If the coordinate is close enough to the radius border line, fill it
                if (dist >= radius - 0.5 && dist <= radius + 0.5) {
                    canvas[y][x] = '*';
                }
            }
        }
    }
}