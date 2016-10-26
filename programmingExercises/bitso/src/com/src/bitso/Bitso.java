package com.src.bitso;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Bitso{
	
	public static void main(String[] args){
		bitsoProblem("inout.txt");
	}
	
	public static void bitsoProblem(String fileName){
		try { 
            BufferedReader bufferedReader = new BufferedReader(new FileReader(fileName));
            int totalCases = Integer.parseInt(bufferedReader.readLine());
            
            // Check all the test cases
            for(int cases=0; cases<totalCases; cases++){
            	int totalIslands = Integer.parseInt(bufferedReader.readLine());
            	int islandMatrix[][];
            	ArrayList<Island> islands = new ArrayList<Island>();
            	
            	// Get all the islands in a collection
            	for(int tI=0; tI<totalIslands; tI++){
            		String newCoordinatesLine = bufferedReader.readLine();
            		int coordinates[] = Utils.getCoordinates(newCoordinatesLine);
            		Island island = new Island(coordinates[0], coordinates[1]);
            		islands.add(island);
            	}
            	
            	islandMatrix = Utils.getIslandMatrix(islands);
            	//printIslandMatrix(islandMatrix);
            	System.out.println(Utils.getTotalArchipielagos(islandMatrix, islands));
            } 
            bufferedReader.close();         
        }catch(FileNotFoundException ex) {
            System.out.println("Unable to open file '" + fileName + "'");                
        }catch(IOException ex) {
            System.out.println("Error reading file '" + fileName + "'");                  
        }
	}
}