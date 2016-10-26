package com.src.bitso;

import java.util.ArrayList;

public class Utils {
	// Get the coordinate from a String
	public static int[] getCoordinates(String line){
		String coordinatesDivided[] = line.split(" ");
		int coordinates[] = new int[2];
		coordinates[0] = Integer.parseInt(coordinatesDivided[0]);
		coordinates[1] = Integer.parseInt(coordinatesDivided[1]);
		return coordinates;
	}
	
	public static void printIslandMatrix(int matrix[][]){
		int rows = matrix.length;
		int cols = matrix[0].length;
		for(int i=0; i<rows; i++){
			for(int j=0; j<cols; j++){
				System.out.print(matrix[i][j] + " ");
			}
			System.out.println("");
		}
	}
	
	public static int[][] getIslandMatrix(ArrayList<Island> islands){
		int totalIslands = islands.size();
		int[][] islandMatrix = new int[totalIslands][totalIslands];
		for(int rows=0; rows<totalIslands; rows++){
    		for(int cols=0; cols<totalIslands; cols++){
    			islandMatrix[rows][cols] = islands.get(rows).getEuclideanDistance(islands.get(cols));
    		}
    	}
		return islandMatrix;
	}
	
	public static int getTotalArchipielagos(int matrix[][], ArrayList<Island> islands){
		int totalIslands = matrix.length;
		ArrayList<Archipielago> archipielagos = new ArrayList<Archipielago>();
		for(int row=0; row<totalIslands; row++){
			for(int col=0; col<totalIslands; col++){
				int baseDistance = matrix[row][col];
				if(baseDistance != 0){
					for(int current = col+1; current<totalIslands; current++){
						int currentDistance = matrix[row][current];
						if(currentDistance == baseDistance){
							// Archipielago found;
							Archipielago newArchipielago = new Archipielago(islands.get(row), islands.get(col), islands.get(current));
							if(addNewArchipielago(archipielagos, newArchipielago)){
								archipielagos.add(newArchipielago);
							}
						}
					}
				}
			}
		}
		return archipielagos.size();
	}
	
	public static boolean addNewArchipielago(ArrayList<Archipielago> archipielagos, Archipielago newArchipielago){
		int total = archipielagos.size();
		for(int i=0; i<total; i++){
			Archipielago current = archipielagos.get(i);
			if(current.isEqual(newArchipielago)){
				return Boolean.FALSE;
			}
		}
		return Boolean.TRUE;
	}
}
