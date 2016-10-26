package com.src.bitso;

public class Archipielago {
	private Island a;
	private Island b;
	private Island c;

	public Archipielago(Island a, Island b, Island c){
		this.a = a;
		this.b = b;
		this.c = c;
	}
	
	public Island getA() {
		return a;
	}

	public Island getB() {
		return b;
	}

	public Island getC() {
		return c;
	}

	public boolean isEqual(Archipielago archipielago){
		boolean aIsland = (this.a.isEqual(archipielago.getA()) || this.a.isEqual(archipielago.getB()) || this.a.isEqual(archipielago.getC()));
		boolean bIsland = (this.b.isEqual(archipielago.getA()) || this.b.isEqual(archipielago.getB()) || this.b.isEqual(archipielago.getC()));
		boolean cIsland = (this.c.isEqual(archipielago.getA()) || this.c.isEqual(archipielago.getB()) || this.c.isEqual(archipielago.getC()));	
		if(aIsland && bIsland && cIsland){
			return Boolean.TRUE;
		}
		return Boolean.FALSE;
	}
}
