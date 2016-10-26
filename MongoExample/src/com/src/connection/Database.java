package com.src.connection;

import org.bson.Document;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;

public class Database {
	
	public static MongoClient getConnection(String url, int port){
		MongoClient client;
		try {
			client = new MongoClient(url, port);
			return client;
		} catch (Exception e) {
			// TODO: handle exception
			return null;
		}
	}
	
	public static MongoDatabase getDatabase(MongoClient client, String databaseName){
		MongoDatabase db = client.getDatabase(databaseName);
		return db;
	}
	
	public static MongoCollection<Document> getCollection(MongoDatabase db, String collection){
		MongoCollection<Document> documentCollection = db.getCollection(collection);
		return documentCollection;
	}
	
	public static void insertDocument(MongoCollection<Document> collection, Document document){
		collection.insertOne(document);
	}
}
