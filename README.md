# Criptat

 - Method: Dynamic Programming
 - Complexity:
   - Time: O(n^2)
      - Explanation: In the for(j = 2; j <= n; j++) loop (O(n)) there is another loop that goes up to j. While j can take values all the way to n, it's complexity will be O(n). So in total we have O(n^2). The sort function is only O(nlogn) which is less.
   - Space: O(n)
      - Explanation: wordsets -> dim = 27 * 3 * (n + 1) => O(n). dp -> dim = 27 * (n + 1) => O(n).
 - In a matrix "wordsets" we store the length, count of dominant letter (lcnt) and ratio (lcnt / length) of each word for each letter.
 - For each letter, we sort the wordsets vector for that letter depending on ratio and then length of word.
 - We set the first partial solution (for the first word) as length of the word.
 - We search for the longest concatenated password so far so that when concatenated with the current word it respects the condition (lcnt > length / 2).
 - If we find a suitable concatenated password, we concatenate the current word to it and update lcnt.
 - Else, "the partial solution" will only be the length of the current word (in case it will fit somewhere else).
 - The final solution will be the maximum partial solution from dp that respects the condition.
