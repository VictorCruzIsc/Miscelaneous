package com.src.elements;

import java.awt.BorderLayout;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.AbstractTableModel;

import org.bson.Document;

import com.mongodb.MongoClient;
import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.src.collections.SensorsCollection;

public class GUI extends Thread{
	
	private MongoCollection<Document> collection;
	
	public GUI(MongoClient client, MongoDatabase db, MongoCollection<Document> collection){
		this.collection = collection;
	}
	
	public void run() {
		// TODO Auto-generated method stub
		
    	final TableModel model = new TableModel();
        JTable table = new JTable(model);

        JFrame frame = new JFrame("Testing");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new BorderLayout());
        frame.add(new JScrollPane(table));
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        
        Thread t = new Thread(new ThreadVisualize(collection, model));
        t.start();
	}
	
	public static class TableModel extends AbstractTableModel {

        private List<SensorsCollection> rows;

        public TableModel() {
            rows = new ArrayList<>();
        }
        
        @Override
        public int getRowCount() {
            return rows.size();
        }

        @Override
        public int getColumnCount() {
            return 4;
        }

        @Override
        public Class<?> getColumnClass(int columnIndex) {
            return Integer.class;
        }

        @Override
        public Object getValueAt(int rowIndex, int columnIndex) {
            SensorsCollection sensorCollection = rows.get(rowIndex);
            switch (columnIndex) {
			case 0:
				return sensorCollection.getNodeId();
			case 1:
				return sensorCollection.getTemperature();
			case 2:
				return sensorCollection.getHumidity();
			case 3:
				return sensorCollection.getLightValue();
			default:
				return 0;
			}
        }
        
        public void renew(MongoCollection<Document> collection){
        	rows.clear();
        	FindIterable<Document> find = collection.find();
			for(Document dc : find){
				int nodeId = (Integer) dc.get("nodeId");
				int temperature = (Integer) dc.get("temperature");
				int humidity = (Integer) dc.get("humidity");
				int lightValue = (Integer) dc.get("lightValue");
				SensorsCollection sensorCollectionElement = new SensorsCollection(nodeId, temperature, humidity, lightValue);
				rows.add(sensorCollectionElement);
			}

            fireTableRowsInserted(0, 0);
        }
    }

	private static class ThreadVisualize implements Runnable{
		private MongoCollection<Document> collection;		
		private TableModel model;
		
		public ThreadVisualize(MongoCollection<Document> collection, TableModel model){
			this.collection = collection;
			this.model = model;
		}
		
		@Override
		public void run() {
			// TODO Auto-generated method stub
			try{
				if(this.collection!=null){
					while(true){
						this.model.renew(collection);
						System.out.println(".");
						Thread.sleep(2000);
					}
				}else{
					System.out.println("Error obteniendo coleccion de sensado");
				}
			}catch(InterruptedException e){
				System.out.println("Excepcion " + e.getMessage());
			}
			
		}
	}
}
