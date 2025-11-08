# 05. Pattern Matching

## Learning Outcomes

After completing this module, you will be able to:

- Understand the string matching problem
- Implement naive pattern matching algorithm
- Apply the Knuth-Morris-Pratt (KMP) algorithm efficiently
- Use the Rabin-Karp algorithm for multiple pattern matching
- Analyze time complexity of various pattern matching algorithms
- Choose the appropriate algorithm for different scenarios

## Theory

### The String Matching Problem

**Given:**
- Text T of length n
- Pattern P of length m (where m ≤ n)

**Goal:** Find all occurrences of P in T

**Example:**
```
Text:    "AABAACAADAABAABA"
Pattern: "AABA"
Result:  Matches at positions 0, 9, 12
```

### Applications

- Text editors (Find/Replace)
- DNA sequence analysis
- Plagiarism detection
- Web search engines
- Intrusion detection systems
- Data compression

## 1. Naive (Brute Force) Algorithm

### Strategy

Check pattern at every possible position in text.

### Pseudocode

```
NaiveStringMatch(T, P):
    n = length(T)
    m = length(P)
    
    for s = 0 to n - m:
        if P[0..m-1] == T[s..s+m-1]:
            print "Pattern found at position", s

// More detailed version with character comparison
NaiveStringMatch_Detailed(T, P):
    n = length(T)
    m = length(P)
    
    for s = 0 to n - m:
        j = 0
        while j < m and P[j] == T[s + j]:
            j = j + 1
        
        if j == m:
            print "Pattern found at position", s
```

### Complexity Analysis

**Best Case**: O(n)
- Pattern found at first position
- Example: T = "AAAA...", P = "AA"

**Worst Case**: O((n-m+1) × m) = O(nm)
- Many false matches
- Example: T = "AAAA...A", P = "AAAB"

**Space Complexity**: O(1)

### When to Use

- Short patterns
- Random text (few false matches expected)
- Simple implementation needed

## 2. Knuth-Morris-Pratt (KMP) Algorithm

### Key Insight

Don't re-examine characters in text that we've already matched. Use information from previous comparisons.

### Prefix Function (π)

The **prefix function** π[i] is the length of the longest proper prefix of P[0..i] that is also a suffix of P[0..i].

**Example:** For pattern "ABABACA"
```
i:     0  1  2  3  4  5  6
P[i]:  A  B  A  B  A  C  A
π[i]:  0  0  1  2  3  0  1
```

**Explanation:**
- π[0] = 0 (by definition)
- π[1] = 0 (no proper prefix)
- π[2] = 1 ("A" is prefix and suffix)
- π[3] = 2 ("AB" is prefix and suffix)
- π[4] = 3 ("ABA" is prefix and suffix)
- π[5] = 0 (no match)
- π[6] = 1 ("A" is prefix and suffix)

### Computing Prefix Function

```
ComputePrefixFunction(P):
    m = length(P)
    π = array of size m
    π[0] = 0
    k = 0  // Length of previous longest prefix suffix
    
    for q = 1 to m - 1:
        while k > 0 and P[k] != P[q]:
            k = π[k - 1]
        
        if P[k] == P[q]:
            k = k + 1
        
        π[q] = k
    
    return π
```

**Time Complexity**: O(m)  
**Space Complexity**: O(m)

### KMP Matching Algorithm

```
KMP_Matcher(T, P):
    n = length(T)
    m = length(P)
    π = ComputePrefixFunction(P)
    q = 0  // Number of characters matched
    
    for i = 0 to n - 1:
        while q > 0 and P[q] != T[i]:
            q = π[q - 1]
        
        if P[q] == T[i]:
            q = q + 1
        
        if q == m:
            print "Pattern found at position", i - m + 1
            q = π[q - 1]
```

### Complexity Analysis

**Time Complexity**: O(n + m)
- O(m) to compute prefix function
- O(n) for matching

**Space Complexity**: O(m) for prefix array

**Advantages:**
- Linear time guaranteed
- Never re-examines text characters
- No backtracking in text

### Example Walkthrough

```
Text:    "ABABDABACDABABCABAB"
Pattern: "ABABCABAB"

Prefix function for "ABABCABAB":
i:     0  1  2  3  4  5  6  7  8
P[i]:  A  B  A  B  C  A  B  A  B
π[i]:  0  0  1  2  0  1  2  3  4

Matching process:
Step 1: Compare at position 0
        ABABDABACDABABCABAB
        ABABCABAB
        Mismatch at position 4 (D vs C)
        Use π[3] = 2, shift pattern

Step 2: Continue from position 2
        Eventually finds match at position 10
```

## 3. Rabin-Karp Algorithm

### Key Insight

Use **hashing** to quickly eliminate positions where pattern cannot match.

### Hash Function

Treat strings as numbers in base d (alphabet size).

**Example:** For pattern "ABC" with d=256:
```
hash("ABC") = 'A'×256² + 'B'×256¹ + 'C'×256⁰
```

### Rolling Hash

Key optimization: compute hash of T[s+1..s+m] from hash of T[s..s+m-1] in O(1) time.

