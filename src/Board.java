import java.util.ArrayList;
import java.util.Arrays;


public class Board {
    static ArrayList<int[]> boards = new ArrayList<int[]>();
    static ArrayList<int[]> winningboards = new ArrayList<>();
    static ArrayList<int[]> losingboards = new ArrayList<>();
    static ArrayList<int[]> currentlosingboards = new ArrayList<>();
    static int[] placeholder = new int[3];//change here for width

    public static void Initialize(int width, int height)
    {
        int[] firstloss=new int[width];
        firstloss[0]=1;
        currentlosingboards.add(firstloss);
        int[] firstwin=new int[width];
        winningboards.add(firstwin);

        allboardstates(0, height);
        boards.remove(0);


        while (true) {
            // find all winning boards one move away from currentlosingboards
            for (int[] j : boards) {
                //compare it to a losing board
                for (int[] i : currentlosingboards) {
                    boolean once = Board.OneMove(j, i);
                    if (once == true) {
                        //if the one move reduction is true add to wins
                        InsertBoard(winningboards,j);
                    }
                }
            }

            //
            for(int[]z : currentlosingboards){
                InsertBoard(losingboards, z);
            }

            // find new losing boards
            currentlosingboards.clear();
            if(losingboards.size()+winningboards.size() > boards.size()) {
                break;
            }
            for (int[]k : boards) {
                    boolean losing = checkLosingPos(k);
                    if(losing == true){
                        InsertBoard(currentlosingboards,k);
                    }
            }
            System.out.println("loop done");
            System.out.println("losing length" + losingboards.size());


            }
        }



    //winning function
    static boolean checkLosingPos(int[]currentboard) {
        for (int i = 0; i < currentboard.length; i++) {
            for (int j = 0; j < currentboard[i]; j++) {
                // taking i,j
                int[] candidateBoard = currentboard.clone();
                for (int k = i; k < currentboard.length; k++) {
                    if (currentboard[k] > j) {
                        candidateBoard[k] = j;
                    }
                }

                boolean iscandidateBoardInWinningSet = false;
                for (int[] m : winningboards) {
                    if (Arrays.equals(m, candidateBoard) == true) {
                        iscandidateBoardInWinningSet = true;
                        break;
                    }
                }

                if (iscandidateBoardInWinningSet == false) {
                    return false;
                }
            }
        }
        return true;
    }

    //subtract 2 boards to get new array  - for all non 0 elements of that array the corresponding elements of subtracted board must be equal
    public static boolean OneMove(int[] input1, int[] input2)//input 1 is greater than input 2
    {
        ArrayList<Integer>subtraction = new ArrayList<>();
        for(int i=0;i<input1.length;i++){
            if(input1[i]-input2[i]>0){
                subtraction.add(i);
            }
        }
        for(int j : subtraction) {
            if (input2[subtraction.get(0)]==input2[j]){

            }
            else{
                return (false);
            }
        }

        return (true);
    }

    //
    public static void InsertBoard(ArrayList<int[]> boardSet, int[] set1)
    {
        boolean add = true;
        for (int[] i : boardSet) {
            if (Arrays.equals(i, set1) == true) {
                add = false;
                break;
            }
        }
        if (add == true) {
            boardSet.add(set1);
        }
    }

    public static void PrintSet(ArrayList<int[]> boardSet)
    {
        for (int[] i : boardSet) {
            System.out.println(Arrays.toString(i));
        }
    }
    public static void allboardstates (int start, int height)
    {
        if (start == 3){//change here for width
            int[] copy = placeholder.clone();
            boards.add(copy);
            return;
        }
        for (int i = 0; i <= height; i++) {
            placeholder[start] = i;
            allboardstates(start + 1, i);
        }
    }
    }


