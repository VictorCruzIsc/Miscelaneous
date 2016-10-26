public class JavaParenthesisExercise{
	//Oracle
	// Given 1 integer, show all the balanced and correct combinations of open and close parenthesis
	public static void p(int a, int c, String str, int total){
		if(a<total){
			p(a+1, c, str + "(", total);
		}
		if(c < a){
			p(a, c+1, str + ")", total);
		}
		if(c == total){
			System.out.println(str);
		}
	}

	public static void main(String []args){
		p(0,0,"",1);
		System.out.println();
		p(0,0,"",2);
		System.out.println();
		p(0,0,"",3);
		System.out.println();
		p(0,0,"",4);
	}	
}