```
hash(T[s+1..s+m]) = d × (hash(T[s..s+m-1]) - T[s] × d^(m-1)) + T[s+m]
```

### Pseudocode

```
RabinKarp(T, P, d, q):
    // d = alphabet size, q = prime modulus
    n = length(T)
    m = length(P)
    h = d^(m-1) mod q
    p = 0  // Hash of pattern
    t = 0  // Hash of text window
    
    // Compute hash of pattern and first window
    for i = 0 to m - 1:
        p = (d × p + P[i]) mod q
        t = (d × t + T[i]) mod q
    
    // Slide pattern over text
    for s = 0 to n - m:
        if p == t:
            // Hash match - verify character by character
            if P[0..m-1] == T[s..s+m-1]:
                print "Pattern found at position", s
        
        // Compute hash for next window
        if s < n - m:
            t = (d × (t - T[s] × h) + T[s + m]) mod q
            if t < 0:
                t = t + q
```

### Complexity Analysis

**Average Case**: O(n + m)
- Few spurious hits with good hash function

**Worst Case**: O(nm)
- Many spurious hits (all hash values match)

**Space Complexity**: O(1)

**Advantages:**
- Simple to extend to 2D pattern matching
- Can search for multiple patterns simultaneously
- Good average-case performance

### Example

```
Text:    "3141592653589793"
Pattern: "26"

Using d=10, q=13:
1. Compute hash of "26": (2×10 + 6) mod 13 = 26 mod 13 = 0
2. Compute hash of first window "31": 31 mod 13 = 5
3. Roll through text:
   - "31": hash = 5 (no match)
   - "14": hash = 1 (no match)
   - "41": hash = 2 (no match)
   - "15": hash = 11 (no match)
   - "59": hash = 7 (no match)
   - "92": hash = 1 (no match)
   - "26": hash = 0 (MATCH! Verify: "26" == "26" ✓)
   Found at position 6
```

## 4. Boyer-Moore Algorithm (Overview)

### Key Ideas

1. **Bad Character Rule**: If mismatch occurs, skip alignments where bad character doesn't occur in pattern
2. **Good Suffix Rule**: If mismatch occurs after matching suffix, skip to next occurrence of that suffix

### Characteristics

**Time Complexity**: 
- Best case: O(n/m) (can skip m characters at a time!)
- Worst case: O(nm)
- Average: O(n)

**Space Complexity**: O(m + σ) where σ is alphabet size

**When to Use:**
- Large alphabets
- Long patterns
- Used in practice (grep, text editors)

## 5. Finite Automaton Matching (Overview)

### Idea

Preprocess pattern to build a finite automaton (state machine).

### Characteristics

**Preprocessing**: O(m³|Σ|) or O(m|Σ|) with optimization  
**Matching**: O(n) - exactly one state transition per character  
**Space**: O(m|Σ|)

**Advantages:**
- Fastest matching phase
- No backtracking

**Disadvantages:**
- High preprocessing cost
- Large space for big alphabets

## Code Examples

### Naive Algorithm (C++)

```cpp
#include <iostream>
#include <string>
#include <vector>

std::vector<int> naiveSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> positions;
    int n = text.length();
    int m = pattern.length();
    
    for (int s = 0; s <= n - m; s++) {
        int j = 0;
        while (j < m && pattern[j] == text[s + j]) {
            j++;
        }
        
        if (j == m) {
            positions.push_back(s);
        }
    }
    
    return positions;
}

int main() {
    std::string text = "AABAACAADAABAABA";
    std::string pattern = "AABA";
    
    auto positions = naiveSearch(text, pattern);
    
    std::cout << "Pattern found at positions: ";
    for (int pos : positions) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### KMP Algorithm (C++)

```cpp
#include <iostream>
#include <string>
#include <vector>

std::vector<int> computePrefixFunction(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> pi(m, 0);
    int k = 0;
    
    for (int q = 1; q < m; q++) {
        while (k > 0 && pattern[k] != pattern[q]) {
            k = pi[k - 1];
        }
        
        if (pattern[k] == pattern[q]) {
            k++;
        }
        
        pi[q] = k;
    }
    
    return pi;
}

std::vector<int> KMP(const std::string& text, const std::string& pattern) {
    std::vector<int> positions;
    int n = text.length();
    int m = pattern.length();
    
    std::vector<int> pi = computePrefixFunction(pattern);
    int q = 0;
    
    for (int i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i]) {
            q = pi[q - 1];
        }
        
        if (pattern[q] == text[i]) {
            q++;
        }
        
        if (q == m) {
            positions.push_back(i - m + 1);
            q = pi[q - 1];
        }
    }
    
    return positions;
}

