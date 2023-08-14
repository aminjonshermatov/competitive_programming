//
// Created by aminjon on 8/14/23.
//
#include <bits/stdc++.h>

using namespace std;

vector<int> prefix_function(string_view s) {
  const auto n = int(s.size());
  vector<int> pi(n, 0);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) {
      j = pi[j - 1];
    }
    if (s[i] == s[j]) {
      j++;
    }
    pi[i] = j;
  }
  return pi;
}