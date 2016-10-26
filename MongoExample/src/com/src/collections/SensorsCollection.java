package com.src.collections;

import org.bson.Document;

public class SensorsCollection {
	private int nodeId;
	private int temperature;
	private int humidity;
	private int lightValue;
	
	public SensorsCollection(int nodeId, int temperature, int humidity, int lightValue){
		this.nodeId = nodeId;
		this.temperature = temperature;
		this.humidity = humidity;
		this.lightValue = lightValue;
	}

	public int getNodeId() {
		return nodeId;
	}

	public void setNodeId(int nodeId) {
		this.nodeId = nodeId;
	}

	public int getTemperature() {
		return temperature;
	}

	public void setTemperature(int temperature) {
		this.temperature = temperature;
	}

	public int getHumidity() {
		return humidity;
	}

	public void setHumidity(int humidity) {
		this.humidity = humidity;
	}

	public int getLightValue() {
		return lightValue;
	}

	public void setLightValue(int lightValue) {
		this.lightValue = lightValue;
	}
	
}
