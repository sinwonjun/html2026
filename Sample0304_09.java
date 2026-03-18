package jump2java;

public class Sample0304_09 {
    public static void main(String[] args) {
        String a = "a:b:c:d";
        
        // ":"을 기준으로 나누어서 배열로 저장
        String[] result = a.split(":");  
        for (String r : result) {
            System.out.println(r);
        }
    }
}