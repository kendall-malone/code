public class MineSweeper {
    public static void main(String[] unused) {
        StdOut.println("Welcome to Minesweeper");

        int SIZE = 10;
        int NUM_MINES = 5;

        boolean[][] minefield = new boolean[SIZE][SIZE];
        boolean[][] revealed = new boolean[SIZE][SIZE];

        initMinefield(minefield, NUM_MINES);

        drawMinefield(minefield, revealed);
        while (!hasWon(minefield, revealed)) {
            processClick(minefield, revealed);
            drawMinefield(minefield, revealed);
        }
        if (hasWon(minefield, revealed)) {
            StdOut.println("You win!");
        }
    }

    /**
     * Returns true if the player has won the game.
     * @param minefield  mine locations
     * @param revealed  player identified mine-less locations
     * @return true if the player has won the game, false otherwise
     */
    public static boolean hasWon(boolean[][] minefield, boolean[][] revealed) {
        for (int x = 0; x < minefield.length; ++x) {
            for (int y = 0; y < minefield[x].length; ++y) {
                if (!(minefield[x][y] || revealed[x][y])) {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Returns the number of mines located immediately next to the current location.
     *
     * Near means one of the eight surrounding locations (N, S, E, W, NE, SE, SW, NW).
     *
     * There is no mine at [x, y].
     * @param minefield  mine locations
     * @param x  current x position
     * @param y  current y position
     * @return the number of mines located near the current location.
     */
    public static int countNeighboringMines(boolean[][] minefield, int x, int y) {
        int count = 0;
        return count;
    }

    public static void processClick(boolean[][] minefield, boolean[][] revealed) {
        while (!StdDraw.isMousePressed()) {
            ; // do nothing!!
        }

        int x = (int)Math.round(StdDraw.mouseX());
        int y = (int)Math.round(StdDraw.mouseY());

        while (StdDraw.isMousePressed()) {
            ; // do nothing!!
        }

        autoClear(minefield, revealed, x, y);

        if (minefield[x][y]) {
            StdOut.println("BOOM!");
        }
    }

    public static void initMinefield(boolean[][] minefield, int numMines) {
        for (int i = 0; i < numMines; ++i) {
            int x = StdRandom.uniform(minefield.length);
            int y = StdRandom.uniform(minefield[x].length);
            if (minefield[x][y]) {
                --i;
            }
            else {
                minefield[x][y] = true;
            }
        }
    }

    public static void drawMinefield(boolean[][] minefield, boolean[][] revealed) {
    }

    public static void autoClear(boolean[][] minefield, boolean[][] revealed, int x, int y) {
    }

}
