# 📝 3498. Reverse Degree of a String (LeetCode)

🔗 [Problem Link](https://leetcode.com/problems/reverse-degree-of-a-string)

![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen) ![Language](https://img.shields.io/badge/Language-C++-blue)

### 💡 Tags
String, Simulation

### 🚀 Performance
- **Runtime:** N/A
- **Memory:** N/A

---

### 📜 Problem Description

Given a string  `s` , calculate its  **reverse degree** .

The  **reverse degree**  is calculated as follows:

	
1. For each character, multiply its position in the  *reversed*  alphabet ( `'a'`  = 26,  `'b'`  = 25, ...,  `'z'`  = 1) with its position in the string  **(1-indexed)** .
	
2. Sum these products for all characters in the string.

Return the  **reverse degree**  of  `s` .

**Example 1:**

**Input:**  s = "abc"

**Output:**  148

**Explanation:**

LetterIndex in Reversed AlphabetIndex in StringProduct `'a'` 26126 `'b'` 25250 `'c'` 24372

The reversed degree is  `26 + 50 + 72 = 148` .

**Example 2:**

**Input:**  s = "zaza"

**Output:**  160

**Explanation:**

LetterIndex in Reversed AlphabetIndex in StringProduct `'z'` 111 `'a'` 26252 `'z'` 133 `'a'` 264104

The reverse degree is  `1 + 52 + 3 + 104 = 160` .

**Constraints:**

	
- `1 <= s.length <= 1000`
	
- `s`  contains only lowercase English letters.