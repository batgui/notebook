class Solution {
    public int uniqueMorseRepresentations(String[] words) {
        String[] MORSE = new String[]{".-","-...","-.-.","-..",".","..-.","--.",
                         "....","..",".---","-.-",".-..","--","-.",
                         "---",".--.","--.-",".-.","...","-","..-",
                         "...-",".--","-..-","-.--","--.."};
        Set<String> seen = new HashSet();
        for (String s : words) {
        	StringBuilder code = new StringBuilder();
        	for (char c : s.toCharArray())
        		code.append(MORSE[c - 'a']);
        	seen.add(code.toString());
        }
        return seen.size();
    }
}