int main() {
    std::string text = "AABAACAADAABAABA";
    std::string pattern = "AABA";
    
    auto positions = KMP(text, pattern);
    
    std::cout << "Pattern found at positions: ";
    for (int pos : positions) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;
    
    // Print prefix function
    std::cout << "Prefix function: ";
    auto pi = computePrefixFunction(pattern);
    for (int val : pi) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### Rabin-Karp Algorithm (C++)

```cpp
#include <iostream>
#include <string>
#include <vector>

const int d = 256;  // Number of characters in alphabet
const int q = 101;  // A prime number

std::vector<int> rabinKarp(const std::string& text, const std::string& pattern) {
    std::vector<int> positions;
    int n = text.length();
    int m = pattern.length();
    int h = 1;
    
    // Calculate h = d^(m-1) mod q
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }
    
    // Calculate hash of pattern and first window of text
    int p = 0;  // Hash of pattern
    int t = 0;  // Hash of text window
    
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }
    
    // Slide pattern over text
    for (int s = 0; s <= n - m; s++) {
        // Check if hash values match
        if (p == t) {
            // Verify character by character
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[s + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                positions.push_back(s);
            }
        }
        
        // Calculate hash for next window
        if (s < n - m) {
            t = (d * (t - text[s] * h) + text[s + m]) % q;
            
            // Make sure t is positive
            if (t < 0) {
                t = t + q;
            }
        }
    }
    
    return positions;
}

int main() {
    std::string text = "AABAACAADAABAABA";
    std::string pattern = "AABA";
    
    auto positions = rabinKarp(text, pattern);
    
    std::cout << "Pattern found at positions: ";
    for (int pos : positions) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

## Exercises

### Easy

1. **Count Occurrences**: Modify the naive algorithm to count the number of pattern occurrences.

2. **Case-Insensitive Search**: Implement case-insensitive pattern matching.

3. **Prefix Function**: Compute the prefix function for pattern "ABABCABAB" by hand.

### Medium

4. **Multiple Patterns**: Extend Rabin-Karp to search for multiple patterns simultaneously.

5. **2D Pattern Matching**: Use Rabin-Karp for 2D pattern matching in a matrix.

6. **Longest Repeated Substring**: Find the longest substring that appears at least twice in a string.

7. **String Rotation**: Check if one string is a rotation of another using KMP.

### Hard

8. **Wildcard Matching**: Implement pattern matching with wildcards ('?' matches any character, '*' matches any sequence).

9. **Approximate Matching**: Find all occurrences allowing at most k mismatches.

10. **Palindrome Patterns**: Find all palindromic substrings using modified KMP.

### Challenge

11. **Aho-Corasick**: Implement the Aho-Corasick algorithm for multiple pattern matching.

12. **Suffix Array**: Build a suffix array for efficient pattern matching queries.

13. **Z-Algorithm**: Implement the Z-algorithm for pattern matching in linear time.

## Algorithm Comparison

| Algorithm | Preprocessing | Matching | Space | Best For |
|-----------|---------------|----------|-------|----------|
| Naive | O(1) | O(nm) | O(1) | Short patterns, random text |
| KMP | O(m) | O(n) | O(m) | Guaranteed linear time |
| Rabin-Karp | O(m) | O(n)† | O(1) | Multiple patterns, 2D |
| Boyer-Moore | O(m+σ) | O(n/m)‡ | O(m+σ) | Large alphabets, long patterns |
| Finite Automaton | O(m³σ) | O(n) | O(mσ) | Many searches, small alphabet |

†Average case, ‡Best case

## When to Use Each Algorithm

**Naive:**
- Pattern length < 10
- Simple implementation needed
- Random text (few false matches)

**KMP:**
- Guaranteed linear time required
- Pattern has repetitive structure
- Small alphabet

**Rabin-Karp:**
- Multiple pattern search
- 2D pattern matching
- Plagiarism detection

**Boyer-Moore:**
- Large alphabet (English text)
- Long patterns
- Single pattern, many texts
- Used in practice (grep, search)

## References

### Books
- **Introduction to Algorithms (CLRS)** - Chapter 32
  - Complete coverage of string matching algorithms
  - Detailed proofs and analysis

- **Algorithms** by Sedgewick & Wayne - Chapter 5.3

### Online Resources
- [GeeksforGeeks - Pattern Searching](https://www.geeksforgeeks.org/algorithms-gfg/pattern-searching/)
- [VisuAlgo - String Matching](https://visualgo.net/en/suffixarray)
- [KMP Visualization](https://www.youtube.com/watch?v=V5-7GzOfADQ)
- [Rabin-Karp Explained](https://www.youtube.com/watch?v=qQ8vS2btsxI)

### Papers
- Knuth, Morris, Pratt - "Fast Pattern Matching in Strings" (1977)
- Boyer, Moore - "A Fast String Searching Algorithm" (1977)
- Karp, Rabin - "Efficient Randomized Pattern-Matching Algorithms" (1987)

## Summary

In this module, we covered:
- ✅ String matching problem and applications
- ✅ Naive algorithm and its limitations
- ✅ KMP algorithm with prefix function
- ✅ Rabin-Karp algorithm with rolling hash
- ✅ Algorithm selection based on use case

**Next Steps:** Proceed to [Module 6: Sorting Algorithms - Basics](06_sorting_basics.md) to learn fundamental sorting methods.

---

*💡 Tip: KMP for guaranteed linear time, Rabin-Karp for multiple patterns, Boyer-Moore for practical applications!*
