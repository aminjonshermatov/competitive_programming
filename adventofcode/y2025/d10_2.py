import sys

from ortools.linear_solver import pywraplp


def solve_ilp(A, b):
    solver = pywraplp.Solver.CreateSolver('SCIP')
    if not solver:
        return 0

    n = len(A[0])
    x = []

    for i in range(n):
        x.append(solver.IntVar(0.0, solver.infinity(), f'x_{i}'))

    for i in range(len(A)):
        constraint = solver.RowConstraint(b[i], b[i], '')
        for j in range(n):
            constraint.SetCoefficient(x[j], A[i][j])

    objective = solver.Objective()
    for i in range(n):
        objective.SetCoefficient(x[i], 1)
    objective.SetMinimization()

    status = solver.Solve()

    if status == pywraplp.Solver.OPTIMAL:
        return int(solver.Objective().Value())
    else:
        print(A, b)
        assert False

sys.stdin = open('input.txt', 'r')

tot = 0
for l in map(lambda x: x.strip(), sys.stdin.readlines()):
    if len(l) == 0:
        continue
    blocks = l.split(' ')
    assert blocks[0][0] == '[' and blocks[0][-1] == ']'

    assert blocks[-1][0] == '{' and blocks[-1][-1] == '}'
    b = [int(x) for x in blocks[-1][1:-1].split(',')]

    xs = blocks[1:-1]
    A = [[0] * len(xs) for _ in range(len(b))]
    for j, ii in enumerate(xs):
        for i in map(int, ii[1:-1].split(',')):
            A[i][j] = 1
    tot += solve_ilp(A, b)

print(tot)