n, x = map(int, input().split())

ss, cs, ps = [0] * n, [0] * n, [0] * n
for i in range(n):
    ss[i], cs[i], ps[i] = map(int, input().split())
    ps[i] /= 100

dp = [[0 for _ in range(x + 1)] for _ in range(1 << n)]

for m in range((1 << n) - 1, -1, -1):
    for i in range(n):
        if m >> i & 1:
            continue
        for s in range(x - cs[i], -1, -1):
            dp[m][s] = max(dp[m][s], (dp[m | (1 << i)][s + cs[i]] + ss[i]) * ps[i] + dp[m][s + cs[i]] * (1 - ps[i]))

print(max(dp[0]))
