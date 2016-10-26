package com.src.main;

import com.src.connection.Database;
import com.src.elements.GUI;
import com.src.elements.Node;

public class Main {
	
	static final int TOTALNODES = 5;
	static final String DATABASEHOST = "localhost";
	static final String DATABASENAME = "sensado";
	static final String COLLECTIONNAME = "sensores";
	static final int PORT = 27017;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Node node[] = new Node[TOTALNODES];
		
		GUI gui = new GUI(Database.getConnection(DATABASEHOST, PORT), 
				Database.getConnection(DATABASEHOST, PORT).getDatabase(DATABASENAME), 
				Database.getConnection(DATABASEHOST, PORT).getDatabase(DATABASENAME).getCollection(COLLECTIONNAME));
		
		gui.start();

		
		//Initialize Nodes
		for(int i=0; i<TOTALNODES; i++){
			node[i] = new Node(i, DATABASEHOST, PORT, DATABASENAME, COLLECTIONNAME);
		}
		
		//Start each node and it's actions
		for(int i=0; i<TOTALNODES; i++){
			node[i].start();
		}	
	}
}
