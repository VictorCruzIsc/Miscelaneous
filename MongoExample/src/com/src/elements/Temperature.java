package com.src.elements;

import java.util.Random;

public class Temperature extends Sensor{
	private int temperatureVariable;
	private Random random;
	private int sleepTime;

	public Temperature(){
		this.temperatureVariable = 0;
		this.sleepTime = 0;
		this.random = new Random();
	}
	
	public int getTemperatureVariable() {
		return temperatureVariable;
	}
	
	public void setTemperatureVariable(int value) {
		this.temperatureVariable = value;
	}
	
	public void resetValue(){
		this.setTemperatureVariable(0);
	}
	
	public int getValue(int low, int high){
		return this.random.nextInt(high) + low;
	}

	public void run() {
		// TODO Auto-generated method stub
		try {
			while(Boolean.TRUE){
				this.temperatureVariable = getValue(15, 30);
				this.sleepTime = getValue(150, 200);
				Thread.sleep(sleepTime);
			}	
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
