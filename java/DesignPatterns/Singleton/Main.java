package com.src.patterns.main;

import com.src.patterns.singleton.DataBaseConnector;

public class Main {

	public static void main(String[] args) {
		System.out.println("Total instance of DatabaseConnector: " +
				DataBaseConnector.getDataBaseConnectorInstances());
		
		// Creating a DatabaseConnector
		//DataBaseConnector dataBaseConnector =  new DataBaseConnector(); // Compiling exception, private method, not public
		//DataBaseConnector dataBaseConnector =  new DataBaseConnector("10.0.0.0", "user", 8081); // Compiling exception, private method, not public
		DataBaseConnector dataBaseConnector = DataBaseConnector.getDataBaseConnectorInstance();
		
		System.out.println("Total instance of DatabaseConnector: " +
				DataBaseConnector.getDataBaseConnectorInstances());
		System.out.println(dataBaseConnector.toString());
		
		DataBaseConnector seconDataBaseConnector = 
				DataBaseConnector.getDataBaseConnectorInstance("192.168.1.34", "root", 8081);
		
		System.out.println("Total instance of DatabaseConnector: " +
				DataBaseConnector.getDataBaseConnectorInstances());
		System.out.println(seconDataBaseConnector.toString());
		
		// I'll a compling exception, due executeDatabaseSentence(args*) is an instance member
		// and needs an instance of DataBaseConnector class to be executed
		//DataBaseConnector.executeDatabaseSentence("Select * from Clientes");
		
		dataBaseConnector.executeDatabaseSentence("Select * from CuentaInversion");
		seconDataBaseConnector.executeDatabaseSentence("Select * from CuentaCobrar");
	}

}
