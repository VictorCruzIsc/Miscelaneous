package com.src.patterns.singleton;

public class DataBaseConnector {
	// Instance attributes
	private String	_host;
	private String	_user;
	private int		_port;
	private int		_id;
	
	// Class attributes
	private static DataBaseConnector _dataBaseConnectorInstance = null;
	private static int _dataBaseConnectorInstances = 0;
	
	// Constructor
	private DataBaseConnector(){
		this._host = "10.0.0.0";
		this._user = "local";
		this._port = 8081;
		this._id = _dataBaseConnectorInstances++;
	}

	// Second constrcutor
	private DataBaseConnector(String host, String user, int port){
		this._host = host;
		this._user = user;
		this._port = port;
		this._id = _dataBaseConnectorInstances++;
	}

	// Instance methods
	public String getHost() {
		return _host;
	}

	public void setHost(String host) {
		this._host = host;
	}

	public String getUser() {
		return _user;
	}

	public void setUser(String user) {
		this._user = user;
	}

	public int getPort() {
		return _port;
	}

	public void set_port(int port) {
		this._port = port;
	}
	
	public int getId() {
		return _id;
	}
	
	public void executeDatabaseSentence(String sentence){
		String execution = "My id is: " + _id + " I'm executing: " + sentence;
		System.out.println(execution);
	}
	
	// This method is inherited from Object class, but we are
	// overwriting it
	public String toString(){
		String dataBaseConnectorDescriptor = "My id is: " + _id
				+ " my connection data are host: " + _host + " port: " + _port
				+ " for security I won't give you my user";
		return dataBaseConnectorDescriptor;
	}

	// Class methods
	public static int getDataBaseConnectorInstances() {
		return _dataBaseConnectorInstances;
	}
	
	// Singleton pattern design with methods (overloading)
	static public DataBaseConnector getDataBaseConnectorInstance(){
		if(_dataBaseConnectorInstance == null){
			_dataBaseConnectorInstance = new DataBaseConnector();
		}
		return _dataBaseConnectorInstance;
	}
	
	static public DataBaseConnector getDataBaseConnectorInstance(
			String host, String user, int port){
		if(_dataBaseConnectorInstance == null){
			_dataBaseConnectorInstance = new DataBaseConnector(host, user, port);
		}
		return _dataBaseConnectorInstance;
	}
}
