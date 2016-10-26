package com.src.elements;

import java.util.Random;

public class Humidity extends Sensor{
	private int humidityVariable;
	private Random random;
	private int sleepTime;
	
	public Humidity(){
		this.humidityVariable = 0;
		this.sleepTime = 0;
		this.random = new Random();
	}
	
	public int getHumidityVariable() {
		return humidityVariable;
	}
	
	public void setHumidityVariable(int value) {
		this.humidityVariable = value;
	}
	
	public void resetValue(){
		this.setHumidityVariable(0);
	}

	public int getValue(int low, int high){
		return this.random.nextInt(high) + low;
	}
	
	public void run() {
		// TODO Auto-generated method stub
		try {
			while(Boolean.TRUE){
				this.humidityVariable = getValue(0, 100);
				this.sleepTime = getValue(200, 250);
				Thread.sleep(sleepTime);
			}	
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
