import java.awt.*;
import java.util.Arrays;
import java.util.ArrayList;



public class MyPlayer {

    public Chip[][] gameBoard;
    public int[] columns;



    public MyPlayer() {
        columns = new int[10];


    }




    //add your code to return the row and the column of the chip you want to take.
    //you'll be returning a data type called Point which consists of two integers.
    public Point move(Chip[][] pBoard) {

        gameBoard = pBoard;
        int column = 0;
        int row = 0;

        Arrays.fill(columns, 0);

        for(int x=0; x<10; x++){//change these to width length
            for(int y=0; y<10; y++){
                if(gameBoard[x][y].isAlive==true){
                    columns[x]++;
                }
            }
        }
        System.out.print(Arrays.toString(columns));

        for (int i=0; i<10; i++){
            for (int j=0; j<=columns[i]; j++){
                int[]dummyboard = columns.clone();
                for (int k=i; k<columns.length;k++){
                    if(columns[k]>j){
                        dummyboard[k]=j;
                    }
                }
                for(int[]m : Board.currentlosingboards){
                    if(Arrays.equals(m,dummyboard) == true){
                        row = i;
                        column = j;
                    }
                }
            }
        }


        System.out.println(row + "" + column);
        Point myMove = new Point(row, column);
        return myMove;
    }

}
