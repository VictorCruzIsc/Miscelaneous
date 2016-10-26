package com.src.elements;

import java.util.Random;

public class Light extends Sensor{
	private int lightVariable;
	private Random random;
	private int sleepTime;
	
	public Light(){
		this.lightVariable = 0;
		this.sleepTime = 0;
		this.random = new Random();
	}
	
	public int getLightVariable() {
		return lightVariable;
	}
	
	public void setLightVariable(int value) {
		this.lightVariable = value;
	}
	
	public void resetValue(){
		this.setLightVariable(0);
	}
	
	public int getValue(int low, int high){
		return this.random.nextInt(high) + low;
	}

	public void run() {
		// TODO Auto-generated method stub
		try {
			while(Boolean.TRUE){
				this.lightVariable = getValue(1000, 5000);
				this.sleepTime = getValue(250, 300);
				Thread.sleep(sleepTime);
			}	
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
