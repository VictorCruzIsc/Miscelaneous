package com.src.bitso;

public class Island {
	private int x;
	private int y;
	
	public Island(int x, int y){
		this.x=x;
		this.y=y;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	//Euclidean distance
	//No square root required for optimization
	public int getEuclideanDistance(Island island){
		int distanceX = island.getX() - this.x;
		int distanceY = island.getY() - this.y;
		distanceX *= distanceX;
		distanceY *= distanceY;
		return distanceX + distanceY;
	}
	
	public boolean isEqual(Island island){
		if(this.x == island.getX() && this.y == island.y){
			return Boolean.TRUE;
		}
		return Boolean.FALSE;
	}
}
