package com.src.elements;

import org.bson.Document;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.src.connection.Database;

public class Node extends Thread{
	private Humidity humidity;
	private Temperature temperature;
	private Light light;
	private int nodeId;
	private String databaseHost;
	private String databaseName;
	private int port;
	private String collectionName;
	private MongoCollection<Document> collection;
	private MongoClient client;
	private MongoDatabase db;
	

	public Node(int nodeId, String databaseHost, int port, String databaseName, String collectionName){
		this.humidity = new Humidity();
		this.temperature =  new Temperature();
		this.light = new Light();
		this.nodeId = nodeId;
		this.databaseHost = databaseHost;
		this.port = port;
		this.databaseName = databaseName;
		this.collectionName = collectionName;
		
		initializeDatabase();
	}
	
	public void resetNodeSensors(){
		this.humidity.resetValue();
		this.temperature.resetValue();
		this.light.resetValue();
	}
	
	public Document generateDocument(){
		Document document = new Document();
		document.put("nodeId", this.nodeId);
		document.put("temperature",this.temperature.getTemperatureVariable());
		document.put("humidity",this.humidity.getHumidityVariable());
		document.put("lightValue",this.light.getLightVariable());
		
		return document;
	}
	
	public void initializeDatabase(){
		this.client = Database.getConnection(databaseHost, port);
		this.db = client.getDatabase(databaseName);
		this.collection = Database.getCollection(db, collectionName);
	}
	
	public void run() {
		//Initialize sensors
		this.humidity.start();
		this.temperature.start();
		this.light.start();
		try {
			while(Boolean.TRUE){
				//System.out.println("Node: " + this.nodeName + " H: " + this.humidity.getHumidityVariable() + " T: " + this.temperature.getTemperatureVariable() + " L: " +  this.light.getLightVariable());
				Document doc = generateDocument();
				this.collection.insertOne(doc);
				resetNodeSensors();
				Thread.sleep(200);
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
