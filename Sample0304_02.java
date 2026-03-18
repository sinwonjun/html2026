package jump2java;

public class Sample0304_02 {
    public static void main(String[] args) {
        String a = "hello";
        String b = new String("hello");
        
        System.out.println(a.equals(b)); 
        System.out.println(a == b);
    }
}
